#include <kernel/memory.h>

/* 设置页表 */
void page_set_table(unsigned int *page_dir, short table, short page, unsigned addr_4k)
{
	addr_4k <<= 12;
	unsigned int *page_table = (void*)(page_dir[table] & 0xfffff000);
	addr_4k |= 0b11;
	page_table[page] = addr_4k;
}

/* 设置页目录 */
void page_set_dir(unsigned int *page_dir, short page, unsigned addr_4k)
{
	addr_4k <<= 12;
	addr_4k |= 0b11;
	page_dir[page] = addr_4k;
}
