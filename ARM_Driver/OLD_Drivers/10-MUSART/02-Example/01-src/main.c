/*
 * Main_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MUSART1_interface.h"
#include "MSTK_interface.h"
#include "MPORT_interface.h"
#include "MGPIO_interface.h"

u8 * LOC_u8Ptr = NULL ;

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of GPIOB */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_USART1 );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();
	/* Initialize USART1 */
	MUSART1_voidInit();

	while(1){

		MUSART1_voidSendStringSynch((u8 *)"Hello IMT\r\n");
		LOC_u8Ptr = MUSART1_PtrReadStringSynch();

		if( LOC_u8Ptr[0] == 'H' && LOC_u8Ptr[1] == 'i' ){

			MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , MGPIO_u8_HIGH );

		}
		else{

			MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , MGPIO_u8_LOW );

		}
		MSTK_voidSetBusyWait(1000000);

	}

}

