#include <arch/x86/page.h>

unsigned int *kernel_page_table_entry = (void*)0x5e8000;

void page_init(void)
{
	for(short i = 0; i < 1024; i++)
	{
		page_set_table_entry(kernel_page_table_entry ,i, 0x5e9000 + 4096 * i);
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