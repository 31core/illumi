#include <kernel/memory.h>

/* 设置页表 */
void page_set_table(unsigned int *page_dir, short table, short page, void *addr)
{
	unsigned int int_addr = (unsigned int)addr;
	unsigned int *page_table = (void*)(page_dir[table] & 0xfffff000);
	int_addr |= 0b11;
	page_table[page] = int_addr;
}

/* 设置页目录 */
void page_set_dir(unsigned int *page_dir, short page, void *addr)
{
	unsigned int int_addr = (unsigned int)addr;
	int_addr |= 0b11;
	page_dir[page] = int_addr;
}