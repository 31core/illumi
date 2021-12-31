#include <arch/x86/x86_asm.h>

/* 串口发送一个字符数据 */
void serial_send_char(char c)
{
	io_out8(0x3f8, c);
}
/* 串口发送数据 */
void serial_send(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		serial_send_char(str[i]);
		i += 1;
	}
}
/* 串口接收一个字符数据 */
char serial_recv_char(void)
{
	while((io_in8(0x3f8 + 5) & 1) == 0);
	return io_in8(0x3f8);
}
/* 串口发送数据 */
void serial_recv(char *ret)
{
	int i = 0;
	while(1)
	{
		ret[i] = serial_recv_char();
		/* 回车 */
		if(ret[i] == '\r')
		{
			serial_send_char('\n');
			ret[i] = '\0';
			return;
		}
		else
		{
			serial_send_char(ret[i]);
			i += 1;
		}
	}
}