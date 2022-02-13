#include <lib/args.h>

void arg_init(struct arg *arg, void *last_arg)
{
	arg->start = last_arg + sizeof(void*);
	arg->count = 0;
}

void arg_get_next(struct arg *arg, void* ret, int size)
{
	char *val = arg->start + arg->count;
	arg->count += sizeof(void*);
	char *ret0 = ret;
	for(int i = 0 ;i < size; i++)
	{
		ret0[i] = val[i];
	}
}
