#include "keyled.h"

/****************************************************
	*
	*Function Name: void TimerTiming_Led(void);
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void TimerTiming_Led(void)
{

 


}
/****************************************************
	*
	*Function Name: void WindLevel_SleepLed(void)
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void WindLevel_SleepLed(void)
{
    Led1=1;
	Led6=0;
	Led9=0;
	Led7 =0;
	Led8= 0;
	Led4 =0; //turn OFF Net
	Led3 = 0;
	Led2=0;


}
/****************************************************
	*
	*Function Name: void WindLevel_MiddleLed(void)
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void WindLevel_MiddleLed(void)
{
	Led9=1;
	Led2= 1; //Timer key lamp led
	Led4 =1; // NET KEY LED ,ON
	Led6=0;
	Led1=0;
	Led7 =0;

}
/****************************************************
	*
	*Function Name: void WindLevel_HighLed(void)
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void WindLevel_HighLed(void)
{
	Led7 =1;
	Led2= 1; // Timer key lamp led
	Led4 =1; // NET KEY lamp LED 
	Led1=0;
	Led6=0;
	Led9 =0;	

}
/****************************************************
	*
	*Function Name: void WindLevel_MiddleLed(void)
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void WindLevel_AutoLed(void)
{
	Led6 =1;
	Led2= 1; //Timer KEY lamp led
	Led4 =1; //NET KEY lamp led
	Led9 =0;
	Led1=0;
	Led7=0;

}
/****************************************************
	*
	*Function Name: void TouchKeyLed_Off(void)
	*Function :
	*Input Ref:No
	*Return Ref:No
	*
*****************************************************/
void TouchKeyLed_AllOff(void)
{
	Led1=0;
	Led6=0;
	Led9=0;
	Led7 =0;
	Led8= 0;
	Led4 =0; //turn OFF Net
	Led3 = 0;
	Led2=0;

}