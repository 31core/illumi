#include <kernel/fs/block.h>
#include <kernel/fs/bitmap.h>

/* 创建引导块 */
void bitmap_create()
{
	block_cleanup(2);
	sblock.bitmap_block = 2; //设置super block中的引导块编号
	super_block_save();
}

char bitmap_data[4096];
/* 加载引导块 */
void bitmap_load()
{
	block_load(sblock.bitmap_block, bitmap_data);
}
/* 保存引导块 */
void bitmap_save()
{
	block_save(sblock.bitmap_block, bitmap_data);
}
/* 获取块是否使用 */
int bitmap_get_used(unsigned int block)
{
	int offset = block / 8; //计算用于存放信息的位置,char为8 bits
	char p = block % 8;
	if((bitmap_data[offset] & (0x100 >> (p + 1))) != 0)
	{
		return 1;
	}
	return 0;
}
/* 标记block已经使用 */
void bitmap_set_used(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	bitmap_data[offset] |= (0x100 >> (p + 1));
}
/* 标记block为可用 */
void bitmap_set_unused(unsigned int block)
{
	int offset = block / 8;
	char p = block % 8;
	bitmap_data[offset] &= !(0x100 >> (p + 1));
}