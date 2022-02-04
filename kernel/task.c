#include <kernel/task.h>
#include <kernel/memory.h>
#include <lib/string.h>
#include <arch/x86/cpu.h>

void init_proc(void);

struct task_info task_list[1024];
int current_pid = 0; //当前运行的任务pid

/* 初始化多任务 */
void task_init(void)
{
	for(int i = 1; i < TASKS_MAX; i++)
	{
		task_list[i].pid = i;
		task_list[i].uid = -1;
		task_list[i].flags = TASK_AVAILABLE;
	}
	/* 创建初始化任务 */
	task_list[0].flags = TASK_RUNNING;
	task_list[0].uid = 0;
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
	int pid = task_get_next_pid();
	if(pid != -1 && pid != current_pid)
	{
		int old_pid = current_pid;
		current_pid = pid;
		asm_task_switch(&task_list[old_pid].state, &task_list[pid].state);
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
			task_list[i].uid = task_list[current_pid].uid;
			task_list[i].ppid = current_pid;
			task_list[i].nice = TASK_DEFAULT_PRIORITY;
			task_list[i].name[0] = '\0';
			int *p = (int*)stack_addr;
			*p = (int)addr; //[esp]为任务跳转地址
			task_set_stack(&task_list[i].state, stack_addr);

			task_list[i].cpu_time = 20 - task_list[i].nice;

			return i; //返回pid
		}
	}
	return -1;
}
/* 运行任务 */
void task_run(int pid)
{
	if(task_list[pid].flags == TASK_PENDING)
	{
		task_list[pid].flags = TASK_RUNNING;
		scheduler_add(&task_list[pid]);
	}
}

/* 设置任务名字 */
void task_set_name(int pid, char *str)
{
	if(pid != 0 && task_list[pid].flags != TASK_AVAILABLE)
	{
		str_cpy(task_list[pid].name, str);
	}
}
/* 获取任务名字 */
int task_get_name(char *ret, int pid)
{
	/* 任务没有运行 */
	if(task_list[pid].flags == TASK_AVAILABLE)
	{
		return -1;
	}
	str_cpy(ret, task_list[pid].name);
	return 0;
}
/* 获取当前任务的pid */
int task_get_pid(void)
{
	return current_pid;
}
/* 获取进程uid */
int task_get_uid(int pid)
{
	if(task_list[pid].flags != TASK_AVAILABLE)
	{
		return task_list[pid].uid;
	}
	return -1;
}
/* 获取父进程pid */
int task_get_ppid(int pid)
{
	if(task_list[pid].flags != TASK_AVAILABLE)
	{
		return task_list[pid].ppid;
	}
	return -1;
}
/* 等待任务结束 */
void task_wait(int pid)
{
	/* 不是当前任务的子进程 */
	if(task_list[pid].ppid != current_pid)
	{
		return;
	}
	while(task_list[pid].flags != TASK_AVAILABLE);
}
/* 杀死任务 */
void task_kill(int pid)
{
	/* 不能杀死init进程 && 任务不在运行 */
	if(pid != 0 && task_list[pid].flags != TASK_AVAILABLE)
	{
		task_list[pid].flags = TASK_AVAILABLE;
		memfrag_free((void*)task_list[pid].init_info.stack_addr);
		scheduler_remove(&task_list[pid]);
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
	if(pid == current_pid)
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
			ret[j] = i;
			j += 1;
		}
	}
	return j; //返回pid个数
}
/* 休眠任务 */
void task_sleep(int pid)
{
	if(task_list[pid].flags == TASK_RUNNING)
	{
		task_list[pid].flags = TASK_SLEEPING;
		scheduler_remove(&task_list[pid]);
	}
}
/* 唤醒任务 */
void task_wakeup(int pid)
{
	if(task_list[pid].flags == TASK_SLEEPING)
	{
		task_list[pid].flags = TASK_RUNNING;
		scheduler_add(&task_list[pid]);
	}
}