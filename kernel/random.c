#include <kernel/time.h>
#include <kernel/types.h>
#include <kernel/string.h>

unsigned int seed = 0;

/* 调整随机数种子 */
static int adjust_seed(int origin_seed)
{
	if(origin_seed < 1000)
	{
		origin_seed += 1000;
	}
	/* 最后2位为0以后的随机数最后2位的0会重复 */
	if(origin_seed % 100 == 0)
	{
		origin_seed += 30;
	}
	return origin_seed;
}

/* 初始化随机数种子 */
void random_init()
{
	LOCAL_TIME tm;
	TIME_STAMP ts;
	time_local_time(&tm);
	time_get_stamp(&ts, tm);
	seed = ts.ts_low;
	if(seed > 9999)
	{
		char str[10];
		uint2str(str, seed);
		seed = str2int(&str[str_len(str) - 4]);
	}
	seed = adjust_seed(seed);
}
/* 生成随机数 */
unsigned int random()
{
	seed = seed * seed;
	char str[10];
	uint2str(str, seed);
	/* 不足8位高位补0 */
	if(str_len(str) == 7)
	{
		int i = str_len(str);
		for(; i >= 0; i--)
		{
			str[i + 1] = str[i];
		}
		str[0] = '0';
	}
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = str[i + 2];
		i += 1;
	}
	str[4] = '\0';
	seed = str2uint(str);
	seed = adjust_seed(seed);
	int randint = seed;

	/* 根据时间戳调整随机数种子以增强不确定性 */
	LOCAL_TIME tm;
	TIME_STAMP ts;
	time_local_time(&tm);
	time_get_stamp(&ts, tm);

	if(ts.ts_low % 2 == 0)
	{
		seed += 2;
	}
	if(ts.ts_low % 3 == 0)
	{
		seed += 3;
	}
	if(ts.ts_low % 5 == 0)
	{
		seed += 5;
	}
	return randint;
}