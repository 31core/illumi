.global asm_task_switch

.section .text
asm_task_switch:
	#保存当前任务状态
	movl 4(%esp), %eax #[esp + 4]指向task_list[old_pid].state
	movl %esp, (%eax)
	movl %ebp, 4(%eax)
	movl %eax, 8(%eax)
	movl %ebx, 12(%eax)
	movl %ecx, 16(%eax)
	movl %edx, 20(%eax)
	movl %esi, 24(%eax)
	movl %edi, 28(%eax)
	#恢复下一个任务状态
	movl 8(%esp), %eax #[esp + 8]指向task_list[pid].state
	movl (%eax), %esp
	movl 4(%eax), %ebp
	movl 8(%eax), %eax
	movl 12(%eax), %ebx
	movl 16(%eax), %ecx
	movl 20(%eax), %edx
	movl 24(%eax), %esi
	movl 28(%eax), %edi
	retl
