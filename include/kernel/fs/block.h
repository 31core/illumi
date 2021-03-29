struct block_index
{
	unsigned int block;
	int size;
};

void GetBlock(unsigned int, char*); //读取一个块的数据
void WriteBlock(unsigned int, char*); //写入一个块的数据
void CleanupBlock(unsigned int);