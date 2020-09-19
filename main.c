
#include <cms.h>
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
#include "usart1.h"
#include "hdkey.h"
#include "keyled.h"


/**********************************************************************/
/*ȫ�ֱ�������*/
/**********************************************************************/
volatile unsigned char ticount;
volatile bit buzf;
volatile unsigned int buzsec;

volatile unsigned char DispData;

static uint8_t usartNum;
static uint8_t usartRunflg =0;
uint8_t powerOn;
uint8_t senddata[3];
/**********************************************************************/
/**********************************************************************/
/***********************************************************************
�Ӻ������ܣ��ϵ��ʼ��ϵͳ�Ĵ���?
��ڲ�����?
�������ݣ�
��ע��
***********************************************************************/
void Init_ic (void)
{
	asm("clrwdt");
	//PORTA = 0;
	//PORTB = 0;
	INTCON = 0x00;
	PIR1 = 0;
	PIR2 = 0;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x01;
	TRISD = 0x00;
	OPTION_REG = 0;
	OSCCON = 0x71;
	PIE1 = 0;
	PIE2 = 0;
	IOCB = 0;
	WPUA = 0;
	WPUB = 0;


}
/***********************************************************************
�������ܣ���ʼ�ϵ�RAM��ֵ
��ڲ�����?
�������ݣ�
��ע��
***********************************************************************/
void Init_ram (void)
{
	asm("clrwdt");
	PIE2 = 0;
	PIE1 = 0B00000010;
	PR2 = 125;				//8M�½�TMR2����Ϊ125us�ж�
	T2CON = 5;				//ʹ�ܶ�ʱ��2
	
	INTCON = 0XC0;			//ʹ���ж�
	buzf = 1;
	buzsec = 600;
}
/***********************************************************************
�������ܣ�ϵͳ�Ĵ���ˢ��
��ڲ�����?
�������ݣ�
��ע��
***********************************************************************/
void Sys_set (void)
{
	asm("clrwdt");
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x01;
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
//����������
***********************************************************************/
void Kscan()
{
	static unsigned int KeyOldFlag = 0,KeyREFFlag = 0;
	static uint8_t childflg =0 ,windflg =0,itimingcount =0;
	unsigned int i = (unsigned int)((KeyFlag[1]<<8) | KeyFlag[0]);
	static uint8_t icount =0;

	if(usartRunflg !=1){
	if(i)
	{
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;			//�м�⵽����?

			buzf = 1;
			buzsec = 600;
		#if 1
			if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02))//Wind KEY + Timer KEY
			{
                 Delay_nms (5000);
				 childflg = childflg ^ 0x01;
				 if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02)){
					 if(childflg ==1){
						usartNum =0; 
						ref.childLock = 1;

						//Set(ref.childLock,6) ;
						usartNum =1;  //child lock
						senddata[0]=(ref.windlevel | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
						senddata[1] =ref.sendCount ;
						senddata[2] = ref.TimingCount;
						USART1_SendData();
								
					 }
					 else{
					 	ref.childLock = 0;
					    usartNum =1; 
						senddata[0]=(ref.windlevel | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
						senddata[1] =ref.sendCount ;
						senddata[2] = ref.TimingCount;
						USART1_SendData();
						
					 }
					 	
				 
				 }
	       }
         

       #endif 
	    
		if(KeyOldFlag & 0x01 && !(KeyOldFlag & 0x02)) //TIMER KEY 
		{
				if(0 == (KeyREFFlag & 0x01)) //Timer KEY 
				{
					KeyREFFlag |= 0x01;
					icount ++;
					if(ref.childLock ==1){

					
						usartNum =1;
						ref.windlevel = icount;
						
					}
					else{
						itimingcount ++ ;
						switch(itimingcount){
				
						case 1:
								Led2=1;// D8,key of led turn on 
								Led3 = 1;
								ref.timerTim = 1;
								usartNum =1;
								ref.sendCount = icount;
								ref.TimingCount =5; // timer timing  5 minute

						break;
						case 2:
								Led2=1; //D8,key of led turn on 
								Led3 = 0;
								Led8 =1 ;
								ref.timerTim = 1; //Tunr on timer on
								usartNum =1;
								ref.sendCount = icount;
								ref.TimingCount = 10;

						break; 
						case 3: 
							Led2=1 ;
							Led3 =0 ;
							Led8 =0;
							Led5= 1;
							ref.timerTim = 1;
							usartNum =1;
							ref.sendCount = icount;
							ref.TimingCount = 15;


						break;

						case 4:
						    itimingcount =0;
							Led2 =1 ;
							Led3 =0 ;
							Led8 =0;
							Led5= 0;
							ref.timerTim = 0; //Turn off timer 
							usartNum =1;
							ref.sendCount = icount;
							ref.TimingCount = 0;

						break;
						} //end timingcount
					}
				}
		}
		
		if(KeyOldFlag & 0x02 && !(KeyOldFlag & 0x01))  // wind key 
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					KeyREFFlag |= 0x02;
					icount++;
					if(ref.childLock ==1){
							usartNum =1;
						
							ref.windlevel = icount;
					}
					else{
						
						windflg ++;
						switch(windflg){

						case 1:
							ref.windlevel   =1;  //sleep_wind
							usartNum =1;
							ref.sendCount = icount;
							Led1=1;
							Led6=0;
							Led9=0;
							Led7 =0;
							Led8= 0;
							Led4 =0; //turn OFF Net
							Led3 = 0;
							Led2=0;
						break;
						case 2: //wind_middle
						
							usartNum =1;
							ref.windlevel  =2;
							ref.sendCount = icount;
							Led9=1;
							Led2= 1; //Timer key lamp led
							Led4 =1; // NET KEY LED ,ON
							Led6=0;
							Led1=0;
							Led7 =0;
						break;
						case 3: //wind_high
					
						    ref.windlevel   =3;
							usartNum =1;
							ref.sendCount = icount;
							Led7 =1;
							Led2= 1; // Timer key lamp led
							Led4 =1; // NET KEY lamp LED 
							Led1=0;
							Led6=0;
							Led9 =0;	
						
						break;
						case 4 : //wind_auto
						    ref.windlevel  =4;
							usartNum =1;
							ref.sendCount = icount;
							windflg=0;
							Led6 =1;
							Led2= 1; //Timer KEY lamp led
							Led4 =1; //NET KEY lamp led
							Led9 =0;
							Led1=0;
							Led7=0;
						break;
					
						}
							
					} 
					
				}
			}
			if(KeyOldFlag & 0x04) //Net KEY
			{

                icount++;
				if(ref.childLock ==1){
					if(0 == (KeyREFFlag & 0x04))
						{
							KeyREFFlag |= 0x04;
							usartNum =1;
							
							ref.windlevel = icount;
						
						}
							
					}
				else
				{
					Delay_nms (3000);
				    Delay_nms (3000);
				   if(KeyOldFlag & 0x04)
				   {
					KeyREFFlag |= 0x04;
					ref.filterNet =1;
					ref.sendCount = icount;
				    Led3=1;
					 usartNum =1;
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
	if(usartNum ==1){
		
		usartNum =0;
		usartRunflg =1;
		senddata[0]=(ref.windlevel | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
		senddata[1] =ref.sendCount ;
		senddata[2] = ref.TimingCount;
		USART1_SendData();
		usartRunflg =0;
			
		}
	
	}
}
/***********************************************************************
�������ܣ��ж���ں���?
***********************************************************************/
void interrupt time0(void)
{
	if(TMR2IF)
	{
	//	usartNum ++ ;
		TMR2IF = 0;
		ticount ++;
		__CMS_GetTouchKeyValue();
	}
	else
	{
		PIR1 = 0;
		PIR2 = 0;
	}
}


/***********************************************************************
 * *
   * Function Name:void main()
   * Function:
   * Inputr Ref:No
   * Retrunr Ref: No
   * 
***********************************************************************/
void main(void)
{
    static uint8_t poweron=0,pwflg=0,pcount=0,keyflg=0;
	asm("clrwdt");
	USART1_Init();
	Init_ic();
	Delay_nms(200);													//�ϵ���ʱ200ms
	Init_ram();	  //�ϵ�����?
	HDKEY_LED_Init();

	while(1)
	{
		OSCCON = 0x71;
	  
	   	
		powerOn= HDKey_Scan(0);
		 // powerOn = POWER_KEY ;
		#if 1
		if(powerOn==1){
			
			pwflg = pwflg ^ 0x01;
			keyflg ++;
			//if(pwflg ==1 && keyflg ==0){
			if(keyflg == 1){
			 // keyflg =1;
			   LED_POWER_RED = 0;
			
			   ref.powerflg =1;
			   ref.sendCount = 0xAA;
			   ref.windlevel = 0x04;
			   ref.TimingCount =0;
			   ref.filterNet =0;
			   ref.childLock =0;
			  senddata[0]=(ref.windlevel | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
		      senddata[1] =ref.sendCount ;
		      senddata[2] = ref.TimingCount;
			   USART1_SendData();
			}
			//else if(keyflg ==0) {
			else {
				 
				keyflg =0;
				ref.powerflg =0;
				ref.sendCount = 0xAB;
				ref.windlevel = 0x04;
			   ref.TimingCount =0;
			   ref.filterNet =0;
			   ref.childLock =0;
			   ref.sendCount ;
			  senddata[0]=(ref.windlevel | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
		      senddata[1] =ref.sendCount ;
		      senddata[2] = ref.TimingCount;
			  USART1_SendData();
			}
		}
		#endif 
		
		if(ref.powerflg ==1){
			if(ticount >= 32)
			{
				ticount = 0;												//������ѭ��4ms
				Sys_set();
			  
				#if (REL_SENDER_ENABLE == 1)//���Ժ궨���Ƿ�Ϊ1
					REL_SenderLoop();//�����ӳ���
				#endif
				__CMS_CheckTouchKey();	//ɨ�谴��
				Kscan();			//��������
			}
		}
		
	}
	  
}
/**********************************************************************/



