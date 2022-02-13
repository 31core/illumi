C_FLAGS = -Wall -fno-stack-protector -Iinclude
LD_FLAGS = -e _start -Ttext 0x800000
ifeq ($(ARCH), x86)
	C_FLAGS += -m32
	LD_FLAGS += -m elf_i386
endif
#是否启用KVM
ifeq ($(KVM), y)
	QEMU += -enable-kvm
endif