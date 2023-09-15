/*
 * Main_Program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MPORT_interface.h"
#include "MGPIO_interface.h"

#include "MSTK_interface.h"

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Initializing The Direction Of The Pins */
	MPORT_voidInit();
	/* Initializing STK Timer */
	MSTK_voidInit ();

	while(1){

		/* Setting The GPIOA Pin0 To HIGH */
		MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , MGPIO_u8_HIGH );
		/* Waiting 1 Second */
		MSTK_voidSetBusyWait(1000000);
		/* Setting The GPIOA Pin0 To LOW */
		MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , MGPIO_u8_LOW  );
		/* Waiting 1 Second */
		MSTK_voidSetBusyWait(1000000);

	}

}

