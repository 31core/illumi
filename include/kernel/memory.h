/* 用来记录一个内存碎片 */
struct mem_fragment
{
	void *addr;
	unsigned int size;
};

void memfrag_init(void);
unsigned int mem_get_size(void);
void* memfrag_alloc(unsigned int);
void memfrag_alloc_with_addr(void*, unsigned int);
void memfrag_free(void*);
unsigned int mem_get_free_size(void);
