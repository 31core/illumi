struct arg
{
	void *start;
	int count;
};

void arg_init(struct arg*, void*);
void arg_get_next(struct arg*, void*, int);
