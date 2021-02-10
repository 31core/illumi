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
void SetGDT(struct GDT_data*,int,int,int);//设置GDT数据
void SetIDT(struct IDT_data*,int,int,int);//设置GDT数据