#include <utils.h>
#include <kernel/task.h>

extern int get_proc_by_pid(int);

int fork(void)
{
	int pid = task_alloc(task_list[current_proc].init_info.code_addr, task_list[current_proc].init_info.code_size);
	if(pid == task_get_pid())
	{
		return 0;
	}
	else
	{
		int proc = get_proc_by_pid(pid);
		char *origin_stack = task_list[current_proc].init_info.stack_addr;
		char *target_stack = task_list[proc].init_info.stack_addr;
		for(int i = 0; i < _4KB * task_list[current_proc].init_info.stack_size; i++)
		{
			target_stack[i] = origin_stack[i];
		}
		task_run(pid);
		return pid;
	}
}