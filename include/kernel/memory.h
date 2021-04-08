/* 用来记录一个内存碎片 */
struct mem_fragment
{
	unsigned int addr, size;
};

unsigned int mem_get_size(); //获取内存大小
void memfrag_init(); //初始化内存碎片管理
unsigned int memfrag_alloc(unsigned int); //分配内存碎片
void memfrag_alloc_with_addr(unsigned int, unsigned int); //分配内存时指定地址
void memfrag_free(unsigned int); //释放内存碎片
unsigned int mem_get_free_size(); //获取内存剩余空间