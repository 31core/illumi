#include <utils.h>
#include <kernel/task.h>
#include <kernel/page.h>
#include "task.h"

unsigned int task_switch_init(void*, unsigned int);

int fork(void)
{
	int pid = task_alloc(task_list[current_proc].init_info.code_addr, task_list[current_proc].init_info.code_size);
	int proc = get_proc_by_pid(pid);
	char *origin_stack = task_list[current_proc].init_info.stack_addr;
	char *target_stack = task_list[proc].init_info.stack_addr;
	for(int i = 0; i < _4KB * task_list[current_proc].init_info.stack_size; i++)
	{
		target_stack[i] = origin_stack[i];
	}
	task_run(pid);
	int old = current_proc;
	current_proc = proc;
	task_switch_init(&task_list[old].stack, (unsigned int)task_list[proc].init_info.stack_addr);
	/* 子进程返回0 */
	if(task_get_pid() == pid)
	{
		return 0;
	}
	return pid;
}
