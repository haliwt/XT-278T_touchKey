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
	
	WPUC = 0B00000001;
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
		if(key_up&&(POWER_KEY== 0))
		{
		    key_up =0 ;
			Delay_nms(20);
			if(POWER_KEY== 0 ) 	return POWER_PRES;
		
		}
		else if(POWER_KEY==1)key_up=1;
		return 0;	//没有按键按下
}
/****************************************************
	*
	*Function Name: void PowerOn_SendData_Init(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: NO
	*
*****************************************************/
void PowerOn_SendData_Init(void)
{
	 LED_POWER_RED = 0;
	WindLevel_AutoLed();
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
/****************************************************
	*
	*Function Name: void PowerOff_SendData_Fun(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: NO
	*
*****************************************************/
void PowerOff_SendData_Fun(void)
{
		LED_POWER_RED = 1;
		TouchKeyLed_AllOff();
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