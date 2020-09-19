#include "hdkey.h"
#include "hdkey.h"


/*****************************************************************
	*
	*Function Name :void Flash_DisplayNumber(void)
	*Function:read flash data
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************/
void HDKEY_LED_Init(void)
{
	TRISC = 0B00000001;
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
			Delay_nms(10);
			if(POWER_KEY== 1 ) 	return POWER_PRES;
		
		}
		else if(POWER_KEY==0)key_up=1;
		return 0;	//没有按键按下
}
