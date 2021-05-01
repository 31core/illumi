#include <kernel/fs/file.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/path.h>
#include <kernel/string.h>

extern struct inode inode_list[INODE_NUM];
extern int inode_count;
/* 创建文件夹 */
void dir_create(char *path)
{
	struct file dir;
	if(file_create(&dir, path) != -1)
	{
		inode_list[dir.inode].type = TYPE_DIRECTOR; //类型更改为文件夹
		inode_save();
	}
}
/* 列出子目录及文件inode */
int dir_list_inode(int *ret, char *path)
{
	int inode = path_get_inode(path);
	int count = 0;
	int i = 1;
	for(; i < inode_count; i++)
	{
		if(inode_list[i].parent_inode == inode && inode_list[i].type != TYPE_AVAILABLE)
		{
			ret[count] = i;
			count += 1;
		}
	}
	return count;
}