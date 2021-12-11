CC = gcc
LD = ld
MAKE = make
ifeq ($(ARCH), x86)
	AS = nasm
	QEMU = qemu-system-i386
endif