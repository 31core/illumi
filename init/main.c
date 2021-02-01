#include<arch/kernel/graphics.h>

void main()
{
	CleanupScreen();
	print("[root /] ");
	while(1);//操作系统主循环
}