/*
 * Main_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MSTK_interface.h"
#include "MPORT_interface.h"
#include "MGPIO_interface.h"
#include "MSPI1_interface.h"
#include "HTFT_interface.h"
#include "IMT.h"


int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of SPI1 */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_SPI1 );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();
	/* Initialize SPI1 */
	MSPI1_voidInit();
	/* Initialize TFT */
	HTFT_voidInitialize();
	/* Draw Image */
	HTFT_voidDisplayImage( Imt_Image );

	while(1){



	}

}

