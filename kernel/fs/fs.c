#include <kernel/fs/block.h>

/* 检测磁盘上有没有没有文件系统 */
int is_fs(void)
{
	if(sblock.fs_header[0] != 0x31 ||
		sblock.fs_header[1] != 0x22 ||
		sblock.fs_header[2] != 0x33 ||
		sblock.fs_header[3] != 0x31)
	{
		return 0;
	}
	return 1;
}