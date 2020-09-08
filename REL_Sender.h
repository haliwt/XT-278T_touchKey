#ifndef _REL_SENDER_
#define _REL_SENDER_

#include "Touch_Kscan_Library.h"

// ���ݷ���ʹ��,1:ʹ�ܣ����಻ʹ��
#define REL_SENDER_ENABLE	0

/**************************************************************************
**************************�������������޸�*********************************
**************************************************************************/ 
void REL_SenderLoop();

//////////////////////////////////////////////////////
// ����ʵ�ֶ���
#include "iic_soft.h"
#define REL_PreSendCallBack()								I2C_WriteStart()
#define REL_SendByte(ch)									I2C_Write1bYTE(ch)
#define REL_EndSendCallBack()								I2C_WriteStop()

// �������Ͷ���
#ifndef s8
typedef int s32;
typedef short int s16;
typedef char s8;

typedef unsigned int u32;
typedef unsigned short int u16;
typedef unsigned char u8;
#endif

//////////////////////////////////////////////////////

// ��ͷ�ֽ�
#define REL_HEADER_BYTE	0xA0

// ��ͷ�ṹ
//#pragma pack(1)
//#pragma anon_unions
typedef struct _PackHeader
{
	u8 length;		//����,sizeof(PackHeader) + sizeof(PackStrcut) * n + 1
	union
	{
		u16 mask;
		struct
		{
			u8 packIdx : 4;		// �ְ�����,��0��ʼ
			u8 packIdxMax : 4;		// ��������
			u8 typeId;				// ����ID,����ʹ�õĽṹ��
		}m;
	};
}PackHeader;
//#pragma pack()

#define REL_TYPE_ID_USE	0x07

typedef struct _PackStrcut
{
	u16 rawData;					//�˲�ֵ
	u16 thresholdA;					//��ֵ1
	#ifdef RS_VALUE
	u16 thresholdB;				 	//��ֵ2
	#endif
	u16 noiseData;					//����ֵ
}PackStrcut;

// ���շ��ͺ���					
#define REL_SendStart(packHeader)	\
	{u8 _checkSum = 0;\
	u8 _i;\
	u8 *_bufPoint;\
	REL_PreSendCallBack();\
	REL_SendByte(REL_HEADER_BYTE);\
	_bufPoint = (u8*)&packHeader;\
	for(_i = 0;_i < sizeof(packHeader);_i++,_bufPoint++) {\
		REL_SendByte(*_bufPoint);\
		_checkSum += *_bufPoint;\
	}
	
#define REL_SendNext(packStrcut) \
	_bufPoint = (u8*)&packStrcut;\
	for(_i = 0;_i < sizeof(packStrcut);_i++,_bufPoint++) {\
		REL_SendByte(*_bufPoint);\
		_checkSum += *_bufPoint;\
	}

#define REL_SendEnd()	\
	REL_SendByte(_checkSum);\
	REL_EndSendCallBack();}
	
#endif /*_REL_SENDER_USER_*/

