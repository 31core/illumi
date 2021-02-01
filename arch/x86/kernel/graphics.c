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
	if(c=='\n')//回车
	{
		int t=vga_addr-VGA_ADDR;
		t-=t%(2*screen_x_size);
		t+=2*screen_x_size;
		vga_addr=t+VGA_ADDR;
		return;
	}
	char *p;
	p=(char*)vga_addr;
	*p=c;
	p=(char*)vga_addr+1;
	*p=(char)0x07;
	vga_addr+=2;//一个字符占2-byte
}
/* 清屏 */
void CleanupScreen()
{
	int i;
	char* p=(char*)VGA_ADDR;
	for(i=2*screen_x_size*screen_y_size;i>0;i--)
	{
		*p=(char)0;//填0字节
		p+=1;
	}
	vga_addr=VGA_ADDR;//重置显存地址
}