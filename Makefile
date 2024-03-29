include config/arch.mk
include config/sources.mk
include config/toolchain.mk
include config/env.mk

all:
	@$(MAKE) -s -C $(ARCH_DIR)/boot
	@$(MAKE) -s kernel.bin
	@$(MAKE) -s image
#系统内核文件
kernel.sys:$(kernel_bins) $(kernel_objs)
	@echo "LD  kernel.sys"
	@$(LD) $(LD_FLAGS) $(kernel_bins) $(kernel_objs) -o kernel.sys

kernel.bin:kernel.sys
	objcopy -S -O binary kernel.sys kernel.bin

%.bin:%.S
	@echo "AS  $@"
	@$(AS) $*.S --32 -o $*.bin
%.o:%.c
	@echo "CC  $@"
	@$(CC) $(C_FLAGS) -c $*.c -o $*.o
#内核镜像
image:
	@echo "DD  hda.img"
	dd if=$(ARCH_DIR)/boot/boot.bin of=hda.img bs=512 count=1
	dd if=$(ARCH_DIR)/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	dd if=kernel.bin of=hda.img bs=512 seek=9 count=10240
	qemu-img resize hda.img 10M
#运行
run:
	@$(MAKE) -s all
	@$(QEMU) -drive file=hda.img,format=raw -serial stdio
#清理生成的文件
clean:
	rm $(kernel_bins) $(kernel_objs)
	rm kernel.sys
	rm kernel.bin
	$(MAKE) -s -C $(ARCH_DIR)/boot clean
	rm hda.img
