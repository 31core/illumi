#define INODE_TABLE_SIZE sizeof(struct inode)
#define INODE_NUM 4096 / INODE_TABLE_SIZE

struct inode
{
	char name[16]; //inode(文件)名
	int parent_block;
	int bitmap_block; //索引块编号
	int size;
	int type; //inode类型
};

int inode_get_availave(); //获取可用inode编号
void inode_load(); //加载inode
void inode_save(); //保存inode