#include <arch/x86/task.h>

struct task_info
{
	char name[11]; //任务名称
	struct task_status status; //任务状态
	int flags;
};

void init_task(); //初始化多任务
int GetNextPid(); //获取下一个任务pid
void SwitchTask(); //切换任务
int CreateTask(unsigned int); //创建任务
int CreateCurrentTask(); //为当前执行的代码创建任务
void KillTask(int); //杀死任务
void SetTaskName(int, char*); //设置任务名字
void GetTaskName(char*, int); //获取任务名字
int GetCurrentPid();//获取当前任务的pid
int ListTask(int*); //获取任务pid列表
