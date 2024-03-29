#include <arch/x86/task.h>

#define TASKS_MAX 1024

#define UNIT_TIME 100

#define TASK_AVAILABLE 0
#define TASK_PENDING 1
#define TASK_RUNNING 2
#define TASK_SLEEPING 3

#define TASK_DEFAULT_PRIORITY 0
#define TASK_NICE_MAX 19
#define TASK_NICE_MIN -20

#define TASK_IDLE_PID 0
#define TASK_INIT_PID 1

#define TASK_CODE_ADDR (1 * 1024 * 1024 * 1024)
#define KERNEL_CODE_ADDR 0x100000
#define KERNEL_CODE_SIZE (1 * 1024 * 1024) //1MB

#define MAX_PID 0x400000

/* 任务初始化信息,释放任务时需要 */
struct task_init_info
{
	void *stack_addr;
	void *code_addr;
};

struct task_info
{
	struct task_init_info init_info;
	struct task_state state; //任务状态
	unsigned int *page;
	char name[30]; //任务名称
	int pid, ppid, uid;
	int nice;
	int flags;
	int cpu_time; //1s中需要运行的时间
	unsigned int cpu_count;
};

struct task_priority
{
	struct task_info *task_list[1024];
	int pointer;
};

extern struct task_info task_list[TASKS_MAX];
extern int current_pid;

void task_init(void);
void task_priority_init(void);
void task_init_register(struct task_state*);
int task_get_next_proc(void);
void task_switch(void);
int task_alloc(void*);
void task_run(int);
void task_kill(int);
void task_wait(int);
void task_sleep(int);
void task_wakeup(int);
void task_set_name(int, char*);
void task_get_name(char*, int);
int task_get_pid(void);
int task_get_uid(int);
int task_get_ppid(int);
int task_get_list(int*);
void task_set_nice(int, int);
void scheduler_add(struct task_info*);
void scheduler_remove(struct task_info*);
