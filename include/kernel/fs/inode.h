#define INODE_TABLE_SIZE 1 * 8
#define INDOE_NUM 512 * INODE_TABLE_SIZE / sizeof(struct inode)

struct inode
{
	char name[16];
	int parent_block;
	int index_block;
	int type;
};

void init_inode();
int GetAvailableINode(); //获取可用inode编号
void LoadINode(); //加载inode
void SaveINode(); //保存inode