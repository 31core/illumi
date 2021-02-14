global LoadGDTR,LoadIDTR
global io_out8,io_in8
global io_cli,io_sti

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
;写8位端口
io_out8:
	mov dx,[esp+4];端口
	mov al,[esp+8];8位数据
	out dx,al
	ret
;读8位端口
io_in8:
	mov dx,[esp+4];端口
	in eax,dx
	ret
;禁用中断
io_cli:
	cli
	ret
;启用中断
io_sti:
	sti
	ret