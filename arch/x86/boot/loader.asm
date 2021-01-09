;loader.asm
org 0x70000

[bits 16]
	mov ax,0x07e0
	mov ds,ax
	mov dword[bx],0x00
	mov dword[bx+4],0x00

	mov dword[bx+8],0x0000ffff ;4GB,可执行代码段
	mov dword[bx+12],0x00cf9a00

	mov dword[bx+16],0x0000ffff ;4GB,可执行数据段
	mov dword[bx+20],0x00cf9200

	mov dword[bx+24],0x8000ffff ;显存
	mov dword[bx+28],0x0040920b

	mov ah,0x00
	mov al,0x03
	int 0x10
	cli ;关闭中断
	mov ax,0x7000
	mov ds,ax
	lgdt [ds:GDT_addr]
	in al,0x92
	or al,2
	out 0x92,al	;enable A20 line
	mov eax,cr0
	or eax,1
	mov cr0,eax ;cr0 PE位置1
	jmp dword 0x08:start

[bits 32]
start:
	mov ax,8
	mov ax,2*8
	mov ds,ax
	mov edx,0x0000b8000
	mov byte[ds:edx],'P'
	mov byte[ds:edx+1],0x07
	hlt
	jmp start

GDT_addr:
	dw 4*8-1
	dd 0x00007e00
