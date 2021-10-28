#include <kernel/fifo.h>
/* 初始化缓冲区 */
void fifo_init(struct fifo8 *fifo, void* addr, int size)
{
	fifo->addr = addr;
	fifo->size = size;
	fifo->free = size;
	fifo->write = 0;
	fifo->read = 0;
}
/* 获取缓冲区未读取的数据大小 */
int fifo_get_info(struct fifo8 fifo)
{
	return fifo.size - fifo.free;
}
/* 写入缓冲区数据 */
void fifo_write_data(struct fifo8 *fifo, char data)
{
	/* 缓冲区空间已满 */
	if(fifo->free == 0)
	{
		return;
	}
	/* 写入位置达到最后一位 */
	if(fifo->write >= fifo->size)
	{
		fifo->write = 0;
	}
	char *p = (char*)fifo->addr;
	p[fifo->write] = data;
	fifo->write += 1;
	fifo->free -= 1;
}
/* 读取缓冲区数据 */
char fifo_read_data(struct fifo8 *fifo)
{
	/* 缓冲区数据大小为0 */
	if(fifo_get_info(*fifo) == 0)
	{
		return -1;
	}
	/* 读到缓冲区最后一位 */
	if(fifo->read >= fifo->size)
	{
		fifo->read = 0;
	}
	char *p = (char*)fifo->addr;
	char data = p[fifo->read];
	fifo->read += 1;
	fifo->free += 1;
	return data;
}