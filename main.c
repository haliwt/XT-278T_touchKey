
#include <cms.h>
#include "led.h"
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
#include "usart1.h"

/**********************************************************************/
/*ȫ�ֱ�������*/
/**********************************************************************/
volatile unsigned char tcount;
volatile bit buzf;
volatile unsigned int buzsec;

volatile unsigned char DispData;
uint8_t ChildLock;


/**********************************************************************/
/**********************************************************************/
/***********************************************************************
�Ӻ������ܣ��ϵ��ʼ��ϵͳ�Ĵ���
��ڲ�����
�������ݣ�
��ע��
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
	TRISC = 0x01;
	TRISD = 0x03;
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
��ڲ�����
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
��ڲ�����
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
//��������
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
			KeyOldFlag = i;			//�м�⵽����

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
								
								ref.childlock = 1;
					 }
					 else{
					 	ref.childlock = 0;

					 }
				 
				 }
	       }
          if(ref.childlock==1){
				Led4=1;
		 }

       #endif 
		if(KeyOldFlag & 0x01)
		{
				if(0 == (KeyREFFlag & 0x01)) //��ʱ����
				{
					KeyREFFlag |= 0x01;
					timerflg = timerflg ^ 0x01;
					if(timerflg ==1){
							Led8=1;
							ref.timerTim = 1;
					}
					else{
						     Led8=0;
							ref.timerTim = 0;

					}
				}
		}
		else
		{
			KeyREFFlag &= ~0x01;
			
		}
			
			if(KeyOldFlag & 0x02)  //���ٵ��ڰ���
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					KeyREFFlag |= 0x02;
					windflg ++;
					if(windflg==1){
						Led6=1;
						Led1=0;
					    Led9=0;
						Led7 =0;
						ref.windlevel =1;
						
					}
					else if(windflg ==2){ //2��
						Led1=1;
						Led6=0;
					    Led9=0;
						Led7 =0;
						ref.windlevel =2;
					}
					else if(windflg ==3){ //3��
						  Led9 =1;
						  Led1=0;
					      Led6=0;
						  Led7 =0;
						  ref.windlevel =3;
					}
					else if(windflg ==4){ //Auto 
						  ref.windlevel =4;
						  windflg=0;
						  Led7 =1;
						  Led9 =0;
						  Led1=0;
					      Led6=0;
						
					}

				}
			}
			else
			{
				KeyREFFlag &= ~0x02;
				Led2=0;
			}
			
			if(KeyOldFlag & 0x04) //�����û�����
			{

                 Delay_nms (3000);
				 Delay_nms (3000);
				if(KeyOldFlag & 0x04)
				{
					KeyREFFlag |= 0x04;
					ref.filterNet =1;
				    Led3=1;
				}
			}
			else
			{
				KeyREFFlag &= ~0x04;
				Led3=0;
			}
		
			
		}
	}
	else
	{
		KeyOldFlag = 0;
		KeyREFFlag = 0;
	}
	 ref.senddata=(ref.windlevel  | ref.filterNet<< 4 | ref.timerTim <<5 | ref.sleep <<6 |ref.childlock << 7 ) & 0xff;
}


/***********************************************************************
�������ܣ��ж���ں���
***********************************************************************/
void interrupt time0(void)
{
	if(TMR2IF)
	{
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
main������
***********************************************************************/
void main(void)
{
	uint8_t powerflg =0;
	asm("clrwdt");
	USART1_Init();
	Init_ic();
	Delay_nms(200);													//�ϵ���ʱ200ms
	Init_ram();	  //�ϵ����ֵ
	
	
	
	while(1)
	{
		OSCCON = 0x71;
	
		powerflg = HDKey_Scan(1);
		if(powerflg==1){
			LED_RED = 0;
			Led2=1;
			Set_Usart_Async();
			USART1_SendData();
			
		}else LED_RED =0 ;
		if(tcount >= 32)
		{
			tcount = 0;												//������ѭ��4ms
			Sys_set();
			//Display();
			#if (REL_SENDER_ENABLE == 1)//���Ժ궨���Ƿ�Ϊ1
				REL_SenderLoop();//�����ӳ���
			#endif
			__CMS_CheckTouchKey();	//ɨ�谴��
			Kscan();			//��������
		}
	}
}
/**********************************************************************/



