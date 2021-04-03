#include <device/disk/disk.h>
#include <kernel/memory.h>
#include <kernel/fs/index.h>
#include <kernel/fs/block.h>

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
/* 清除一个块的数据 */
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

struct super_block sblock;
/* 加载超级块的数据 */
void LoadSuperBlock()
{
	GetBlock(1, (char*)&sblock); //加载超级块
}
/* 保存超级块的数据 */
void SaveSuperBlock()
{
	WriteBlock(1, (char*)&sblock.index_block); //加载超级块
}
/* 获取引导块的位置 */
int SuperBlockGetIndex()
{
	return sblock.index_block;
}
/* 创建一个块 */
int CreateBlock()
{
	int i;
	for(i = 2; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(IndexAreaGetUsed(i) == 0)
		{
			IndexAreaSetUsed(i); //设置为已用
			SaveIndexArea();
			CleanupBlock(i); //清除此数据块数据
			return i;
		}
	}
	return -1;
}
