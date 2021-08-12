#include <arch/x86/task.h>

/* 初始化寄存器 */
void task_init_register(struct task_state *state)
{
	state->eax = 0;
	state->ebx = 0;
	state->ecx = 0;
	state->edx = 0;
	state->esi = 0;
	state->edi = 0;
	state->ebp = 0;
}
/* 设置任务栈地址 */
void task_set_stack(struct task_state *state, unsigned int addr)
{
	state->esp = addr;
}