/* 系统信息 */
struct sysinfo
{
	void *mem_size, *mem_free;
};

extern struct sysinfo sysinfo;

void sysinfo_init(void);
