#include <arch/x86/cpu.h>
#include <kernel/init.h>
#include <kernel/fork.h>
#include <kernel/fs/fs.h>

void shell(void);

int main(void)
{
	kernel_init(); //初始化内核
	fs_create();
	fs_init();

	if(fork() == 0)
	{
		shell();
	}

	while(1)
	{
		cpu_halt();
	}
}
