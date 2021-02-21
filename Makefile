include config/sources.mk

MAKE=make
QEMU=qemu-system-i386

GCC=gcc
NASM=nasm
LD=ld
DD=dd

ARCH=arch/x86
C_FLAGS=-m32 -Wall -fno-stack-protector -Iinclude

BINS=$(patsubst %.asm,%.bin,$(wildcard $(asm_src)))
OBJS=$(patsubst %.c,%.o,$(wildcard $(c_src)))

default:
	@$(MAKE) -s -C $(ARCH)/boot
	@$(MAKE) -s kernel.sys
	@$(MAKE) -s image
#系统内核文件
kernel.sys:$(BINS) $(OBJS)
	@echo [LD] kernel.sys
	@$(LD) -m elf_i386 -e _start -Ttext 0x100000 $(BINS) $(OBJS) -o kernel.sys

%.bin:%.asm
	@echo [NASM] $@
	@$(NASM) -f elf $*.asm -o $*.bin
%.o:%.c
	@echo [CC] $@
	@$(GCC) $(C_FLAGS) -c $*.c -o $*.o
#内核镜像
image:
	@echo [DD] hda.img
	@$(DD) if=$(ARCH)/boot/boot.bin of=hda.img bs=512 count=1
	@$(DD) if=$(ARCH)/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	@$(DD) if=kernel.sys of=hda.img bs=512 seek=9 count=348

run:
	@$(MAKE) -s default
	$(QEMU) -hda hda.img

clean:
	rm $(BINS) $(OBJS)
	rm kernel.sys
	$(MAKE) -s -C $(ARCH)/boot clean
	rm hda.img
