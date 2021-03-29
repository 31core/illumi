#include <device/disk/disk.h>

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