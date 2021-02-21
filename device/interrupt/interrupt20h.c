#include<arch/x86/asmfunc.h>

void interrupt20h()
{
    io_out8(0x20,0x60);//通知PIC已经发生中断
}