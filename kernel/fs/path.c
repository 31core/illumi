#include <kernel/fs/inode.h>
#include <kernel/string.h>

extern struct inode inode_list[INODE_NUM];
extern int inode_count;

/* 获取路径基名称 */
void path_get_basename(char *ret, char *path)
{
	char tmp_path[50];
	str_cpy(tmp_path, path);
	if(tmp_path[str_len(path) - 1] == '/')
	{
		tmp_path[str_len(path) - 1] = '\0';
	}
	str_split(ret, path, "/", str_count(path, "/"));
}
/* 获取父目录名称 */
void path_get_dirname(char *ret, char *path)
{
	char tmp_path[50];
	str_cpy(tmp_path, path);
	if(tmp_path[str_len(path) - 1] == '/')
	{
		tmp_path[str_len(path) - 1] = '\0';
	}
	str_split(ret, path, "/", str_count(path, "/") - 1);
	if(ret[0] == '\0')
	{
		str_cpy(ret, "/");
	}
}
/* 检查路径是否存在 */
int path_exist(char *path)
{
	if(str_cmp(path, "/") == 1)
	{
		return 1;
	}
	char now_name[20];
	int times = 0;
	int i = 0;
	int now = 0;
	for(; times < str_count(path, "/"); times++)
	{
		str_split(now_name, path, "/", times + 1); //获取目录名
		for(i = 1; i < inode_count; i++)
		{
			if(str_cmp(inode_list[i].name, now_name) == 1 && inode_list[i].parent_inode == now)
			{
				/* 存在 */
				if(inode_list[i].type != TYPE_AVAILABLE)
				{
					if(times == str_count(path, "/") - 1)
					{
						return 1;
					}
					now = i;
				}
			}
		}
	}
	return 0;
}