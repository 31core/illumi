#include <arch/x86/task.h>

/* 初始化寄存器 */
void task_init_register(struct task_status *status)
{
	status->eax = 0;
	status->ebx = 0;
	status->ecx = 0;
	status->edx = 0;
	status->esi = 0;
	status->edi = 0;
	status->ebp = 0;
}