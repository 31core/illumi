#include<device/video/graphics.h>
/* 键盘中断程序 */
void interrupt21h(int *esp)
{
	print("You pressed the keyboard.");
}