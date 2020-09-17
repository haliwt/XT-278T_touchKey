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
/****************************************************
	*
	*Function Name: uint8_t HDKey_Scan(uint8_t mode)
	*Function :
	*Inpute Ref: 0 ---不支持连续按键
	*Return Ref: 0 --没有按键按下， 1---有按键按下
	*
*****************************************************/
uint8_t HDKey_Scan(uint8_t mode)
{
	
		static uint8_t key_up=1;	 //°´¼üËÉ¿ª±êÖ¾
		if(mode==1)key_up=1;	// 支持连续按键
		if(key_up&&(POWER_KEY== 1))
		{
		    key_up =0 ;
			Delay_nms(20);
			if(POWER_KEY== 1 ) 	return POWER_PRES;
		
		}else if(POWER_KEY==0)key_up=1;
		return 0;	//没有按键按下
}

