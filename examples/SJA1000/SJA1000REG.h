#ifndef _SJA1000REG_H_
#define _SJA1000REG_H_
 
/*************************************************************
 * 模式和控制寄存器的地址和位定义
**************************************************************/
#define REG_CAN_MODE	0x00	//模式和控制寄存器
#define RM_RR_BIT		0x01	//复位模式(请求)位
#define LOM_BIT    		0x02	//监听模式位
#define STM_BIT    		0x04	//自我测试模式位
#define AFM_BIT    		0x08	//验收滤波器模式位, AFM=1 单滤波 AFM=0 双滤波 默认双滤波
#define SM_BIT     		0x10	//睡眠模式位

/*************************************************************
 * 命令寄存器的地址和位定义
**************************************************************/
#define REG_CAN_CMR    0x01		   //命令寄存器
#define TR_BIT         0x01        //发送请求位
#define AT_BIT         0x02        //中止发送位
#define RRB_BIT        0x04        //释放接收缓冲器位
#define CDO_BIT        0x08        //清除数据溢出位
#define SRR_BIT        0x10        //自身接收请求位

/*************************************************************
 * 状态寄存器的地址和位定义
**************************************************************/
#define REG_CAN_SR		  0X02		//状态寄存器		
#define RBS_BIT           0x01		//接收缓冲器状态位
#define DOS_BIT           0x02		//数据溢出状态位
#define TBS_BIT           0x04		//发送缓冲器状态位
#define TCS_BIT           0x08		//发送完成状态位
#define RS_BIT            0x10		//接收状态位
#define TS_BIT            0x20		//发送状态位
#define ES_BIT            0x40		//错误状态位
#define BS_BIT            0x80		//总线状态位

/*************************************************************
 * 中断寄存器的地址和位定义
**************************************************************/
#define REG_CAN_IR		  0X03		//中断寄存器
#define RI_BIT            0x01		//接收中断位
#define TI_BIT            0x02		//发送中断位
#define EI_BIT            0x04		//错误警告中断位
#define DOI_BIT           0x08		//数据溢出中断位
#define WUI_BIT           0x10		//唤醒中断位
#define EPI_BIT           0x20		//错误消极中断位
#define ALI_BIT           0x40		//仲裁丢失中断位
#define BEI_BIT           0x80		//总线错误中断位

/*************************************************************
 * 中断使能寄存器的地址和位定义
**************************************************************/
#define REG_CAN_IER		  0x04		//中断使能寄存器
#define RIE_BIT           0x01		//接收中断使能位
#define TIE_BIT           0x02		//发送中断使能位
#define EIE_BIT           0x04		//错误警告中断使能位
#define DOIE_BIT          0x08		//数据溢出中断使能位
#define WUIE_BIT          0x10		//唤醒中断使能位
#define EPIE_BIT          0x20		//错误消极中断使能位
#define ALIE_BIT          0x40		//仲裁丢失中断使能位
#define BEIE_BIT          0x80		//总线错误中断使能位

/*************************************************************
 * 0x05 寄存器功能保留
**************************************************************/

/*************************************************************
 * 总线定时器寄存器的地址和位定义
**************************************************************/
#define REG_CAN_BTR0   	  0x06		//总线定时器0寄存器
#define REG_CAN_BTR1      0x07		//总线定时器1寄存器
#define SAM_BIT           0x80		//采样模式位:0==总线被采样1次,1==总线被采样3次

/*************************************************************
 * 输出控制器寄存器的地址和位定义
**************************************************************/
#define REG_CAN_OCR   	  0x08		//输出控制寄存器
/* OCMODE1, OCMODE0 */
#define BiPhaseMode       0x00		//双相输出模式
#define NormalMode        0x02		//正常输出模式
#define ClkOutMode        0x03		//时钟输出模式
/* TX1的输出管脚配置 */
#define OCPOL1_BIT        0x20		//输出极性控制位
#define Tx1Float          0x00		//配置为悬空
#define Tx1PullDn         0x40		//配置为下拉
#define Tx1PullUp         0x80		//配置为上拉
#define Tx1PshPull        0xc0		//配置为推挽
/* TX0的输出管脚配置 */
#define OCPOL0_BIT        0x04		//输出极性控制位
#define Tx0Float          0x00		//配置为悬空
#define Tx0PullDn         0x08		//配置为下拉
#define Tx0PullUp         0x10		//配置为上拉
#define Tx0PshPull        0x18		//配置为推挽

/*************************************************************
 * 测试寄存器的地址和位定义
**************************************************************/
#define REG_CAN_TEST	  0x09		//测试寄存器

/*************************************************************
 * 0x0a 寄存器功能保留
**************************************************************/

/*************************************************************
 * 其他寄存器的地址定义
**************************************************************/
#define REG_CAN_ALC		  0x0b		//仲裁丢失捕捉寄存器
#define REG_CAN_ECC       0x0c		//错误捕捉寄存器
#define REG_CAN_EWLR      0x0d		//错误报警限制寄存器
#define REG_CAN_RXERR     0x0e		//RX 错误计数器寄存器
#define REG_CAN_TXERR     0x0f		//TX 错误计数器寄存器

/*************************************************************
 * 验收滤波器寄存器的地址定义
**************************************************************/
#define REG_CAN_ACR0      16		//验收代码0寄存器
#define REG_CAN_ACR1      17		//验收代码1寄存器
#define REG_CAN_ACR2      18		//验收代码2寄存器
#define REG_CAN_ACR3      19		//验收代码3寄存器
#define REG_CAN_AMR0      20		//验收屏蔽0寄存器
#define REG_CAN_AMR1      21		//验收屏蔽1寄存器
#define REG_CAN_AMR2      22		//验收屏蔽2寄存器
#define REG_CAN_AMR3      23		//验收屏蔽3寄存器

/*************************************************************
 * TX缓冲器的地址定义
**************************************************************/
/* 仅写地址 */
#define REG_CAN_TXFMINFO  16		//TX帧信息（标准帧、扩展帧）寄存器
#define REG_CAN_TXBUF1	  17		//TX帧信息（标准帧识别码1、扩展帧识别码1）寄存器
#define REG_CAN_TXBUF2	  18		//TX帧信息（标准帧识别码2、扩展帧识别码2）寄存器
#define REG_CAN_TXBUF3	  19		//TX帧信息（标准帧数据1、扩展帧识别码3）寄存器
#define REG_CAN_TXBUF4	  20		//TX帧信息（标准帧数据2、扩展帧识别码4）寄存器
#define REG_CAN_TXBUF5	  21		//TX帧信息（标准帧数据3、扩展帧数据1）寄存器
#define REG_CAN_TXBUF6	  22		//TX帧信息（标准帧数据4、扩展帧数据2）寄存器
#define REG_CAN_TXBUF7	  23		//TX帧信息（标准帧数据5、扩展帧数据3）寄存器
#define REG_CAN_TXBUF8	  24		//TX帧信息（标准帧数据6、扩展帧数据4）寄存器
#define REG_CAN_TXBUF9	  25		//TX帧信息（标准帧数据7、扩展帧数据5）寄存器
#define REG_CAN_TXBUF10	  26		//TX帧信息（标准帧数据8、扩展帧数据6）寄存器
#define REG_CAN_TXBUF11	  27		//TX帧信息（扩展帧数据7）寄存器
#define REG_CAN_TXBUF12	  28		//TX帧信息（扩展帧数据8）寄存器
/* 仅读地址 */
#define REG_CAN_TXFMRD    96		//读取TX帧信息（标准帧、扩展帧）寄存器
#define REG_CAN_TXRD1	  97		//读取TX帧信息（标准帧识别码1、扩展帧识别码1）寄存器
#define REG_CAN_TXRD2	  98		//读取TX帧信息（标准帧识别码2、扩展帧识别码2）寄存器
#define REG_CAN_TXRD3	  99		//读取TX帧信息（标准帧数据1、扩展帧识别码3）寄存器
#define REG_CAN_TXRD4	  100		//读取TX帧信息（标准帧数据2、扩展帧识别码4）寄存器
#define REG_CAN_TXRD5	  101		//读取TX帧信息（标准帧数据3、扩展帧数据1）寄存器
#define REG_CAN_TXRD6	  102		//读取TX帧信息（标准帧数据4、扩展帧数据2）寄存器
#define REG_CAN_TXRD7	  103		//读取TX帧信息（标准帧数据5、扩展帧数据3）寄存器
#define REG_CAN_TXRD8	  104		//读取TX帧信息（标准帧数据6、扩展帧数据4）寄存器
#define REG_CAN_TXRD9	  105		//读取TX帧信息（标准帧数据7、扩展帧数据5）寄存器
#define REG_CAN_TXRD10	  106		//读取TX帧信息（标准帧数据8、扩展帧数据6）寄存器
#define REG_CAN_TXRD11	  107		//读取TX帧信息（扩展帧数据7）寄存器
#define REG_CAN_TXRD12	  108		//读取TX帧信息（扩展帧数据8）寄存器

/*************************************************************
 * RX缓冲器的地址定义
**************************************************************/
#define REG_CAN_RXFMINFO  16		//RX帧信息（标准帧、扩展帧）寄存器
#define REG_CAN_RXBUF1    17		//RX帧信息（标准帧识别码1、扩展帧识别码1）寄存器
#define REG_CAN_RXBUF2    18		//RX帧信息（标准帧识别码2、扩展帧识别码2）寄存器
#define REG_CAN_RXBUF3    19		//RX帧信息（标准帧数据1、扩展帧识别码3）寄存器
#define REG_CAN_RXBUF4    20		//RX帧信息（标准帧数据2、扩展帧识别码4）寄存器
#define REG_CAN_RXBUF5    21		//RX帧信息（标准帧数据3、扩展帧数据1）寄存器
#define REG_CAN_RXBUF6    22		//RX帧信息（标准帧数据4、扩展帧数据2）寄存器
#define REG_CAN_RXBUF7    23		//RX帧信息（标准帧数据5、扩展帧数据3）寄存器
#define REG_CAN_RXBUF8    24		//RX帧信息（标准帧数据6、扩展帧数据4）寄存器
#define REG_CAN_RXBUF9    25		//RX帧信息（标准帧数据7、扩展帧数据5）寄存器
#define REG_CAN_RXBUF10   26		//RX帧信息（标准帧数据8、扩展帧数据6）寄存器
#define REG_CAN_RXBUF11   27		//RX帧信息（扩展帧数据7）寄存器
#define REG_CAN_RXBUF12   28		//RX帧信息（扩展帧数据8）寄存器
#define REG_CAN_RMC	   	  29		//RX信息计数器寄存器
#define REG_CAN_RBSA	  30		//RX缓冲区起始地址寄存器

/*************************************************************
 * 时钟分频器的地址和位定义
**************************************************************/
#define REG_CAN_CDR       31		//时钟分频寄存器
#define CLKOff_BIT        0x08		//时钟关闭位，时钟输出管脚控制位  -->  关闭有助于减少EMC干扰
#define RXINTEN_BIT       0x20		//用于接收中断的引脚TX1
#define CBP_BIT           0x40		//CAN比较器旁路控制位  -->  根据电路图来确定
#define CANMode_BIT       0x80		//CAN模式控制位  -->  0:Basic 1:Peli

#endif
