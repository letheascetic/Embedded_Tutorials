#include "util.h" 
#include <reg52.h>

#define T0_MASK 0x0F

/*************************************************************
 * 函数名称：TimerDelay
 * 函数功能：通过定时器实现精确延时
 * 输入参数：n 延时的10ms个数
 * 输出参数：无
 * 返回值：  无
 * 注意事项：定时器的中断使能位不能置位
**************************************************************/
void Timer0Init(void)
{
	TMOD &= ~T0_MASK;		//清楚旧设置
	TMOD |= 0x01;			//设置为16位定时模式
}

void Timer0Delay(unsigned int n)
{
	do{
		TL0 = LOW_BYTE(65536UL - CPUCLK / 100);
		TH0 = HIGH_BYTE(65536UL - CPUCLK / 100);
		TR0 = 1;
		while(!TF0);
		TR0 = 0;
		TF0 = 0;
	}while(--n);
}
