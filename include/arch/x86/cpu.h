#define GDT_ADDR 0x200800 //GDT地址
#define IDT_ADDR 0x200000 //IDT地址

/* GDT数据结构体 */
struct GDT_data
{
	short limit_low, base_low;
	char base_mid, access;
	char limit_high, base_high;
};
/* IDT数据结构体 */
struct IDT_data
{
	short offset_low, selector;
	char count, access;
	short offset_high;
};

void cpu_init();
void GDT_set(short, int, int, short);
void IDT_set(char, int, short, char);