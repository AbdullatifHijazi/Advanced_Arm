/*
 * MHIR_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MSTK_interface.h"
#include "MEXTI_interface.h"
#include "MGPIO_interface.h"

#include "HIR_interface.h"
#include "HIR_private.h"
#include "HIR_config.h"

volatile u32 FrameData[50] = {0} ;
volatile u8  StartFlag     =  0  ;
volatile u8  EdgeCounter   =  0  ;
volatile u8  Data          =  0  ;


void ( *HIR_CallBack )( u8 Copy_u8Data ) ;


void HIR_voidInit( void ){

	/* Set HIR_voidGetFrame Function To EXTI Handler */
	MEXTI_voidSetCallBack( HIR_OUTPUT_PIN , HIR_voidGetFrame );

}

static void HIR_voidTakeAction( void ){

	u8 LOC_u8Iterator = 0 ;
	Data              = 0 ;

	/* Check The Start Of IR Frame */
	if( ( FrameData[0] >= 10000 ) && ( FrameData[0] <= 14000 ) ){

		/* Convert The Time Calculated By HIR_voidGetFrame Function To Logic One Or Logic Zero */
		for( LOC_u8Iterator = 0 ; LOC_u8Iterator < 8 ; LOC_u8Iterator++ ){

			if( ( FrameData[ 17 + LOC_u8Iterator ] >= 2000 ) && ( FrameData[ 17 + LOC_u8Iterator ] <= 2300 ) ){

				SET_BIT( Data , LOC_u8Iterator );

			}else{

				CLR_BIT( Data , LOC_u8Iterator );

			}

		}

		HIR_CallBack( Data );

	}else{  /* Invalid Frame */  }

	StartFlag    = 0 ;
	FrameData[0] = 0 ;
	EdgeCounter  = 0 ;

}

static void HIR_voidGetFrame( void ){

	/* Calculate Time between Each Pulse */
	if( StartFlag == 0 ){

		MSTK_voidSetIntervalSingle( 1000000 , HIR_voidTakeAction );
		StartFlag = 1 ;

	}else{

		FrameData[ EdgeCounter ] = MSTK_u32GetElapsedTime();
		MSTK_voidSetIntervalSingle( 1000000 , HIR_voidTakeAction );
		EdgeCounter++ ;

	}

}

void HIR_voidSetCallBack( void (*Copy_ptrCallBack)(u8 Copy_u8Data) ){

	/* Set The Call Back Function To IR  */
	HIR_CallBack = Copy_ptrCallBack ;

}
