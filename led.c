#include "led.h"

/****************************************************
	*
	*Function Name: void TunrnOff_ALL_LED(void)
	*Function :
	*
	*
*****************************************************/
void TunrnOff_ALL_LED(void)
{
   Led1 = 0;
   Led2 = 0;
   Led3 = 0;
   Led4 = 1; //control 4 led on and off 
   Led5 = 0;
   Led6 = 0;
   Led7 = 0;
   Led8 = 0;
   Led9 = 0;


}

/****************************************************
	*
	*Function Name: void NET_LED_On(void)
	*Function :
	*
	*
*****************************************************/
void NET_LED_On(void)
{
    Led4 =0 ;

}

