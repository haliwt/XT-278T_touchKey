
#include <cms.h>
#include "led.h"
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"

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
	static uint8_t childflg =0 ;
	unsigned int i = (unsigned int)((KeyFlag[1]<<8) | KeyFlag[0]);

	if(i)
	{
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;			//�м�⵽����

			buzf = 1;
			buzsec = 600;
		#if 0
			if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02))
			{
                 Delay_nms (3000);
				 childflg = childflg ^ 0x01;
				 if((KeyOldFlag & 0x01) && (KeyOldFlag & 0x02)){
				 if(childflg ==1){
							ChildLock =1;
				 }
				 else ChildLock = 0;
				 
				 }
	       }
          if(ChildLock ==1){



		  }

       #endif 
		if(KeyOldFlag & 0x01)
			{
				if(0 == (KeyREFFlag & 0x01))
				{
					KeyREFFlag |= 0x01;
				//	DispData ^= 0x01;
					Led1=1;
				}
			}
			else
			{
				KeyREFFlag &= ~0x01;
				Led1=0;
			}
			
			if(KeyOldFlag & 0x02)
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					KeyREFFlag |= 0x02;
				//	DispData ^= 0x02;
					Led2=1;
				}
			}
			else
			{
				KeyREFFlag &= ~0x02;
				Led2=0;
			}
			
			if(KeyOldFlag & 0x04)
			{
				if(0 == (KeyREFFlag & 0x04))
				{
					KeyREFFlag |= 0x04;
				//	DispData ^= 0x04;
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
}

/***********************************************
�������ƣ�Display
�������ܣ���ʾ����
��ڲ�������
���ڲ�������
��ע��
************************************************/
void Display()//ѭ��ɨ�����COM��
{
	//Com = 1;
	Led1 = 0;
	Led2 = 0;
	Led3 = 0;
	Led4 = 0;
	
	if(DispData & 0x01) //TouchKey 2 RA1
	  Led4 = 1;	//Led1 = 1;
	if(DispData & 0x02) //TouchKey 1  RA2
		Led2 = 1;
	if(DispData & 0x04)//TouchKey 0 RA0  
		Led3 = 1;
	
	
	

	
	
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
	Init_ic();
	Delay_nms(200);													//�ϵ���ʱ200ms
	Init_ram();														//�ϵ����ֵ
	
	while(1)
	{
		OSCCON = 0x71;
	
		powerflg = HDKey_Scan(1);
		if(powerflg==1)LED_RED = 1;
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



