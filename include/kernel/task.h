#include<arch/x86/task.h>

struct task_info
{
	char name[11];//任务名称
	struct task_status status;//任务状态
	int flags;
};

void init_task();//初始化多任务
int GetNextPid();//获取下一个任务pid
void SwitchTask();//切换任务
int CreateTask(unsigned int);//创建任务