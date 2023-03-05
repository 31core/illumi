#include <device/interrupt/interrupt.h>

/* allocate a timer */
int timer_alloc(void)
{
	timer_num += 1;
	timer_list[timer_num - 1] = time_count;
	return timer_num - 1; //返回计时器编号
}

/* get past seconds */
int timer_get_time(int num)
{
	return time_count - timer_list[num];
}

/* release timer */
void timer_free(int num)
{
	for(; num < timer_num - 1; num++)
	{
		timer_list[num] = timer_list[num + 1];
	}
	timer_num -= 1;
}
