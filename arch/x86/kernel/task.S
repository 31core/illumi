.global task_switch_asm, task_switch_init

.section .text

task_switch_init:
	movl (%esp), %esi
	movl 4(%esp), %eax
	movl %esp, (%eax)
	movl 8(%esp), %esp
	jmp %esi

task_switch_asm:
	movl 4(%esp), %eax
	movl %esp, (%eax)
	movl 8(%esp), %esp
	ret
