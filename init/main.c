#include<arch/x86/dsctbl.h>
#include<arch/x86/asmfunc.h>
#include<device/video/graphics.h>
#include<device/interrupt/init.h>
#include<device/interrupt/interrupt.h>
#include<kernel/fifo.h>

struct fifo8 key_fifo;
int main()
{
	init_fifo(&key_fifo,0,10);
	init_dsctbl();//初始化dsctbl
	init_pic();//初始化PIC
	io_sti();//启用中断
	CleanupScreen();
	print("[root /] ");
	//操作系统主循环
	while(1)
	{
		if(GetFifoInfo(key_fifo)!=0)
		{
			printchar(ReadData(&key_fifo));
		}
	}
}