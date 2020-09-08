/*

*/
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_

#include "TouchKeyConst.h"
#pragma warning disable 752,759
//�ӿں�������
extern void __CMS_CheckTouchKey(void);		//����ɨ�������̺���,������2.5ms~5ms�ڵ���
extern void __CMS_GetTouchKeyValue(void);//�˺��������жϣ������ж�ɨ��ʱ��125us
extern volatile bit b_kerr;				//��λ������־
extern volatile bit KeyOnceHave,KeyOnceOver;//���߻�����
//ÿ��������Ӧ�ڼĴ�����1��λ,�ɸ�����һһ��Ӧ
//KeyFlag[0]��Ӧ��Key7,...,Key1,Key0
//KeyFlag[1]��Ӧ��Key15,...,Key9,Key8
//������Чʱ��ӦλΪ1,��ЧʱΪ0
extern volatile unsigned char KeyFlag[2];
//-------------------------------------------------------
//ʹ��ʱ����ʵ��Ӳ�������޸��������������������
//ע������Ĵ�С����С�ڼ��İ�������

//���ͨ���趨,ΪC_KCHS0��C_KCHS15����֮һ
const unsigned char Table_KeyChannel[] = {
	C_KCHS0,		//����1��Ӧ����ͨ��
	C_KCHS1,		//����2��Ӧ����ͨ��
	C_KCHS2,        //����3��Ӧ����ͨ��
	
};

//�仯��ֵ1
const unsigned int Table_KeyDown[] = 
{
	69,
	58,
	78,
	70,
};

//�仯��ֵ2,һ�����������ֵ1��𲻴�
const unsigned int Table_KeyDown_Pro[] = 
{
	69,
	62,
	77,
	67,
};
//������ֵ�޵�����,Ĭ��ֵΪDAT_STEP3��DAT_STEP0~DAT_STEP5
//�������ݹ����쳣ʱ���������Ӵ˵�λ
//�������ݹ�С�쳣ʱ�����Լ��ٴ˵�λ
const unsigned int Table_Dat_Step[] = 
{
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3,
	DAT_STEP3
};
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
���津��Ч����������
*/
//����ⰴ������,����
#define 	C_KEY_TOTAL		4

//����������������C_KEY_SHAKE
#define		C_KEY_SHAKE		3//2~8

//�����ſ���������C_OFF_SHAKE
#define		C_OFF_SHAKE		3//2~8

//������ֵ
#define		VOL_VALUE		10			//�޸����µ����������ֵ*2,����ֵΪ10

//����ֵ
#define		SLU_VALUE		10			//��ָ���ºͷſ��л�������ֵ,��ֵ��С�ڵ���VOL_VALUE

//������׼ֵ������������
#define		CM_BASE			10			//����ʱ��ԼΪ(���������ʱ��4ms*2 + ��������*1.5) * CM_BASE

//ͬʱ���������Ч������,������ֵ����Ϊ�Ǹ���
#define		C_VALID_KEY		1

//�������������Чʱ��,��ɨ��ʱ�䣨����5ms��Ϊ��׼����,Ϊ0ʱ������
#define		C_VALID_TIME	(1000/5)*20//20S

/*-------------------------------------------------------
��������ͨ������²����޸�
-------------------------------------------------------*/
//�쳣�ж�ʹ�ܣ���TKֵ�쳣���½�������Ӧ
#define		UNNOL_CHECK		1
//�쳣�ж��Իָ��������������ٽ����Իָ�
#define		UNNOL_TIMES		5

//��Ƶʹ��
//0���ر�
//1�����������Ͷ���ɧ��
#define		C_TP_EN			1

//�˲�ʹ��
//0���ر�
//1������
//��������ֵ��ͬʱ�ή����Ӧ�ٶ�
//�˹��ܹر�ʱ��������ֵVOL_VALUE������һ��
#define		LVBO_EN			2//1

//������λ��
#define 	TK_TIME			TK_TIME3//0~7 (TK_TIME+8)λ

//��RSʹ��
#define 	RS_LVBO			0//

#define 	RS_VALUE		50//Ĭ�ϼ���
/***********************************************************
��������������޸�
***********************************************************/
const unsigned char KeyTotalNumber = C_KEY_TOTAL;
const unsigned char KeyShakeCounter = C_KEY_SHAKE;
const unsigned char OffShakeCounter = C_OFF_SHAKE;
const unsigned char VolValue = VOL_VALUE;
const unsigned char SluValue = SLU_VALUE;
const unsigned char CmBase = CM_BASE;
const unsigned char KeyValidNumber = C_VALID_KEY;
const unsigned int  KeyValidTime = C_VALID_TIME;
//-------------------------------------------------------
const unsigned char UnNol_Check = UNNOL_CHECK;
const unsigned char UnNol_Times = UNNOL_TIMES;
const unsigned char C_Tp_En = C_TP_EN;
const unsigned char TK_Time = TK_TIME;
const unsigned char RS_LvBo = RS_LVBO;
const unsigned char RS_Value = RS_VALUE;
const unsigned char LvBo_En = LVBO_EN;
//--------------------------------------------------
#endif





