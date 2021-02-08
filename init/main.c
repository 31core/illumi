#include<arch/x86/dsctbl.h>
#include<device/video/graphics.h>
#include<device/interrupt/init.h>

void main()
{
	init_dsctbl();//初始化dsctbl
	init_pic();//初始化PIC
	CleanupScreen();
	print("[root /] ");
	while(1);//操作系统主循环
}