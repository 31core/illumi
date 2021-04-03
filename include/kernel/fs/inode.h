#define INODE_TABLE_SIZE sizeof(struct inode)
#define INODE_NUM 4096 / INODE_TABLE_SIZE

struct inode
{
	char name[16]; //inode(文件)名
	int parent_block;
	int index_block; //索引块编号
	int type; //inode类型
};

int GetAvailableINode(); //获取可用inode编号
void LoadINode(); //加载inode
void SaveINode(); //保存inode