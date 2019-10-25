/****This code is usded to store CODE A B for cpu to process*********/
#include <REGX51.H>
#include <intrins.h>
#define RdCommand 0x01//定义ISP操作命令
#define PrgCommand 0x02
#define EraseCommand 0x03
#define Error 1
#define Ok 0
#define WaitTime 0x01
sfr ISP_DATA=0xe2;//ISP特殊功能寄存器
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTER=0xe7;
sbit led_done=P3^1;//写入完成led
sbit Flag=P3^0;//模式选择
sbit led_finaldone=P3^4;//写入EEPROM完成
unsigned char flag;//模式标志
unsigned int addr=0,y;//待写入数据的地址
unsigned char addr_p,data_p,temp;//读信息
unsigned char xdata container[256];//装入A_B_CODE,放入RAM拓展区（256BYTE）
void byte_write(unsigned int byte_adddr,unsigned char original_data);
void SectorErase(unsigned int sector_addr);
unsigned char byte_read(unsigned int byte_addr);
void ISPgoon(void);
void ISP_IAP_disable(void);
void ISP_IAP_enable(void);
void load_RAM();
void delayms(unsigned int ms);
/*******************************
主函数
*******************************/
void main()
{
	flag=Flag;//读模式
	for(y=0;y<256;y++)//A_B_CODE清零
		{
			container[y]=0x00;
		}
	if(flag==0)//程序数据发送
	{
		load_RAM();//装载数组
		while(1)
		{
			addr=P0;//读P0口，获得addr
			P1=container[addr];//送出A_B_CODE
			temp=container[addr];//取反操作
			P2=~temp;//显示A_B_CODE
		}
	}
	else//写A_B_CODE
	{
		IT0=0;//INTO低电平触发
		IT1=0;//INT1低电平触发
		EX0=1;//INT0中断
		EX1=1;//INT1中断
		EA=1;//开总中断
		while(1)//等待中断
		{
			led_done=1;//关闭LED
			led_finaldone=1;//关闭LED
		}
	}
}
/*********************************
打开ISP/IAP功能
*********************************/
void ISP_IAP_enable(void)
{
	EA=0;//防止被打断
	ISP_CONTER=ISP_CONTER&0x18;//0001,1000
	ISP_CONTER=ISP_CONTER|WaitTime;//写入硬件延时
	ISP_CONTER=ISP_CONTER|0x80;//ISPEN=1
}
/*********************************
关闭ISP/IAP功能
*********************************/
void ISP_IAP_disable(void)
{
	ISP_CONTER=ISP_CONTER&0x7f;//ISPEN=0
	ISP_TRIG=0x00;
	EA=1;
}
/*********************************
触发代码
*********************************/
void ISPgoon(void)
{
	ISP_IAP_enable();//开ISP_IAP
	ISP_TRIG=0x46;//触发ISP_IAP命令字节1
	ISP_TRIG=0xb9;//触发ISP_IAP命令字节2
	_nop_();//延时一个机器周期
}
/*********************************
字节读
*********************************/
unsigned char byte_read(unsigned int byte_addr)
{
	ISP_ADDRH=(unsigned char)(byte_addr>>8);//地址赋值
	ISP_ADDRL=(unsigned char)(byte_addr&0x00ff);
	ISP_CMD=ISP_CMD&0xf8;//清除低三位
	ISP_CMD=ISP_CMD|RdCommand;//写入读命令
	ISPgoon();//触发
	ISP_IAP_disable();//关闭ISP/IAP功能
	return(ISP_DATA);//返回读到的数据
}
/*********************************
扇区擦除
*********************************/
void SectorErase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr=(sector_addr&0xfe00);//取扇区地址
	ISP_ADDRH=(unsigned char)(iSectorAddr>>8);
	ISP_ADDRL=0x00;
	ISP_CMD=ISP_CMD&0xf8;//清空低三位
	ISP_CMD=ISP_CMD|EraseCommand;//擦除命令三
	ISPgoon();//触发
	ISP_IAP_disable();//关闭ISP/IAP功能
}
/*********************************
字节写
*********************************/
void byte_write(unsigned int byte_addr,unsigned char original_data)
{
	ISP_ADDRH=(unsigned char)(byte_addr>>8);  //取地址
	ISP_ADDRL=(unsigned char)(byte_addr&0x00ff);
	ISP_CMD=ISP_CMD&0xf8;//清低三位
	ISP_CMD=ISP_CMD|PrgCommand;//写命令2
	ISP_DATA=original_data;//写入数据
	ISPgoon();//触发
	ISP_IAP_disable();////关闭ISP/IAP功能
}
/******************************************
装载入RAM,将EEPROM第一扇区低256byte读入数组
*******************************************/
void load_RAM()
{
	unsigned int x;
	for(x=0;x<256;x++)//读EEPROM
	{
		container[x]=byte_read(0x2000+x);
	}
}
/********************************
外部中断0，写入container
**********************************/
void INT0_ISR() interrupt 0
{
	EA=0;
	delayms(200);
	addr_p=P0;//地址
	data_p=P1;//数据
	container[addr_p]=data_p;//写入
	led_done=0;//led亮
	delayms(200);
	EA=1;
}
/**********************************
外部中断1，RAM写入EEPROM
**********************************/
void INT1_ISR() interrupt 2
{
	unsigned int z;
	unsigned char temp1;
	EA=0;
	delayms(200);
	SectorErase(0x2000);//擦除第一扇区
	for(z=0;z<256;z++)//写256byte入EEPROM
	{
		temp1=container[z];
		byte_write((0x2000+z),temp1);
	}
	led_finaldone=0;//写入完成
	delayms(200);
	EA=1;
}
/*********************************
延时函数
*********************************/
void delayms(unsigned int ms)
{
	unsigned int j,k;
	for(j = ms;j > 0;j--)
	{
		for(k = 110;k > 0;k--)
		{
		}
	}
}
















