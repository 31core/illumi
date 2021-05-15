/* 记录时间的结构体 */
struct local_time
{
	int Y, m, d; //年,月,日
	int H, M, S; //时,分,秒
};

void sleep(unsigned int);
void time_localtime(struct local_time*);