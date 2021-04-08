#include <kernel/fs/inode.h>
#include <kernel/fs/block.h>
#include <device/disk/disk.h>

struct inode inode_list[INODE_NUM];
int inode_count = 0; //node的数量

extern struct super_block sblock;

/* 获取可用inode编号 */
int inode_get_availave()
{
	int i = 1;
	/* 循环查找未使用的inode */
	for(i = 1; i < inode_count; i++)
	{
		/* inode未使用 */
		if(inode_list[i].type == 0)
		{
			return i; //返回此inode编号
		}
	}
	/* 所有的inode已经使用 */
	int new = block_create(); //分配一个新的块作为inode表
	if(new != -1)
	{
		for(i = 0; i < 1024 - 1; i++)
		{
			/* 将这个块写入超级块 */
			if(sblock.inode_table[i] == 0)
			{
				sblock.inode_table[i] = new;
				super_block_save(); //写入数据
				break;
			}
		}
		inode_load(); //重新加载inode
		for(i = 1; i < inode_count; i++)
		{
			if(inode_list[i].type == 0)
			{
				return i;
			}
		}
	}
	return -1;
}
/* 从超级块加载inode */
void inode_load()
{
	int i = 0;
	int j = 0;
	for(; i < 1024 - 1; i++)
	{
		/* 指向了一个存在的块 */
		if(sblock.inode_table[i] != 0)
		{
			block_load(sblock.inode_table[i], (char*)&inode_list[INODE_NUM * j]); //加载该块的数据
			j += 1;
		}
	}
	inode_count = j * INODE_NUM; //更新inode数量
}
/* 保存inode */
void inode_save()
{
	int i = 0;
	for(; i < inode_count; i++)
	{
		block_save(sblock.inode_table[i], (char*)&inode_list[INODE_TABLE_SIZE * i]);
	}
}
