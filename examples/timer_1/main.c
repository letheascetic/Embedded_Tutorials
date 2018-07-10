# include <reg52.h>
# include <intrins.h>

/*
	1 LED1~LED8每隔1秒循环点亮
	2 LED组每循环一次，蜂鸣器鸣一次，鸣1s
	3 每次按键K1按下，从LED1开始重新循环点亮
*/


sbit key = P3^2;
unsigned char data timer_count = 0;
void init();


void main()
{
	init();
	while(1){
		if(timer_count == 10){
			P1 = _crol_(P1, 1);
			timer_count = 0;
		}
	}
}


void init()
{	
	key = 1;
	P1 = 0xFE;
	
	// 设置Timer0
	// 模式1 -> TMOD
	TMOD = 0x01;
	// 装载初始值
	TH0 = (65536 - 46080) / 256;
	TL0 = (65536 - 46080) % 256;
	
	// 设置外部中断0
	// 边沿触发 -> TCON
	IT0 = 1;
	
	// 设置中断使能
	EA = 1;
	ET0 = 1;
	EX0 = 1;
	
	// 启动定时器
	TR0 = 1;
}

void timer0_int() interrupt 1
{
	TH0 = (65536 - 46080) / 256;
	TL0 = (65536 - 46080) % 256;
	++timer_count;	
}


void int0_int() interrupt 0
{
	P1 = 0xFE;
	
	timer_count = 0;
	TH0 = (65536 - 46080) / 256;
	TL0 = (65536 - 46080) % 256;
	
}
