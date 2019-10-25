#include <REGX51.H>
sbit dis_en=P3^0;
unsigned char x;
void delayms(unsigned int y);

void main()
{
	TMOD=0x20;
	TH1=0xfd;//9600bps
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	while(1)
	{	
	  x=P0;
		SBUF=x;
	  while(!TI);
		TI=0;
		delayms(2000);
	}
	/*dis_en=1;
	P0=0xaa;
	dis_en=0;
	P0=0xff;
	while(1);*/
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