#include <kernel/fs/block.h>
#include <kernel/fs/bitmap.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/dir.h>

extern int inode_count;

/* 初始化文件系统 */
void fs_init()
{
	inode_count = 0;
	super_block_load(); //加载超级块
	bitmap_load();
	inode_load(); //加载inode表到内存
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
	dir_create("/"); //创建根目录
}