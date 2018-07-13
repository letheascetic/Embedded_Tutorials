#ifndef _UTIL_H_
#define _UTIL_H_

#define OSCCLK 11059200UL
#define CPUCLK (OSCCLK / 12)

#define LOW_BYTE(x)  (unsigned char)(x)
#define HIGH_BYTE(x) (unsigned char)((unsigned int)(x) >> 8)

void Timer0Init(void);
void Timer0Delay(unsigned int n);
void SerialPortInit(void);

#endif