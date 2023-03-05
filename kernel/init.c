#include <arch/x86/cpu.h>
#include <device/interrupt/init.h>
#include <device/input/keyboard.h>
#include <kernel/page.h>
#include <kernel/user.h>
#include <kernel/task.h>
#include <kernel/pipe.h>
#include <kernel/memory.h>
#include <kernel/timer.h>
#include <kernel/random.h>
#include <kernel/sysinfo.h>
#include <kernel/fs/fs.h>
#include <device/video/cli_print.h>

/* initialize kernel */
void kernel_init(void)
{
	sysinfo_init();
	memfrag_init();
	memfrag_alloc_with_addr((void*)GDT_ADDR, GDT_SIZE);
	memfrag_alloc_with_addr((void*)IDT_ADDR, IDT_SIZE);
	memfrag_alloc_with_addr((void*)0x100000, 4 * 0x100000); //为内核分配4MB空间
	fifo_init(&key_fifo, memfrag_alloc_4k(1), 0x1000);
	page_init();
	task_init();
	cpu_init();
	PIC_init();
	io_sti(); //enable interruption
	random_init();
	fs_init();
	user_init();
}
