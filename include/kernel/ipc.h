struct pipe
{
	int target_pid;
	unsigned int data_addr; //数据的内存地址
	int size, w, r;
};

void pipe_init(); //初始化管道(pipe)
void pipe_create(struct pipe*, int); //分配一个pipe
int pipe_get(struct pipe**); //获取pipe
int pipe_write(struct pipe*, char*, int); //写入管道数据
int pipe_read(struct pipe*, char*, int); //读取管道数据
void pipe_close(struct pipe*); //关闭管道