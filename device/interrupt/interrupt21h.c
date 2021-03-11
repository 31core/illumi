#include <device/video/graphics.h>
#include <arch/x86/asmfunc.h>
#include <kernel/fifo.h>

struct fifo8 key_fifo;
char key_caps = 1; //1未按下, 2按下
char key_shift = 1; //1未按下, 2按下

/* 键盘中断程序 */
void interrupt21h()
{
	io_out8(0x20, 0x61); //通知PIC已经发生中断
	unsigned char data = io_in8(0x60); //读取键盘数据
	/* shift抬起 */
	if(data == 0xaa || data == 0xb6)
	{
		key_shift = 1;
	}
	/* shift按下 */
	else if(data == 0x2a || data == 0x36)
	{
		key_shift = 2;
	}
	/* caps按下 */
	else if(data == 0xba)
	{
		if(key_caps == 1)
		{
			key_caps = 2;
		}
		else if(key_caps == 2)
		{
			key_caps = 1;
		}
	}
	WriteData(&key_fifo, data); //将数据写入缓冲区
}