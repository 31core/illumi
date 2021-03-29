#include <kernel/fs/inode.h>
#include <device/disk/disk.h>

struct inode inode_list[INDOE_NUM];

void init_inode()
{
	struct inode none;
	int i = 0;
	for(; i < INDOE_NUM; i++)
	{
		inode_list[i] = none;
	}
}
/* 获取可用inode编号 */
int GetAvailableINode()
{
	int i = 1;
	for(; i < INDOE_NUM; i++)
	{
		if(inode_list[i].type == 0)
		{
			return i;
		}
	}
	return -1;
}
/* 加载inode */
void LoadINode()
{
	LBA28ReadDisk((short*)inode_list, 16, INODE_TABLE_SIZE);
}
/* 保存inode */
void SaveINode()
{
	LBA28WriteDisk((short*)inode_list, 16, INODE_TABLE_SIZE);
}