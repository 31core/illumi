;loader.asm
org 0x70000

KERNEL_ADDR equ 0x100000

[bits 16]
	mov ax,0x07e0
	mov ds,ax
	mov dword[0],0
	mov dword[4],0

	mov dword[8],0x0000ffff;4GB,可执行段
	mov dword[12],0x00cf9a00

	mov dword[16],0x0000ffff;4GB,可读写段
	mov dword[20],0x00cf9200

	mov ah,0x00
	mov al,0x03
	int 0x10
	cli;关闭中断
	mov ax,0x7000
	mov ds,ax
	lgdt [GDT_addr];加载GDTR
	in al,0x92
	or al,2
	out 0x92,al;启用 A20 line
	mov eax,cr0
	or eax,1
	mov cr0,eax;cr0 PE位置1
	jmp dword 8:start

[bits 32]
start:
	mov ax,2*8
	mov ds,ax
	mov ss,ax
	call load_kernel
	jmp dword 8:KERNEL_ADDR
;加载内核
load_kernel:
	mov cx,23
	mov ebx,9
	mov edx,KERNEL_ADDR
	call load_block;加载内核到内存

	mov eax,0
	mov ebx,0
	mov eax,KERNEL_ADDR
	mov bl,[KERNEL_ADDR+28];bl=program header地址
	add eax,ebx
	sub eax,0x20
.check_flag:
	add eax,0x20;下一个program header地址
	mov dh,[eax+24];dh=flag
	cmp dh,0x05;flag是否为R E
	je .next
	jmp .check_flag

.next:
	mov ebx,[eax+4];eax=记录.text偏移数据地址
	add ebx,KERNEL_ADDR;ebx=.text偏移地址

	mov cx,0xffff
	mov edx,KERNEL_ADDR
	call memcpy
	ret

;读取磁盘块
;cx:加载扇区个数 ebx:起始扇区 edx:加载内存地址
load_block:
	push edx
	mov dx,0x1f2
	mov al,cl
	out dx,al;0x1f2端口写加载扇区数
	mov al,bl
	add dx,1;0x1f3
	out dx,al;LBA0~7位
	shr ebx,8
	mov al,bl
	add dx,1;0x1f4
	out dx,al;LBA8~15位
	shr ebx,8
	mov al,bl
	add dx,1;0x1f5
	out dx,al;LBA16~23位
	shr ebx,8
	and bl,0x0f;保留低4位
	or bl,0xe0;LBA,主盘
	mov al,bl
	add dx,1;0x1f6
	out dx,al;LBA24~27位
	mov al,0x20;读取磁盘
	add dx,1;0x1f7
	out dx,al

	mov ax,cx
	mov dx,256
	mul dx;循环次数=扇区数*512/2
	mov cx,ax
	pop edx
	mov ebx,edx
	mov dx,0x1f0
.read_data:
	call .check_disk;检查磁盘控制器是否可用
	mov dx,0x1f0
	in ax,dx
	mov [ebx],ax
	add ebx,2;一次读取2-byte
	loop .read_data
	ret
.check_disk:
	mov dx,0x1f7
	in al,dx
	and al,0x88
	cmp al,0x08
	jnz .check_disk
	ret
;复制内存数据
;ebx:原始数据地址 edx:目标内存地址
memcpy:
	mov ah,[ebx]
	mov [edx],ah
	add ebx,1
	add edx,1
	loop memcpy
	ret

GDT_addr:
	dw 3*8-1
	dd 0x00007e00
