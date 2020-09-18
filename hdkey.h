#ifndef __HDKEY_H__
#define __HDKEY_H__

#include <cms.h>
#include "delay.h"

/*******************************************************
					位定义
********************************************************/
#define	Set(x,y)	((x) |= (1 << (y)))				//位置1
#define	Clr(x,y)	((x) &= ~ (1 << (y)))			//位清0

#define	b0(x,y)		(((x) & (1 << (y))) == 0)		//位0判断 if(b0(x,y)) 判断是否为0
#define	b1(x,y)		((x) & (1 << (y)))				//位1判断 if(b1(x,y)) 判断是否为1
/*******************************************************
					宏定义
********************************************************/
typedef 	unsigned char  uint8_t ;
typedef    char     int8_t;
typedef     unsigned int   uint16_t;
typedef  	int     int16_t;
/*******************************************************/
/*******************************************************/
/*******************************************************/



#define  POWER_KEY    RC0     //input IO POWER KEY
#define  POWER_PRES   1

#define    LED_POWER_RED     RD0  //电源按键指示灯

//led output port config 
#define     LED1	RA3
#define     LED2 	RA4
#define		LED3    RB0
#define		LED4	RB2 //
#define     LED5    RB1
#define     LED6    RB4
#define     LED7    RC1
#define     LED8    RC2
#define     LED9    RC3







void HDKEY_LED_Init(void);
void TouchKey_1_LEDOn(void);
void TouchKey_1_LEDOff(void);
void TouchKey_2_LEDOn(void);
void TouchKey_2_LEDOff(void);

void TouchKey_3_LEDOn(void);
void TouchKey_3_LEDOff(void);

void PowerKey_LEDOn(void);
void PowerKey_LEDOff(void);



void HDKEY_LED_Init(void);
uint8_t HDKey_Scan(uint8_t mode);









#endif