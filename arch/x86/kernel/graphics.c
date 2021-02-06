#define VGA_ADDR 0xb8000

int vga_addr=VGA_ADDR;//显存地址
int screen_x_size=80;//屏幕宽
int screen_y_size=25;//屏幕高
/* 打印字符串 */
void print(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		putchar(str[i]);
		i+=1;
	}
}
/* 打印单字符 */
void putchar(char c)
{
	/* 回车字符处理 */
	if(c=='\n')
	{
		int t=vga_addr-VGA_ADDR;
		t-=t%(2*screen_x_size);
		t+=2*screen_x_size;
		vga_addr=t+VGA_ADDR;
	}
	/* 超出屏幕范围则下滚一行 */
	if((vga_addr-VGA_ADDR+2)>2*screen_x_size*screen_y_size)
	{
		char* i;
		for(i=(char*)VGA_ADDR;i<(char*)(VGA_ADDR+2*screen_x_size*(screen_y_size-1));i++)
		{
			*i=*(i+2*screen_x_size);
		}
		/* 填充最后一行 */
		for(;i<=(char*)(VGA_ADDR+2*screen_x_size*screen_y_size);i++)
		{
			*i=0;//填充0字节
		}
		vga_addr=VGA_ADDR+2*screen_x_size*(screen_y_size-1);//显存指针在最后一行第一字符
	}
	/* 不为回车则打印当前字符 */
	if(c!='\n')
	{
		char* p;
		p=(char*)vga_addr;
		*p=c;
		p=(char*)vga_addr+1;
		*p=0x07;//字体颜色
		vga_addr+=2;//一个字符占2-byte
	}
}
/* 清屏 */
void CleanupScreen()
{
	int i;
	char* p=(char*)VGA_ADDR;
	for(i=2*screen_x_size*screen_y_size;i>0;i--)
	{
		*p=0;//填0字节
		p+=1;
	}
	vga_addr=VGA_ADDR;//重置显存地址
}