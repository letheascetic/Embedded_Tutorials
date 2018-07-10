#include <reg52.h>
#include <absacc.h>
#include<intrins.h>

sbit select_seg = P2^7;
sbit select_data = P2^6;

sbit s2=P3^4;
sbit beep=P2^3;

void delay(unsigned char i);

void main()
{	
//	unsigned char start = 0xfe;
//	
//	select_seg = 0;
//	select_data = 0;
		
	while(1){
		
		if(!s2)
			beep=0;
		else
			beep=1;
		
//		P0 = 0x4f;
//		select_data = 1;
//		select_data = 0;
//		
//		P0 = start;
//		select_seg = 1;
//		select_seg = 0;
//		
//		start = _crol_(start, 1);
//		delay(5);
	}
}

// n*100ms
void delay(unsigned char n)
{	
	unsigned int i;
	while(n--){
		for(i=10000;i>0;i--);
	}
}