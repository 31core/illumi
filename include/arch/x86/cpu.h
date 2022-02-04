#define GDT_ADDR (8 * 0x100000 + 0x800) //GDT地址
#define IDT_ADDR (8 * 0x100000) //IDT地址

#define ACC_CODE 0b10011000
#define ACC_DATA 0b10010000
#define ACC_READ 0b0010
#define ACC_WRITE 0b0010

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

void cpu_init(void);
void GDT_set(short, int, int, short);
void IDT_set(char, int, short, char);
void GDTR_load(int, int);
void IDTR_load(int, int);
void io_out8(int, int);
int io_in8(int);
void io_out16(int, int);
int io_in16(int);
void io_cli(void);
void io_sti(void);
void cpu_halt(void);
