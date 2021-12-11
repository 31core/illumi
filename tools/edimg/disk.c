#include <stdio.h>

char image_file[50];

void lba28_read(char *buf, unsigned int offset, unsigned char count)
{
	FILE *fp = fopen(image_file, "r");
	fseek(fp, offset * 512, 0);
	for(int i = 0; i < count * 512; i++)
	{
		buf[i] = fgetc(fp);
	}
	fclose(fp);
}

void lba28_write(char *data, unsigned int offset, unsigned char count)
{
	FILE *fp = fopen(image_file, "a+");
	fseek(fp, offset * 512, 0);
	for(int i = 0; i < count * 512; i++)
	{
		fputc(data[i], fp);
	}
	fclose(fp);
}