#include <device/disk/disk.h>
#include <kernel/time.h>

void init_IndexArea()
{
	char data[512];
	int i = 0;
	for(; i < 512; i++)
	{
		data[i] = 0;
	}
	for(i = 8; i < 16; i++)
	{
		LBA28WriteDisk((short*)data, i, 1);
		sleep(1);
	}
}
char index_area_data[8 * 4096];
void LoadIndexArea()
{
	LBA28ReadDisk((short*)index_area_data, 8, 8);
}
void SaveIndexArea()
{
	LBA28WriteDisk((short*)index_area_data, 8, 8);
}
int IndexAreaGetUsed(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	if((index_area_data[offset] & (0x100 >> p)) != 0)
	{
		return 1;
	}
	return 0;
}
/* 标记block已经使用 */
void IndexAreaSetUsed(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	index_area_data[offset] |= (0x100 >> p);
}
/* 标记block为可用 */
void IndexAreaSetUnused(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	index_area_data[offset] &= !(0x100 >> p);
}