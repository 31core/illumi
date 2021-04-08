#include <kernel/fs/index.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/file.h>
#include <kernel/fs/block.h>
#include <kernel/string.h>
#include <kernel/memory.h>

#define DATA_BLOCK_BEGIN 2

extern struct inode inode_list[INODE_NUM];
extern int inode_count;

/* 创建文件 */
void file_create(struct file *file, char *name)
{
	int inode = inode_get_availave();
	/* 找到了未使用的块 */
	if(inode != -1)
	{
		inode_list[inode].type = 1;
		str_cpy(inode_list[inode].name, name);
	}
	else
	{
		return;
	}
	int i = DATA_BLOCK_BEGIN;
	/* 为文件分配块索引 */
	for(; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(index_area_get_used(i) == 0)
		{
			index_area_set_used(i); //标记块为已用
			index_area_save();
			inode_list[inode].index_block = i; //当前索引块编号保存到inode
			block_cleanup(i); //清除索引块数据
			break;
		}
	}
	inode_save(); //保存inode索引
	file->inode = inode;
	file->seek = 0;
}
/* 获取文件大小 */
int GetFileSize(struct file file)
{
	struct block_index *index_data = (struct block_index*)memfrag_alloc(4096);
	block_load(inode_list[file.inode].index_block, (char*)index_data); //加载索引块
	int i = 0;
	int size = 0;
	for(; i < 4096 / sizeof(struct block_index); i++)
	{
		if(index_data[i].block != 0)
		{
			size += index_data[i].size;
		}
	}
	memfrag_free((unsigned int)index_data);
	return size;
}
/* 打开文件 */
int file_open(struct file *file, char *filename)
{
	if(str_len(filename) == 0)
	{
		return -1;
	}
	int i = 1;
	for(; i < inode_count; i++)
	{
		/* 此inode未被分配 */
		if(inode_list[i].type == 0)
		{
			continue;
		}
		else if(str_cmp(inode_list[i].name, filename) == 1)
		{
			file->inode = i;
			file->seek = 0;
			return 0;
		}
	}
	return -1;
}
/* 写入文件 */
void file_write(struct file *file, char *data, int size)
{
	struct block_index *index_data = (struct block_index*)memfrag_alloc(4096);
	block_load(inode_list[file->inode].index_block, (char*)index_data); //获取此inode中的索引块数据
	int i = 0;
	/* 释放此inode占用的数据块 */
	for(; i < 1024; i++)
	{
		if(index_data[i].block != 0)
		{
			index_area_set_unused(i); //标记块为未用
			index_data[i].block = 0;
		}
	}
	index_area_save();
	block_cleanup(inode_list[file->inode].index_block); //清除引导块
	/* end = 写入数据块数 */
	int end = size / 4096;
	if(size % 4096 != 0)
	{
		end += 1;
	}
	char *data_block = (char*)memfrag_alloc(4096);
	int data_w = 0; //用于访问data位置
	int w = 0;
	for(i = 0; i < end; i++)
	{
		int j = DATA_BLOCK_BEGIN;
		/* 分配一个用于存数据的块 */
		for(; j < 1024; j++)
		{
			/* 找到未使用的块 */
			if(index_area_get_used(j) == 0)
			{
				index_area_set_used(j);
				index_area_save();
				block_cleanup(j); //清除此数据块数据
				break;
			}
		}
		index_data[i].block = j;
		w = 0;
		/* 将4 kb数据写入当前块 */
		for(j = 0; j < 4096; j++)
		{
			data_block[w] = data[data_w];
			w += 1;
			data_w += 1;
			/* 已写入所有数据 */
			if(data_w == size)
			{
				index_data[i].size = w;
				block_save(index_data[i].block, data_block);
				memfrag_free((unsigned int)data_block);
				block_save(inode_list[file->inode].index_block, (char*)index_data); //保存索引块
				memfrag_free((unsigned int)index_data);
				return;
			}
		}
		index_data[i].size = 4096;
		block_save(index_data[i].block, data_block); //保存当前块数据
	}
}
/* 读取文件 */
int file_read(struct file *file, char *data, int size)
{
	if(size == 0)
	{
		size = GetFileSize(*file);
	}
	struct block_index *index_data = (struct block_index*)memfrag_alloc(4096);
	char *data_block = (char*)memfrag_alloc(4096);
	block_load(inode_list[file->inode].index_block, (char*)index_data);
	int i = 0;
	int data_r = 0;
	int r;
	for(; i < 4096 / sizeof(struct block_index); i++)
	{
		if(index_data[i].block == 0)
		{
			continue;
		}
		block_load(index_data[i].block, data_block);
		int j = 0;
		r = 0;
		for(; j < index_data[i].size; j++)
		{
			data[data_r] = data_block[r];
			data_r += 1;
			r += 1;
			if(data_r == size)
			{
				memfrag_free((unsigned int)data_block);
				memfrag_free((unsigned int)index_data);
				return size;
			}
		} 
	}
	return 0;
}