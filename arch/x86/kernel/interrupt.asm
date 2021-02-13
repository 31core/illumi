global asm_interrupt21h
extern interrupt21h

asm_interrupt21h:
	pushad
	call interrupt21h
	popad
	iretd
