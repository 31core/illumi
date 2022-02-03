#include <kernel/string_format.h>

/* 溢出 */
void interrupt04h(void)
{
	print_format("kernel panic: int04\n");
}
/* 非法操作码 */
void interrupt06h(void)
{
	print_format("kernel panic: int06\n");
}
/* 堆栈段异常 */
void interrupt0ch(void)
{
	print_format("kernel panic: int0c\n");
}
/* 通用保护异常 */
void interrupt0dh(void)
{
	print_format("kernel panic: int0d\n");
}
