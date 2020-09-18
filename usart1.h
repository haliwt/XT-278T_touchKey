#ifndef __USART1_H__
#define __USART1_H__
#include <cms.h>
#include "mytype.h"


struct senddata{
     uint8_t windlevel ;
	 uint8_t sendCount;
	 uint8_t filterNet :1;
	 uint8_t timerTim :1;
	 uint8_t sleep :1;
	 uint8_t childLock:1;
	 uint8_t powerflg:1;

};
extern struct  senddata ref;

void USART1_Init(void);
void USART1_SendData(void);
void delay_ns(unsigned char t);
void Set_Usart_Async(void);

uint8_t BCC(void);







#endif 