#include <kernel/page.h>
#include <kernel/memory.h>

unsigned int *kernel_page_table_dir;
unsigned int *page_dirs[1024];

/* 初始化页管理 */
void page_init(void)
{
	for(int i = 0; i < 1024; i++)
	{
		page_dirs[i] = 0;
	}
	kernel_page_table_dir = page_alloc();
	unsigned int *kernel_page_table =  memfrag_alloc_4k(1 + 1024);
	for(short i = 0; i < 1024; i++)
	{
		page_set_table_entry(kernel_page_table_dir ,i, kernel_page_table + 4096 * i);
	}
	for(short i = 0; i < 1024; i++)
	{
		for(short j = 0; j < 1024; j++)
		{
			page_set_table(kernel_page_table_dir, i, j, (void*)((i * 1024 + j) * 4096));
		}
	}
	set_cr3(kernel_page_table_dir);
	page_enable();
}

/* 分配页目录 */
unsigned int* page_alloc(void)
{
	for(int i = 0; i < 1024; i++)
	{
		if(page_dirs[i] == 0)
		{
			page_dirs[i] = memfrag_alloc_4k(1);
			return page_dirs[i];
		}
	}
	return 0;
}
/* 释放页目录 */
void page_free(void *page)
{
	for(int i = 0; i < 1024; i++)
	{
		if(page_dirs[i] == (unsigned int*)page)
		{
			memfrag_free(page);
			page_dirs[i] = 0;
			return;
		}
	}
}
/* 分配页表 */
void page_set(unsigned int *page, int virt_addr)
{
	void *addr = memfrag_alloc_4k(1);
	int table = virt_addr / 1024;
	int table_count = virt_addr % 1024;
	if(page[table] == 0)
	{
		page[table] = (unsigned int)memfrag_alloc_4k(1);
	}
	page_set_table(page, table, table_count, addr);
}
/* 释放页表 */
void page_unset(unsigned int *page_dir, int virt_addr)
{
	int table = virt_addr / 1024;
	int table_count = virt_addr % 1024;
	unsigned int *page_table = (unsigned int*)page_dir[table];
	memfrag_free((void*)page_table[table_count]);
}