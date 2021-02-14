/* 获取内存大小 */
int GetMemorySize()
{
	char *p,old;
	for(p=(char*)0x10000;p<(char*)0xffffffff;p+=4096)
    {
        old=*p;
		*p=0xff;
		if(*p!=0xff)
		{
			break;
		}
        *p=old;
	}
	return (int)p;
}