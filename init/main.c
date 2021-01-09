void main()
{
	char *p;
	p=(char *)0xb8000;
	*p='A';
	p=(char *)0xb8001;
	*p=0x07;
}