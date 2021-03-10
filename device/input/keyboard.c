#include<kernel/fifo.h>
#include<device/video/graphics.h>
#include<device/input/keyboard.h>

extern struct fifo8 key_fifo;
extern char key_caps;
extern char key_shift;

char keyboard_set[] = {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', 
'9', '0', '-', '=', 0x0e, ' ', 'q', 'w', 'e', 'r', 
't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', ' ', 
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 
'\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 
'm', ',', '.', '/', 0, ' ', ' ', ' ', 0, ' '};
char keyboard_set_shift[] = {' ', ' ', '!', '@', '#', '$', '%', '^', '&', '*', 
'(', ')', '_', '+', 0x0e, ' ', 'Q', 'W', 'E', 'R', 
'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', ' ', 
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
'"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 
'M', '<', '>', '?', 0, ' ', ' ', ' ', 0, ' '};

/* 输入字符串 */
void input(char *str)
{
	int i = 0;
	while(1)
	{
		char data = inputchar();
		if(data == 0)
		{
			continue;
		}
		/* 退格键的处理 */
		if(data == 0x0e)
		{
			if(i == 0)
			{
				continue; //str长度为0
			}
			printchar(0x0e);
			i -= 1; //删除上一个字符
			continue; //仅打印不写入退格符
		}
		str[i] = data;
		printchar(data);
		if(data == '\n')
		{
			break;
		}
		i += 1;
	}
	str[i] = '\0';
}
/* 单字符输入 */
char inputchar()
{
	while(1)
	{
		if(GetFifoInfo(key_fifo) != 0)
		{
			char data = ReadData(&key_fifo);
			/* 按键抬起 */
			if(data < 0)
			{
				return 0;
			}
			if(key_shift == 1)
			{
				char c = keyboard_set[(int)data];
				/* caps lock且输入是字母 */
				if(key_caps == 2 && c >= 0x61 && c <= 0x7a)
				{
					return c - 32;
				}
				return c;
			}
			else if(key_shift == 2)
			{
				char c = keyboard_set_shift[(int)data];
				/* caps lock且输入是字母 */
				if(key_caps == 2 && c >= 0x41 && c <= 0x5a)
				{
					return c + 32;
				}
				return c;
			}
		}
	}
}
/* 获取一个输入按键的键码 */
unsigned char inputcode()
{
	while(1)
	{
		if(GetFifoInfo(key_fifo) != 0)
		{
			unsigned char data = ReadData(&key_fifo);
			return data;
		}
	}
}
