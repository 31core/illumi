#include <device/video/cli_print.h>

int vga_addr = VGA_ADDR; //显存地址
int screen_x_size = 80; //屏幕宽
int screen_y_size = 25; //屏幕高

/* 打印字符串 */
void cli_print(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		cli_print_char(str[i]);
		i += 1;
	}
}
/* 打印单字符 */
void cli_print_char(char c)
{
	/* 回车字符处理 */
	if(c == '\n')
	{
		int t = vga_addr - VGA_ADDR;
		t -= t % (2 * screen_x_size);
		t += 2 * screen_x_size;
		vga_addr = t + VGA_ADDR;
		video_move_cursor((vga_addr - VGA_ADDR) / 2);
	}
	/* 退格键 */
	if(c == 0x0e)
	{
		vga_addr -= 2;
		short *bak_cln = (short*)vga_addr;
		*bak_cln = 0x0700;
		video_move_cursor((vga_addr - VGA_ADDR) / 2);
		return;
	}
	/* 超出屏幕范围则下滚一行 */
	if((vga_addr - VGA_ADDR + 2) > 2 * screen_x_size * screen_y_size)
	{
		short *i;
		/* 处最后一行整体向前移一行 */
		for(i = (short*)VGA_ADDR; i < \
		(short*)(VGA_ADDR + 2 * screen_x_size * (screen_y_size - 1)); i++)
		{
			*i = *(i + screen_x_size);
		}
		/* 填充最后一行 */
		for(; i <= (short*)(VGA_ADDR + 2 * screen_x_size * screen_y_size); i++)
		{
			*i = 0x0700; //覆盖文本内容
		}
		vga_addr = VGA_ADDR + 2 * screen_x_size * (screen_y_size - 1); //显存指针在最后一行第一字符
	}
	/* 不为回车则打印当前字符 */
	if(c != '\n')
	{
		char *p;
		p = (char*)vga_addr;
		*p = c;
		p = (char*)vga_addr + 1;
		*p = 0x07; //字体颜色
		vga_addr += 2; //一个字符占2-byte
	}
	video_move_cursor((vga_addr - VGA_ADDR) / 2);
}
/* 清屏 */
void video_cleanup(void)
{
	int i;
	short *p = (short*)VGA_ADDR;
	for(i = screen_x_size * screen_y_size; i > 0; i--)
	{
		*p = 0x0700; //覆盖文本内容
		p += 1;
	}
	vga_addr = VGA_ADDR; //重置显存地址
}