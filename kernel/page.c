#include <kernel/page.h>
#include <kernel/memory.h>

#define PAGE_DIRS_SIZE 1024

unsigned int *kernel_page_dir; //kernel page directory
unsigned int *page_dirs[PAGE_DIRS_SIZE];

/* initialize page management */
void page_init(void)
{
	for(int i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		page_dirs[i] = 0;
	}
	kernel_page_dir = page_alloc();
	unsigned int kernel_page_table = (unsigned int)memfrag_alloc_4k(1024);
	/* set directories */
	for(short i = 0; i < PAGE_DIRS_SIZE; i++)
	{
		page_set_dir(kernel_page_dir , i, kernel_page_table + i);
	}
	/* set tables */
	for(short table = 0; table < PAGE_DIRS_SIZE; table++)
	{
		for(short page = 0; page < PAGE_DIRS_SIZE; page++)
		{
			page_set_table(kernel_page_dir, table, page, table * 1024 + page);
		}
	}
	page_switch(kernel_page_dir);
}

/* allocate page directory */
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

/* release page directory */
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

/*  set page */
void page_set(unsigned int *page_dir, unsigned int phy_addr_4k, unsigned int virt_addr_4k)
{
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
	if(page_dir[table] == 0)
	{
		page_set_dir(page_dir, table, (unsigned int)memfrag_alloc_4k(1) / 4096);
	}
	page_set_table(page_dir, table, page, phy_addr_4k);
}

/* allock 4k memory and set page */
void* page_add(unsigned int *page_dir, unsigned int virt_addr_4k)
{
	unsigned int addr = (unsigned int)memfrag_alloc_4k(1) / 4096;
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
	if(page_dir[table] == 0)
	{
		page_set_dir(page_dir, page, (unsigned int)memfrag_alloc_4k(1) / 4096);
	}
	page_set_table(page_dir, table, page, addr);
	return (void*)(addr * 4096);
}

/* unset page */
void page_unset(unsigned int *page_dir, unsigned int virt_addr_4k)
{
	int table = virt_addr_4k / 1024;
	int page = virt_addr_4k % 1024;
	unsigned int *page_table = (unsigned int*)page_dir[table];
	memfrag_free((void*)page_table[page]);
	page_table[page] = 0;
}

/* reload page table */
void page_reload(void)
{
	page_disable();
	page_enable();
}

/* switch page table */
void page_switch(void *page_dir)
{
	page_disable();
	set_cr3(page_dir);
	page_enable();
}
