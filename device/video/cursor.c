#include <arch/x86/asmfunc.h>

/* 移动光标 */
void video_move_cursor(short p)
{
	io_out8(0x3d4, 0xe);
	io_out8(0x3d5, p >> 8);
	io_out8(0x3d4, 0xf);
	io_out8(0x3d5, p & 0xff);
}