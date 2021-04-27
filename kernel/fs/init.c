#include <kernel/fs/block.h>
#include <kernel/fs/bitmap.h>
#include <kernel/fs/inode.h>

extern int inode_count;

/* 初始化文件系统 */
void fs_init()
{
	inode_count = 0;
	super_block_load();
	bitmap_load();
	inode_load();
}
/* 创建文件系统 */
void fs_create()
{
	block_cleanup(1); //清除超级块
	bitmap_create();
	bitmap_load();
	bitmap_set_used(2);
	bitmap_save();
	fs_init();
}