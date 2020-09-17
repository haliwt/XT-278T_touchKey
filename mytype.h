#ifndef _MYTYPE_H_
#define _MYTYPE_H_

/*******************************************************
					λ����
********************************************************/
#define	Set(x,y)	((x) |= (1 << (y)))				//set up "1"
#define	Clr(x,y)	((x) &= ~ (1 << (y)))			//set up "0"

#define	b0(x,y)		(((x) & (1 << (y))) == 0)		//λ0�ж� if(b0(x,y)) �ж��Ƿ�Ϊ0
#define	b1(x,y)		((x) & (1 << (y)))				//λ1�ж� if(b1(x,y)) �ж��Ƿ�Ϊ1
/*******************************************************
					�궨��
********************************************************/
#define uchar	unsigned char
#define uint	unsigned int
#define ulong	unsigned long


typedef uchar uint8_t;
typedef uint  int8_t;
typedef  ulong  uint16_t;

#endif
