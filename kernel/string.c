/* 获取字符串大小 */
int str_len(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		i+=1;
	}
	return i;
}
/* 比较字符串 */
int str_cmp(char *a,char *b)
{
	if(str_len(a)!=str_len(b))
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
void str_cpy(char *a,char *b)
{
	int i=0;
	while(b[i]!='\0')
	{
		a[i]=b[i];
		i+=1;
	}
	a[i]='\0';
}