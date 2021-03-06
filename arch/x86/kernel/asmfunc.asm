global LoadGDTR,LoadIDTR
global LoadTR
global io_out8,io_in8
global io_out16,io_in16
global io_cli,io_sti
global RecordTaskStatus,RestoreTaskStatus

[bits 32]
;加载GDRT寄存器
LoadGDTR:
	mov ax,[esp+4]
	mov [esp+6],ax
	lgdt [esp+6]
	ret
;加载IDRT寄存器
LoadIDTR:
	mov ax,[esp+4]
	mov [esp+6],ax
	lidt [esp+6]
	ret
LoadTR:
	ltr [esp+4]
	ret
;写8位端口
io_out8:
	mov dx,[esp+4];端口
	mov al,[esp+8];8位数据
	out dx,al
	ret
;读8位端口
io_in8:
	mov dx,[esp+4];端口
	in al,dx
	ret
;写8位端口
io_out16:
	mov dx,[esp+4];端口
	mov ax,[esp+8];16位数据
	out dx,ax
	ret
;读8位端口
io_in16:
	mov dx,[esp+4];端口
	in ax,dx
	ret
;禁用中断
io_cli:
	cli
	ret
;启用中断
io_sti:
	sti
	ret
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
	ret
global asm_farjump
asm_farjump:
	jmp far [esp+4]
	ret
global asm_jump
asm_jump:
	jmp [esp+4]
	ret
