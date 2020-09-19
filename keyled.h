#ifndef __LED_H__
#define __LED_H__
#include <cms.h>


// touch key led 
#define		Led1		RA3
#define		Led2		RA4  //D12
#define		Led3		RB0  //
#define		Led4		RB2   //com control 4 led swtich
#define     Led5        RB1
#define     Led6        RB5
#define     Led7        RC1
#define     Led8        RC2
#define     Led9        RC3


void TimerTiming_Led(void);
void WindLevel_SleepLed(void);
void WindLevel_MiddleLed(void);
void WindLevel_HighLed(void);
void WindLevel_AutoLed(void);

void TouchKeyLed_AllOff(void);










#endif 

