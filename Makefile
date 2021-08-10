include config/arch.mk
include config/sources.mk
include config/toolchain.mk
include config/env.mk

all:
	@$(MAKE) -s -C $(ARCH_DIR)/boot
	@$(MAKE) -s kernel.sys
	@$(MAKE) -s image
#系统内核文件
kernel.sys:$(kernel_bins) $(kernel_objs)
	@echo "LD  kernel.sys"
	@$(LD) $(LD_FLAGS) $(kernel_bins) $(kernel_objs) -o kernel.sys

%.bin:%.asm
	@echo "AS  $@"
	@$(AS) -f elf $*.asm -o $*.bin
%.o:%.c
	@echo "CC  $@"
	@$(CC) $(C_FLAGS) -c $*.c -o $*.o
#内核镜像
image:
	@echo "DD  hda.img"
	@$(DD) if=$(ARCH_DIR)/boot/boot.bin of=hda.img bs=512 count=1
	@$(DD) if=$(ARCH_DIR)/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	@$(DD) if=kernel.sys of=hda.img bs=512 seek=9 count=348
#运行
run:
	@$(MAKE) -s all
	@$(QEMU) -drive file=hda.img,format=raw
#清理生成的文件
clean:
	rm $(kernel_bins) $(kernel_objs)
	rm kernel.sys
	$(MAKE) -s -C $(ARCH_DIR)/boot clean
	rm hda.img
