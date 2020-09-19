#ifndef __HDKEY_H__
#define __HDKEY_H__

#include <cms.h>
#include "delay.h"
#include "usart1.h"
#include "keyled.h"

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

#define    LED_POWER_RED     RD2  //电源按键指示灯







void PowerOn_SendData_Init(void);
void PowerOff_SendData_Fun(void);



void HDKEY_LED_Init(void);
uint8_t HDKey_Scan(uint8_t mode);









#endif