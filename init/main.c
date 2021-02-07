#include<arch/kernel/graphics.h>
#include<arch/x86/dsctbl.h>

void main()
{
	init_dsctbl();//初始化dsctbl
	CleanupScreen();
	print("[root /] ");
	while(1);//操作系统主循环
}