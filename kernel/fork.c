#include <utils.h>
#include <kernel/task.h>
#include <kernel/page.h>
#include "task.h"

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
		if(task_get_pid() == 0)
		{
			current_proc = proc;
			page_switch(task_list[proc].page_dir);
			asm("addl $(1017 * 0x100000), %esp");
			return 0;
		}
		return pid;
	}
}
