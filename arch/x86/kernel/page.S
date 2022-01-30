.global page_enable, page_disable
.global set_cr3

.section .text
#启用分页
page_enable:
	movl %cr0, %eax
	orl $0x80000001, %eax
	movl %eax, %cr0
	ret

page_disable:
	movl %cr0, %eax
	andl $0x7fffffff, %eax
	movl %eax, %cr0
	ret

set_cr3:
	movl 4(%esp), %eax
	movl %eax, %cr3
	ret
