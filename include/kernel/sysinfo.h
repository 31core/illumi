/* 系统信息 */
struct sysinfo
{
	unsigned int mem_size, mem_free;
};

extern struct sysinfo sysinfo;

void sysinfo_init();
