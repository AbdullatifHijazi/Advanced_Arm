/*
 * Main_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"

#include "HLDM_interface.h"

u8 Hamok4a[]={ 0, 152, 87, 253, 87, 152, 0, 0 };

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of GPIOB */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOB );
	/* Initialize LDM Display */
	HLDM_voidInit();

	while(1){

		/* Draw Hamoksha On LDM */
		HLDM_voidDisplay(Hamok4a);

	}

}

