#include "intterrupts.h"

.global asm_interrupt00h, asm_interrupt04h
.global asm_interrupt05h
.global asm_interrupt06h, asm_interrupt08h
.global asm_interrupt0ah, asm_interrupt0bh
.global asm_interrupt0ch, asm_interrupt0dh
.global asm_interrupt0eh
.global asm_interrupt11h
.global asm_interrupt15h
.global asm_interrupt1eh
.global asm_interrupt20h, asm_interrupt21h

.extern kernel_mode, user_mode

.section .text
asm_interrupt00h:
	pusha
	calll kernel_mode
	calll interrupt00h
	calll kernel_mode
	popa
	iret
asm_interrupt04h:
	pusha
	calll kernel_mode
	calll interrupt04h
	calll kernel_mode
	popa
	iret
asm_interrupt05h:
	pusha
	calll kernel_mode
	calll interrupt04h
	calll kernel_mode
	popa
	iret
asm_interrupt06h:
	pusha
	calll kernel_mode
	calll interrupt06h
	calll kernel_mode
	popa
	iret
asm_interrupt08h:
	pusha
	calll kernel_mode
	calll interrupt08h
	calll kernel_mode
	popa
	iret
asm_interrupt0ah:
	pusha
	calll kernel_mode
	calll interrupt0ch
	calll kernel_mode
	popa
	iret
asm_interrupt0bh:
	pusha
	calll kernel_mode
	calll interrupt0ch
	calll kernel_mode
	popa
	iret
asm_interrupt0ch:
	pusha
	calll kernel_mode
	calll interrupt0ch
	calll kernel_mode
	popa
	iret
asm_interrupt0dh:
	pusha
	calll kernel_mode
	calll interrupt0dh
	calll kernel_mode
	popa
	iret
asm_interrupt0eh:
	pusha
	calll kernel_mode
	calll interrupt0eh
	calll kernel_mode
	popa
	iret
asm_interrupt11h:
	pusha
	calll kernel_mode
	calll interrupt15h
	calll kernel_mode
	popa
	iret
asm_interrupt15h:
	pusha
	calll kernel_mode
	calll interrupt15h
	calll kernel_mode
	popa
	iret
asm_interrupt1eh:
	pusha
	calll kernel_mode
	calll interrupt15h
	calll user_mode
	popa
	iret
asm_interrupt20h:
	pusha
	calll kernel_mode
	calll interrupt20h
	calll kernel_mode
	popa
	iret
asm_interrupt21h:
	pusha
	calll kernel_mode
	calll interrupt21h
	calll kernel_mode
	popa
	iret
