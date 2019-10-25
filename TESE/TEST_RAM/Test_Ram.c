#include <REGX51.H>
unsigned char temp;
void delayms(unsigned int y);

void main()
{
	IT0=0;//INT0低电平触发
	EX0=1;//开放INT0中断
	EA=1;//开总中断
	while(1)
	{
		temp=P3;
		P0=~temp;
	}
}

void INTO_ISR() interrupt 0
{
	EA=0;
	P0^0=0;
	delayms(2000);
	P0^0=1;
	EA=1;
}
void delayms(unsigned int y)
{
	unsigned char a,b;
	for(a=y;a>0;a--)
	{
		for(b=110;b>0;b--)
		{}
	}
}