/* 获取字符串大小 */
int str_len(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		i += 1;
	}
	return i;
}
/* 比较字符串 */
int str_cmp(char *a, char *b)
{
	if(str_len(a) != str_len(b))
	{
		return 0;
	}
	int i = 0;
	while(a[i] != '\0')
	{
		if(a[i] != b[i])
		{
			return 0;
		}
		i += 1;
	}
	return 1;
}
/* 复制字符串 */
void str_cpy(char *a, char *b)
{
	int i = 0;
	while(b[i] != '\0')
	{
		a[i] = b[i];
		i += 1;
	}
	a[i] = '\0';
}
/* 分割字符串 */
void str_split(char *ret, char *str, char byte, int count)
{
	int i = 0;
	int j = 0;
	/* 查找第n个字符串开始位置 */
	while(j < count)
	{
		if(str[i] == byte)
		{
			j += 1;
		}
		if(str[i] == '\0')
		{
			ret[0] = '\0';
			return;
		}
		i += 1;
	}
	j = 0;
	/* 复制字符串 */
	while(str[i] != byte && str[i] != '\0')
	{
		ret[j] = str[i];
		i += 1;
		j += 1;
	}
	ret[j] = '\0'; //字符串结尾标志
}