#include <kernel/strfmt.h>
#include <kernel/panic.h>

/* #DE: 除零错误 */
void interrupt00h(void)
{
	printfmt("int00: division exception\n");
	kernel_panic();
}
/* #OF: 溢出 */
void interrupt04h(void)
{
	printfmt("int04: overflow\n");
	kernel_panic();
}
/* #UD: 无效指令 */
void interrupt06h(void)
{
	printfmt("int06: undefined code\n");
	kernel_panic();
}
/* #DF: 双重错误 */
void interrupt08h(void)
{
	printfmt("int08: double fault\n");
	kernel_panic();
}
/* #SS: 堆栈段异常 */
void interrupt0ch(void)
{
	printfmt("int0c: stack segfault\n");
	kernel_panic();
}
/* #GP: 通用保护异常 */
void interrupt0dh(void)
{
	printfmt("int0d: general protection exception\n");
	kernel_panic();
}
/* #PF: 页错误 */
void interrupt0eh(void)
{
	printfmt("int0e: page fault\n");
	kernel_panic();
}

