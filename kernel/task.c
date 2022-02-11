#include <kernel/task.h>
#include <kernel/memory.h>
#include <lib/string.h>
#include <arch/x86/cpu.h>

void init_proc(void);

struct task_info task_list[1024];
int current_proc = 0; //当前运行的任务pid

int get_proc_by_pid(int pid)
{
	for(int i = 0; i < TASKS_MAX; i++)
	{
		if(task_list[i].pid == pid)
		{
			return i;
		}
	}
	return -1;
}
/* 生成未使用的PID */
static int generate_pid(void)
{
	static int max_pid = 0;
	if(max_pid > MAX_PID)
	{
		max_pid = 0;
	}
	for(int pid = max_pid + 1; pid < MAX_PID; pid++)
	{
		if(get_proc_by_pid(pid) == -1)
		{
			max_pid = pid;
			return pid;
		}
	}
	return -1;
}
/* 初始化多任务 */
void task_init(void)
{
	for(int i = 1; i < TASKS_MAX; i++)
	{
		task_list[i].pid = -1;
		task_list[i].uid = -1;
		task_list[i].flags = TASK_AVAILABLE;
	}
	/* 创建初始化任务 */
	task_list[0].flags = TASK_RUNNING;
	task_list[0].uid = 0;
	task_list[0].pid = 0;
	task_list[0].ppid = 0;
	task_list[0].nice = 0;
	str_cpy(task_list[0].name, "idle");
	scheduler_add(&task_list[0]);

	/* 创建init进程 */
	int init_pid = task_alloc(init_proc);
	task_run(init_pid);
	task_set_name(init_pid, "init");
}
/* 切换任务 */
void task_switch()
{
	int proc = task_get_next_proc();
	if(proc != -1 && proc != current_proc)
	{
		int old_proc = current_proc;
		current_proc = proc;
		io_sti(); //重新启用中断
		asm_task_switch(&task_list[old_proc].state, &task_list[proc].state);
	}
}
/* 创建任务 */
int task_alloc(void *addr)
{
	for(int i = 0; i < TASKS_MAX; i++)
	{
		if(task_list[i].flags == TASK_AVAILABLE)
		{
			void *stack_addr = memfrag_alloc(1024) + 1024; //分配该任务的栈地址
			task_init_register(&task_list[i].state);
			task_list[i].init_info.stack_addr = stack_addr;
			task_list[i].flags = TASK_PENDING;
			task_list[i].uid = task_list[current_proc].uid;
			task_list[i].pid = generate_pid();
			task_list[i].ppid = task_list[current_proc].pid;
			task_list[i].nice = TASK_DEFAULT_PRIORITY;
			task_list[i].name[0] = '\0';
			task_list[i].cpu_count = 0;
			int *p = (int*)stack_addr;
			*p = (int)addr; //[esp]为任务跳转地址
			task_set_stack(&task_list[i].state, stack_addr);

			task_list[i].cpu_time = 20 - task_list[i].nice;

			return task_list[i].pid; //返回pid
		}
	}
	return -1;
}
/* 运行任务 */
void task_run(int pid)
{
	int proc = get_proc_by_pid(pid);
	if(task_list[proc].flags == TASK_PENDING)
	{
		task_list[proc].flags = TASK_RUNNING;
		scheduler_add(&task_list[proc]);
	}
}

/* 设置任务名字 */
void task_set_name(int pid, char *str)
{
	int proc = get_proc_by_pid(pid);
	if(pid != 0 && proc != -1)
	{
		str_cpy(task_list[proc].name, str);
	}
}
/* 获取任务名字 */
void task_get_name(char *ret, int pid)
{
	int proc = get_proc_by_pid(pid);
	/* 任务没有运行 */
	if(proc != -1)
	{
		str_cpy(ret, task_list[proc].name);
		return;
	}
	ret[0] = '\0';
}
/* 获取当前任务的pid */
int task_get_pid(void)
{
	return task_list[current_proc].pid;
}
/* 获取进程uid */
int task_get_uid(int pid)
{
	int proc = get_proc_by_pid(pid);
	if(proc != -1)
	{
		return task_list[proc].uid;
	}
	return -1;
}
/* 获取父进程pid */
int task_get_ppid(int pid)
{
	int proc = get_proc_by_pid(pid);
	if(proc != -1)
	{
		return task_list[proc].ppid;
	}
	return -1;
}
/* 等待任务结束 */
void task_wait(int pid)
{
	int proc = get_proc_by_pid(pid);
	/* 不是当前任务的子进程 */
	if(task_list[proc].ppid != current_proc)
	{
		return;
	}
	while(task_list[proc].flags != TASK_AVAILABLE);
}
/* 杀死任务 */
void task_kill(int pid)
{
	int proc = get_proc_by_pid(pid);
	/* 不能杀死idle进程 && 任务不在运行 */
	if(pid != 0 && proc != -1)
	{
		task_list[proc].flags = TASK_AVAILABLE;
		task_list[proc].pid = -1;
		memfrag_free((void*)task_list[proc].init_info.stack_addr);
		scheduler_remove(&task_list[proc]);
		int i = 0;
		/* 为子进程重新分配父进程 */
		for(; i < TASKS_MAX; i++)
		{
			if(task_list[i].flags != TASK_AVAILABLE && task_list[i].ppid == pid)
			{
				task_list[i].ppid = 0;
			}
		}
	}
	/* 杀死当前任务 */
	if(proc == current_proc)
	{
		task_switch();
	}
}
/* 获取任务pid列表 */
int task_get_list(int *ret)
{
	int i, j = 0;
	for(i = 0; i < TASKS_MAX; i++)
	{
		if(task_list[i].flags != TASK_AVAILABLE)
		{
			ret[j] = task_list[i].pid;
			j += 1;
		}
	}
	return j; //返回pid个数
}
/* 休眠任务 */
void task_sleep(int pid)
{
	int proc = get_proc_by_pid(pid);
	if(task_list[proc].flags == TASK_RUNNING)
	{
		task_list[proc].flags = TASK_SLEEPING;
		scheduler_remove(&task_list[proc]);
	}
}
/* 唤醒任务 */
void task_wakeup(int pid)
{
	int proc = get_proc_by_pid(pid);
	if(task_list[proc].flags == TASK_SLEEPING)
	{
		task_list[proc].flags = TASK_RUNNING;
		scheduler_add(&task_list[proc]);
	}
}