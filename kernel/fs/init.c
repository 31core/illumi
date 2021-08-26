#include <kernel/fs/fs.h>
#include <kernel/fs/block.h>
#include <kernel/fs/bitmap.h>
#include <kernel/fs/inode.h>
#include <kernel/fs/dir.h>

extern struct super_block sblock;

/* 初始化文件系统 */
void fs_init()
{
	inode_count = 0;
	super_block_load(); //加载超级块
	/* 磁盘上没有文件系统 */
	if(is_fs() == 0)
	{
		return;
	}
	bitmap_load();
	inode_load(); //加载inode表到内存
}
/* 创建文件系统 */
void fs_create()
{
	block_cleanup(1); //清除超级块
	super_block_load();
	bitmap_create();
	bitmap_load();
	bitmap_set_used(2);
	bitmap_save();
	dir_create("/"); //创建根目录
	sblock.fs_header[0] = 0x31;
	sblock.fs_header[1] = 0x22;
	sblock.fs_header[2] = 0x33;
	sblock.fs_header[3] = 0x31;
	super_block_save();
	fs_init();
}