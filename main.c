
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

uint16_t usartNum;
uint8_t senddata[2];
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
//����������
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
								
								ref.childLock = 1;
								Led4=1;
								 USART1_SendData();
					 }
					 else{
					 	ref.childLock = 0;
						Led4=0;
						 USART1_SendData();

					 }
				 
				 }
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
							 USART1_SendData();
					}
					else{
						     Led8=0;
							ref.timerTim = 0;
							 USART1_SendData();

					}
				}
		}
		
			
			if(KeyOldFlag & 0x02)  //���ٵ��ڰ���
			{
				if(0 == (KeyREFFlag & 0x02))
				{
					KeyREFFlag |= 0x02;
					windflg ++;
					if(windflg==1){
						
						ref.windlevel =1;  //˯�߷�
						Led1=1;
						Led6=0;
					    Led9=0;
						Led7 =0;
						Led8= 0;
						Led4 =1;
						Led3 = 0;
						Led2=0;
						 USART1_SendData();
						
					}
					else if(windflg ==2){ //2��
						Led9=1;
						Led2= 1; //��ʱ��������
						Led4 =0; //���������� ��
						Led6=0;
					    Led1=0;
						Led7 =0;
						
						ref.windlevel =2;
						 USART1_SendData();
					}
					else if(windflg ==3){ //3��
						  Led7 =1;
						  Led2= 1; //��ʱ��������
						  Led4 =0; //���������� ��
						  Led1=0;
					      Led6=0;
						  Led9 =0;
						  ref.windlevel =3;
						   USART1_SendData();
					}
					else if(windflg ==4){ //Auto 
						  ref.windlevel =4;
						  windflg=0;
						  Led6 =1;
						  Led2= 1; //��ʱ��������
						  Led4 =0; //���������� ��
						  Led9 =0;
						  Led1=0;
					      Led7=0;
						   USART1_SendData();
						
					}

				}
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
					 USART1_SendData();
				}
			}
		
		
			
		}
	}
	else
	{
		KeyOldFlag = 0;
		KeyREFFlag = 0;
	}
	if(usartNum >=1000){
		usartNum =0;
		// Sys_set ();
		ref.powerflg=1;
	  senddata[0]=(ref.windlevel  | ref.filterNet<< 4 | ref.timerTim <<5 |ref.childLock << 6|ref.powerflg<<7 ) & 0xff;
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
	   #if 0
		poweron= HDKey_Scan(1);
		if(poweron==1){
			LED_RED = 1;
			ref.powerflg=1;
		}
		#endif 
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



