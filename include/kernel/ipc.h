struct pipe
{
	int target_pid;
	unsigned int data_addr; //数据的内存地址
	int size, w, r;
};

void pipe_init();
void pipe_create(struct pipe*, int);
int pipe_get(struct pipe**);
int pipe_write(struct pipe*, char*, int);
int pipe_read(struct pipe*, char*, int);
void pipe_close(struct pipe*);