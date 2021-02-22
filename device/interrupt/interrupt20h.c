#include<arch/x86/asmfunc.h>

unsigned int time_count=0;
unsigned int timer_list[1000];
int timer_num;

void interrupt20h()
{
	io_out8(0x20,0x60);//通知PIC已经发生中断
	time_count+=1;
}