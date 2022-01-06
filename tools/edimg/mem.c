#include <stdlib.h>

/*
kernel/memory.c 的C语言实现
*/

void* memfrag_alloc(size_t size)
{
	return malloc(size);
}
void* memfrag_alloc_4k(size_t size)
{
	return malloc(4096 * size);
}
void memfrag_free(void *addr)
{
	free(addr);
}