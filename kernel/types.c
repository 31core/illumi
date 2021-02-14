#include<kernel/string.h>

void int2str(char *str,int num)
{
    char *str0="          ";
	int check=10;
	int i,j;
    i=9;
    j=0;
	while(num!=0)
	{
		if(num%check==0)
		{
			str0[i]=j+48;
			check*=10;
            i-=1;
            j=0;
		}
		j+=check/10;;
		num-=check/10;;
	}
	strcpy(str0,str);
}