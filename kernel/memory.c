#include<kernel/memory.h>

/* 获取内存大小 */
unsigned int GetMemorySize()
{
	int *p,old;
	for(p=(int*)0x100000;p<(int*)0xffffffff;p+=4096)
	{
		old=*p;
		*p=0xff00ff00;
		if(*p!=0xff00ff00)
		{
			break;
		}
		*p=old;
	}
	return (unsigned int)p;
}

struct mem_fragment mem_frag_list[1000];
int mem_frag_num=1;
/* 初始化内存碎片管理 */
void init_MemFragCtl()
{
	mem_frag_list[0].addr=0x100000;
	mem_frag_list[0].size=GetMemorySize();
}
/* 分配内存碎片 */
unsigned int AllocMemfrag(unsigned int size)
{
	int i;
	for(i=0;i<mem_frag_num;i++)
	{
		/* 找到了足够大的内存碎片 */
		if(mem_frag_list[i].size>=size)
		{
			int addr=mem_frag_list[i].addr;
			mem_frag_list[i].addr+=size;
			mem_frag_list[i].size-=size;
			/* 如果当前碎片大小为0则删除此碎片 */
			if(mem_frag_list[i].size==0)
			{
				for(;i<mem_frag_num;i++)
				{
					mem_frag_list[i]=mem_frag_list[i+1];
				}
				mem_frag_num-=1;
			}
			return addr;
		}
	}
	return -1;
}
/* 释放内存碎片 */
void FreeMemfrag(unsigned int addr,unsigned int size)
{
	int i;
	/* 查找插入位置 */
	for(i=-1;i+1<mem_frag_num;i++)
	{
		if(mem_frag_list[i+1].addr>=addr)
		{
			break;
		}
	}
	/* 单独的内存碎片 */
	if(addr!=mem_frag_list[i].addr+mem_frag_list[i].size&&addr+size!=mem_frag_list[i+1].addr)
	{
		int j=mem_frag_num;
		/* 列表中后面的内存碎片往后移 */
		for(;j>i+1;j--)
		{
			mem_frag_list[j]=mem_frag_list[j-1];
		}
		/* 单独创建一个内存碎片信息 */
		mem_frag_list[i+1].addr=addr;
		mem_frag_list[i+1].size=size;
		mem_frag_num+=1;
		return;
	}
	/* 和前面的内存碎片是连续的 */
	if(i!=-1&&mem_frag_list[i].addr+mem_frag_list[i].size==addr)
	{
		mem_frag_list[i].size+=size;
	}
	/* 和后面的内存碎片是连续的 */
	if(addr+size==mem_frag_list[i+1].addr)
	{
		mem_frag_list[i+1].addr+=addr;
		mem_frag_list[i+1].size+=size;
		return;
	}
	/* 检查前后内存碎片是否重叠 */
	if(mem_frag_list[i].addr+mem_frag_list[i].size>mem_frag_list[i+1].addr)
	{
		mem_frag_list[i].size+=mem_frag_list[i+1].size-size;
		/* 列表中后面的内存碎片往前移 */
		for(i+=1;i<mem_frag_num-1;i++)
		{
			mem_frag_list[i]=mem_frag_list[i+1];
		}
		mem_frag_num-=1;
	}
}
/* 获取内存剩余空间 */
unsigned int GetMemoryFreeSize()
{
	int i;
	unsigned int size=0;
	for(i=0;i<mem_frag_num;i++)
	{
		size+=mem_frag_list[i].size;
	}
	return size;
}