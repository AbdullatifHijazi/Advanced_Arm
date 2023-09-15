/*
 * Main_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MEXTI_interface.h"
#include "MNVIC_interface.h"
#include "MSTK_interface.h"
#include "MPORT_interface.h"

#include "HIR_interface.h"


void IR_CallBack( u8 Copy_u8Data ){

	switch( Copy_u8Data ){

	case HIR_POWER_BUTTON : MGPIO_enumSetPinValue( MGPIO_u8_PORTB , MGPIO_u8_PIN0 , MGPIO_u8_HIGH ); break;
	case HIR_MODE_BUTTON  : MGPIO_enumSetPinValue( MGPIO_u8_PORTB , MGPIO_u8_PIN0 , MGPIO_u8_LOW  ); break;

	}

}

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of GPIOB */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOB );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();
	/* Initialize STK */
	MSTK_voidInit();
	HIR_voidInit();
	/* Set IR CallBack Function */
	HIR_voidSetCallBack( IR_CallBack );
	/* Initialize EXTI */
	MEXTI_voidInit();
	/* Enable EXTI */
	MEXTI_voidEnableEXTI( MEXTI_LINE0 );
	/* Initialize NVIC */
	MNVIC_voidInit();
	/* Enable EXTI0 From NVIC */
	MNVIC_voidEnablePeripheral( MNVIC_EXTI0 );
	/* Initialize IR Sensor */

	while(1){

	}

}

