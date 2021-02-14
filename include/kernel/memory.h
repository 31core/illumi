/* 用来记录一个内存碎片 */
struct mem_fragment
{
	unsigned int addr,size;
};

int GetMemorySize();//获取内存大小
unsigned int AllocMemfrag(unsigned int);//分配内存碎片
void FreeMemfrag(unsigned int,unsigned int);//释放内存碎片
unsigned int GetMemoryFreeSize();//获取内存剩余空间