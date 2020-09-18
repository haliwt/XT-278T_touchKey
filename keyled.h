#ifndef __LED_H__
#define __LED_H__
#include <cms.h>



/*******************************************************
					IO����				  
********************************************************/
#define		keyLed1		RA7
#define		keyLed2		RB0
#define		keyLed3		RB1  //



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






//extern uint8_t  ChildLock ;

void KeyLed_Init(void);



#endif 

