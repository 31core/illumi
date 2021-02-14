#include<kernel/fifo.h>
#include<device/video/graphics.h>
#include<device/input/keyboard.h>

struct fifo8 key_fifo;

void input(char *str)
{
	int i=0;
	while(1)
	{
		char data=inputchar();
		str[i]=data;
		printchar(data);
		if(data=='\n')
		{
			break;
		}

	}
	str[i]='\0';
}

char inputchar()
{
	while(1)
	{
		if(GetFifoInfo(key_fifo)!=0)
		{
			char data=ReadData(&key_fifo);
			return keyboard_set[(int)data];
		}
	}
}