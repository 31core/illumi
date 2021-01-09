KERNEL_STACK_TOP EQU 0x8009fc00

[bits 32]
extern main	

global gdt_limit
global gdt_addr

global _start
_start:
	mov ax,0x10	;the data 
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov esp,KERNEL_STACK_TOP
	
	sgdt [gdtr_ptr]
	
	call main

stop_run:
	hlt
	jmp stop_run

[section .data]
gdtr_ptr:
gdt_limit: dw 0
gdt_addr: dd 0
