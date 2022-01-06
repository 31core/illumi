#include <kernel/pipe.h>
#include <kernel/memory.h>
#include <kernel/task.h>

int pipe_count = 0; //pipe数量
struct pipe *pipe_list[1024];

/* 初始化管道(pipe) */
void pipe_init(void)
{
	pipe_count = 0;
}
/* 分配一个pipe */
void pipe_create(struct pipe *pipe, int target_pid)
{
	fifo_init(&pipe->fifo, memfrag_alloc(1024), 1024);
	pipe->target_pid = target_pid;
	pipe_list[pipe_count] = pipe;
	pipe_count += 1;
}
/* 获取pipe */
int pipe_get(struct pipe **pipe)
{
	for(int i = 0; i < pipe_count; i++)
	{
		if(task_get_pid() == pipe_list[i]->target_pid)
		{
			*pipe = pipe_list[i];
			return 0;
		}
	}
	return -1;
}
/* 写入管道数据 */
int pipe_write(struct pipe *pipe, char *data, int size)
{
	for(int i = 0; i < size; i++)
	{
		fifo_write_data(&pipe->fifo, data[i]);
	}
	return size;
}
/* 读取管道数据 */
int pipe_read(struct pipe *pipe, char* data, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(fifo_get_info(pipe->fifo) == 0)
		{
			return i;
		}
		data[i] = fifo_read_data(&pipe->fifo);
	}
	return size;
}
/* 关闭管道 */
void pipe_close(struct pipe *pipe)
{
	for(int i = 0; i < pipe_count; i++)
	{
		if(pipe_list[i] == pipe)
		{
			for(; i < pipe_count - 1; i++)
			{
				pipe_list[i] = pipe_list[i + 1];
			}
			pipe_count -= 1;
			return;
		}
	}
}