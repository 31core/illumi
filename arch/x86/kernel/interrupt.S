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

.section .text
asm_interrupt00h:
	pusha
	calll interrupt00h
	popa
	iret
asm_interrupt04h:
	pusha
	calll interrupt04h
	popa
	iret
asm_interrupt05h:
	pusha
	calll interrupt04h
	popa
	iret
asm_interrupt06h:
	pusha
	calll interrupt06h
	popa
	iret
asm_interrupt08h:
	pusha
	calll interrupt08h
	popa
	iret
asm_interrupt0ah:
	pusha
	calll interrupt0ch
	popa
	iret
asm_interrupt0bh:
	pusha
	calll interrupt0ch
	popa
	iret
asm_interrupt0ch:
	pusha
	calll interrupt0ch
	popa
	iret
asm_interrupt0dh:
	pusha
	calll interrupt0dh
	popa
	iret
asm_interrupt0eh:
	pusha
	calll interrupt0eh
	popa
	iret
asm_interrupt11h:
	pusha
	calll interrupt15h
	popa
	iret
asm_interrupt15h:
	pusha
	calll interrupt15h
	popa
	iret
asm_interrupt1eh:
	pusha
	calll interrupt15h
	popa
	iret
asm_interrupt20h:
	pusha
	calll interrupt20h
	popa
	iret
asm_interrupt21h:
	pusha
	calll interrupt21h
	popa
	iret
