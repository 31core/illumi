global asm_interrupt20h, asm_interrupt21h
extern interrupt20h, interrupt21h

asm_interrupt20h:
	pushad
	call interrupt20h
	popad
	iretd

asm_interrupt21h:
	pushad
	call interrupt21h
	popad
	iretd
