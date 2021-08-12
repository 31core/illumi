#include <kernel/task.h>

struct task_priority priority_0;
struct task_priority priority_1;
struct task_priority priority_2;
struct task_priority priority_3;

extern unsigned int time_count;

/* 通过优先级获取task_priority指针 */
static struct task_priority* get_task_priority_pointer(int level)
{
	struct task_priority *priority;
	if(level == 0)
	{
		priority = (struct task_priority*)&priority_0;
	}
	else if(level == 1)
	{
		priority = (struct task_priority*)&priority_1;
	}
	else if(level == 2)
	{
		priority = (struct task_priority*)&priority_2;
	}
	else if(level == 3)
	{
		priority = (struct task_priority*)&priority_3;
	}
	return priority;
}

/* 任务优先级初始化 */
void task_priority_init()
{
	priority_0.task_list[0] = 0;
	priority_1.task_list[0] = 0;
	priority_2.task_list[0] = 0;
	priority_3.task_list[0] = 0;

	priority_0.pointer = 0;
	priority_1.pointer = 0;
	priority_2.pointer = 0;
	priority_3.pointer = 0;
}

/* 获取下一个任务pid */
int task_get_next_pid()
{
	int level = 0;
	for(; level <= 3; level++)
	{
		struct task_priority *priority = get_task_priority_pointer(level);
		int i = priority->pointer;
		while(priority->task_list[i] != 0)
		{
			int timeout = 5 + 5 * level;
			/* 找到了超时需要切换的任务 */
			if(priority->task_list[i]->last_tick + timeout <= time_count)
			{
				priority->pointer = i;
				priority->task_list[i]->last_tick = time_count; //更新上一次任务切换tick
				return priority->task_list[i]->pid;
			}
			i += 1;
		}
	}
	/* 将priority_x的pointer重置为0 */
	for(level = 0; level <= 3; level++)
	{
		struct task_priority *priority = get_task_priority_pointer(level);
		priority->pointer = 0;
	}
	return -1; //没有正在运行的任务
}
/* 向priority_x添加任务 */
void task_priority_append(struct task_info *task, int level)
{
	struct task_priority *priority = get_task_priority_pointer(level);
	int i = 0;
	while(priority->task_list[i] != 0)
	{
		i += 1;
	}
	priority->task_list[i] = task;
	priority->task_list[i + 1] = 0;
}
/* 移除task */
void task_remove(struct task_info *task)
{
	int i = 0, level = 0;
	for(; level < 4; level++)
	{
		struct task_priority *priority = get_task_priority_pointer(level);
		/* 遍历task_list */
		i = 0;
		while(priority->task_list[i] != 0)
		{
			if(priority->task_list[i] == task)
			{
				while(priority->task_list[i] != 0)
				{
					priority->task_list[i] = priority->task_list[i + 1];
					i += 1;
				}
				return;
			}
			i += 1;
		}
	}
}
/* 设置任务优先级 */
void task_set_priority(int pid, int level)
{
	task_remove(&task_list[pid]);
	task_priority_append(&task_list[pid], level);
}