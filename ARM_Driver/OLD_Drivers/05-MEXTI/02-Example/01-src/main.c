/*
 * Main_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MPORT_interface.h"
#include "MGPIO_interface.h"

#include "MNVIC_interface.h"
#include "MEXTI_interface.h"
#include "MSTK_interface.h"
#include "MAFIO_interface.h"


void EXTI1_CallBack(void){

	static u8 LOC_u8Tog = 0 ;
	TOG_BIT( LOC_u8Tog , 0 );
	MSTK_voidSetBusyWait(200000);
	MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , LOC_u8Tog );

}

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of GPIOB */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOB );
	/* Enable AFIO Clock From RCC */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_AFIO );
	/* Initializing The Direction Of The Pins */
	MPORT_voidInit();
	/*Initializing The NVIC With 2 Sub Priority & 2 Group Priority */
	MNVIC_voidInit();
	/* Initialize AFIO Peripheral */
	MAFIO_voidInit();
	/* Re-map EXTI Line To MGPIOB Line 1 */
	MAFIO_voidSetExternalInterruptConfiguration( MAFIO_EXTI1 , MAFIO_GPIOB );
	/* Enable EXTI1 From NVIC */
	MNVIC_voidEnablePeripheral( MNVIC_EXTI1 );
	/* Set The Call Back Function To The Handler Of EXTI1 before Enabling It */
	MEXTI_voidSetCallBack( MEXTI_LINE1 , EXTI1_CallBack );
	/* Set The Signal Latch Of EXTI1 and Enable It */
	MEXTI_voidSetSignalLatch(MEXTI_LINE1 , MEXTI_FALLING_EDGE);

	while(1){


	}

}

