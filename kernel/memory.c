#include <kernel/memory.h>
#include <kernel/sysinfo.h>

struct mem_fragment mem_frag_list[4096];
int mem_frag_num = 0; //内存碎片总数

/* 刷新内存剩余空间 */
static void refresh_free_size(void)
{
	sysinfo.mem_free = sysinfo.mem_size;
	for(int i = 1; i <= mem_frag_num; i++)
	{
		sysinfo.mem_free -= mem_frag_list[i].size;
	}
}

/* 获取内存大小 */
void* mem_get_size(void)
{
	/* 已经检测过内存则返回该值 */
	if(sysinfo.mem_size != 0)
	{
		return sysinfo.mem_size;
	}
	int *p, old;
	for(p = (int*)0x100000; p < (int*)0xffffffff; p += 4096)
	{
		old = *p; //保存初始内存内容
		*p = 0xff00ff00;
		if(*p != 0xff00ff00)
		{
			break;
		}
		*p = old;
	}
	return (void*)p;
}

/* 初始化内存碎片管理 */
void memfrag_init(void)
{
	sysinfo.mem_size = mem_get_size();
	sysinfo.mem_free = sysinfo.mem_size;
	mem_frag_list[0].addr = (void*)0x100000;
	mem_frag_list[0].size = 0;
	mem_frag_list[1].addr = sysinfo.mem_size;  //结尾的地址为内存大小
	mem_frag_list[1].size = 0;
}
/* 分配内存碎片 */
void* memfrag_alloc(unsigned int size)
{
	int i = 1;
	for(; i <= mem_frag_num + 1; i++)
	{
		/* 找到了足够大的内存碎片 */
		if(mem_frag_list[i].addr - mem_frag_list[i - 1].size -\
		mem_frag_list[i - 1].addr >= size)
		{
			break;
		}
	}
	void *addr = mem_frag_list[i - 1].addr + mem_frag_list[i - 1].size;
	int j = mem_frag_num + 1;
	for(; j >= i; j--)
	{
		mem_frag_list[j + 1] = mem_frag_list[j];
	}
	mem_frag_list[i].addr = addr;
	mem_frag_list[i].size = size;
	mem_frag_num += 1;
	refresh_free_size();
	return addr;
}
/* 以4kb为单位分配内存 */
void* memfrag_alloc_4k(unsigned int size)
{
	size *= 4096;
	int i = 1;
	void* addr;
	for(; i <= mem_frag_num + 1; i++)
	{
		addr = (void*)(((unsigned int)mem_frag_list[i - 1].addr + mem_frag_list[i - 1].size + 0xfff) & 0xfffff000);
		/* 找到了足够大的内存碎片 */
		if(mem_frag_list[i].addr - addr >= size)
		{
			break;
		}
	}

	int j = mem_frag_num + 1;
	for(; j >= i; j--)
	{
		mem_frag_list[j + 1] = mem_frag_list[j];
	}
	mem_frag_list[i].addr = addr;
	mem_frag_list[i].size = size;
	mem_frag_num += 1;
	refresh_free_size();
	return addr;
}
/* 分配内存时指定地址 */
void memfrag_alloc_with_addr(void *addr, unsigned int size)
{
	int i = 1;
	/* 查找插入内存片段位置 */
	for(; i <= mem_frag_num + 1; i++)
	{
		if(mem_frag_list[i].addr > addr)
		{
			break;
		}
	}
	/* 需要分配的内存已被使用 */
	if(mem_frag_list[i - 1].addr + mem_frag_list[i - 1].size > addr || \
	addr + size > mem_frag_list[i].addr)
	{
		return;
	}
	int j = mem_frag_num + 1; //j为最后一个成员位置
	/* 向后移动成员 */
	for(; j >= i; j--)
	{
		mem_frag_list[j + 1] = mem_frag_list[j];
	}
	mem_frag_list[i].addr = addr;
	mem_frag_list[i].size = size;
	mem_frag_num += 1;
	refresh_free_size();
}
/* 释放内存碎片 */
void memfrag_free(void* addr)
{
	int i = 1;
	for(; i <= mem_frag_num; i++)
	{
		if(mem_frag_list[i].addr == addr)
		{
			/* 向前移动成员 */
			for(; i <= mem_frag_num; i++)
			{
				mem_frag_list[i] = mem_frag_list[i + 1];
			}
			mem_frag_num -= 1;
			break;
		}
	}
	refresh_free_size();
}

/* 获取内存剩余空间 */
void* mem_get_free_size(void)
{
	return sysinfo.mem_free;
}
