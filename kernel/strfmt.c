#include <lib/types.h>
#include <lib/args.h>
#include <lib/string.h>
#include <device/video/cli_print.h>

/* 格式化输出 */
void printfmt(char *str, ...)
{
	int i = 0;
	struct arg arg;
	arg_init(&arg, &str);
	while(str[i] != '\0')
	{
		if(str[i] == '%')
		{
			if(str[i + 1] == 's')
			{
				char *str0;
				arg_get_next(&arg, &str0, sizeof(str0));
				cli_print(str0);
			}
			else if(str[i + 1] == 'd')
			{
				int int0;
				arg_get_next(&arg, &int0, sizeof(int0));
				char str1[50];
				int2str(str1, int0);
				cli_print(str1);
			}
			else if(str[i + 1] == 'u')
			{
				int int0;
				arg_get_next(&arg, &int0, sizeof(int0));
				char str1[50];
				uint2str(str1, int0);
				cli_print(str1);
			}
			else if(str[i + 1] == '%')
			{
				cli_print_char('%');
			}
			i += 2;
			continue;
		}
		cli_print_char(str[i]);
		i += 1;
	}
}
/* 格式化字符串 */
void strfmt(char *ret, char *str, ...)
{
	int i = 0;
	int j = i;
	struct arg arg;
	arg_init(&arg, &str);
	while(str[i] != '\0')
	{
		if(str[i] == '%')
		{
			if(str[i + 1] == 's')
			{
				char *str0;
				arg_get_next(&arg, &str0, sizeof(str0));
				str_cat(ret, str0);
				j += str_len(str0);
			}
			else if(str[i + 1] == 'd')
			{
				int int0;
				arg_get_next(&arg, &int0, sizeof(int0));
				char str1[50];
				int2str(str1, int0);
				str_cat(ret, str1);
				j += str_len(str1);
			}
			else if(str[i + 1] == 'u')
			{
				int int0;
				arg_get_next(&arg, &int0, sizeof(int0));
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
			i += 2;
			continue;
		}
		ret[j] = str[i];
		ret[j + 1] = '\0';
		i += 1;
		j += 1;
	}
}