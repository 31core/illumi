#include <kernel/task.h>
#include <kernel/memory.h>
#include <kernel/string.h>
#include <arch/x86/asmfunc.h>

struct task_info task_list[1024];
int now_task_pid = 0; //当前运行的任务pid

/* 初始化多任务 */
void task_init()
{
	now_task_pid = 0;
	int i = 0;
	for(; i < 1024; i++)
	{
		task_list[i].pid = i;
		task_list[i].flags = TASK_AVAILABLE;
	}
	/* 创建初始化任务 */
	task_list[0].flags = TASK_RUNNING;
	task_list[0].parent_pid = 0;
	str_cpy(task_list[0].name, "init");
	task_priority_init();
	task_priority_append(&task_list[0], 0);
}
/* 切换任务 */
void task_switch()
{
	int pid = task_get_next_pid();
	if(pid != -1)
	{
		int old_pid = now_task_pid;
		now_task_pid = pid;
		asm_task_switch(&task_list[old_pid].state, &task_list[pid].state);
	}
}
/* 创建任务 */
int task_alloc(unsigned int addr)
{
	int i = 0;
	for(; i < 1024; i++)
	{
		if(task_list[i].flags == TASK_AVAILABLE)
		{
			unsigned int esp_addr = memfrag_alloc(1024) + 1024; //分配该任务的栈地址
			task_init_register(&task_list[i].state);
			task_list[i].state.esp = esp_addr;
			task_list[i].init_info.stack_addr = esp_addr;
			task_list[i].flags = TASK_RUNNING;
			task_list[i].parent_pid = now_task_pid;
			task_list[i].name[0] = '\0';
			int *p = (int*)esp_addr;
			*p = addr; //[esp]为任务跳转地址
			task_priority_append(&task_list[i], 2);
			return i; //返回pid
		}
	}
	return -1;
}

/* 设置任务名字 */
void task_set_name(int pid, char *str)
{
	if(pid != 0)
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
int task_get_pid()
{
	return now_task_pid;
}
/* 获取父进程pid */
int task_get_ppid(int pid)
{
	if(pid == 0)
	{
		return 0; //init进程的父进程为0
	}
	if(task_list[pid].flags != TASK_AVAILABLE)
	{
		return task_list[pid].parent_pid;
	}
	return -1;
}
/* 等待任务结束 */
void task_wait(int pid)
{
	/* 不是当前任务的子进程 */
	if(task_list[pid].parent_pid != now_task_pid)
	{
		return;
	}
	while(task_list[pid].flags != TASK_AVAILABLE);
}
/* 杀死任务 */
void task_kill(int pid)
{
	/* 不能杀死init进程 */
	if(pid != 0)
	{
		task_list[pid].flags = TASK_AVAILABLE;
		memfrag_free(task_list[pid].init_info.stack_addr);
		task_remove(&task_list[pid]);
		int i = 0;
		/* 为子进程重新分配父进程 */
		for(; i < 1024; i++)
		{
			if(task_list[i].flags != TASK_AVAILABLE && task_list[i].parent_pid == pid)
			{
				task_list[i].parent_pid = 0;
			}
		}
	}
	/* 杀死当前任务 */
	if(pid == now_task_pid)
	{
		task_switch();
	}
}
/* 获取任务pid列表 */
int task_get_list(int *ret)
{
	int i, j = 0;
	for(i = 0; i < 1024; i++)
	{
		if(task_list[i].flags != TASK_AVAILABLE)
		{
			ret[j] = i;
			j += 1;
		}
	}
	return j; //返回pid个数
}