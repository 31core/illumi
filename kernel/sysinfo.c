#include <kernel/sysinfo.h>

struct sysinfo sysinfo;

void sysinfo_init(void)
{
	sysinfo.mem_size = 0;
	sysinfo.mem_free = 0;
}