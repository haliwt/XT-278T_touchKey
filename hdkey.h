#ifndef __HDKEY_H__
#define __HDKEY_H__

#include <cms.h>
#include "keyled.h"
#include"mytype.h"
#include "usart1.h"



/*******************************************************
					IO����				  
********************************************************/
#define		Led1		RA3
#define		Led2		RA4  //D12
#define		Led3		RB0  //
#define		Led4		RB2   //com control 4 led swtich
#define     Led5        RB1
#define     Led6        RB5
#define     Led7        RC1
#define     Led8        RC2
#define     Led9        RC3




#define    LED_RED     RD2


#define  POWER_KEY    RC0     //input IO ������
#define  POWER_PRES   1


//extern uint8_t  ChildLock ;

void TurnOff_LED(void);
void Net_LED_On(void);
unsigned char HDKey_Scan(unsigned char mode);
















#endif