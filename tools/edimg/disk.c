#include <stdio.h>

void lba28_read(char *buf, unsigned int offset, unsigned char count)
{
FILE *fp = fopen("image.img", "r");
int i = 0;
fseek(fp, offset * 512, 0);
for(; i < count * 512; i++)
{
buf[i] = fgetc(fp);
}

}

void lba28_write(char *data, unsigned int offset, unsigned char count)
{
FILE *fp = fopen("image.img", "w");
int i = 0;
fseek(fp, offset * 512, 0);
for(; i < count * 512; i++)
{
fputc(data[i], fp);
}
}