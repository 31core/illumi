struct block_index
{
	unsigned int block;
	int size;
};
/* 超级块数据 */
struct super_block
{
	unsigned index_block; //引导块编号
	unsigned inode_table[1024 - 1]; //inode块编号
};

void super_block_load(); //加载超级块的数据
void super_block_save(); //保存超级块的数据
int super_block_get_index(); //获取引导块的位置
void block_load(unsigned int, char*); //读取一个块的数据
void block_save(unsigned int, char*); //写入一个块的数据
void block_cleanup(unsigned int); //清除一个块的数据
int block_create(); //创建一个块