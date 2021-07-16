#include <arch/x86/asmfunc.h>
#include <kernel/time.h>

/* 获取系统时间 */
void time_local_time(struct local_time* lt)
{
	io_out8(0x70, 0x0);
	char S = io_in8(0x71);
	io_out8(0x70, 0x2);
	char M = io_in8(0x71);
	io_out8(0x70, 0x4);
	char H = io_in8(0x71);
	io_out8(0x70, 0x7);
	char d = io_in8(0x71);
	io_out8(0x70, 0x8);
	char m = io_in8(0x71);
	io_out8(0x70, 0x9);
	char Y = io_in8(0x71);
	io_out8(0x70, 0x32);
	char Y10 = io_in8(0x71); //获取公元数
	lt->S = (S >> 4) * 10 + (S & 0xf);
	lt->M = (M >> 4) * 10 + (M & 0xf);
	lt->H = (H >> 4) * 10 + (H & 0xf);
	lt->d = (d >> 4) * 10 + (d & 0xf);
	lt->m = (m >> 4) * 10 + (m & 0xf);
	Y10 = (Y10 >> 4) * 10 + (Y10 & 0xf);
	lt->Y = Y10 * 100 + (Y >> 4) * 10 + (Y & 0xf);
}