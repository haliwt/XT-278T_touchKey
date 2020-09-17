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


	WPUA = 0B00000001;				//配置上拉情况
	WPUB = 0B00000000;
	WPUC = 0B00000000;
	
	TRISA = 0B00000000;
	TRISB = 0B00000000;

	TRISC = 0B00000001;
	TRISD = 0x00;
	
}
