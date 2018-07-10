#include <reg52.h>
#include "util.h"
#include "SJAhelper.h"

/*************************************************************/
sbit D1 = P1^0;
sbit SJA_RST = P1^2;
/* 验收滤波器的参数，接收所有帧 */
unsigned char SJA_CAN_Filter[] = {
	0x00, 0x00, 0x00, 0x00,				//ACR0~ACR3
	0xff, 0xff, 0xff, 0xff				//AMR0~AMR3
};
unsigned char SJA_CAN_Filter2[] = {
	0x21, 0x10, 0x05, 0x24,				//ACR0~ACR3
	0x00, 0x00, 0x00, 0x03				//AMR0~AMR3
};
unsigned char SJA_SEND_BUFFER[] = {
	0x08,											//标准数据帧，数据长度=8
	0xEA, 0x60,										//帧ID=0x753
	0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa	//帧数据
};
unsigned char SJA_RCV_BUFFER[13];
/*************************************************************/
void TestSJAConnect(void);
void TestSJASend(void);
void TestSJARcv(void);
void TestSJAFilter(void);
/*************************************************************/
void main(void)
{
	TestSJASend();
}
/*************************************************************/
//SJA1000硬件连接测试
void TestSJAConnect(void)
{
	Timer0Init();
	D1 = 0;
	for(;;){
		if(SJAConnectTest() == 1){
			D1 = !D1;
			Timer0Delay(100);
		}else{
			D1 = !D1;
			Timer0Delay(10);
		}
	}
}
//SJA1000发送测试
void TestSJASend(void)
{
	Timer0Init();
	SJA_RST = 0;
	Timer0Delay(50);
	SJA_RST = 1;
	SJAInit(0X00, 0X14, SJA_CAN_Filter);			//初始化SJA1000，设置波特率1Mbps
	for(;;){
		if(SJASendData(SJA_SEND_BUFFER, 0x02)){		//发送数据
			D1 = !D1;
			Timer0Delay(100);
		}else{
			D1 = !D1;
			Timer0Delay(10);
		}			
	}
}

void TestSJARcv(void)
{
	Timer0Init();
	SJA_RST = 1;
	Timer0Delay(50);
	SJA_RST = 0;
	SJAInit(0X00, 0X14, SJA_CAN_Filter);
	for(;;){
		if(SJARcvData(SJA_RCV_BUFFER)){
			D1 = !D1;
			Timer0Delay(100);
		}else{
			D1 = !D1;
			Timer0Delay(10);
		}
	}
}

void TestSJAFilter(void)
{
	Timer0Init();
	SJA_RST = 1;
	Timer0Delay(50);
	SJA_RST = 0;
	SJAInit(0X00, 0X14, SJA_CAN_Filter);
	SJAConfigFilter(1, SJA_CAN_Filter2);
	for(;;){
		if(SJARcvData(SJA_RCV_BUFFER)){
			D1 = !D1;
		}
	}
}
