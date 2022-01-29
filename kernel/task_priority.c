#include <kernel/task.h>

struct task_info *tasks[TASKS_MAX];
int tasks_count = 0;
int tasks_posit = 1;
extern struct task_info task_list[TASKS_MAX];
extern unsigned int time_count;

/* 获取下一个任务pid */
int task_get_next_pid()
{
	if(time_count % 100 == 0)
	{
		tasks_posit = 1;
		/* 重新计算cpu_time */
		for(int i = 1; i < tasks_count; i++)
		{
			tasks[i]->cpu_time = 20 - tasks[i]->nice;
		}
	}
	for(int i = tasks_posit; i < tasks_count; i++)
	{
		if(tasks[tasks_posit]->cpu_time > 0)
		{
			tasks[tasks_posit]->cpu_time -= 1;
			return tasks[tasks_posit]->pid;
		}
		tasks_posit += 1;
	}
	return 0;
}
/* nice从低到高添加任务 */
void task_priority_add(struct task_info *task)
{
	for(int i = 0; i < tasks_count; i++)
	{
		if(tasks[i]->nice <= task->nice && tasks[i + 1]->nice > task->nice)
		{
			for(int j = tasks_count; j > i + 1; j--)
			{
				tasks[j] = tasks[j - 1];
			}
			tasks_count += 1;
			tasks[i + 1] = task;
			return;
		}
	}
	/* 添加到列表最后 */
	tasks[tasks_count] = task;
	tasks_count += 1;
}
/* 移除task */
void task_remove(struct task_info *task)
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
void task_set_priority(int pid, int nice)
{
	task_remove(&task_list[pid]);
	task_list[pid].nice = nice;
	task_priority_add(&task_list[pid]);
}