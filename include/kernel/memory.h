/* 用来记录一个内存碎片 */
struct mem_fragment
{
	unsigned int addr, size;
};

void memfrag_init();
unsigned int mem_get_size();
unsigned int memfrag_alloc(unsigned int);
void memfrag_alloc_with_addr(unsigned int, unsigned int);
void memfrag_free(unsigned int);
unsigned int mem_get_free_size();