global LoadGDTR,LoadIDTR
global io_out8

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

io_out8:
	mov edx,[esp+4];端口
	mov al,[esp+8];8位数据
	out dx,al
	ret