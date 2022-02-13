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
		return -1;
	}
	int i = 0;
	while(a[i] != '\0')
	{
		if(a[i] != b[i])
		{
			return -1;
		}
		i += 1;
	}
	return 0;
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
/* 拼接字符串 */
void str_cat(char *a, char *b)
{
	int i = str_len(a);
	int j = 0;
	while(b[j] != '\0')
	{
		a[i] = b[j];
		i += 1;
		j += 1;
	}
	a[i] = '\0';
}
/* 查找字符串 */
int str_find(char *origin, char *str, int index)
{
	int size = str_len(origin) - str_len(str);
	for(int i = 0; i <= size; i++)
	{
		/* 测试origin[i]处是否匹配str */
		int j = 0;
		while(str[j] != '\0')
		{
			if(origin[i + j] != str[j])
			{
				break;
			}
			j += 1;
		}
		/* origin[i]处匹配str */
		if(j == str_len(str))
		{
			index -= 1;
		}
		if(index == -1)
		{
			return i; //返回字符串位置
		}
	}
	return -1;
}
/* 统计字符串中出现字符串次数 */
int str_count(char *origin, char *str)
{
	int count = 0;
	int len = str_len(str);
	while(1)
	{
		int i = str_find(origin, str, 0);
		if(i == -1)
		{
			break;
		}
		count += 1;
		origin += len + i;
	}
	return count;
}
/* 分割字符串 */
void str_split(char *ret, char *str, char *symbol, int index)
{
	int start = 0;
	/* 获取原字符串开始位置 */
	if(index != 0)
	{
		start = str_find(str, symbol, index - 1) + str_len(symbol);
	}
	int end = str_find(str, symbol, index); //获取原字符串结束位置
	if(end == -1)
	{
		end = str_len(str);
	}
	int i = 0;
	/* 复制字符串 */
	while(start < end)
	{
		ret[i] = str[start];
		start += 1;
		i += 1;
	}
	ret[i] = '\0'; //字符串结尾标志
}
/* 字符串切片 */
void str_slice(char *ret, char *src, int start, int end)
{
	char str[100];
	str_cpy(str, src);
	str[end + 1] = '\0';
	str_cpy(ret, str + start);
}
/* 替换字符串 */
void str_replace(char *str, char *a, char *b)
{
	int len_a = str_len(a);
	int len_b = str_len(b);
	char bak[100];
	while(1)
	{
		int i = str_find(str, a, 0);
		if(i == -1)
		{
			break;
		}
		str_cpy(bak, str + len_a + i);
		str_cpy(str + i, b);
		str_cat(str, bak);
		str += len_b + i;
	}
}
