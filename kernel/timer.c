extern unsigned int time_count;
extern unsigned int timer_list[1000];
extern int timer_num; //计时器的数量
/* 分配一个计时器 */
int timer_alloc()
{
	timer_num += 1;
	timer_list[timer_num - 1] = time_count;
	return timer_num - 1; //返回计时器编号
}
/* 获取计时器时间 */
int timer_get_time(int num)
{
	return time_count - timer_list[num];
}
/* 释放计时器 */
void timer_free(int num)
{
	for(; num < timer_num - 1; num++)
	{
		timer_list[num] = timer_list[num + 1];
	}
	timer_num -= 1;
}
