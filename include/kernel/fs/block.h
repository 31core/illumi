#define SUPER_BLOCK 1
#define DATA_BLOCK_BEGIN 2

/* 超级块数据 */
struct super_block
{
	unsigned char fs_header[4]; //文件系统标识
	unsigned int bitmap_block; //bitmap块编号
	unsigned int inode_table[1024 - 2]; //inode块编号
};

extern struct super_block sblock;

void super_block_load();
void super_block_save();
int super_block_get_index();
void block_load(unsigned int, void*);
void block_save(unsigned int, void*);
void block_cleanup(unsigned int);
int block_create();