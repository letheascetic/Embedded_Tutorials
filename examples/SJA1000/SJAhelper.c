#include "SJAhelper.h"
#include "SJA1000REG.h"
#include <reg52.h>

#define SJA_BASE_ADDR 0x7f00
#define STD_FRAMEID_LENTH 2
#define EXT_FRAMEID_LENTH 4

sbit CS = P2^7;																//SJA1000片选，低电平使能
unsigned char xdata *SJA_CS_Point = (unsigned char xdata *)SJA_BASE_ADDR;	//指针指向片外数据存储区

/*************************************************************
 * 写SJA1000寄存器
**************************************************************/
void WriteSJAReg(unsigned char regAdr, unsigned char value)
{
	*(SJA_CS_Point + regAdr) = value;
}

/*************************************************************
 * 写SJA1000寄存器
**************************************************************/
unsigned char ReadSJAReg(unsigned char regAdr)
{
	return (*(SJA_CS_Point + regAdr));
}

/*************************************************************
 * 函数名称：SetBitMask
 * 函数功能：设置指定寄存器的指定位为1
 * 输入参数：regAdr 寄存器地址
 * 			 bitValue 设置的位值
 * 输出参数：无
 * 返回值：  1=操作成功，0=操作失败
**************************************************************/
unsigned char SetBitMask(unsigned char regAdr, unsigned char bitValue)
{
	unsigned char status;
	unsigned char value;
	
	value = ReadSJAReg(regAdr);
	value = value | bitValue;
	WriteSJAReg(regAdr, value);
	
	status = ReadSJAReg(regAdr) == value ? 1 : 0;
	return status;
}

/*************************************************************
 * 函数名称：ClearBitMask
 * 函数功能：将指定寄存器的指定位清零
 * 输入参数：regAdr 寄存器地址
* 			 bitValue 设置的位值(bitValue中为1的位，对应的位被清零)
 * 输出参数：无
 * 返回值：  1=操作成功，0=操作失败
**************************************************************/
unsigned char ClearBitMask(unsigned char regAdr, unsigned char bitValue)
{
	unsigned char status;
	unsigned char value;
	
	value = ReadSJAReg(regAdr);
	value = value & (~bitValue);
	WriteSJAReg(regAdr, value);
	
	status = ReadSJAReg(regAdr) == value ? 1 : 0;
	return status;
}

/*************************************************************
 * 函数名称：WriteSJARegBlock
 * 函数功能：连续写多个寄存器
 * 输入参数：regAdr   寄存器起始地址
 * 			 valueBuf 写寄存器时使用的指针
 * 			 len 	  要连续写入的寄存器数
 * 输出参数：无
 * 返回值：  连续写入的寄存器数
**************************************************************/
unsigned char WriteSJARegBlock(unsigned char regAdr, unsigned char *valueBuf, unsigned char len)
{
	unsigned char i;
	for(i=0; i<len; i++){
		WriteSJAReg(regAdr + i, valueBuf[i]);
	}
	return (len > 0 ? i+1 : i);
}

/*************************************************************
 * 函数名称：ReadSJARegBlock
 * 函数功能：连续读多个寄存器
 * 输入参数：regAdr   寄存器起始地址
 * 			 valueBuf 读寄存器时使用的指针
 * 			 len 	  要连续读出的寄存器数
 * 输出参数：无
 * 返回值：  连续读到的寄存器数
**************************************************************/
unsigned char ReadSJARegBlock(unsigned char regAdr, unsigned char *valueBuf, unsigned char len)
{
	unsigned char i;
	for(i=0; i<len; i++){
		valueBuf[i] = ReadSJAReg(regAdr + i);
	}
	return (len > 0 ? i+1 : i);
}

/*************************************************************
 * 函数名称：SJAConnectTest
 * 函数功能：测试函数，验证主控制器和SJA1000的硬件连接
 * 输入参数：无
 * 输出参数：无
 * 返回值：  1=硬件连接正常，可以通信；0=通信故障
**************************************************************/
//unsigned char SJAConnectTest(void)
//{
//	unsigned char status;
//	WriteSJAReg(REG_CAN_TEST, 0x55);
//	status = ReadSJAReg(REG_CAN_TEST) == 0x55 ? 1 : 0;
//	return status;
//}

/*************************************************************
 * 函数名称：SJAInit
 * 函数功能：CAN控制器初始化函数
 * 输入参数：brt0   总线定时器0
 *			 btr1   总线定时器1
 * 			 filter 滤波器设置指针
 * 输出参数：无
 * 返回值：  无
**************************************************************/
void SJAInit(unsigned char mode, unsigned char btr0, unsigned char btr1, unsigned char *filter)
{
	SetBitMask(REG_CAN_MODE, RM_RR_BIT);	//进入复位模式
	WriteSJAReg(REG_CAN_CDR, 0x88);         //设置分配寄存器（10001000）PeliCAN模式 
											//CBP=0,CLKOff_BIT=1 不激活比较器旁路(建议激活)，不输出时钟
	//WriteSJAReg(REG_CAN_MODE, 0x0d);		//AFM=1,STM=1 单滤波模式 只检测模式
	WriteSJARegBlock(REG_CAN_ACR0, filter, 8);	//配置验收代码/屏蔽寄存器
	WriteSJAReg(REG_CAN_BTR0, btr0);			//配置总线定时器0
	WriteSJAReg(REG_CAN_BTR1, btr1);			//配置总线定时器1
	WriteSJAReg(REG_CAN_OCR, 0x1A);				//配置输出引脚为TX0和RX0，推挽模式
	//SetBitMask(REG_CAN_MODE, STM_BIT | AFM_BIT);
	SetBitMask(REG_CAN_MODE, mode);
	ClearBitMask(REG_CAN_MODE, RM_RR_BIT);		//退出复位模式，进入工作模式
}

/*************************************************************
 * 函数名称：SJAInit
 * 函数功能：CAN控制器初始化函数
 * 输入参数：brt0   总线定时器0
 *			 btr1   总线定时器1
 * 			 filter 滤波器设置指针
 * 输出参数：无
 * 返回值：  无
**************************************************************/
void SJAStdInit(unsigned char btr0, unsigned char btr1, unsigned char *filter)
{
	/* 定义外部中断0优先级和触发方式 */
	PX0 = 1;		//外部中断0高优先级
	IT0 = 0;		//外部中断0低电平触发
	/* 使能SJA1000通讯借口 */
	CS = 0;			
	/* 禁能所有中断和外部中断0 */
	EA = 0;
	EX0 = 0;
	
	SetBitMask(REG_CAN_MODE, RM_RR_BIT);
	while(!SetBitMask(REG_CAN_MODE, RM_RR_BIT));				//确保进入复位模式
	
	WriteSJAReg(REG_CAN_CDR, CANMode_BIT | CLKOff_BIT);         //设置分配寄存器（10001000）PeliCAN模式 
																//CBP=0,CLKOff_BIT=1 不激活比较器旁路(建议激活)，不输出时钟
	WriteSJAReg(REG_CAN_IR, 0x00);				//禁能SJA1000所有中断
	WriteSJARegBlock(REG_CAN_ACR0, filter, 8);	//配置验收代码/屏蔽寄存器
	WriteSJAReg(REG_CAN_BTR0, btr0);			//配置总线定时器0
	WriteSJAReg(REG_CAN_BTR1, btr1);			//配置总线定时器1
	WriteSJAReg(REG_CAN_OCR, 0x1A);				//配置输出引脚为TX0和RX0，推挽模式，正常输出
	
	while(!SetBitMask(REG_CAN_MODE, STM_BIT));	//进入只检测模式
	while(!ClearBitMask(REG_CAN_MODE, RM_RR_BIT));	//清除复位模式
	
	EX0 = 1;	//使能外部中断0
	EA = 1;		//使能所有中断
}

/*************************************************************
 * 函数名称：SetSJASendCmd
 * 函数功能：设置SJA1000发送类型，启动发送
 * 输入参数：cmd 发送命令 0:正常发送 1:单次发送 2:自发自收 0xff:中止发送
 * 输出参数：无
 * 返回值：  1=发送成功 0=发送失败
**************************************************************/
unsigned char SetSJASendCmd(unsigned char cmd)
{
	unsigned char status;
	switch(cmd){
		default:
		case 0:
			status = SetBitMask(REG_CAN_CMR, TR_BIT);			//正常发送，置位TR_BIT
			break;
		case 1:
			status = SetBitMask(REG_CAN_CMR, TR_BIT | AT_BIT);	//单次发送，置位TR_BIT | AT_BIT
			break;
		case 2:
			status = SetBitMask(REG_CAN_CMR, AT_BIT | SRR_BIT);	//自发自收
			break;
		case 0xff:
			status = SetBitMask(REG_CAN_CMR, AT_BIT);
			break;
	}
	return status;
}

/*************************************************************
 * 函数名称：SJASendData
 * 函数功能：发送函数
 * 输入参数：dataBuf 发送CAN帧缓冲区
 * 			 cmd 发送命令 0:正常发送 1:单次发送 2:自发自收
 * 输出参数：无
 * 返回值：  1=发送成功 0=发送失败
**************************************************************/
unsigned char SJASendData(unsigned char *dataBuf, unsigned char cmd)
{
	unsigned char status = 0;
	unsigned char len, dlc;
	//判断SJA发送缓冲区是否锁定或正在发送
	if((ReadSJAReg(REG_CAN_SR) & (TBS_BIT | TCS_BIT)) != (TBS_BIT | TCS_BIT))
	//if((ReadSJAReg(REG_CAN_SR) & TBS_BIT) != TBS_BIT)
	{
		status = 0;
	}
	else{
		dlc = (*dataBuf & 0x0f);	//从发送缓冲区的帧信息中取得CAN数据长度
		dlc = dlc > 8 ? 8 : dlc;
		switch(*dataBuf & 0xc0){
			case 0x00:									//标准数据帧
				len = STD_FRAMEID_LENTH + dlc + 1;
				break;
			case 0x40:									//标准远程帧
				len = STD_FRAMEID_LENTH + 1;
				break;
			case 0x80:									//扩展数据帧
				len = EXT_FRAMEID_LENTH + dlc + 1;
				break;	
			case 0xc0:									//扩展远程帧
				len = EXT_FRAMEID_LENTH + 1;
				break;
			default:
				len = 0;
				status = 0;
				break;
		}
		if(len){
			WriteSJARegBlock(REG_CAN_TXFMINFO, dataBuf, len);
			SetSJASendCmd(cmd);
			status = 1;
		}
	}
	return status;
}

/*************************************************************
 * 函数名称：SJARcvData
 * 函数功能：通过查询方式读取接收缓冲区中的CAN报文
 * 输入参数：dataBuf 指向存储报文使用的空间的指针
 * 输出参数：无
 * 返回值：  1=读取报文成功 0=没有收到报文
**************************************************************/
unsigned char SJARcvData(unsigned char *dataBuf)
{
	unsigned char status = 0;
	unsigned char dlc, len;
	if((ReadSJAReg(REG_CAN_SR) & RBS_BIT) == 0){
		status = 0;
	}else{
		*dataBuf = ReadSJAReg(REG_CAN_RXFMINFO);
		dlc = (*dataBuf & 0x0f);
		dlc = dlc > 8 ? 8 : dlc;
		//根据帧类型确定接收缓冲区中有效数据长度
		switch(*dataBuf & 0xc0){
			case 0x00:
				len = STD_FRAMEID_LENTH + dlc;
				break;
			case 0x40:
				len = STD_FRAMEID_LENTH;
				break;
			case 0x80:
				len = EXT_FRAMEID_LENTH + dlc;
				break;
			case 0xc0:
				len = EXT_FRAMEID_LENTH;
				break;
			default:
				len = 0;
				break;
		}
		if(len){
			ReadSJARegBlock(REG_CAN_RXBUF1, dataBuf + 1, len);
			SetBitMask(REG_CAN_CMR, RRB_BIT);
			status = 1;
		}
	}
	return status;
}

/*************************************************************
 * 函数名称：SJAConfigFilter
 * 函数功能：配置SJA的滤波器模式和滤波参数
 * 输入参数：mode 滤波器模式选择 >0:单滤波模式 其余:双滤波模式
 *			 filter 滤波器参数指针
 * 输出参数：无
 * 返回值：  无
**************************************************************/
void SJAConfigFilter(unsigned char mode, unsigned char *filter)
{
	SetBitMask(REG_CAN_MODE, RM_RR_BIT);		//进入复位模式
	if(mode){
		SetBitMask(REG_CAN_MODE, AFM_BIT);		//单滤波模式
	}else{
		ClearBitMask(REG_CAN_MODE, AFM_BIT);	//双滤波模式
	}
	WriteSJARegBlock(REG_CAN_ACR0, filter, 8);	//配置验收代码寄存器/屏蔽寄存器
	ClearBitMask(REG_CAN_MODE, RM_RR_BIT);		//退出复位模式，进入工作模式
}


