#include <kernel/fs/block.h>
#include <kernel/fs/index.h>

/* 创建引导块 */
void CreateIndexArea()
{
	CleanupBlock(2);
	LoadIndexArea();
}

char index_area_data[8 * 4096];
/* 加载引导块 */
void LoadIndexArea()
{
	GetBlock(2, index_area_data);
}
/* 保存引导块 */
void SaveIndexArea()
{
	WriteBlock(2, index_area_data);
}
/* 获取块是否使用 */
int IndexAreaGetUsed(unsigned int block)
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