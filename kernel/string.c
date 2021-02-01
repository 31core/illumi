/* 获取字符串大小 */
int strlen(char* str)
{
	int i=0;
	while(str[i]!='\0')
	{
		i+=1;
	}
	return i;
}
/* 比较字符串 */
int strcmp(char* a,char* b)
{
	if(strlen(a)!=strlen(b))
	{
		return 0;
	}
	int i=0;
	while(a[i]!='\0')
	{
		if(a[i]!=b[i])
		{
			return 0;
		}
		i+=1;
	}
	return 1;
}
/* 复制字符串 */
void strcpy(char* a,char* b)
{
    int i=0;
    while(a[i]!='\0')
    {
        b[i]=a[i];
        i+=1;
    }
    b[i]='\0';
}