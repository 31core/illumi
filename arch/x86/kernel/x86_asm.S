.global GDTR_load, IDTR_load
.global io_out8, io_in8
.global io_out16, io_in16
.global io_cli, io_sti

.section .text
#加载GDRT寄存器
GDTR_load:
	movw 8(%esp), %ax
	movl 4(%esp), %ebx
	movl %ebx, 6(%esp)
	movw %ax, 4(%esp)
	lgdtl 4(%esp)
	retl
#加载IDRT寄存器
IDTR_load:
	movw 8(%esp), %ax
	movl 4(%esp), %ebx
	movl %ebx, 6(%esp)
	movw %ax, 4(%esp)
	lidtl 4(%esp)
	retl
#写8位端口
io_out8:
	movw 4(%esp), %dx #端口
	movb 8(%esp), %al #8位数据
	outb %al, %dx
	retl
#读8位端口
io_in8:
	movw 4(%esp), %dx #端口
	inb %dx, %al
	retl
#写16位端口
io_out16:
	movw 4(%esp), %dx #端口
	movw 8(%esp), %ax #16位数据
	outw %ax, %dx
	retl
#读16位端口
io_in16:
	movw 4(%esp), %dx #端口
	inw %dx, %ax
	retl
#禁用中断
io_cli:
	cli
	retl
#启用中断
io_sti:
	sti
	retl
