.global task_save_state, task_load_state

.section .text
task_save_state:
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
	retl

task_load_state:
	movl 4(%esp), %eax #[esp + 4]指向task_list[x].state
	movl (%eax), %esp
	movl 4(%eax), %ebp
	movl 8(%eax), %eax
	movl 12(%eax), %ebx
	movl 16(%eax), %ecx
	movl 20(%eax), %edx
	movl 24(%eax), %esi
	movl 28(%eax), %edi
	retl