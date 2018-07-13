
#ifndef _SJAHELPER_H_
#define _SJAHELPER_H_

void WriteSJAReg(unsigned char regAdr, unsigned char value);
unsigned char ReadSJAReg(unsigned char regAdr);
unsigned char SetBitMask(unsigned char regAdr, unsigned char bitValue);
unsigned char ClearBitMask(unsigned char regAdr, unsigned char bitValue);
unsigned char WriteSJARegBlock(unsigned char regAdr, unsigned char *valueBuf, unsigned char len);
unsigned char ReadSJARegBlock(unsigned char regAdr, unsigned char *valueBuf, unsigned char len);
unsigned char SJAConnectTest(void);
void SJAInit(unsigned char mode, unsigned char btr0, unsigned char btr1, unsigned char *filter);
void SJAStdInit(unsigned char btr0, unsigned char btr1, unsigned char *filter);
unsigned char SetSJASendCmd(unsigned char cmd);
unsigned char SJASendData(unsigned char *dataBuf, unsigned char cmd);
unsigned char SJARcvData(unsigned char *dataBuf);
void SJAConfigFilter(unsigned char mode, unsigned char *filter);
#endif
