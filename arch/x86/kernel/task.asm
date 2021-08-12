global asm_task_switch
asm_task_switch:
	;保存当前任务状态
	mov eax, [esp + 4] ;[esp + 4]指向task_list[old_pid].state
	mov [eax], esp
	mov [eax + 4], ebp
	mov [eax + 8], eax
	mov [eax + 12], ebx
	mov [eax + 16], ecx
	mov [eax + 20], edx
	mov [eax + 24], esi
	mov [eax + 28], edi
	;恢复下一个任务状态
	mov eax, [esp + 8] ;[esp + 8]指向task_list[pid].state
	mov esp, [eax]
	mov ebp, [eax + 4]
	mov eax, [eax + 8]
	mov ebx, [eax + 12]
	mov ecx, [eax + 16]
	mov edx, [eax + 20]
	mov esi, [eax + 24]
	mov edi, [eax + 28]
	ret
