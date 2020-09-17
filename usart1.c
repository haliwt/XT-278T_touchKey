#include "usart1.h"

struct  senddata ref;


extern uint8_t senddata[1];



/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/

void delay_ns(unsigned char t)
{
  unsigned int j;
  for(j=t;j>0;j--){
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");

}
}
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
void USART1_Init(void)
{

	//OSCCON = 0x71;				//8M内部时钟
	INTCON = 0;
	
	PIR1 = 0;
	PIE1 = 0;
	PIR2 = 0;
	PIE2 = 0;
	
	TRISA = 0B00000000;
	PORTA = 0B00000000;
    TRISB = 0B00000000;
	PORTB = 0B00000000;
	/*初始化USART通信模块*/
	Set_Usart_Async();

}
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/

void USART1_SendData(void)
{
	    //senddata[0]=(ref.windlevel  | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock <<6 | ref.powerflg <<7) & 0xff;
		
        TXREG1   = 0xAA; //Recebuffer[0];//Recebuffer[0] ;
		delay_ns(200);//delay_ns(100);
		TXREG1   = senddata[0];  //数据
		delay_ns(200);//delay_ns(200);
		TXREG1   = senddata[1];  //数据
		delay_ns(200);
		TXREG1   = BCC();
		delay_ns(200); 	//delay_ns(400); 	
		

}

/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
uint8_t BCC(void)
{
     uint8_t sbytes[1];
	 sbytes[0]=0xAA;
	 uint8_t tembyte ;//= sbytes[0];
	 senddata[1] = 0x4b;
	// senddata[0]=(ref.windlevel  | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock <<6| ref.powerflg <<7) & 0xff;
	 // senddata[0]=ref.senddata ;
      tembyte =  sbytes[0]^ senddata[0]^ senddata[1];
    
    return tembyte;

}
/***********************************************
函数名称：Set_Usart_Async
函数功能：Usart状态设置（异步）
入口参数：无
出口参数：无
备注：
************************************************/
/*
SYNC = 0,BRG16 = 0,BRGH = 0;目标波特率 = Fosc/(64*([SPBRGH:SPBRG]+1))

SYNC = 0,BRG16 = 0,BRGH = 1;
SYNC = 0,BRG16 = 1,BRGH = 0;目标波特率 = Fosc/(16*([SPBRGH:SPBRG]+1))

SYNC = 0,BRG16 = 1,BRGH = 1;目标波特率 = Fosc/(4*([SPBRGH:SPBRG]+1))
*/
void Set_Usart_Async(void)
{
	//SPBRG1 = 102;			//设置波特率为9600 bps，误差0.16%	
	
	SPBRG1 = 51;  //WT.EDIT 	
	
		
	
	SYNC1 = 0;				//0为异步模式，1为同步模式
	SCKP1 = 0;
	
    SPEN1 = 1;				//允许串口操作
	RC1IE = 1;				//接收中断  
	TX1IE = 0;				//发送中断
    RX9EN1 = 0;				//0为8位接收，1为9位接收
	TX9EN1 = 0;				//0为8位发送，1为9位发送
	CREN1 = 1;				//0为禁止接收，1为使能接收
    TXEN1 = 1;				//0为禁止发送，1为使能发送
}


