#include <kernel/page.h>
#include <kernel/memory.h>

unsigned int *kernel_page_table_entry;
unsigned int *page_tables[1024];

/* 初始化页管理 */
void page_init(void)
{
	for(int i = 0; i < 1024; i++)
	{
		page_tables[i] = 0;
	}
	kernel_page_table_entry = page_alloc();
	unsigned int *kernel_page_table =  memfrag_alloc_4k(1 + 1024);
	for(short i = 0; i < 1024; i++)
	{
		page_set_table_entry(kernel_page_table_entry ,i, (int)kernel_page_table + 4096 * i);
	}
	for(short i = 0; i < 1024; i++)
	{
		for(short j = 0; j < 1024; j++)
		{
			page_set_table(kernel_page_table_entry, i, j, (i * 1024 + j) * 4096);
		}
	}
	set_cr3(kernel_page_table_entry);
	page_enable();
}

/* 分配页表 */
unsigned int* page_alloc(void)
{
	for(int i = 0; i < 1024; i++)
	{
		if(page_tables[i] == 0)
		{
			page_tables[i] = memfrag_alloc_4k(1);
			return page_tables[i];
		}
	}
	return 0;
}
/* 释放页表 */
void page_free(void *page)
{
	for(int i = 0; i < 1024; i++)
	{
		if(page_tables[i] == (unsigned int*)page)
		{
			memfrag_free(page);
			page_tables[i] = 0;
			return;
		}
	}
}