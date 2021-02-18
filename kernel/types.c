#include<kernel/string.h>

/* 整形数字转字符串 */
void int2str(char *str,unsigned int num)
{
	char str0[11];
	int check=10;//用于检测最低位是否为0
	int i,j;
	i=9;//用于从后到前写入str0字符
	j=0;//用于记录最低位的大小
	while(1)
	{
		/* 最低位为0 */
		if(num%check==0)
		{
			str0[i]=j+48;
			check*=10;//最低位为个位、十位以此类推
			i-=1;
			j=0;
			if(num==0)
			{
				break;
			}
		}
		else
		{
			j+=1;
			num-=check/10;
		}
	}
	str_cpy(str,str0+i+1);
}
/* 字符串转整形数字 */
int str2int(char *str)
{
	unsigned int i=0;//i用来累计str数值
	int x,y,t;
	x=0;//用来从高到低取str
	int j=str_len(str)-1;
	while(str[x]!='\0')
	{
		t=str[x]-48;//获取那一位的数字
		/* t=t*10^j */
		for(y=0;y<j;y++)
		{
			t*=10;
		}
		i+=t;
		x+=1;//接下来取str的下一个数字
		j-=1;
	}
	return i;
}