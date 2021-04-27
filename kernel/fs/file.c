#include <kernel/fs/bitmap.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/file.h>
#include <kernel/fs/dir.h>
#include <kernel/fs/block.h>
#include <kernel/fs/path.h>
#include <kernel/string.h>
#include <kernel/memory.h>

#define DATA_BLOCK_BEGIN 2

extern struct inode inode_list[INODE_NUM];
extern int inode_count;

/* 创建文件 */
void file_create(struct file *file, char *name)
{
	if(path_exist(name) == 0)
	{
		return;
	}
	int inode = inode_get_available();
	/* 未找到未使用的块 */
	if(inode == -1)
	{
		return;
	}
	int i = DATA_BLOCK_BEGIN;
	/* 为文件分配块索引 */
	for(; i < 1024; i++)
	{
		/* 找到未使用的块 */
		if(bitmap_get_used(i) == 0)
		{
			bitmap_set_used(i); //标记块为已用
			bitmap_save();
			inode_list[inode].index_block = i; //当前索引块编号保存到inode
			block_cleanup(i); //清除索引块数据
			break;
		}
	}
	inode_list[inode].parent_inode = dir_get_inode(name);
	inode_list[inode].type = TYPE_FILE;
	path_get_basename(inode_list[inode].name, name);
	inode_save(); //保存inode索引
	file->inode = inode;
	file->seek = 0;
}
/* 获取文件大小 */
int file_get_size(struct file file)
{
	return inode_list[file.inode].size;
}
/* 打开文件 */
int file_open(struct file *file, char *filename)
{
	if(str_len(filename) == 0)
	{
		return -1;
	}
	int i = 1;
	int parent_inode = dir_get_inode(filename);
	char basename[20];
	str_split(basename, filename, "/", str_count(filename, "/")); //获取文件名
	for(; i < inode_count; i++)
	{
		/* 此inode未被分配 */
		if(inode_list[i].type == TYPE_AVAILABLE)
		{
			continue;
		}
		else if(str_cmp(inode_list[i].name, basename) == 1)
		{
			if(inode_list[i].parent_inode != parent_inode)
			{
				continue;
			}
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
	int *index_data = (int*)memfrag_alloc(4096);
	block_load(inode_list[file->inode].index_block, (char*)index_data); //获取此inode中的索引块数据
	int i = 0;
	/* 释放此inode占用的数据块 */
	for(; i < 1024; i++)
	{
		if(index_data[i] != 0)
		{
			bitmap_set_unused(i); //标记块为未用
			index_data[i] = 0;
		}
	}
	bitmap_save();
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
	/* 循环写入使用数据 */
	for(i = 0; i < end; i++)
	{
		int j = DATA_BLOCK_BEGIN;
		/* 分配一个用于存数据的块 */
		for(; j < 1024; j++)
		{
			/* 找到未使用的块 */
			if(bitmap_get_used(j) == 0)
			{
				bitmap_set_used(j);
				bitmap_save();
				block_cleanup(j); //清除此数据块数据
				break;
			}
		}
		index_data[i] = j;
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
				inode_list[file->inode].size = size;
				block_save(index_data[i], data_block); //保存当前块数据
				block_save(inode_list[file->inode].index_block, (char*)index_data); //保存索引块
				inode_save(); //保存inode
				memfrag_free((unsigned int)data_block);
				memfrag_free((unsigned int)index_data);
				return;
			}
		}
		block_save(index_data[i], data_block); //保存当前块数据
	}
}
/* 读取文件 */
int file_read(struct file *file, char *data, int size)
{
	if(size == 0)
	{
		size = file_get_size(*file);
	}
	int *index_data = (int*)memfrag_alloc(4096);
	char *data_block = (char*)memfrag_alloc(4096);
	block_load(inode_list[file->inode].index_block, (char*)index_data); //加载块索引
	int i = 0;
	int data_r = 0;
	int r;
	for(; i < 1024; i++)
	{
		/* 数据块未使用 */
		if(index_data[i] == 0)
		{
			continue;
		}
		block_load(index_data[i], data_block); //加载数据块
		int j = 0;
		r = 0;
		/* 读取4 kb数据 */
		for(; j < 4096; j++)
		{
			data[data_r] = data_block[r];
			data_r += 1;
			r += 1;
			/* 已读取所有数据 */
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
/* 删除文件 */
void file_remove(char *filename)
{
	struct file file;
	/* 文件不存在 */
	if(file_open(&file, filename) == -1)
	{
		return;
	}
	int *index_data = (int*)memfrag_alloc(4096);
	block_load(inode_list[file.inode].index_block, (char*)index_data); //获取此inode中的索引块数据
	int i = 0;
	/* 释放此inode占用的数据块 */
	for(; i < 1024; i++)
	{
		if(index_data[i] != 0)
		{
			bitmap_set_unused(i); //标记块为未用
			index_data[i] = 0;
		}
	}
	bitmap_set_unused(inode_list[file.inode].index_block);
	bitmap_save();
	inode_list[file.inode].type = TYPE_AVAILABLE; //此unode标记为未用
	inode_save(); //保存inode
	memfrag_free((unsigned int)index_data);
}
/* 通过inode获取文件名 */
void file_get_name_by_inode(char *ret, int inode)
{
	str_cpy(ret, inode_list[inode].name);
}