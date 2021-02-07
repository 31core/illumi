global LoadGDTR,LoadIDTR

[bits 32]
;加载GDRT寄存器
LoadGDTR:
	mov ax,[esp+4]
	mov [esp+6],ax
	lgdt [esp+6]
	ret
;加载IDRT寄存器
LoadIDTR:
	mov	ax,[esp+4]
	mov	[esp+6],ax
	lidt [esp+6]
	ret
