#include <device/disk/disk.h>
#include <kernel/memory.h>
#include <kernel/fs/bitmap.h>
#include <kernel/fs/block.h>

/* 读取一个块的数据 */
void block_load(unsigned int block, void *data)
{
	lba28_read((short*)data, block * 8, 8);
}
/* 写入一个块的数据 */
void block_save(unsigned int block, void *data)
{
	lba28_write((short*)data, block * 8, 8);
}
/* 清除一个块的数据 */
void block_cleanup(unsigned int block)
{
	char *data = memfrag_alloc_4k(1);
	for(int i = 0; i < 4096; i++)
	{
		data[i] = 0;
	}
	block_save(block, data);
	memfrag_free(data);
}

struct super_block sblock;
/* 加载超级块的数据 */
void super_block_load(void)
{
	block_load(SUPER_BLOCK, &sblock); //加载超级块
}
/* 保存超级块的数据 */
void super_block_save(void)
{
	block_save(SUPER_BLOCK, &sblock); //保存超级块
}
/* 获取引导块的位置 */
int super_block_get_index(void)
{
	return sblock.bitmap_block;
}
/* 创建一个块 */
int block_create(void)
{
	for(int i = 2; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(!bitmap_get_used(i))
		{
			bitmap_set_used(i); //设置为已用
			bitmap_save();
			block_cleanup(i); //清除此数据块数据
			return i;
		}
	}
	return -1;
}
