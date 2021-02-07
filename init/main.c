#include<arch/x86/dsctbl.h>
#include<device/video/graphics.h>

void main()
{
	init_dsctbl();//初始化dsctbl
	CleanupScreen();
	print("[root /] ");
	while(1);//操作系统主循环
}