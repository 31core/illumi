.global cpuid_get_vendorid
.global cpuid_get_brand

.section .text
#获取cpu vendor ID
cpuid_get_vendorid:
	movl $0, %eax
	cpuid
	movl 4(%esp), %eax
	movl %ebx, (%eax)
	movl %edx, 4(%eax)
	movl %ecx, 8(%eax)
	movb $0, 12(%eax)
	retl
#获取cpu商标信息
cpuid_get_brand:
	movl $0x80000002, %eax
	cpuid
	movl 4(%esp), %esi
	movl %eax, %esi
	movl %ebx, 4(%esi)
	movl %ecx, 8(%esi)
	movl %edx, 12(%esi)
	movl $0x80000003, %eax
	cpuid
	movl 4(%esp), %esi
	movl %eax, 16(%esi)
	movl %ebx, 20(%esi)
	movl %ecx, 24(%esi)
	movl %edx, 28(%esi)
	movl $0x80000004, %eax
	cpuid
	movl 4(%esp), %esi
	movl %eax, 32(%esi)
	movl %ebx, 36(%esi)
	movl %ecx, 40(%esi)
	movl %edx, 44(%esi)
	movb $0, 48(%esi)
	retl
