#include <kernel/page.h>
#include <kernel/memory.h>
#include <const.h>

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
	unsigned int kernel_page_table = _4KB_ALIGN((unsigned int)memfrag_alloc_4k(1024));
	/* 初始化内核页目录 */
	for(short i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		page_set_dir(kernel_page_dir ,i, kernel_page_table + i);
	}
	/* 初始化内核页表 */
	for(short i = 0; i < _4KB_ALIGN(0xffffffff); i++)
	{
		page_set(kernel_page_dir , i, i);
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
			for(int j = 0; j < 1024; j++)
			{
				page_dirs[i][j] = 0;
			}
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
void page_set(unsigned int *page_dir, unsigned int phy_addr_4k, unsigned int virt_addr_4k)
{
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
	if(page_dir[table] == 0)
	{
		page_set_dir(page_dir, table, _4KB_ALIGN((unsigned int)memfrag_alloc_4k(1)));
	}
	page_set_table(page_dir, table, page, phy_addr_4k);
}
/* 设置页表 */
void* page_add(unsigned int *page_dir, unsigned int virt_addr_4k)
{
	unsigned int addr = _4KB_ALIGN((unsigned int)memfrag_alloc_4k(1));
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
	if(page_dir[table] == 0)
	{
		page_set_dir(page_dir, table, _4KB_ALIGN((unsigned int)memfrag_alloc_4k(1)));
	}
	page_set_table(page_dir, table, page, addr);
	return (void*)(addr * 4096);
}
/* 释放页表 */
void page_unset(unsigned int *page_dir, unsigned int virt_addr_4k)
{
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
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
