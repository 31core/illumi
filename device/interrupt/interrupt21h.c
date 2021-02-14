#include<device/video/graphics.h>
#include<arch/x86/asmfunc.h>
#include<kernel/fifo.h>

struct fifo8 key_fifo;

/* 键盘中断程序 */
void interrupt21h(int *esp)
{
	io_out8(0x20,0x61);//通知PIC已经发生中断
	char data=io_in8(0x60);//读取键盘数据
	WriteData(&key_fifo,data);//将数据写入缓冲区
}