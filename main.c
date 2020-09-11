
#include <cms.h>
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
#include "usart1.h"
#include "keyled.h"
#include "slideled.h"


/**********************************************************************/
/*ȫ�ֱ�������*/
/**********************************************************************/
volatile unsigned char tcount;
volatile bit buzf;
volatile unsigned int buzsec;

volatile unsigned char DispData;

uint16_t usartNum;
uint8_t senddata[1];
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
	TRISC = 0x00;
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
		
		if(KeyOldFlag & 0x01)
		{
				if(0 == (KeyREFFlag & 0x01)) //KEY 2 
				{
					keyLed4=0;
					keyLed3=0;
					keyLed2=1;
					keyLed1=0;
				}
		}
		
			
			if(KeyOldFlag & 0x02)  //KEY1 ---keyLed2
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					keyLed4=0;
					keyLed3=0;
					keyLed2=0;
					keyLed1=1;

				}
			}
			
		  if(KeyOldFlag & 0x04) //KEY4 POWER KEY
			{
				if(0 == (KeyREFFlag & 0x04))
				{
					keyLed4=1;
					keyLed3=0;
					keyLed2=0;
					keyLed1=0;

				}

			}
		   if(KeyOldFlag & 0x08) //KEY3  Wind KEY
			{
				if(0 == (KeyREFFlag & 0x08))
				{
					keyLed4=0;
					keyLed3=1;
					keyLed2=0;
					keyLed1=0;
				}

			}
		   if(KeyOldFlag & 0x10) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x10))
				{
					SldLed_1 =1;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
		   if(KeyOldFlag & 0x20) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x20))
				{
					SldLed_1 =0;
					SldLed_2 = 1;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
		   if(KeyOldFlag & 0x40) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x40))
				{
				   SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =1;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
		   if(KeyOldFlag & 0x80) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x80))
				{
					SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =1;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;
				}

			}
		   if(KeyOldFlag & 0x100) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x100))
				{
					SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =1;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;
				}

			}
		   if(KeyOldFlag & 0x200) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x200))
				{
					SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =1;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
		   if(KeyOldFlag & 0x400) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x400))
				{
					SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =1;
					SldLed_8 =0;

				}

			}
			if(KeyOldFlag & 0x800) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x800))
				{
					SldLed_1 =0;
					SldLed_2 = 0;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =1;

				}

			}
			if(KeyOldFlag & 0x1000) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x1000))
				{
					SldLed_1 =1;
					SldLed_2 = 1;
					SldLed_3 =0;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
			if(KeyOldFlag & 0x2000) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x2000))
				{
					SldLed_1 =0;
					SldLed_2 =1;
					SldLed_3 =1;
					SldLed_4 =0;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
			if(KeyOldFlag & 0x4000) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x4000))
				{
					SldLed_1 =0;
					SldLed_2 =0;
					SldLed_3 =1;
					SldLed_4 =1;
					SldLed_5 =0;
					SldLed_6 =0;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
			if(KeyOldFlag & 0x8000) //�����û�����
			{
				if(0 == (KeyREFFlag & 0x8000))
				{
					SldLed_1 =0;
					SldLed_2 =0;
					SldLed_3 =0;
					SldLed_4 =1;
					SldLed_5 =1;
					SldLed_6 =1;
					SldLed_7 =0;
					SldLed_8 =0;

				}

			}
		}
	}
	else
	{
		KeyOldFlag = 0;
		KeyREFFlag = 0;
	}
	if(usartNum >=10000){
		usartNum =0;
		 Sys_set ();
		ref.powerflg=1;
	 
	  USART1_SendData();
	}
}


/***********************************************************************
�������ܣ��ж���ں���
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
main������
***********************************************************************/
void main(void)
{
    static uint8_t poweron=0;
	asm("clrwdt");
	USART1_Init();
	Init_ic();
	Delay_nms(200);													//�ϵ���ʱ200ms
	Init_ram();	  //�ϵ����ֵ
	
	
	
	while(1)
	{
		OSCCON = 0x71;
	
	

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



