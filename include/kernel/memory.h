/* 用来记录一个内存碎片 */
struct mem_fragment
{
	unsigned int addr, size;
};

unsigned int GetMemorySize(); //获取内存大小
void init_MemFragCtl(); //初始化内存碎片管理
unsigned int AllocMemfrag(unsigned int); //分配内存碎片
void AllocMemfragWithAddr(unsigned int, unsigned int); //分配内存时指定地址
void FreeMemfrag(unsigned int); //释放内存碎片
unsigned int GetMemoryFreeSize(); //获取内存剩余空间