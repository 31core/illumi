#include <kernel/fs/index.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/file.h>
#include <kernel/fs/block.h>
#include <kernel/string.h>
#include <kernel/memory.h>

extern struct inode inode_list[1024];

/* 创建文件 */
void CreateFile(struct file *file, char *name)
{
	int inode = GetAvailableINode();
	if(inode != -1)
	{
		inode_list[inode].type = 1;
		str_cpy(inode_list[inode].name, name);
	}
	int i = 3;
	/* 为文件分配块索引 */
	for(; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(IndexAreaGetUsed(i) == 0)
		{
			IndexAreaSetUsed(i);
			SaveIndexArea();
			inode_list[inode].index_block = i;
			CleanupBlock(i);
			break;
		}
	}
	WriteBlock(2, (char*)inode_list); //保存inode索引
	file->index = inode;
	file->seek = 0;
}
/* 获取文件大小 */
int GetFileSize(struct file file)
{
	struct block_index *index_data = (struct block_index*)AllocMemfrag(4096);
	GetBlock(inode_list[file.index].index_block, (char*)index_data); //加载索引块
	int i = 0;
	int size = 0;
	for(; i < 4096 / sizeof(struct block_index); i++)
	{
		if(index_data[i].block != 0)
		{
			size += index_data[i].size;
		}
	}
	return size;
}

void WriteFile(struct file *file, char *data, int size)
{
	struct block_index *index_data = (struct block_index*)AllocMemfrag(4096);
	GetBlock(inode_list[file->index].index_block, (char*)index_data); //加载索引块
	int i = 0;
	int data_w = 0;
start_write:
	/* 文件没有多余的空间 */
	if(GetFileSize(*file) >= size)
	{
		i = 4096 / sizeof(struct block_index) - 1;
		for(; i >= 0; i--)
		{
			if(index_data[i].block == 0)
			{
				int j = 3;
				/* 分配一个用于存数据的块 */
				for(; j < 1024; j++)
				{
					/* 找到未使用的块 */
					if(IndexAreaGetUsed(j) == 0)
					{
						IndexAreaSetUsed(j);
						SaveIndexArea();
						CleanupBlock(j);
						break;
					}
				}
				index_data[i].block = j;
				index_data[i].size = 0;
				break;
			}
		}
	}
	else
	{
		for(i = 0; i < 4096 / sizeof(struct block_index); i++)
		{
			/* 获取有剩余空间的数据块 */
			if(index_data[i].block != 0 && index_data[i].size < 4096)
			{
				break;
			}
		}
	}
	char *data_block = (char*)AllocMemfrag(4096);
	GetBlock(index_data[i].block, data_block);
	int w = index_data[i].size;
	while(index_data[i].size <= 4096)
	{
		data_block[w] = data[data_w];
		w += 1;
		data_w += 1;
		if(data_w == size)
		{
			WriteBlock(index_data[i].block, data_block);
			break;
		}
	}
	if(data_w < size - 1)
	{
		WriteBlock(index_data[i].block, data_block);
		FreeMemfrag((unsigned int)data_block);
		goto start_write;
	}
	FreeMemfrag((unsigned int)data_block);
	WriteBlock(inode_list[file->index].index_block, (char*)index_data); //保存索引块
}