#include <arch/x86/task.h>

#define TASK_AVAILABLE 0
#define TASK_RUNNING 1
#define TASK_PAUSED 2

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

void task_init(); //初始化多任务
int task_get_next_pid(); //获取下一个任务pid
void task_switch(); //切换任务
int task_create(unsigned int); //创建任务
void task_kill(int); //杀死任务
void task_wait(int); //等待任务结束
void task_set_name(int, char*); //设置任务名字
void task_get_name(char*, int); //获取任务名字
int task_get_parent_pid(int); //获取父进程pid
int task_get_current_pid();//获取当前任务的pid
int task_get_list(int*); //获取任务pid列表
