C_FLAGS = -Wall -fno-stack-protector -Iinclude
LD_FLAGS = -e _start -Ttext 0x100000
ifeq ($(ARCH), x86)
	C_FLAGS += -m32
	LD_FLAGS += -m elf_i386
endif
