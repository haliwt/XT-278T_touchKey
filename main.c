
#include <cms.h>
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
#include "usart1.h"
#include "keyled.h"
#include "slideled.h"
#include "hdkey.h"


/**********************************************************************/
/*??????????*/
/**********************************************************************/
volatile unsigned char tcount;
volatile bit buzf;
volatile unsigned int buzsec;

volatile unsigned char DispData;

uint16_t usartNum;
uint8_t senddata[2];
 

/**********************************************************************/
/**********************************************************************/
/***********************************************************************
????????????????????????
????????
?????????
?????
***********************************************************************/
void Init_ic (void)
{
	asm("clrwdt");
	PORTA = 0;
	PORTB = 0;
	INTCON = 0x00;
	PIR1 = 0;
	PIR2 = 0;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
	TRISD = 0x00;
	Clr(TRISD, 0); //code down load code 
	Clr(TRISD, 1);
	OPTION_REG = 0;
	OSCCON = 0x71;
	PIE1 = 0;
	PIE2 = 0;
	IOCB = 0;
	WPUA = 0;
	WPUB = 0;


}
/***********************************************************************
???????????????RAM???
????????
?????????
?????
***********************************************************************/
void Init_ram (void)
{
	asm("clrwdt");
	PIE2 = 0;
	PIE1 = 0B00000010;
	PR2 = 125;				//8M???TMR2?????125us???
	T2CON = 5;				//???????2
	
	INTCON = 0XC0;			//??????
	buzf = 1;
	buzsec = 600;
}
/***********************************************************************
???????????????????
????????
?????????
?????
***********************************************************************/
void Sys_set (void)
{
	asm("clrwdt");
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
	TRISD = 0x00;
	OPTION_REG = 0;
	PIE1 = 0B00000010;
	PR2 = 125;
	INTCON = 0XC0;
	if(5 != T2CON)
		T2CON = 5;
	//WPUB = 0B01010010;
	//WPUA = 0B10000000;
}

/***********************************************************************
//??????????
***********************************************************************/
void Kscan()
{
	static unsigned int KeyOldFlag = 0,KeyREFFlag = 0;
	static uint8_t childflg =0 ,timerflg =0,windflg =0;
	unsigned int i = (unsigned int)((KeyFlag[1]<<8) | KeyFlag[0]);

	if(i)
	{
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;			//????????

			buzf = 1;
			buzsec = 600;

			#if 1
			if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02))
			{
                 Delay_nms (3000);
				 Delay_nms (3000);
				 childflg = childflg ^ 0x01;
				 if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02)){
					 if(childflg ==1){
								
								ref.childLock = 1;
								Led4=1;
								 ref.senddata=1;
					 }
					 else{
					 	ref.childLock = 0;
						Led4=0;
						 ref.senddata=1;

					 }
				 
				 }
	       }
         

       #endif 
		
		if(KeyOldFlag & 0x01)
		{
				if(0 == (KeyREFFlag & 0x01)) //KEY Timer_KEY
				{
					if(0 == (KeyREFFlag & 0x01)) //定时按键
				{
					if(ref.childLock ==1){
						
						ref.powerflg=1;
	 				 	senddata[0]=0X08;
	  					USART1_SendData();
					}
					else{
						KeyREFFlag |= 0x01;
						timerflg = timerflg ^ 0x01;
						if(timerflg ==1){
								Led8=1;
								ref.timerTim = 1;
								 ref.senddata=1;
						}
						else{
							    Led8=0;
								ref.timerTim = 0;
								 ref.senddata=1;

						}
				 }
				}
				}
			}
		
			if(KeyOldFlag & 0x02)  //KEY ---WIND_KEY
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					if(ref.childLock ==1){
							
						senddata[0]=0X08;
	  					USART1_SendData();
					}
                    else {
						KeyREFFlag |= 0x02;
						windflg ++;
						if(windflg==1){
							
							ref.windlevel =1;  //睡眠风
							Led1=1;
							Led6=0;
						    Led9=0;
							Led7 =0;
							Led8= 0;
							Led4 =1;
							Led3 = 0;
							Led2=0;
							 ref.senddata=1;
						
					}
					else if(windflg ==2){ //2档
						Led9=1;
						Led2= 1; //定时器按键灯
						Led4 =0; //滤网按键灯 打开
						Led6=0;
					    Led1=0;
						Led7 =0;
						
						ref.windlevel =2;
						 ref.senddata=1;
					}
					else if(windflg ==3){ //3档
						  Led7 =1;
						  Led2= 1; //定时器按键灯
						  Led4 =0; //滤网按键灯 打开
						  Led1=0;
					      Led6=0;
						  Led9 =0;
						  ref.windlevel =3;
						   ref.senddata=1;
					}
					else if(windflg ==4){ //Auto 
						  ref.windlevel =4;
						  windflg=0;
						  Led6 =1;
						  Led2= 1; //定时器按键灯
						  Led4 =0; //滤网按键灯 打开
						  Led9 =0;
						  Led1=0;
					      Led7=0;
						 ref.senddata=1;
					}

				}
			}
			
		  }
		  if(KeyOldFlag & 0x04) //KEY4 POWER_KEY --motor up and dow move
			{
				if(0 == (KeyREFFlag & 0x04))
				{
						  Delay_nms (3000);
					 Delay_nms (3000);
					if(KeyOldFlag & 0x04)
					{
						
						if(ref.childLock ==1){
							senddata[0]=0X08;
		  					USART1_SendData();
						}
						else{
							KeyREFFlag |= 0x04;
							ref.filterNet =1;
						    Led3=1;
						    ref.senddata=1;
					    }
					}
				}

			}
		  
		}
	}
	
	else
	{
		KeyOldFlag = 0;
		KeyREFFlag = 0;
	}
	if(ref.senddata==1){
		ref.senddata =0;
		// Sys_set ();
		ref.powerflg=1;
	  senddata[0]=(ref.windlevel  | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
	  senddata[1]= 0xCD;
	  USART1_SendData();
	}
}


/***********************************************************************
??????????????????
***********************************************************************/
void interrupt time0(void)
{
	if(TMR2IF)
	{
		usartNum ++ ;
		TMR2IF = 0;
		tcount ++;
		__CMS_GetTouchKeyValue();
	}
	else
	{
		PIR1 = 0;
		PIR2 = 0;
	}
}


/***********************************************************************
main??????
***********************************************************************/
void main(void)
{
    static uint8_t poweron=0;
	asm("clrwdt");
	USART1_Init();
	Init_ic();
	Delay_nms(200);													//??????200ms
	Init_ram();	  //???????
	Set_Usart_Async();
	
	
	while(1)
	{
		OSCCON = 0x71;
	
	

		if(tcount >= 32)
		{
			tcount = 0;												//?????????4ms
			Sys_set();
			//Display();
			#if (REL_SENDER_ENABLE == 1)//???????????1
				REL_SenderLoop();//?????????
			#endif
			__CMS_CheckTouchKey();	//?????
			Kscan();			//????????
		}
	}
}
/**********************************************************************/



