struct fifo8
{
	unsigned int addr; //缓冲区地址
	int size; //缓冲区大小
	int free; //缓冲区可用空间
	int write, read; //数据读写位置
};

void fifo_init(struct fifo8*, unsigned int, int); //初始化缓冲区
int fifo_get_info(struct fifo8); //获取缓冲区未读取的数据大小
void fifo_write_data(struct fifo8*, char); //写入缓冲区数据
char fifo_read_data(struct fifo8*); //读取缓冲区数据