#include <arch/x86/asmfunc.h>

/* 串口发送数据 */
void serial_send(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		io_out8(0x3f8, str[i]);
		i += 1;
	}
}