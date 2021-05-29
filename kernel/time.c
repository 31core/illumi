#include <kernel/time.h>
#include <kernel/timer.h>

/* 延时函数,单位:ms */
void delay(unsigned int time)
{
	int i = timer_alloc(); //分配一个计时器
	while(1)
	{
		/* 经过的时间到了需要等待的时间 */
		if(timer_get_time(i) >= time)
		{
			break;
		}
	}
	timer_free(i);
}
/* 等待,单位:s */
void sleep(unsigned int time)
{
	delay(100 * time);
}
#define Y_SEC (365 * 24 * 60 * 60)
#define D_SEC (24 * 60 * 60)
/* 获取时间戳 */
void time_get_stamp(struct time_stamp *ts, struct local_time lt)
{
	ts->ts_low += Y_SEC * (lt.Y - 1970);
	int i = 1972; //1970后第一个闰年
	for(; i < lt.Y; i += 4)
	{
		ts->ts_low += D_SEC;
	}
	/* 加上每个月的秒数 */
	for(i = 1; i < lt.m; i++)
	{
		if((i % 2 != 0 && i <= 7) || (i % 2 == 0 && i >=8))
		{
			ts->ts_low += 31 * D_SEC;
		}
		else
		{
			if(i == 2)
			{
				ts->ts_low += 28 * D_SEC;
				continue;
			}
			ts->ts_low += 30 * D_SEC;
		}
	}
	ts->ts_low += (lt.d - 1) * D_SEC;
	ts->ts_low += lt.H * 60 * 60;
	ts->ts_low += lt.M * 60;
	ts->ts_low += lt.S;
}
