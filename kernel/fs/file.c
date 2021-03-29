#include <kernel/fs/inode.h>
#include <kernel/string.h>

extern struct inode inode_list[1024];

/* 创建文件 */
void CreateFile(char *name)
{
	int inode = GetAvailableINode();
	if(inode != -1)
	{
		inode_list[inode].type = 1;
		str_cpy(inode_list[inode].name, name);
	}
}