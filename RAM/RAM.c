/*****************这段代码用于CPU访问RAM***************/
#include <REGX52.H>
#include <intrins.h>
sbit rw=P3^0;//读写信号线,输入
sbit rame=P3^1;//读写RAM拓展区，输入
sbit ramen=P3^2;//RAM使能信号，输入
sbit finish=P3^6;//RAM访问结束信号，输出
sbit reg_en=P3^4;//锁存器LE端，锁存信号输出
sbit reg_hr=P3^5;//锁存器高阻输出端
unsigned char addr,Data,x,temp;//flag=0;
unsigned char xdata RAMA[256];//RAM A区，放CPU运算结果
unsigned char data RAMB[64];//RAM B区，大小待定,64Byte
void delayms(unsigned int y);

/************************************
主函数
************************************/
void main()
{
	finish=1;//初始化为1
	reg_hr=1;//锁存器OE端口初始化
	while(1)
	{
		ramen=P3^2;
		while(ramen==0)
		{
			delayms(5);//防止误判
			ramen=P3^2;
			while(ramen==0)
			{
			finish=1;
			rw=P3^0;
			if(rw==1)//读RAM
			{
				rame=P3^1;
				if(rame==1)//A区
				{
					addr=P1;//获取地址
					reg_en=1;//开放
					P2=RAMA[addr];//送出数据
					reg_en=0;//锁存
					temp=RAMA[addr];//灌电流显示，取反操作
					P0=~temp;//显示数据
					finish=0;//结束
				}
				else//B区
				{
					addr=P1;//获取地址
					reg_en=1;//开放
					P2=RAMB[addr];//送出数据
					reg_en=0;//锁存
					temp=RAMB[addr];
					P0=~temp;//显示数据
					finish=0;//结束
				}
			}
			else//写RAM
			{
				rame=P3^1;
				if(rame==1)//A区
				{
					reg_hr=0;
					addr=P1;//获取地址
					Data=P2;//获取数据
					reg_hr=1;
					RAMA[addr]=Data;//写入A区
					temp=RAMA[addr];
					P0=~temp;//显示A区
					finish=0;//结束
				}
				else//B区
				{
					reg_hr=0;
					addr=P1;//获取地址
					Data=P2;//获取数据
					reg_hr=1;
					RAMB[addr]=Data;//写入B区
					temp=RAMB[addr];
					P0=~temp;//显示B区
					finish=0;//结束
				}
			}
		}
	}
 }
}
/***************************************
延时函数
***************************************/
void delayms(unsigned int y)
{
	unsigned char a,b;
	for(a=y;a>0;a--)
	{
		for(b=110;b>0;b--)
		{}
	}
}





