/* 记录时间的结构体 */
struct local_time
{
	int Y, m, d; //年,月,日
	int H, M, S; //时,分,秒
};
/* 64位时间戳 */
struct time_stamp
{
	int ts_low, ts_hight;
};

void sleep(unsigned int);
void time_localtime(struct local_time*);
void time_get_stamp(struct time_stamp*, struct local_time);