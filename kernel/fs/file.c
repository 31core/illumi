#include <kernel/fs/bitmap.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/file.h>
#include <kernel/fs/dir.h>
#include <kernel/fs/block.h>
#include <kernel/fs/path.h>
#include <kernel/string.h>
#include <kernel/memory.h>

#define DATA_BLOCK_BEGIN 2

/* 创建文件 */
int file_create(struct file *file, char *name)
{
	char dirname[50];
	path_get_dirname(dirname, name);
	/* 文件已存在 */
	if(path_exist(name) == 1 && str_cmp(name, "/") == 0)
	{
		return -1;
	}
	/* 父级目录不存在 */
	else if(path_exist(dirname) == 0)
	{
		return -1;
	}
	int inode = inode_get_available();
	/* 未找到未使用的块 */
	if(inode == -1)
	{
		return -1;
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
	inode_list[inode].parent_inode = path_get_inode(dirname);
	inode_list[inode].type = TYPE_FILE;
	path_get_basename(inode_list[inode].name, name);
	inode_save(); //保存inode索引
	file->inode = inode;
	file->seek = 0;
	return 0;
}
/* 获取文件大小 */
int file_get_size(struct file file)
{
	return inode_list[file.inode].size;
}
/* 打开文件 */
int file_open(struct file *file, char *path)
{
	/* 文件不存在 */
	if(path_exist(path) == 0)
	{
		return -1;
	}
	int i = 0;
	char dirname[50], basename[50];
	path_get_basename(basename, path);
	path_get_dirname(dirname, path);
	int parent_inode = path_get_inode(dirname);
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
	int i = 1;
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
	int index_block = inode_list[file->inode].index_block; //当前引导块编号
	/* 循环写入使用数据 */
	for(i = 1; i < end + 1; i++)
	{
		int j = DATA_BLOCK_BEGIN;
		if(i == 1024)
		{
			/* 分配下一个引导块 */
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
			/* index_data[0]记录了下一个索引块编号, 为0则没有下一个 */
			index_data[0] = j;
			block_save(index_block, (char*)index_data); //保存当前索引块
			index_block = j;
			index_data[0] = 0;
			end -= 1024 - 1;
			i = 1;
		}
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
				block_save(index_block, (char*)index_data); //保存索引块
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
	int i = 1;
	int data_r = 0;
	int r;
	for(; i <= 1024; i++)
	{
		/* 加载下一个引导块 */
		if(i == 1024 && index_data[0] != 0)
		{
			block_load(index_data[0], (char*)index_data); //加载下一个引导块
			i = 1;
		}
		else if(i == 1024)
		{
			break;
		}
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
	int i = 1;
	int index_block = inode_list[file.inode].index_block;
	/* 释放此inode占用的数据块 */
	for(; i <= 1024; i++)
	{
		/* 加载下一个引导块 */
		if(i == 1024 && index_data[0] != 0)
		{
			block_load(index_data[0], (char*)index_data); //加载下一个引导块
			bitmap_set_unused(index_block);
			index_block = index_data[0];
			i = 1;
		}
		else if(i == 1024)
		{
			break;
		}
		if(index_data[i] != 0)
		{
			bitmap_set_unused(i); //标记块为未用
			index_data[i] = 0;
		}
	}
	bitmap_set_unused(index_block);
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