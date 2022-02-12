#include <kernel/strfmt.h>
#include <kernel/panic.h>

/* #DE: 除零错误 */
void interrupt00h(void)
{
	printfmt("int00: divide-by-zero error\n");
	kernel_panic();
}
/* #OF: 溢出 */
void interrupt04h(void)
{
	printfmt("int04: overflow\n");
	kernel_panic();
}
/* BR: 边界检查 */
void interrupt05h(void)
{
	printfmt("int05: bound range exceeded\n");
	kernel_panic();
}
/* #UD: 无效指令 */
void interrupt06h(void)
{
	printfmt("int06: invalid opcode\n");
	kernel_panic();
}
/* #DF: 双重错误 */
void interrupt08h(void)
{
	printfmt("int08: double fault\n");
	kernel_panic();
}
/* #TS: 无效TSS异常 */
void interrupt0ah(void)
{
	printfmt("int0a: invalid TSS\n");
	kernel_panic();
}
/* #NP: 段不存在 */
void interrupt0bh(void)
{
	printfmt("int0b: segment not present\n");
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
/* #CP: 对齐检查 */
void interrupt11h(void)
{
	printfmt("int11: alignment check\n");
	kernel_panic();
}
/* #CP: 控制保护异常 */
void interrupt15h(void)
{
	printfmt("int15: control protection exception\n");
	kernel_panic();
}
/* #CX: 安全异常 */
void interrupt1eh(void)
{
	printfmt("int1e: security exception\n");
	kernel_panic();
}
