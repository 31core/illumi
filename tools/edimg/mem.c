#include <stdlib.h>

void* memfrag_alloc(int size)
{
return malloc(size);
}

void memfrag_free(void *addr)
{
free(addr);
}