struct fifo8
{
	unsigned int addr; //缓冲区地址
	int size; //缓冲区大小
	int free; //缓冲区可用空间
	int write, read; //数据读写位置
};

void init_fifo(struct fifo8*, unsigned int, int); //初始化缓冲区
int GetFifoInfo(struct fifo8); //获取缓冲区未读取的数据大小
void WriteData(struct fifo8*, char); //写入缓冲区数据
char ReadData(struct fifo8*); //读取缓冲区数据