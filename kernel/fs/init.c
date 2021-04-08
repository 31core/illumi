#include <kernel/fs/block.h>
#include <kernel/fs/index.h>
#include <kernel/fs/inode.h>

extern int inode_count;

/* 初始化文件系统 */
void fs_init()
{
	inode_count = 0;
	super_block_load();
	index_area_load();
	inode_load();
}
/* 创建文件系统 */
void fs_create()
{
	block_cleanup(1); //清除超级块
	index_area_create();
	index_area_load();
	index_area_set_used(2);
	index_area_save();
	fs_init();
}