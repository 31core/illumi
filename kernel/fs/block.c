#include <device/disk/disk.h>
#include <kernel/memory.h>
#include <kernel/fs/bitmap.h>
#include <kernel/fs/block.h>

/* 读取一个块的数据 */
void block_load(unsigned int block, char *data)
{
	LBA28ReadDisk((short*)data, block * 8, 8);
}
/* 写入一个块的数据 */
void block_save(unsigned int block, char *data)
{
	LBA28WriteDisk((short*)data, block * 8, 8);
}
/* 清除一个块的数据 */
void block_cleanup(unsigned int block)
{
	char *data = (char*)memfrag_alloc(4096);
	int i = 0;
	for(; i < 4096; i++)
	{
		data[i] = 0;
	}
	block_save(block, data);
	memfrag_free((unsigned int)data);
}

struct super_block sblock;
/* 加载超级块的数据 */
void super_block_load()
{
	block_load(1, (char*)&sblock); //加载超级块
}
/* 保存超级块的数据 */
void super_block_save()
{
	block_save(1, (char*)&sblock.bitmap_block); //加载超级块
}
/* 获取引导块的位置 */
int super_block_get_index()
{
	return sblock.bitmap_block;
}
/* 创建一个块 */
int block_create()
{
	int i;
	for(i = 2; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(index_area_get_used(i) == 0)
		{
			index_area_set_used(i); //设置为已用
			index_area_save();
			block_cleanup(i); //清除此数据块数据
			return i;
		}
	}
	return -1;
}
