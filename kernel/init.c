#include <arch/x86/cpu.h>
#include <arch/x86/x86_asm.h>
#include <device/interrupt/init.h>
#include <device/input/keyboard.h>
#include <kernel/fifo.h>
#include <kernel/task.h>
#include <kernel/ipc.h>
#include <kernel/memory.h>
#include <kernel/timer.h>
#include <kernel/random.h>
#include <kernel/fs/init.h>
#include <device/video/cli_print.h>

/* 初始化内核 */
void kernel_init()
{
	fifo_init(&key_fifo, 0, 10);
	timer_init(); //初始化计时器
	task_init(); //初始化多任务
	pipe_init(); //初始化管道(pipe)
	cpu_init(); //初始化cpu相关设定
	PIC_init(); //初始化PIC
	io_sti(); //启用中断
	random_init();
	fs_init(); //初始化文件系统
	/* 初始化内存碎片管理 */
	memfrag_init();
	memfrag_alloc_with_addr(VGA_ADDR, 2 * 80 * 25); //显存
	memfrag_alloc_with_addr(GDT_ADDR, 8 * 0x2000);
	memfrag_alloc_with_addr(IDT_ADDR, 8 * 0x100);
	memfrag_alloc_with_addr(0x100000, 64 * 1024); //为内核分配64 kb空间
}