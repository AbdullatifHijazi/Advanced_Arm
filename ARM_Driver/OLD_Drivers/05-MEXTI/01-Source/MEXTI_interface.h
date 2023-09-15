/*
 * MEXTI_INTERFACE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */
 
#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

/* MEXTI Modes */

#define		 MEXTI_FALLING_EDGE		1

#define		 MEXTI_RISING_EDGE		3

#define		 MEXTI_ON_CHANGE		5

/* MEXTI Lines */

#define		 MEXTI_LINE0			0

#define		 MEXTI_LINE1			1

#define		 MEXTI_LINE2			2

#define		 MEXTI_LINE3			3

#define		 MEXTI_LINE4			4

#define		 MEXTI_LINE5			5

#define		 MEXTI_LINE6			6

#define		 MEXTI_LINE7			7

#define		 MEXTI_LINE8			8

#define		 MEXTI_LINE9			9

#define		 MEXTI_LINE10			10

#define		 MEXTI_LINE11			11

#define		 MEXTI_LINE12			12

#define		 MEXTI_LINE13			13

#define		 MEXTI_LINE14			14

#define		 MEXTI_LINE15			15

typedef enum
{ 
	MEXTI_LINE0 = 0,
	MEXTI_LINE1, 
	MEXTI_LINE2, 
	MEXTI_LINE3, 
	MEXTI_LINE4, 
	MEXTI_LINE5, 
	MEXTI_LINE6, 
	MEXTI_LINE7, 
	MEXTI_LINE8, 
	MEXTI_LINE9, 
	MEXTI_LINE10, 
	MEXTI_LINE11, 
	MEXTI_LINE12, 
	MEXTI_LINE13, 
	MEXTI_LINE14, 
	MEXTI_LINE15 ,
}EXTI_LineNumber_t;

void MEXTI_voidInit(void);
void MEXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode);
void MEXTI_voidEnableEXTI(u8 Copy_u8EXTILine);
void MEXTI_voidDisableEXTI(u8 Copy_u8EXTILine);
void MEXTI_voidSoftWareTrigger( u8 LOC_u8EXTILine );

void MEXTI_voidSetCallBack( u8 LOC_u8EXTILine , void ( *Copy_ptrCallBack )( void ) );

#endif /* MEXTI_INTERFACE_H_ */
