#include <kernel/fs/block.h>
#include <kernel/fs/bitmap.h>

extern struct super_block sblock;

/* 创建引导块 */
void index_area_create()
{
	block_cleanup(2);
	index_area_load();
	sblock.bitmap_block = 2; //设置super block中的引导块编号
}

char index_area_data[4096];
/* 加载引导块 */
void index_area_load()
{
	block_load(2, index_area_data);
}
/* 保存引导块 */
void index_area_save()
{
	block_save(2, index_area_data);
}
/* 获取块是否使用 */
int index_area_get_used(unsigned int block)
{
	int offset = block / 8; //计算用于存放信息的位置,char为8 bits
	char p = block % 8;
	if((index_area_data[offset] & (0x100 >> p)) != 0)
	{
		return 1;
	}
	return 0;
}
/* 标记block已经使用 */
void index_area_set_used(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	index_area_data[offset] |= (0x100 >> p);
}
/* 标记block为可用 */
void index_area_set_unused(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	index_area_data[offset] &= !(0x100 >> p);
}