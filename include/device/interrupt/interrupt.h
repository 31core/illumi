extern unsigned int time_count;/* 记录经过的时间 */
extern unsigned int timer_list[1000];
extern int timer_num;

void asm_interrupt20h(void);
void asm_interrupt21h(void);
