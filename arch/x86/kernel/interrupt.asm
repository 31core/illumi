global asm_interrupt21h
extern interrupt21h

asm_interrupt21h:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call interrupt21h
	pop eax
	popad
	pop ds
	pop es
	iretd
