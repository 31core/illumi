#include <kernel/ipc.h>
#include <kernel/memory.h>
#include <kernel/task.h>

int pipe_count = 0; //pipe数量
struct pipe *pipe_list[1024];

/* 初始化管道(pipe) */
void init_pipe()
{
	pipe_count = 0;
}
/* 分配一个pipe */
void CreatePipe(struct pipe *pipe, int target_pid)
{
	pipe->size = 1024;
	pipe->w = 0;
	pipe->r = 0;
	pipe->target_pid = target_pid;
	pipe->data_addr = AllocMemfrag(1024);
	pipe_list[pipe_count] = pipe;
	pipe_count += 1;
}
/* 获取pipe */
int GetPipe()
{
	int i = 0;
	for(; i < pipe_count; i++)
	{
		if(GetCurrentPid() == pipe_list[i]->target_pid)
		{
			return (int)pipe_list[i];
		}
	}
	return -1;
}
/* 写入管道数据 */
int WritePipe(struct pipe *pipe, char *data, int size)
{
	char *p = (char*)pipe->data_addr;
	int i = 0;
	for(; i < size; i++)
	{
		if(pipe->w == (pipe->size - 1))
		{
			return i; //返回写入数据大小
		}
		p[pipe->w] = data[i];
		pipe->w += 1;
	}
	return size;
}
/* 读取管道数据 */
int ReadPipe(struct pipe *pipe, char* data, int size)
{
	char *p = (char*)pipe->data_addr;
	int i = 0;
	for(; i < size; i++)
	{
		if(pipe->r == pipe->w)
		{
			return i; //返回读取数据大小
		}
		data[i] = p[pipe->r];
		pipe->r += 1;
	}
	return size;
}
/* 关闭管道 */
void ClosePipe(struct pipe *pipe)
{
	int i = 0;
	for(; i < pipe_count; i++)
	{
		if(pipe_list[i] == pipe)
		{
			for(; i < pipe_count; i++)
			{
				pipe_list[i] = pipe_list[i + 1];
			}
			pipe_count -= 1;
			return;
		}
	}
}