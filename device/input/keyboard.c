#include<kernel/fifo.h>
#include<device/video/graphics.h>
#include<device/input/keyboard.h>

struct fifo8 key_fifo;
char key_caps;
char key_shift;
/* 输入字符串 */
void input(char *str)
{
	int i=0;
	while(1)
	{
		char data=inputchar();
		if(data==0)
		{
			continue;
		}
		/* 退格键的处理 */
		if(data==0x0e)
		{
			if(i==0)
			{
				continue;//str长度为0
			}
			printchar(0x0e);
			i-=1;//删除上一个字符
			continue;//仅打印不写入退格符
		}
		str[i]=data;
		printchar(data);
		if(data=='\n')
		{
			break;
		}
		i+=1;
	}
	str[i]='\0';
}
/* 单字符输入 */
char inputchar()
{
	while(1)
	{
		if(GetFifoInfo(key_fifo)!=0)
		{
			char data=ReadData(&key_fifo);
			/* 按键抬起 */
			if(data<0)
			{
				return 0;
			}
			if(key_shift==1)
			{
				char c=keyboard_set[(int)data];
				/* caps lock且输入是字母 */
				if(key_caps==2&&c>=0x61&&c<123)
				{
					return c-32;
				}
				return c;
			}
			else if(key_shift==2)
			{
				char c=keyboard_set_shift[(int)data];
				if(key_caps==2&&c>=65&&c<=90)
				{
					return c+32;
				}
				return c;
			}
		}
	}
}
/* 获取一个输入按键的键码 */
char inputcode()
{
	while(1)
	{
		if(GetFifoInfo(key_fifo)!=0)
		{
			char data=ReadData(&key_fifo);
			return data;
		}
	}
}