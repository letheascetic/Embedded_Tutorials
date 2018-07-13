#include <reg52.h>
#include <stdio.h>
#include "util.h"
#include "SJAhelper.h"

/*************************************************************/
sbit D1 = P1^0;
sbit SJA_RST = P1^2;

unsigned char SJA_CAN_Filter2[] = {
	0x21, 0x10, 0x05, 0x24,				//ACR0~ACR3
	0x00, 0x00, 0x00, 0x03				//AMR0~AMR3
};
/*************************************************************/
void TestSJAConnect(void);
void TestSerialPort(void);
void TsetSJASendRcv(void);
void TestSJASend(void);
void TestSJARcv(void);
void TestSJAFilter(void);
void PrintData(unsigned char *buf, unsigned char len);
/*************************************************************/
void main(void)
{
	TestSJASend();
}
/*************************************************************/
/* 串口输出测试 */
void TestSerialPort(void)
{
	Timer0Init();
	SerialPortInit();
	while(1){
		printf("serial port test!~\n");
		Timer0Delay(100);
	}
}

/* 硬件连接测试 */
void TestSJAConnect(void)
{
	unsigned char write_data, read_data;
	Timer0Init();
	SerialPortInit();
	while(1){
		for(write_data = 0; write_data < 100; write_data++){
			printf("\n**************************************************************\n");
			WriteSJAReg(0x09, write_data);
			read_data = ReadSJAReg(0x09);
			printf("write data: %bu,\t read data: %bu\n", write_data, read_data);
			Timer0Delay(100);
		}
	}
}

/* SJA1000自收发测试 */
//void TsetSJASendRcv(void)
//{
//	unsigned char i;
//	unsigned char len;
//	
//	unsigned char SJA_SEND_DATA[] = {
//		0x08,											//标准数据帧，数据长度=8
//		0xEA, 0x60,										//帧ID=0x753
//		0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa	//帧数据
//	};
//	/* 验收滤波器的参数，接收所有帧 */
//	unsigned char SJA_CAN_Filter[] = {
//		0x00, 0x00, 0x00, 0x00,				//ACR0~ACR3
//		0xff, 0xff, 0xff, 0xff				//AMR0~AMR3
//	};
//	
//	unsigned char SJA_SEND_BUFFER[13], SJA_RCV_BUFFER[13], SJA_RCV_BUFFER_FUNC[13];
//	
//	len = sizeof(SJA_SEND_DATA) / sizeof(unsigned char);
//	
//	/* init */
//	Timer0Init();
//	SerialPortInit();
//	
//	/* reset and init SJA1000 */
//	SJA_RST = 0;
//	Timer0Delay(50);
//	SJA_RST = 1;
//	SJAInit(0x0c, 0x00, 0x14, SJA_CAN_Filter);	//自检测 单滤波 波特率1mbps 接收所有帧
//	
//	for(;;){
//		for(i=0; i<100; i++){
//			printf("\n**************************************************************\n");
//			
//			SJA_SEND_DATA[len-1] = i;
//			
//			SJASendData(SJA_SEND_DATA, 0x02);		//自收发模式
//			printf("sja send data: ");
//			PrintData(SJA_SEND_DATA, len);
//			Timer0Delay(10);
//			
//			ReadSJARegBlock(96, SJA_SEND_BUFFER, len);
//			printf("sja send buffer(at 0x60, read only): ");
//			PrintData(SJA_SEND_BUFFER, len);
//			Timer0Delay(10);
//			
//			ReadSJARegBlock(16, SJA_RCV_BUFFER, len);
//			printf("sja receive buffer(at 0x10): ");
//			PrintData(SJA_RCV_BUFFER, len);
//			Timer0Delay(10);
//			
//			SJARcvData(SJA_RCV_BUFFER_FUNC);
//			printf("sja receive buffer(using SJARcvData func): ");
//			PrintData(SJA_RCV_BUFFER_FUNC, len);
//			Timer0Delay(10);
//			
//			printf("sja ecc reg(at 0x0c): %bu\n", ReadSJAReg(0x0c));
//			printf("sja err warn reg(at 0x0d): %bu\n", ReadSJAReg(0x0d));
//			printf("sja rx error reg(at 0x0e): %bu\n", ReadSJAReg(0x0e));
//			printf("sja tx error reg(at 0x0f): %bu\n", ReadSJAReg(0x0f));
//			Timer0Delay(300);
//		}
//	}
//}

//SJA1000发送测试
void TestSJASend(void)
{
	unsigned char i;
	unsigned char len;
	
	unsigned char SJA_SEND_DATA[] = {
		0x08,											//标准数据帧，数据长度=8
		0xEA, 0x60,										//帧ID=0x753
		0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa	//帧数据
	};
	/* 验收滤波器的参数，接收所有帧 */
	unsigned char SJA_CAN_Filter[] = {
		0x00, 0x00, 0x00, 0x00,				//ACR0~ACR3
		0xff, 0xff, 0xff, 0xff				//AMR0~AMR3
	};
	
	len = sizeof(SJA_SEND_DATA) / sizeof(unsigned char);
	
	/* init */
	Timer0Init();
	SerialPortInit();

	/* reset and init SJA1000 */
	SJA_RST = 0;
	Timer0Delay(50);
	SJA_RST = 1;
	SJAInit(0x08, 0x00, 0x14, SJA_CAN_Filter);	//正常工作 单滤波 波特率1mbps 接收所有帧

	for(;;){
		for(i=0; i<100; i++){
			printf("\n**************************************************************\n");
			SJA_SEND_DATA[len-1] = i+1;
			
			//单次发送模式
			if(SJASendData(SJA_SEND_DATA, 0x01)){
				printf("sja send data success: ");
			}else{
				printf("sja send data failed: ");
			}
			PrintData(SJA_SEND_DATA, len);
			printf("sja ecc reg(at 0x0c): %bu\n", ReadSJAReg(0x0c));
			printf("sja err warn reg(at 0x0d): %bu\n", ReadSJAReg(0x0d));
			printf("sja rx error reg(at 0x0e): %bu\n", ReadSJAReg(0x0e));
			printf("sja tx error reg(at 0x0f): %bu\n", ReadSJAReg(0x0f));
			Timer0Delay(300);
		}
	}
}

//void TestSJARcv(void)
//{
//	Timer0Init();
//	SJA_RST = 1;
//	Timer0Delay(50);
//	SJA_RST = 0;
//	SJAInit(0x00, 0x14, SJA_CAN_Filter);
//	for(;;){
//		if(SJARcvData(SJA_RCV_BUFFER)){
//			D1 = !D1;
//			Timer0Delay(100);
//		}else{
//			D1 = !D1;
//			Timer0Delay(10);
//		}
//	}
//}

//void TestSJAFilter(void)
//{
//	Timer0Init();
//	SJA_RST = 1;
//	Timer0Delay(50);
//	SJA_RST = 0;
//	SJAInit(0x00, 0x14, SJA_CAN_Filter);
//	SJAConfigFilter(1, SJA_CAN_Filter2);
//	for(;;){
//		if(SJARcvData(SJA_RCV_BUFFER)){
//			D1 = !D1;
//		}
//	}
//}

void PrintData(unsigned char *buf, unsigned char len)
{
	int i;
	for(i=0; i<len; i++){
		printf("%bu\t", buf[i]);
	}
	printf("\n");
}

