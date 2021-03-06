#include<kernel/task.h>
#include<kernel/memory.h>
#include<arch/x86/asmfunc.h>

struct task_info task_list[1024];
int now_task_pid=0;//当前运行的任务pid
/* 初始化多任务 */
void init_task()
{
	now_task_pid=0;
	int i=0;
	for(;i<1024;i++)
	{
		task_list[i].flags=0;
	}
}
/* 获取下一个任务pid */
int GetNextPid()
{
	int i=now_task_pid+1;
	for(;i<1024;i++)
	{
		if(task_list[i].flags==1)
		{
			now_task_pid=i;
			return i;
		}
	}
	for(i=0;i<now_task_pid;i++)
	{
		if(task_list[i].flags==1)
		{
			now_task_pid=i;
			return i;
		}
	}
	return -1;//没有正在运行的任务
}
/* 切换任务 */
void SwitchTask()
{
	int pid=GetNextPid();
	if(pid!=-1)
	{
		RecordTaskStatus(&task_list[now_task_pid].status);
		RestoreTaskStatus(&task_list[pid].status);
	}
}
/* 创建任务 */
int CreateTask()
{
	int i=0;
	for(;i<1024;i++)
	{
		if(task_list[i].flags==0)
		{
			unsigned int addr=AllocMemfrag(1024);
			task_list[i].flags=1;
			RecordTaskStatus(&task_list[i].status);
			task_list[i].status.esp=addr;
			return i;
		}
	}
	return -1;
}