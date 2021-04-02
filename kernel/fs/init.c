#include <kernel/fs/block.h>
#include <kernel/fs/index.h>
#include <kernel/fs/inode.h>
/* 初始化文件系统 */
void init_fs()
{
	LoadSuperBlock();
	LoadIndexArea();
	LoadINode();
}
/* 创建文件系统 */
void CreateFileSystem()
{
	CleanupBlock(1); //清除超级块
	CreateIndexArea();
	LoadIndexArea();
	IndexAreaSetUsed(2);
	SaveIndexArea();
}