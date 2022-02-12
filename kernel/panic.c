#include <arch/x86/cpu.h>
#include <kernel/strfmt.h>

void kernel_panic(void)
{
	io_cli();
	printfmt("kernel panic.\n");
	while(1)
	{
		cpu_halt();
	}
}