#include <kernel/page.h>
#include <kernel/memory.h>

#define PAGE_DIRS_SIZE 1024

unsigned int *kernel_page_dir; //内核页目录
unsigned int *page_dirs[PAGE_DIRS_SIZE];

/* 初始化页管理 */
void page_init(void)
{
	for(int i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		page_dirs[i] = 0;
	}
	kernel_page_dir = page_alloc();
	unsigned int *kernel_page_table =  memfrag_alloc_4k(1 + 1024);
	/* 初始化内核页目录 */
	for(short i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		page_set_dir(kernel_page_dir ,i, kernel_page_table + 4096 * i);
	}
	/* 初始化内核页表 */
	for(short i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		for(short j = 0; j < PAGE_DIRS_SIZE; j++)
		{
			page_set_table(kernel_page_dir, i, j, (void*)((i * 1024 + j) * 4096));
		}
	}
	set_cr3(kernel_page_dir);
	page_enable();
}

/* 分配页目录 */
unsigned int* page_alloc(void)
{
	for(int i = 0; i < PAGE_DIRS_SIZE; i++)
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
	for(int i = 0; i < PAGE_DIRS_SIZE; i++)
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
void page_set(unsigned int *page_dir, int virt_addr)
{
	void *addr = memfrag_alloc_4k(1);
	int table = virt_addr / 1024;
	int page = virt_addr % 1024;
	if(page_dir[table] == 0)
	{
		page_dir[table] = (unsigned int)memfrag_alloc_4k(1);
	}
	page_set_table(page_dir, table, page, addr);
}
/* 释放页表 */
void page_unset(unsigned int *page_dir, int virt_addr)
{
	int table = virt_addr / 1024;
	int page = virt_addr % 1024;
	unsigned int *page_table = (unsigned int*)page_dir[table];
	memfrag_free((void*)page_table[page]);
	page_table[page] = 0;
}
/* 重新加载页表 */
void page_reload(void)
{
	page_disable();
	page_enable();
}
/* 切换页表 */
void page_switch(void *page_dir)
{
	page_disable();
	set_cr3(page_dir);
	page_enable();
}