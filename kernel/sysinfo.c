#include <kernel/sysinfo.h>

struct sysinfo sysinfo;

/* 初始化系统信息 */
void sysinfo_init()
{
	sysinfo.mem_size = 0;
	sysinfo.mem_free = 0;
}