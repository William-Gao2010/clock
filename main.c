#include <STC89C5xRC.H>
#include "intrins.H"

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;
sbit Beep = P1^5;

#define ACycle 60
#define None 0

unsigned char sec , min;

unsigned char disp_num[17]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
};

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void Delay5ms(unsigned char num)		//@11.0592MHz
{
	while(num--)
	{		
	unsigned char i, j;

			i = 9;
			j = 244;
			do
			{
				while (--j);
			} while (--i);
		}
}


void disp(unsigned char byte,n)
{
	if(byte==3)
	{
		LSA = 0; LSB = 1; LSC = 0;
		P0 = disp_num[n];
	}
	
	if(byte==2)
	{
		LSA = 1; LSB = 1; LSC = 0;
		P0 = disp_num[n];
	}
	
	if(byte==1)
	{
		LSA = 0; LSB = 0; LSC = 1;
		P0 = disp_num[n];
	}
}

void clock(unsigned char second,min)
{
	disp(1,min);
	Delay5ms(1);
	disp(2,second/10);
	Delay5ms(1);
	disp(3,second%10);
	Delay5ms(1);
}

void main()
{
	Timer0Init();
	while(1)
	{
		clock(sec,min);
	}
}

void Timer() interrupt 1
{
	unsigned char i;
	i++;
	if(i>=100)
	{
		sec++;  i=0;  
		if(sec>=60)
		{
			min++; sec=0;
			if(min>=1)
			{
				min=0;
			}
		}
	}
		
}
