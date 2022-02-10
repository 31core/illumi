#include <kernel/strfmt.h>

/* #DE: 除零错误 */
void interrupt00h(void)
{
	printfmt("kernel panic: int00: division exception\n");
}
/* #OF: 溢出 */
void interrupt04h(void)
{
	printfmt("kernel panic: int04: overflow\n");
}
/* #UD: 无效指令 */
void interrupt06h(void)
{
	printfmt("kernel panic: int06: undefined code\n");
}
/* #DF: 双重错误 */
void interrupt08h(void)
{
	printfmt("kernel panic: int08: double fault\n");
}
/* #SS: 堆栈段异常 */
void interrupt0ch(void)
{
	printfmt("kernel panic: int0c: stack segfault\n");
}
/* #GP: 通用保护异常 */
void interrupt0dh(void)
{
	printfmt("kernel panic: int0d: general protection exception\n");
}
/* #PF: 页错误 */
void interrupt0eh(void)
{
	printfmt("kernel panic: int0e: page fault\n");
}

