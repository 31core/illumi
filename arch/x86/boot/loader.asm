;loader.asm
org 0x70000

KERNEL_ADDR equ 0x10000

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
	mov dword[bx+28],0x0040f20b

	mov ah,0x00
	mov al,0x03
	int 0x10
	cli ;关闭中断
	mov ax,0x7000
	mov ds,ax
	lgdt [ds:GDT_addr] ;加载GDTR
	in al,0x92
	or al,2
	out 0x92,al	;enable A20 line
	mov eax,cr0
	or eax,1
	mov cr0,eax ;cr0 PE位置1
	jmp dword 0x08:start

[bits 32]
start:
	mov ax,2*8
	mov ds,ax
	mov byte[ds:0xb8000],'P'
	mov byte[ds:0xb8001],0x07
	call load_kernel
	mov byte[ds:0xb8000],'L'
	mov byte[ds:0xb8001],0x07
	jmp dword 0x08:KERNEL_ADDR
;加载内核
load_kernel:
	mov cx,1
	mov ebx,8
	mov edx,KERNEL_ADDR

	call load_block
	ret

;读取磁盘块
;cx:加载扇区个数 ebx:起始扇区 edx:加载内存地址
load_block:
	push edx
	mov dx,0x1f2
	out dx,al
	mov al,bl
	add dx,1 ;0x1f3
	out dx,al ;LBA0~7位
	shr ebx,8
	mov al,bl
	add dx,1 ;0x1f4
	out dx,al ;LBA8~15位
	shr ebx,8
	mov al,bl
	add dx,1 ;0x1f5
	out dx,al ;LBA16~23位
	shr ebx,8
	and bl,0x0f
	or bl,0xe0
	mov al,bl
	add dx,1 ;0x1f6
	out dx,al ;LBA24~27位
	mov al,0x20 ;读取磁盘
	add dx,1 ;0x1f7
	out dx,al

.check_disk:
	in al,dx
	and al,0x88
	cmp al,0x08
	jnz .check_disk

	mov ax,cx
	mov dx,256
	mul dx
	mov cx,ax
	mov dx,0x1f0
	pop edx
.read_data:
	in ax,dx
	mov [edx],ax
	add edx,2
	loop .read_data
	ret
GDT_addr:
	dw 4*8-1
	dd 0x00007e00
