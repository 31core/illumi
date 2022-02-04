#include <kernel/fs/fs.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/path.h>
#include <lib/string.h>

/* 创建文件夹 */
int dir_create(char *path)
{
	/* 避免重复创建根目录 */
	if(!str_cmp(path, "/") && is_fs())
	{
		return FS_FAILED;
	}
	ST_FILE dir;
	if(file_create(&dir, path) == FS_FAILED)
	{
		return FS_FAILED;
	}
	inode_list[dir.inode].type = TYPE_DIRECTOR; //类型更改为文件夹
	inode_save();
	return FS_SUCCESS;
}
/* 列出子目录及文件inode */
int dir_list_inode(int *ret, char *path)
{
	int inode = path_get_inode(path);
	int count = 0;
	for(int i = 1; i < inode_count; i++)
	{
		if(inode_list[i].parent_inode == inode && inode_list[i].type != TYPE_AVAILABLE)
		{
			ret[count] = i;
			count += 1;
		}
	}
	return count;
}