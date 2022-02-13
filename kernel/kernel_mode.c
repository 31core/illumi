#include <kernel/page.h>
#include <kernel/task.h>

/* 进入内核模式 */
void kernel_mode(void)
{
	task_save_state(&task_list[current_proc].state);
	task_load_state(&task_list[0].state);
	page_switch(kernel_page_dir);
}
/* 进入用户模式 */
void user_mode(void)
{
	task_save_state(&task_list[0].state);
	task_load_state(&task_list[current_proc].state);
	page_switch(task_list[current_proc].page_dir);
}
