#include<kernel/timer.h>

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