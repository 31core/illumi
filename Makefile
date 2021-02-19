include sources.mk

MAKE=make
QEMU=qemu-system-i386

ARCH=arch/x86

BINS=$(patsubst %.asm,%.bin,$(wildcard $(asm_src)))
OBJS=$(patsubst %.c,%.o,$(wildcard $(c_src)))

default:
	@$(MAKE) -s -C $(ARCH)
	@$(MAKE) -s -C kernel
	@$(MAKE) -s -C device
	@$(MAKE) -s -C init
	@$(MAKE) -s kernel.sys
	@$(MAKE) -s image
#系统内核文件
kernel.sys:
	@echo [LD] kernel.sys
	@ld -m elf_i386 -e _start -Ttext 0x100000 $(BINS) $(OBJS) -o kernel.sys
#内核镜像
image:
	@echo [DD] hda.img
	@dd if=$(ARCH)/boot/boot.bin of=hda.img bs=512 count=1
	@dd if=$(ARCH)/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	@dd if=kernel.sys of=hda.img bs=512 seek=9 count=348

run:
	@$(MAKE) -s default
	$(QEMU) -hda hda.img

clean:
	rm hda.img
	rm kernel.sys
	rm $(BINS) $(OBJS)
	$(MAKE) -s -C $(ARCH)/boot clean
