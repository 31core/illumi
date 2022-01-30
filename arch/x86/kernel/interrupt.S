.global asm_interrupt20h, asm_interrupt21h
.extern interrupt20h, interrupt21h

.section .text
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
