#include <stdio.h>

char image_file[50];

void lba28_read(char *buf, unsigned int offset, unsigned char count)
{
	FILE *fp = fopen(image_file, "r");
	int i = 0;
	fseek(fp, offset * 512, 0);
	for(; i < count * 512; i++)
	{
		buf[i] = fgetc(fp);
	}
}

void lba28_write(char *data, unsigned int offset, unsigned char count)
{
	FILE *fp = fopen(image_file, "a+");
	int i = 0;
	fseek(fp, offset * 512, 0);
	for(; i < count * 512; i++)
	{
		fputc(data[i], fp);
	}
}