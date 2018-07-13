/*
	SJA1000的寄存器有关控制
*/
#ifndef SJA1000_H
#define SJA1000_H
/*指定SJA1000的起始地址为0x7800*/
#define SJA_REG_BaseADD 0x7800  
                                                                                            
#define REG_MODE XBYTE[SJA_REG_BaseADD + 0x00]                       
#define REG_CMD XBYTE[SJA_REG_BaseADD + 0x01]                        
#define REG_SR XBYTE[SJA_REG_BaseADD + 0x02]                         
#define REG_IR XBYTE[SJA_REG_BaseADD + 0x03]                         
#define REG_IR_ABLE XBYTE[SJA_REG_BaseADD + 0x04]                    
#define REG_BTR0 XBYTE[SJA_REG_BaseADD + 0x06] //05保留              
#define REG_BTR1 XBYTE[SJA_REG_BaseADD + 0x07]                       
#define REG_OCR XBYTE[SJA_REG_BaseADD + 0x08]                        
#define REG_TEST XBYTE[SJA_REG_BaseADD + 0x09]                       
#define REG_ALC XBYTE[SJA_REG_BaseADD + 0x0b] //0a保留               
#define REG_ECC XBYTE[SJA_REG_BaseADD + 0x0c]                        
#define REG_EMLR XBYTE[SJA_REG_BaseADD + 0x0d]                       
#define REG_RXERR XBYTE[SJA_REG_BaseADD + 0x0e]                      
#define REG_TXERR XBYTE[SJA_REG_BaseADD + 0x0f]                      
                                                                     
#define REG_ACR0 XBYTE[SJA_REG_BaseADD + 0x10]                       
#define REG_ACR1 XBYTE[SJA_REG_BaseADD + 0x11]                       
#define REG_ACR2 XBYTE[SJA_REG_BaseADD + 0x12]                       
#define REG_ACR3 XBYTE[SJA_REG_BaseADD + 0x13]                       
#define REG_AMR0 XBYTE[SJA_REG_BaseADD + 0x14]                       
#define REG_AMR1 XBYTE[SJA_REG_BaseADD + 0x15]                       
#define REG_AMR2 XBYTE[SJA_REG_BaseADD + 0x16]                       
#define REG_AMR3 XBYTE[SJA_REG_BaseADD + 0x17]                       
 
 /*接收缓冲区*/                                                                   
#define REG_RxBuffer0 XBYTE[SJA_REG_BaseADD + 0x10]                  
#define REG_RxBuffer1 XBYTE[SJA_REG_BaseADD + 0x11]                  
#define REG_RxBuffer2 XBYTE[SJA_REG_BaseADD + 0x12]                  
#define REG_RxBuffer3 XBYTE[SJA_REG_BaseADD + 0x13]                  
#define REG_RxBuffer4 XBYTE[SJA_REG_BaseADD + 0x14]                  
#define REG_RxBuffer5 XBYTE[SJA_REG_BaseADD + 0x15]                
#define REG_RxBuffer6 XBYTE[SJA_REG_BaseADD + 0x16]                
#define REG_RxBuffer7 XBYTE[SJA_REG_BaseADD + 0x17]                
#define REG_RxBuffer8 XBYTE[SJA_REG_BaseADD + 0x18]                
#define REG_RxBuffer9 XBYTE[SJA_REG_BaseADD + 0x19]                
#define REG_RxBuffer10 XBYTE[SJA_REG_BaseADD + 0x1a]                
#define REG_RxBuffer11 XBYTE[SJA_REG_BaseADD + 0x1b]                
#define REG_RxBuffer12 XBYTE[SJA_REG_BaseADD + 0x1c]  
 
 /*发送缓冲区*/                                                       
#define REG_TxBuffer0 XBYTE[SJA_REG_BaseADD + 0x10]                  
#define REG_TxBuffer1 XBYTE[SJA_REG_BaseADD + 0x11]                  
#define REG_TxBuffer2 XBYTE[SJA_REG_BaseADD + 0x12]                  
#define REG_TxBuffer3 XBYTE[SJA_REG_BaseADD + 0x13]                  
#define REG_TxBuffer4 XBYTE[SJA_REG_BaseADD + 0x14]                                                                                    
#define REG_TxBuffer5 XBYTE[SJA_REG_BaseADD + 0x15]                
#define REG_TxBuffer6 XBYTE[SJA_REG_BaseADD + 0x16]                
#define REG_TxBuffer7 XBYTE[SJA_REG_BaseADD + 0x17]                
#define REG_TxBuffer8 XBYTE[SJA_REG_BaseADD + 0x18]                
#define REG_TxBuffer9 XBYTE[SJA_REG_BaseADD + 0x19]                
#define REG_TxBuffer10 XBYTE[SJA_REG_BaseADD + 0x1a]                
#define REG_TxBuffer11 XBYTE[SJA_REG_BaseADD + 0x1b]                
#define REG_TxBuffer12 XBYTE[SJA_REG_BaseADD + 0x1c] 
#define REG_TxBufferRd0 XBYTE[SJA_REG_BaseADD + 0x60]                  
#define REG_TxBufferRd1 XBYTE[SJA_REG_BaseADD + 0x61]                  
#define REG_TxBufferRd2 XBYTE[SJA_REG_BaseADD + 0x62]                  
#define REG_TxBufferRd3 XBYTE[SJA_REG_BaseADD + 0x63]                  
#define REG_TxBufferRd4 XBYTE[SJA_REG_BaseADD + 0x64]                                                                               
#define REG_TxBufferRd5 XBYTE[SJA_REG_BaseADD + 0x65]                
#define REG_TxBufferRd6 XBYTE[SJA_REG_BaseADD + 0x66]                
#define REG_TxBufferRd7 XBYTE[SJA_REG_BaseADD + 0x67]                
#define REG_TxBufferRd8 XBYTE[SJA_REG_BaseADD + 0x68]                
#define REG_TxBufferRd9 XBYTE[SJA_REG_BaseADD + 0x69]                
#define REG_TxBufferRd10 XBYTE[SJA_REG_BaseADD + 0x6a]                
#define REG_TxBufferRd11 XBYTE[SJA_REG_BaseADD + 0x6b]                
#define REG_TxBufferRd12 XBYTE[SJA_REG_BaseADD + 0x6c]  

#define REG_RBSA XBYTE[SJA_REG_BaseADD + 0x1e]
#define REG_CDR XBYTE[SJA_REG_BaseADD + 0x1f]