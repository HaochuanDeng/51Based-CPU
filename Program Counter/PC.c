/******************************
给CPU输出PC
******************************/
#include <REGX51.H>
#define initnum 6//T0 方式二的初值
#define initchecknum 3686//检测值
sbit mode=P2^0;//模式选择
sbit clk_ua=P2^1;//手动时钟检测
unsigned int num=0,addr=0;
unsigned char temp;
void delayms(unsigned int z);

void main()
{
	TMOD=0x02;//T0方式2
	TH0=initnum;//装初值
	TL0=initnum;
	ET0=1;//开放T0中断
	IT0=0;//INT0低电平触发
	EX0=1;//开放INT0中断
	IT1=0;//INT1低电平触发
	EX1=1;//开放INT1中断
	EA=1;//开总中断
	P0=(unsigned char)addr;//输出PC
	temp=(unsigned char)addr;//显示PC
	P1=~temp;
	if(mode==0)//自动模式
	{
		TR0=1;//开启T0
		while(1)
		{
			if(num==initchecknum)//1s到
			{
				TR0=0;//关T0
				num=0;
				addr++;
				if(addr==256)
				{
					addr=0;
				}
				P0=(unsigned char)addr;//输出PC
				temp=(unsigned char)addr;//显示PC
	      P1=~temp;
				TR0=1;//开T0
			}
		}
	}
	else//手动模式
	{
		while(1)
		{
			while(clk_ua==0)//按下了
		 {
			delayms(5);//延时
			while(clk_ua==0)//确实按下了
			{
				while(clk_ua==0)//释放检测
				{
					clk_ua=P2^1;
				}
				addr++;
				if(addr==256)
				{
					addr=0;
				}
				P0=(unsigned char)addr;//输出PC
				temp=(unsigned char)addr;//显示PC
	      P1=~temp;
			}
		 }
		}
	}
}

void delayms(unsigned int z)
{
	unsigned int x,y;
	for(x=100;x>0;x--)
	{
		for(y=z;y>0;y--)
		{}
	}
}


void T0_ISR() interrupt 1
{
	num++;
}

void INT0_ISR() interrupt 0//PC++
{
	EA=0;
	addr++;
	if(addr==256)
	{
		addr=0;
	}
	P0=(unsigned char)addr;//输出PC
	temp=(unsigned char)addr;//显示PC
	P1=~temp;
	EA=1;
}

void INT1_ISR() interrupt 2//HALT
{
	EA=0;
	ET0=0;//关T0中断
	EX0=0;//关INT0中断
	EX1=0;//关INT1中断
	TR0=0;//关T0
	while(1);
}