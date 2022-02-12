.extern main
.global _start

.section .text
_start:
	movw $(2 * 8), %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movl $0x700000, %esp
	jmp main
