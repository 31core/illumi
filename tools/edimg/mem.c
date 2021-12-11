#include <stdlib.h>

void* memfrag_alloc(size_t size)
{
	return malloc(size);
}

void memfrag_free(void *addr)
{
	free(addr);
}