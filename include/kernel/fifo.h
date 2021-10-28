struct fifo8
{
	void* addr; //缓冲区地址
	int size; //缓冲区大小
	int free; //缓冲区可用空间
	int write, read; //数据读写位置
};

void fifo_init(struct fifo8*, void*, int);
int fifo_get_info(struct fifo8);
void fifo_write_data(struct fifo8*, char);
char fifo_read_data(struct fifo8*);