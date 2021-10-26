#include <arch/x86/x86_asm.h>
#include <kernel/task.h>

unsigned int time_count = 0;/* 记录经过的时间,10ms */
unsigned int timer_list[1000];
int timer_num = 0;

void interrupt20h()
{
	io_out8(0x20, 0x60); //通知PIC已经发生中断
	time_count += 1;
	io_sti(); //重新启用中断
	task_switch();
	io_cli(); //iretd之前要禁用中断
}
