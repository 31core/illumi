#include<arch/x86/asmfunc.h>

/* LBA读取磁盘 */
void LBA28ReadDisk(char *buf,int offset,char count)
{
	io_out8(0x1f2,count);
	io_out8(0x1f3,offset&0xff);
	io_out8(0x1f4,offset&0xff00>>8);
	io_out8(0x1f5,offset&0xff0000>>2*8);
	io_out8(0x1f6,(offset>>3*8&0x0f)|0xe0);
	io_out8(0x1f7,0x20);//读取磁盘
	int i=0;
	for(;i<count*512/2;i++)
	{
		/* 等待磁盘驱动器 */
		while(1)
		{
			if((io_in8(0x1f7)&0x88)==0x08)
			{
				break;
			}
		}
		buf[2*i]=io_in16(0x1f0);
	}
}
/* LBA写入磁盘 */
void LBA28WriteDisk(char *data,int offset,char count)
{
	io_out8(0x1f2,count);
	io_out8(0x1f3,offset&0xff);
	io_out8(0x1f4,offset&0xff00>>8);
	io_out8(0x1f5,offset&0xff0000>>2*8);
	io_out8(0x1f6,(offset>>3*8&0x0f)|0xe0);
	io_out8(0x1f7,0x30);//写入磁盘
	int i=0;
	/* 等待磁盘驱动器 */
	for(;i<count*512/2;i++)
	{
		while(1)
		{
			if((io_in8(0x1f7)&0x88)==0x08)
			{
				break;
			}
		}
		io_out16(0x1f0,data[2*i]);
	}
}