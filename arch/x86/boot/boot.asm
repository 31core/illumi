;boot.asm
org 0x7c00

SECTOR_OFFSET equ 1 ;起始扇区
SECTOR_COUNT equ 8 ;读入扇区数
MEMORY_SEG equ 0x7000 ;读入内存基地址

[bits 16]
entry:
	mov ah, 0x42
	mov dl, 0x80
	mov si, packet
	int 0x13
	jmp 0x7000:0

packet:
	db 0x10
	db 0
	db SECTOR_COUNT
	db 0
	dw 0
	dw MEMORY_SEG
	dq SECTOR_OFFSET

times 510-($-$$) db 0
db 0x55, 0xaa
