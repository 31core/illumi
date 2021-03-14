#include <kernel/memory.h>

/* 获取内存大小 */
unsigned int GetMemorySize()
{
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
	return (unsigned int)p;
}

struct mem_fragment mem_frag_list[4096];
int mem_frag_num = 0; //内存碎片总数
unsigned int memory_size; //内存大小

/* 初始化内存碎片管理 */
void init_MemFragCtl()
{
	memory_size = GetMemorySize();
	mem_frag_num = 0;
	mem_frag_list[0].addr = 0;
	mem_frag_list[0].size = 0;
	mem_frag_list[1].addr = memory_size;  //结尾的地址为内存大小
	mem_frag_list[1].size = 0;
}
/* 分配内存碎片 */
unsigned int AllocMemfrag(unsigned int size)
{
	int i = 1;
	for(; i < mem_frag_num + 2; i++)
	{
		/* 找到了足够大的内存碎片 */
		if(mem_frag_list[i].addr - mem_frag_list[i - 1].size -\
		mem_frag_list[i - 1].addr >= size)
		{
			break;
		}
	}
	int addr = mem_frag_list[i - 1].addr + mem_frag_list[i - 1].size;
	int j = mem_frag_num + 1;
	for(; j > i; j--)
	{
		mem_frag_list[j + 1] = mem_frag_list[j];
	}
	mem_frag_list[i].addr = addr;
	mem_frag_list[i].size = size;
	mem_frag_num += 1;
	return addr;
}
/* 释放内存碎片 */
void FreeMemfrag(unsigned int addr)
{
	int i = 1;
	for(; i < mem_frag_num + 1; i++)
	{
		if(mem_frag_list[i].addr == addr)
		{
			/* 向前移动成员 */
			for(; i < mem_frag_num + 1; i++)
			{
				mem_frag_list[i] = mem_frag_list[i + 1];
			}
			mem_frag_num -= 1;
			return;
		}
	}
}
/* 获取内存剩余空间 */
unsigned int GetMemoryFreeSize()
{
	int i = 1;
	unsigned int size = memory_size;
	for(; i < mem_frag_num + 1; i++)
	{
		size -= mem_frag_list[i].size;
	}
	return size;
}