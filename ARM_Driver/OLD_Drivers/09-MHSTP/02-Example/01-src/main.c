/*
 * Main_prgram.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSTK_interface.h"
#include "MPORT_interface.h"


int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of GPIOB */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOB );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();

	while(1){

		for( u8 i = 0 ; i < 8 ; i++ ){

			HSTP_voidSendByteSynchronous( 1 << i );
			MSTK_voidSetBusyWait(500000);
		}

	}

}

