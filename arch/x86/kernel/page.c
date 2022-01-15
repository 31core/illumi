#include <kernel/memory.h>

/* 设置页表 */
void page_set_table(unsigned int *page_table_entry, short entry, short count, unsigned int addr)
{
	unsigned int *page_table = (void*)page_table_entry[entry] - 3;
	addr |= 0b11;
	page_table[count] = addr;
}

/* 设置页表 */
void page_set_table_with_addr(unsigned int *page_table_entry, unsigned int addr)
{
	int entry = addr >> 22;
	int count = (addr >> 12) & 0b1111111111;
	unsigned int *page_table = (void*)page_table_entry[entry] - 3;
	addr |= 0b11;
	page_table[count] = addr;
}

/* 设置页目录 */
void page_set_table_entry(unsigned int *page_table_entry, short count, unsigned int addr)
{
	addr |= 0b11;
	page_table_entry[count] = addr;
}