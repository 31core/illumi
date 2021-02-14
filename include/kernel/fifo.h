struct fifo8
{
	int addr;
	int size;
	int write,read;
};

void init_fifo(struct fifo8*,int,int);
int GetFifoInfo(struct fifo8);
void WriteData(struct fifo8*,char);
char ReadData(struct fifo8*);