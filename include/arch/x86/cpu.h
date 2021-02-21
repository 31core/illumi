#define GDT_ADDR 0x270000
#define IDT_ADDR 0x26f800

/* GDT数据结构体 */
struct GDT_data
{
	short limit_low,base_low;
	char base_mid,access;
	char limit_high,base_high;
};
/* IDT数据结构体 */
struct IDT_data
{
	short offset_low,selector;
	char count,access;
	short offset_high;
};

void init_dsctbl();
void SetGDT(short,int,int,short);//设置GDT数据
void SetIDT(char,int,short,char);//设置GDT数据