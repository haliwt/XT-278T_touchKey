#ifndef __HD_KEY__
#define __HD_KEY__
#include <cms.h>

#define		HDKey	RC0				//定义RC口 取名HDKey input

//led output port config 
#define     LED1	RA3
#define     LED2 	RA4
#define		LED3    RB0
#define		LED4	RB1
#define     LED5    RB2
#define     LED6    RB4
#define     LED7    RC1
#define     LED8    RC2
#define     LED9    RC3
#define     LED_RED    RD2   //电源按键指示灯






void HDKEY_LED_Init(void);
void TouchKey_1_LEDOn(void);
void TouchKey_1_LEDOff(void);
void TouchKey_2_LEDOn(void);
void TouchKey_2_LEDOff(void);

void TouchKey_3_LEDOn(void);
void TouchKey_3_LEDOff(void);

void PowerKey_LEDOn(void);
void PowerKey_LEDOff(void);






#endif 