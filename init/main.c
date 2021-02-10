#include<arch/x86/dsctbl.h>
#include<arch/x86/asmfunc.h>
#include<device/video/graphics.h>
#include<device/interrupt/init.h>

int main()
{
	init_dsctbl();//初始化dsctbl
	init_pic();//初始化PIC
	io_sti();//启用中断
	CleanupScreen();
	print("[root /] ");
	while(1);//操作系统主循环
}