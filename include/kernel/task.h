#include <arch/x86/task.h>

/* 任务初始化信息,释放任务时需要 */
struct task_init_info
{
	unsigned int stack_addr;
};

struct task_info
{
	struct task_init_info init_info;
	char name[11]; //任务名称
	struct task_status status; //任务状态
	int parent_pid; //父进程pid
	int flags;
};

void init_task(); //初始化多任务
int GetNextPid(); //获取下一个任务pid
void SwitchTask(); //切换任务
int CreateTask(unsigned int); //创建任务
void KillTask(int); //杀死任务
void WaitTask(int); //等待任务结束
void SetTaskName(int, char*); //设置任务名字
void GetTaskName(char*, int); //获取任务名字
int GetParentPid(int); //获取父进程pid
int GetCurrentPid();//获取当前任务的pid
int GetTaskList(int*); //获取任务pid列表
