/* 获取内存大小 */
int GetMemorySize()
{
	int *p,old;
	for(p=(int*)0x100000;p<(int*)0xffffffff;p+=4096)
    {
        old=*p;
		*p=0xff00ff00;
		if(*p!=0xff00ff00)
		{
			break;
		}
        *p=old;
	}
	return (int)p;
}