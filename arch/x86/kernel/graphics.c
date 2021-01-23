void print(int* vga_addr,char *str)
{
	int i=0;
	char *p;
	while(1)
	{
		if(str[i]=='\0')
		{
			return;
		}
		p=(char*)*vga_addr;
		*p=str[i];
		p=(char*)*vga_addr+1;
		*p=(char)0x07;
		i+=1;
		*vga_addr+=2;
	}
}

void putchar(int* vga_addr,char c)
{
	char *p;
	p=(char*)*vga_addr;
	*p=c;
	p=(char*)*vga_addr+1;
	*p=(char)0x07;
	*vga_addr+=2;
}