#include <device/disk/disk.h>
#include <kernel/memory.h>

/* 读取一个块的数据 */
void GetBlock(unsigned int block, char *data)
{
	LBA28ReadDisk((short*)data, block * 8, 8);
}
/* 写入一个块的数据 */
void WriteBlock(unsigned int block, char *data)
{
	LBA28WriteDisk((short*)data, block * 8, 8);
}
void CleanupBlock(unsigned int block)
{
	char *data = (char*)AllocMemfrag(4096);
	int i = 0;
	for(; i < 4096; i++)
	{
		data[i] = 0;
	}
	WriteBlock(block, data);
	FreeMemfrag((unsigned int)data);
}