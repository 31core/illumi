#define TYPE_AVAILABLE 0
#define TYPE_FILE 1
#define TYPE_DIRECTOR 2

#define INODE_TABLE_SIZE sizeof(struct inode)
#define INODE_NUM (4096 / INODE_TABLE_SIZE)

/* inode数据 */
struct inode
{
	char name[16]; //inode(文件)名
	int parent_inode;
	int index_block; //索引块编号
	int size;
	int type; //inode类型
};

extern struct inode inode_list[INODE_NUM];
extern int inode_count;

int inode_get_available();
void inode_load();
void inode_save();