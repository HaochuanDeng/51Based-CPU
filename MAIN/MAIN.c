/************控制器*****************/
#include <REGX52.H>
#include <intrins.h>
sbit halt=P1^0;
sbit PC=P1^1;
sbit floatout=P1^2;
sbit code_hr=P1^3;
sbit code_en=P1^4;
sbit a_en=P1^5;
sbit a_hr=P1^6;
sbit b_hr=P1^7;
sbit b_en=P2^0;
sbit ram_data_in_hr=P2^1;
sbit ram_data_out_en=P2^2;
sbit ram_addr_out_en=P2^3;
sbit ram_e=P2^4;
sbit ram_en=P2^5;
sbit ram_finish=P2^6;
sbit ram_rw=P2^7;
sbit pc_hr=P3^1;
sbit pc_en=P3^2;
unsigned char pc=0,pc_new=0,code_,a=0,b=0,c=0,data_,addr,finish,x,flag=1;
void initIO();
void delayms(unsigned int y);

void main()
{
	initIO();//初始化IO口
	while(1)
	{
		while(flag)//判断有无新的PC
		{
			pc_hr=0;//读PC
			pc_en=1;
			pc_en=0;
			pc_new=P0;
			pc_hr=1;
			if(pc_new==pc)//pc没变
			{
			}
			else//pc变了
			{
				pc=pc_new;
				flag=0;
			}
		}
		flag=1;
		code_hr=0;//读CODE
		code_en=1;
		code_en=0;
		code_=P0;
		code_hr=1;
		switch(code_)
		{
		 case 0x01://A+B
			a_hr=0;//读A
			a_en=1;
		  a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
		  b_en=0;
			b=P0;
			b_hr=1;
			
			c=a+b;
			floatout=~CY;
		 
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x02://A-B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a-b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x03://A%B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a%b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x04://a/b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a/b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x05://a*b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a*b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x06://a+b_p
			c=a+b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x07://a-b_p
			c=a-b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x08://a%b_p
			c=a%b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x09://a/b_p
			c=a/b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0a://a*b_p
			c=a*b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0b://a<<b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a<<b;
      floatout=~CY;			
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0c://a>>b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a>>b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0d://a<b,循环左移，下同
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=_crol_(a,b);
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0e://a>b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=_cror_(a,b);
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x0f://a and b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a&b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x10://a or b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a|b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x11://~a
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			c=~a;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x12://a 按位同或 b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a^b;
			c=~c;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x13://a 按位异或 b
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			c=a^b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x14://a<<b_P
			c=a<<b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x15://a>>b_p
			c=a>>b;
			floatout=~CY;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x16://a<b_p
			c=_crol_(a,b);
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x17://a>b_p
			c=_cror_(a,b);
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x18://a and b_p
			c=a&b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x19://a or b_p
			c=a|b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x1a://~a_p
			c=~a;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x1b://a 按位同或 b
			c=a^b;
			c=~c;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x1c://a 按位异或b
			c=a^b;
			floatout=1;
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=pc;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=c;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			break;
			
			case 0x1d://halt
      halt=0;
      halt=1;
			floatout=1;
			break;
			
			case 0x1e://load_a
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			floatout=1;
			break;
			
			case 0x1f://load_b
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			floatout=1;
			break;
			
			case 0x20://wRAM
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			//写ram
			ram_rw=0;//写
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=b;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			floatout=1;
			break;
			
			case 0x21://wRAMe
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			//写ram
			ram_rw=0;//写
			ram_e=0;//B
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			ram_data_out_en=1;
			P0=b;
			ram_data_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			floatout=1;
			break;
			
			case 0x22://rRAM_A
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_data_in_hr=0;
			ram_rw=1;//读
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			
			a=P0;//读到的数据
			ram_data_in_hr=1;
			floatout=1;
			break;
			
			case 0x23://rRAM_B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_data_in_hr=0;
			ram_rw=1;//读
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			
			b=P0;//读到的数据
			ram_data_in_hr=1;
			floatout=1;
			break;
			
			case 0x24://rRAMe_A
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_data_in_hr=0;
			ram_rw=1;//读
			ram_e=0;//B
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			
			a=P0;//读到的数据
			ram_data_in_hr=1;
			floatout=1;
			break;
			
			case 0x25://rRAMe_B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_data_in_hr=0;
			ram_rw=1;//读
			ram_e=0;//B
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			
			b=P0;//读到的数据
			ram_data_in_hr=1;
			floatout=1;
			break;
			
			case 0x26://DIS_RAM
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_rw=1;//读
			ram_e=1;//A
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			floatout=1;
			break;
			
			case 0x27://DIS_RAMe
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			//读RAM
			ram_rw=1;//读
			ram_e=0;//B
			ram_addr_out_en=1;
			P0=a;
			ram_addr_out_en=0;
			
			ram_en=0;
	    delayms(100);
	    ram_en=1;
			
			ram_finish=P2^6;//操作完毕?
			while(ram_finish)
			{
				ram_finish=P2^6;
			}
			floatout=1;
			break;
			
			case 0x28://GOTO_A
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			for(x=a;x>0;x--)//跳转
		  {
				PC=0;
				PC=1;
				delayms(10);//PC中断函数执行时间，下同
			}
			floatout=1;
			break;
			
			case 0x29://JUMP A>B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			if(a>b)
			{
			}
			else
			{
				for(x=2;x>0;x--)//跳转
				{
				  PC=0;
				  PC=1;
				  delayms(10);
				}
			}
			floatout=1;
			break;
			
			case 0x2a://JUMP A=B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			if(a==b)
			{
			}
			else
			{
				for(x=2;x>0;x--)//跳转
				{
				  PC=0;
				  PC=1;
				  delayms(10);
				}
			}
			floatout=1;
			break;
			
			case 0x2b://JUMP A<B
			a_hr=0;//读A
			a_en=1;
			a_en=0;
			a=P0;
			a_hr=1;
			
			b_hr=0;//读B
			b_en=1;
			b_en=0;
			b=P0;
			b_hr=1;
			
			if(a<b)
			{
			}
			else
			{
				for(x=2;x>0;x--)//跳转
				{
				  PC=0;
				  PC=1;
				  delayms(10);
				}
			}
			floatout=1;
			break;
			
			default://0x00
			break;
		}
	}
}
//初始化IO口
void initIO()
{
	halt=1;
	PC=1;
	floatout=1;
	code_hr=1;
	code_en=0;
	a_en=0;
	a_hr=1;
	b_hr=1;
	b_en=0;
	ram_data_in_hr=1;
	ram_data_out_en=0;
	ram_addr_out_en=0;
	ram_e=1;
	ram_en=1;
	ram_rw=1;
	pc_hr=1;
	pc_en=0;
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