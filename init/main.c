#include <arch/x86/cpu.h>
#include <kernel/init.h>
#include <kernel/task.h>
#include <kernel/fs/fs.h>

void shell(void);

int main(void)
{
	kernel_init(); //初始化内核
	fs_create();
	fs_init();

	int pid = task_alloc(shell);
	task_set_name(pid, "shell");
	task_run(pid);

	while(1)
	{
		cpu_halt();
	}
}
