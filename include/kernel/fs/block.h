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

void LoadSuperBlock(); //加载超级块的数据
void SaveSuperBlock(); //保存超级块的数据
int SuperBlockGetIndex(); //获取引导块的位置
void GetBlock(unsigned int, char*); //读取一个块的数据
void WriteBlock(unsigned int, char*); //写入一个块的数据
void CleanupBlock(unsigned int); //清除一个块的数据
int CreateBlock(); //创建一个块