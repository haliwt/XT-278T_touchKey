
#include <cms.h>
#include "main.h"
#include "delay.h"
#include "mytype.h"
#include "CheckTouchKey.h"
#include "hd_key.h"
/**********************************************************************/
/*ȫ�ֱ�������*/
/**********************************************************************/
volatile unsigned char tcount;
volatile bit buzf;
volatile unsigned int buzsec;

volatile unsigned char DispData;
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
	WDTCON = 0;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
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
	WDTCON = 0;
	//TRISA = 0B00000000;
	//TRISB = 0B00000000;
	HDKEY_LED_Init();
	//TRISC = 0x00;
	//TRISD = 0x00;
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
     *
     *Function Name:void Kscan(void)
     *
     *
     *
     
***********************************************************************/
void Kscan()
{
	static unsigned int KeyOldFlag = 0;
	unsigned int i = (unsigned int)((KeyFlag[1]<<8) | KeyFlag[0]);
	if(i)
	{
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;			//�м�⵽����
			buzf = 1;
			buzsec = 600;

			if(0x1&i){DispData ^= 0x01;}
			else if(0x2&i){DispData ^= 0x02;}
			else if(0x4&i){DispData ^= 0x04;}
			else if(0x8&i){DispData ^= 0x08;}
		}
	}
	else
	{
		KeyOldFlag = 0;
	}
}



/***********************************************
�������ƣ�Display
�������ܣ���ʾ����
��ڲ�������
���ڲ�������
��ע��
************************************************/
#if 0
void Display()//ѭ��ɨ�����COM��
{
	Com = 1;
	Led1 = 0;
	Led2 = 0;
	Led3 = 0;
	Led4 = 0;
	
	if(DispData & 0x01)
		Led1 = 1;
	if(DispData & 0x02)
		Led2 = 1;
	if(DispData & 0x04)
		Led3 = 1;
	if(DispData & 0x08)
		Led4 = 1;
		
	Com = 0;
	
	SEGEN0 = 0X80;
	SEGEN1 = 0X07;
	SEGEN2 = 0X50;
}
#endif 
/***********************************************************************
	*
	*Functin Name: void interrupt time0(void)
	*Function :interrupt function
	*
	*
	*
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
	/******************************************************************/
	asm("clrwdt");
	Init_ic();
	Delay_nms(200);													//�ϵ���ʱ200ms
	Init_ram();														//�ϵ����ֵ
	
	while(1)
	{
		OSCCON = 0x71;
		if(tcount >= 32)
		{
			tcount = 0;												//������ѭ��4ms
		//	Display();
			__CMS_CheckTouchKey();	//ɨ�谴��
			Kscan();			//��������
			Sys_set();
		}
	}
}
/**********************************************************************/



