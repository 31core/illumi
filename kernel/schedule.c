#include <kernel/task.h>

struct task_info *tasks[TASKS_MAX];
int tasks_count = 0;
int tasks_posit = 1;
extern struct task_info task_list[TASKS_MAX];
extern unsigned int time_count;
extern int get_proc_by_pid(int);

/* 计算CPU时间 */
static int get_cpu_time(int nice)
{
	int prio = (TASK_NICE_MAX + 1) - nice;
	int max_prio = 0;
	for(int i = 0; i < tasks_count; i++)
	{
		max_prio += (TASK_NICE_MAX + 1) - tasks[i]->nice;
	}
	float cpu_time = UNIT_TIME * ((float)prio / (float)max_prio);
	return (int)cpu_time;
}

/* 获取下一个任务pid */
int task_get_next_proc()
{
	for(int i = tasks_posit; i < tasks_count; i++)
	{
		/* tasks[tasks_posit]的CPU时间未计算 */
		if(tasks[tasks_posit]->cpu_time == -1)
		{
			tasks[tasks_posit]->cpu_time = get_cpu_time(tasks[tasks_posit]->nice);
			tasks[tasks_posit]->cpu_count += tasks[tasks_posit]->cpu_time;
			tasks[tasks_posit]->cpu_time -= 1;
			return tasks_posit;
		}
		/* CPU时间为0, 准备下一个任务 */
		else if(tasks[tasks_posit]->cpu_time == 0)
		{
			tasks[tasks_posit]->cpu_time = -1;
			tasks_posit += 1;
		}
		else
		{
			tasks[tasks_posit]->cpu_time -= 1;
			return tasks_posit;
		}
	}
	tasks_posit = 0;
	return 0;
}
/* 添加任务到调度器 */
void scheduler_add(struct task_info *task)
{
	tasks[tasks_count] = task;
	tasks_count += 1;
	task->cpu_time = -1;
}
/* 移除task */
void scheduler_remove(struct task_info *task)
{
	for(int i = 0; i < TASKS_MAX; i++)
	{
		if(tasks[i] == 0)
		{
			return;
		}
		if(tasks[i] == task)
		{
			for(int j = i; j < tasks_count - 1; j++)
			{
				tasks[j] = tasks[j + 1];
			}
			tasks_count -= 1;
		}
	}
}
/* 设置任务优先级 */
void task_set_nice(int pid, int nice)
{
	int proc = get_proc_by_pid(pid);
	scheduler_remove(&task_list[proc]);
	task_list[proc].nice = nice;
	scheduler_add(&task_list[proc]);
}