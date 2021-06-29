#include <kernel/time.h>
#include <kernel/types.h>
#include <kernel/string.h>

unsigned int seed = 0;

/* 初始化随机数种子 */
void random_init()
{
	struct local_time tm;
	struct time_stamp ts;
	time_localtime(&tm);
	time_get_stamp(&ts, tm);
	seed = ts.ts_low;
	if(seed > 9999)
	{
		char str[10];
		uint2str(str, seed);
		seed = str2int(&str[str_len(str) - 4]);
	}
	if(seed < 1000)
	{
		seed += 1000;
	}
	if(seed % 10 == 0)
	{
		seed += 3;
	}
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
	if(seed < 1000)
	{
		seed += 1000;
	}
	if(seed % 10 == 0)
	{
		seed += 3;
	}
	return seed;
}