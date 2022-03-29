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

#define MAX_PID 0x400000

#define TASK_CODE_ADDR (32 * 0x100000)
#define TASK_STACK_ADDR (1024 * 0x100000)
#define TASK_STACK_SIZE (6 * 0x100000)

#define IDLE_PROC 0

/* 任务初始化信息,释放任务时需要 */
struct task_init_info
{
	void *code_addr;
	void *stack_addr;
	unsigned int code_size, stack_size;
};

struct task_info
{
	struct task_init_info init_info;
	void *stack;
	void *page_dir;
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
extern int current_proc;

void task_init(void);
void task_priority_init(void);
int task_get_next_proc(void);
void task_switch(void);
int task_alloc(void*, unsigned int);
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
