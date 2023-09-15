/*
 * MEXTI_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MEXTI_interface.h"
#include "MEXTI_private.h"
#include "MEXTI_config.h"

void ( *MEXTI_CallBack[16] )( void );

void MEXTI_voidInit(void)
{

	/* Enable Specific EXTI Line Based On The Configured Value In MEXTI_config.h */
	#if		( MEXTI_LINE >= MEXTI_LINE0 ) && ( MEXTI_LINE <= MEXTI_LINE15 )

		SET_BIT( MEXTI -> IMR , MEXTI_LINE );


	#else
	#error ("Wrong Externl Interrupt Line !")

	#endif

	/* Choose EXTI Signal Latch Based On The Configured Value In MEXTI_config.h */
	#if		( MEXTI_SENSE_MODE == MEXTI_FALLING_EDGE ) && ( ( MEXTI_LINE >= MEXTI_LINE0 ) && ( MEXTI_LINE <= MEXTI_LINE15 ) )

		SET_BIT( MEXTI -> FTSR , MEXTI_LINE );

	#elif	( MEXTI_SENSE_MODE == MEXTI_RISING_EDGE   ) && ( ( MEXTI_LINE >= MEXTI_LINE0 ) && ( MEXTI_LINE <= MEXTI_LINE15 ) )

		SET_BIT( MEXTI -> RTSR , MEXTI_LINE );

	#elif	( MEXTI_SENSE_MODE == MEXTI_ON_CHANGE     ) && ( ( MEXTI_LINE >= MEXTI_LINE0 ) && ( MEXTI_LINE <= MEXTI_LINE15 ) )

		SET_BIT( MEXTI -> RTSR , MEXTI_LINE );
		SET_BIT( MEXTI -> FTSR , MEXTI_LINE );

	#else

	#error ("Wrong Externl Interrupt Sense Mode !")

	#endif

    CLR_BIT( MEXTI -> IMR , MEXTI_LINE );

}
void MEXTI_voidSetSignalLatch( u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode )
{
	/* Choosing The Sense Mode Of Specific EXTI Line Passed To This Function */
	switch(Copy_u8EXTISenseMode)
	{

	case	MEXTI_RISING_EDGE		:	SET_BIT( MEXTI -> RTSR , Copy_u8EXTILine );	break;
	case	MEXTI_FALLING_EDGE	    :	SET_BIT( MEXTI -> FTSR , Copy_u8EXTILine );	break;
	case	MEXTI_ON_CHANGE		    :	SET_BIT( MEXTI -> RTSR , Copy_u8EXTILine );
										SET_BIT( MEXTI -> FTSR , Copy_u8EXTILine );	break;
	}

	/* Enable Specific EXTI Line Passed To This Function */
	SET_BIT( MEXTI -> IMR , Copy_u8EXTILine );
}
void MEXTI_voidEnableEXTI( u8 Copy_u8EXTILine )
{
	/* Enable Specific EXTI Line Passed To This Function */
	SET_BIT( MEXTI -> IMR , Copy_u8EXTILine );
}
void MEXTI_voidDisableEXTI( u8 Copy_u8EXTILine )
{
	/* Disable Specific EXTI Line Passed To This Function */
	CLR_BIT( MEXTI -> IMR , Copy_u8EXTILine );

}

void MEXTI_voidSoftWareTrigger( u8 LOC_u8EXTILine ){

	/* Trigger Software Interrupt Of Specific EXTI Line Passed To This Function */
	SET_BIT( MEXTI->SWIER , LOC_u8EXTILine );

}


void MEXTI_voidSetCallBack( u8 LOC_u8EXTILine , void ( *Copy_ptrCallBack )( void ) ){

	/* Set The Call Back To The Handler Of EXTI Of Specific Line */
	if( ( Copy_ptrCallBack != NULL ) && (  LOC_u8EXTILine <= MEXTI_LINE15 ) ){

		MEXTI_CallBack[ LOC_u8EXTILine ] = Copy_ptrCallBack ;
		MEXTI_CallBackNumber             = LOC_u8EXTILine   ;

	}

}


void EXTI0_IRQHandler(void){

	MEXTI_CallBack[ 0 ]();
	SET_BIT( MEXTI->PR , 0 );

}

void EXTI1_IRQHandler(void){

	MEXTI_CallBack[ 1 ]();
	SET_BIT( MEXTI->PR , 1 );

}

void EXTI2_IRQHandler(void){

	MEXTI_CallBack[ 2 ]();
	SET_BIT( MEXTI->PR , 2 );

}

void EXTI3_IRQHandler(void){

	MEXTI_CallBack[ 3 ]();
	SET_BIT( MEXTI->PR , 3 );

}

void EXTI4_IRQHandler(void){

	MEXTI_CallBack[ 4 ]();
	SET_BIT( MEXTI->PR , 4 );

}

void EXTI9_5_IRQHandler(void){

	if( MEXTI_CallBackNumber == MEXTI_LINE5 ){

		MEXTI_CallBack[ 5 ]();
		SET_BIT( MEXTI->PR , 5 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE6 ){

		MEXTI_CallBack[ 6 ]();
		SET_BIT( MEXTI->PR , 6 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE7 ){

		MEXTI_CallBack[ 7 ]();
		SET_BIT( MEXTI->PR , 7 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE8 ){

		MEXTI_CallBack[ 8 ]();
		SET_BIT( MEXTI->PR , 8 );

	}

	else if( MEXTI_CallBackNumber == MEXTI_LINE9 ){

		MEXTI_CallBack[ 9 ]();
		SET_BIT( MEXTI->PR , 9 );

	}

}

void EXTI15_10_IRQHandler(void){

	if( MEXTI_CallBackNumber == MEXTI_LINE10 ){

		MEXTI_CallBack[ 10 ]();
		SET_BIT( MEXTI->PR , 10 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE11 ){

		MEXTI_CallBack[ 11 ]();
		SET_BIT( MEXTI->PR , 11 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE12 ){

		MEXTI_CallBack[ 12 ]();
		SET_BIT( MEXTI->PR , 12 );

	}
	else if( MEXTI_CallBackNumber == MEXTI_LINE13 ){

		MEXTI_CallBack[ 13 ]();
		SET_BIT( MEXTI->PR , 13 );

	}

	else if( MEXTI_CallBackNumber == MEXTI_LINE14 ){

			MEXTI_CallBack[ 14 ]();
			SET_BIT( MEXTI->PR , 14 );

	}

	else if( MEXTI_CallBackNumber == MEXTI_LINE15 ){

			MEXTI_CallBack[ 15 ]();
			SET_BIT( MEXTI->PR , 15 );

	}

}
