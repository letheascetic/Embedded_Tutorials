/*------------------------------------------------------------------------------
HELLO.C
Copyright 1995-2005 Keil Software, Inc.
------------------------------------------------------------------------------*/
 
#include <REG52.H>                /* special function register declarations   */
                                  /* for the intended 8051 derivative         */
 
#include <stdio.h>                /* prototype declarations for I/O functions */
#include "sja1000_reg.h"  		  /* sja1000T的寄存器定义文件*/
#include <absacc.h>				  /* 主要是用于寻址外部存储器*/
 
sbit SJARst = P2^6; 			  //复位控制     

void SJA1000_Tx_Display(void)
{
	printf( " TBSR3 = 0x%x \n", REG_TxBufferRd3 );  
	printf( " TBSR4 = 0x%x \n", REG_TxBufferRd4 );  
	printf( " TBSR5 = 0x%x \n", REG_TxBufferRd5 );  
	printf( " TBSR6 = 0x%x \n", REG_TxBufferRd6 );  
	printf( " TBSR7 = 0x%x \n", REG_TxBufferRd7 );  
	printf( " TBSR8 = 0x%x \n", REG_TxBufferRd8 );  
	printf( " TBSR9 = 0x%x \n", REG_TxBufferRd9 );  
	printf( " TBSR10 = 0x%x \n",REG_TxBufferRd10);  
}
/*显示发送的信息,之前直接使用发送缓冲区，这种方法是错误的，因为0x10开始的13个寄存器，读的时候是接收缓冲区，写的时候是发送缓冲区*/
 
void SJA_Init(void)                          
{    
	//SJA1000复位                                        
	 unsigned char i;                            
	 for(i = 0;i < 125;i++);           
	 SJARst = 0;                                 
	 for(i = 0;i < 125;i++);//给RST引脚一个低脉冲
	 SJARst = 1;                                 
	 for(i = 0;i < 125;i++);                     
}  

void SJA1000_TxData(void)
{
	while(REG_SR & 0x10);		//当SJA1000不处于接收状态时才可继续执行，SR.4==0x1，正在接收，等待
    while(!(REG_SR & 0x08)); 	//SR.3=0,发送请求未处理完，等待直到SR.3=1
    while(!(REG_SR & 0x04)); 	//SR.2=0,发送缓冲器被锁。等待直到SR.2=1   
	
	REG_TxBuffer0 = 0x08;//帧信息,标准帧，数据帧，8字节        
	                                                           
	REG_TxBuffer1 = 0xEA;//标识符1                             
	REG_TxBuffer2 = 0x60;//标识符2                     
	                                                 
	REG_TxBuffer3 = 0x11;//发送数据位：1                       
	REG_TxBuffer4 = 0x22;//发送数据位：2                       
	REG_TxBuffer5 = 0x33;                                      
	REG_TxBuffer6 = 0x44;                                      
	REG_TxBuffer7 = 0x55;                                      
	REG_TxBuffer8 = 0x66;                                      
	REG_TxBuffer9 = 0x77;                                      
	REG_TxBuffer10 = 0x88;//here Over                          
                             
 	SJA1000_Tx_Display();
	REG_CMD = 0x12;				//自接收
	while(!(REG_SR & 0x08));	//检测发送完毕	
}

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/
void main (void) 
{
 
/*------------------------------------------------
Setup the serial port for 9600 baud at 11.0592MHz.
------------------------------------------------*/
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 0xFD;               /* TH1:  reload value for 9600 baud @ 11.0595MHZ   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;                  /* TI:   set TI to send first char of UART    */
	PX0=1;                                          //外部中断0高优先级
 	IT0=1;                                          //设置INT0为下降沿中断
 	EX0=1;                                          //使能INT0中断
 
/*------------------------------------------------
Note that an embedded program never exits (because
there is no operating system to return to).  It
must loop and execute forever.
------------------------------------------------*/
   
    printf ("Hello World\n");   /* Print "Hello World" */
	SJA_Init();//主要是使芯片复位
	/*
		Enter the reset Mode
	*/
	REG_MODE = 0x01; 
	while((REG_MODE&0x01)!= 0x01);	//确定进入复位模式 
	printf("1.Enter the Reset Mode,REG_MODE=0x%x\n",REG_MODE);
              
	REG_CDR = 0xc8;		//设置时钟分频寄存器。CDR.7 = 1,PeliCAN模式；CDR.6（RX0激活，关闭RX1）  fCLKOUT = fOSC/2, CDR.3(Close the CLKOUT)
	REG_RBSA = 0x00;	//RX缓冲器起始地址
                   
	/* Configure acceptance code and mask register */		                                             
	REG_ACR0 = 0xff;	//验收码寄存器                       
    REG_ACR1 = 0xff;                            
	REG_ACR2 = 0xff;                            
	REG_ACR3 = 0xff;                            
		                                             
	REG_AMR0 = 0xff;	//验收屏蔽寄存器，接收任何标识符的数据包         
	REG_AMR1 = 0xff;                            
	REG_AMR2 = 0xff;                            
	REG_AMR3 = 0xff;    
	                        
 
	/*configure bus timing registers*/
	REG_BTR0 = 0x00;                            
	REG_BTR1 = 0x14; 	//100k     
	                                    
	REG_IR_ABLE = 0x01;	//Peli模式中断使能,接收中断使能，发送中断禁止                  
    
	REG_OCR = 0x1a;		//设置输出模式：正常输出，从TX0口输出;TX1悬空
	                                      
	REG_MODE = 0x0c; 	//进入自接收模式.CDR.3(选择单个验收滤波器),CDR.2 (此模式可以检测所有节点)
 
	while(REG_MODE != 0x0c);//确定进入自接收模式下
	printf("2.Enter the self-test Mode,REG_MODE=0x%x\n",REG_MODE);
 
	SJA1000_TxData();//发送数据
	printf("\n\n");
	//SJA1000_Rx_Display();//接收数据展示
	EA = 1;//使能全局中断
	while(1);
}

/************************************************************
		函数：ex0_int 
		说明：中断服务程序
		入口：无
		返回：无
***********************************************************/
void handle_int(void) interrupt 0 using 1
{
 	if(REG_IR & 0x01)      //产生了接收中断
	{ 
		#pragma disable
		printf( " Received message.\n");
		printf( " RBSR3 = %x \n", REG_RxBuffer3 );
		printf( " RBSR4 = %x \n", REG_RxBuffer4 );
		printf( " RBSR5 = %x \n", REG_RxBuffer5 );     
		printf( " RBSR6 = %x \n", REG_RxBuffer6 );     
		printf( " RBSR7 = %x \n", REG_RxBuffer7 );     
		printf( " RBSR8 = %x \n", REG_RxBuffer8 );     
		printf( " RBSR9 = %x \n", REG_RxBuffer9 );     
		printf( " RBSR10 = %x \n",REG_RxBuffer10);   
	}  
}
