CC = gcc
LD = ld
AS = as
MAKE = make
ifeq ($(ARCH), x86)
	QEMU = qemu-system-i386
endif