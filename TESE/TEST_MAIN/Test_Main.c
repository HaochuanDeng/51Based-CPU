#include <REGX52.H>
sbit flag=P1^2;
sbit ram_data_in_hr=P2^1;
sbit ram_data_out_en=P2^2;
sbit ram_addr_out_en=P2^3;
sbit ram_e=P2^4;
sbit ram_en=P2^5;
sbit ram_finish=P2^6;
sbit ram_rw=P2^7;
void delayms(unsigned int y);

void main()
{
	ram_en=1;//初始化RAM使能信号
	flag=1;//初始化LED
	ram_rw=0;//写
	ram_e=0;//B
	ram_addr_out_en=1;
	P0=0x01;
	ram_addr_out_en=0;
	ram_data_out_en=1;
	P0=0x02;
	ram_data_out_en=0;
	
	ram_en=0;
	delayms(100);
	ram_en=1;
	
  ram_finish=P2^6;//操作完毕?
	while(ram_finish==1)
	{
		ram_finish=P2^6;
	}

	flag=0;
	delayms(3000);
	flag=1;
	while(1);
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