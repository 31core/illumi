#include <arch/x86/x86_asm.h>
#include <kernel/fifo.h>
#include <device/input/keyboard.h>

/* 键盘中断程序 */
void interrupt21h(void)
{
	io_out8(0x20, 0x61); //通知PIC已经发生中断
	unsigned char data = io_in8(0x60); //读取键盘数据
	/* shift抬起 */
	if(data == 0xaa || data == 0xb6)
	{
		key_shift = KEY_UP;
	}
	/* shift按下 */
	else if(data == 0x2a || data == 0x36)
	{
		key_shift = KEY_DOWN;
	}
	/* caps按下 */
	else if(data == 0xba)
	{
		if(key_caps == KEY_UP)
		{
			key_caps = KEY_DOWN;
		}
		else if(key_caps == KEY_DOWN)
		{
			key_caps = KEY_UP;
		}
	}
	fifo_write_data(&key_fifo, data); //将数据写入缓冲区
}