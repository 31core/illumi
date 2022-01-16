#include <kernel/memory.h>

/* 设置页表 */
void page_set_table(unsigned int *page_dir, short entry, short count, void *addr)
{
	unsigned int int_addr = (unsigned int)addr;
	unsigned int *page_table = (void*)page_dir[entry] - 3;
	int_addr |= 0b11;
	page_table[count] = int_addr;
}

/* 设置页目录 */
void page_set_table_entry(unsigned int *page_dir, short count, void *addr)
{
	unsigned int int_addr = (unsigned int)addr;
	int_addr |= 0b11;
	page_dir[count] = int_addr;
}