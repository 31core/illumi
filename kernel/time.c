#include<kernel/timer.h>

/* 延时函数 */
void sleep(unsigned int time)
{
	int i = AllocTimer(); //分配一个计时器
	while(1)
	{
		/* 经过的时间到了需要等待的时间 */
		if(GetTimerTime(i) >= time)
		{
			break;
		}
	}
	FreeTimer(i);
}
