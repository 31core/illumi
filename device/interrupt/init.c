#include<arch/x86/asmfunc.h>
#include<device/interrupt/init.h>

/* 初始化PIC */
void init_PIC()
{
	io_out8(0x21, 0xff); //禁止所有中断
	io_out8(0xa1, 0xff); //禁止所有中断
	/* 下面初始化PIC0 */
	io_out8(0x20, 0x11); //边沿触发模式
	io_out8(0x21, 0x20); //IRQ0 - 7由INT20 - 27接收
	io_out8(0x21, 1 << 2); //PIC1由IRQ2连接
	io_out8(0x21, 0x01); //无缓冲区模式
	/* 下面初始化PIC1 */
	io_out8(0xa0, 0x11); //边沿触发模式
	io_out8(0xa1, 0x28); //IRQ8 - 15由INT28 - 2f接收
	io_out8(0xa1, 2); //PIC1由IRQ2连接
	io_out8(0xa1, 0x01); //无缓冲区模式

	io_out8(0x21, 0xfc); //重新启用中断
	io_out8(0xa1, 0xff);

	init_PIT();
}

void init_PIT()
{
	io_out8(0x43, 0x34);
	io_out8(0x40, 0x9c); //每10ms产生一次中断
	io_out8(0x40, 0x2e);
}