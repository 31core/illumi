struct local_time
{
	int Y, m, d; //year, month, day
	int H, M, S; //hour, minute, second
};
/* 64-bit time stamp */
struct time_stamp
{
	int ts_low, ts_hight;
};

typedef struct time_stamp TIME_STAMP;
typedef struct local_time LOCAL_TIME;

void delay(unsigned int);
void time_local_time(struct local_time*);
void time_get_stamp(struct time_stamp*, struct local_time);