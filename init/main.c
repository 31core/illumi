#include<arch/kernel/graphics.h>



void main()
{
	int vga_addr=0xb8000;//现存地址
	putchar(&vga_addr,'U');
	print(&vga_addr,"sss");
	while(1);
}