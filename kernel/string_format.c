#include <kernel/types.h>
#include <kernel/string.h>
#include <device/video/graphics.h>

/* 格式化输出 */
void print_format(char *str, ...)
{
	int i = 0;
	int arg = 1;
	while(str[i] != '\0')
	{
		if(str[i] == '%')
		{
			if(str[i + 1] == 's')
			{
				char *str0 = *(&str + arg);
				print(str0);
			}
			else if(str[i + 1] == 'd')
			{
				int int0 = (int)*(&str + arg);
				char str1[50];
				int2str(str1, int0);
				print(str1);
			}
			else if(str[i + 1] == 'u')
			{
				int int0 = (int)*(&str + arg);
				char str1[50];
				uint2str(str1, int0);
				print(str1);
			}
			else if(str[i + 1] == '%')
			{
				printchar('%');
			}
			arg += 1;
			i += 2;
			continue;
		}
		printchar(str[i]);
		i += 1;
	}
}
/* 格式化字符串 */
void string_format(char *ret, char *str, ...)
{
	int i = 0;
	int j = i;
	int arg = 1;
	while(str[i] != '\0')
	{
		if(str[i] == '%')
		{
			if(str[i + 1] == 's')
			{
				char *str0 = *(&str + arg);
				str_cat(ret, str0);
				j += str_len(str0);
			}
			else if(str[i + 1] == 'd')
			{
				int int0 = (int)*(&str + arg);
				char str1[50];
				int2str(str1, int0);
				str_cat(ret, str1);
				j += str_len(str1);
			}
			else if(str[i + 1] == 'u')
			{
				int int0 = (int)*(&str + arg);
				char str1[50];
				uint2str(str1, int0);
				str_cat(ret, str1);
				j += str_len(str1);
			}
			else if(str[i + 1] == '%')
			{
				ret[j] = '%';
				j += 1;
			}
			arg += 1;
			i += 2;
			continue;
		}
		ret[j] = str[i];
		ret[j + 1] = '\0';
		i += 1;
		j += 1;
	}
}