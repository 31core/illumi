#define INODE_TABLE_SIZE sizeof(struct inode)
#define INODE_NUM 4096 / INODE_TABLE_SIZE

struct inode
{
	char name[16];
	int parent_block;
	int index_block;
	int type;
};

int GetAvailableINode(); //获取可用inode编号
void LoadINode(); //加载inode
void SaveINode(); //保存inode