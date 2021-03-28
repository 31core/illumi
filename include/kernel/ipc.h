struct pipe
{
	int target_pid;
	unsigned int data_addr; //数据的内存地址
	int size, w, r;
};

void init_pipe(); //初始化管道(pipe)
void CreatePipe(struct pipe*, int); //分配一个pipe
int WritePipe(struct pipe*, char*, int); //写入管道数据
int ReadPipe(struct pipe*, char*, int); //读取管道数据
void ClosePipe(struct pipe*); //关闭管道