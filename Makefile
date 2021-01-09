MAKE=make
NASN=nasm
LD=ld
QEMU=qemu-system-i386

OBJS=init/main.o

default:
	$(MAKE) -C ./arch/x86/boot
	$(MAKE) -C ./arch/x86/kernel
	$(MAKE) -C ./init
	$(MAKE) img

kernel.sys:
	$(LD) -m elf_i386 -e start arch/x86/kernel/_start.bin $(OBJS) -o kernel.sys

	
img:kernel.sys
	dd if=arch/x86/boot/boot.bin of=hda.img bs=512 count=1
	dd if=arch/x86/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	dd if=kernel.sys of=hda.img bs=512 seek=9 count=348

run:
	$(MAKE) default
	$(QEMU) -hda hda.img

clean:
	rm hda.img
	rm kernel.sys
	$(MAKE) -C ./arch/x86/boot clean
	$(MAKE) -C ./arch/x86/kernel clean
	$(MAKE) -C ./init clean
	