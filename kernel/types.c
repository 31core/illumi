#include<kernel/string.h>

/* 整形数字转字符串 */
void int2str(char *str,int num)
{
	char *str0="          ";
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
	str0+=i+1;
	strcpy(str,str0);
}