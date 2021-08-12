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
	struct task_state state; //任务状态
	char name[30]; //任务名称
	int pid, ppid;
	int flags;
	int last_tick; //上一次任务切换tick
};

struct task_priority
{
	struct task_info *task_list[1024];
	int pointer;
};

extern struct task_info task_list[1024];
extern int now_task_pid;

void task_init();
void task_priority_init();
void task_init_register(struct task_state*);
int task_get_next_pid();
void task_switch();
int task_alloc(unsigned int);
void task_kill(int);
void task_wait(int);
void task_set_name(int, char*);
int task_get_name(char*, int);
int task_get_pid();
int task_get_ppid(int);
int task_get_list(int*);
void task_set_priority(int, int);
void task_priority_append(struct task_info*, int);
void task_remove(struct task_info*);
