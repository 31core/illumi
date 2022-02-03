#include "intterrupts.h"

.global asm_interrupt20h, asm_interrupt21h
.global asm_interrupt04h, asm_interrupt06h
.global asm_interrupt0ch, asm_interrupt0dh

.section .text
asm_interrupt04h:
	pusha
	calll interrupt04h
	popa
	iret
asm_interrupt06h:
	pusha
	calll interrupt06h
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
