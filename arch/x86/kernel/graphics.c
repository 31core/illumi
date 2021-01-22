void print(char *str)
{
    static int vga_addr=0xb8000;
    int i=0;
    char *p;
    while(1)
    {
        if(str[i]==(char)0)
        {
            return;
        }
        p=(char*)vga_addr;
        *p=str[i];
        p+=1;
        *p=0x07;
        i+=1;
        vga_addr+=2;
    }
}