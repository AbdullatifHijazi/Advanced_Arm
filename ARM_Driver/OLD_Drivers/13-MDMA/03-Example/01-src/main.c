/*
 *  Main_program.c
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MPORT_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "MDMA_interface.h"

u32 Source[1000]={0};
u32 Destination[1000];

u32 Source2[1000]={0};
u32 Destination2[1000];

u16 i = 0;

/* Put a break at line 29 to check the speed between the CPU and DMA then read the variable i */
void DMA_voidCallBack(void)
{

	MDMA_voidClearFlag( MDMA_CHANNEL1 , MDMA_TCIF );

}

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of SPI1 */
	MRCC_enumEnablePerClock( MRCC_AHB  , MRCC_DMA1 );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();
	/* Initialize NVIC */
	MNVIC_voidInit();
	/* Enable USART1 From NVIC */
	MNVIC_voidEnablePeripheral( MNVIC_DMA );

	MDMA_voidSetConfiguratin( MDMA_CHANNEL1 , MDMA_MEM_TO_MEM , MDMA_DISABLE_CIRC , MDMA_MEM_INC_EN , MDMA_MEM_INC_EN ,
			MDMA_WORD , MDMA_WORD , MDMA_VERY_HIGH );

	MDMA_voidSetCallBack( MDMA_CHANNEL1 , DMA_voidCallBack );

	MDMA_voidSetAddress( MDMA_CHANNEL1 , Source , Destination , 1000 );

	MDMA_voidInterruptEnable( MDMA_CHANNEL1 , MDMA_TCIE );

	MDMA_voidEnable( MDMA_CHANNEL1 );

	//For Processor
	for( i =0 ; i < 1000 ;i++ ){

		Destination2[i]=Source2[i];

	}

	while(1){

	}

}

