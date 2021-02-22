#include<kernel/timer.h>

/* 延时函数 */
void sleep(unsigned int time)
{
	int i=AllocTimer();
	while(1)
	{
	if(GetTimerTime(i)>=time)
	{
			break;
		}
	}
	FreeTimer(i);
}