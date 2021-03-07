global RecordTaskStatus,RestoreTaskStatus

;记录任务状态
RecordTaskStatus:
	mov eax,[esp+4]
	mov [eax],esp
	mov [eax+4],eax
	mov [eax+8],ebx
	mov [eax+12],ecx
	mov [eax+16],edx
	ret
;恢复任务状态
RestoreTaskStatus:
	mov eax,[esp+4]
	mov esp,[eax]
	mov eax,[eax+4]
	mov ebx,[eax+8]
	mov ecx,[eax+12]
	mov edx,[eax+16]
	ret;返回时会返回到esp栈所指向的地址