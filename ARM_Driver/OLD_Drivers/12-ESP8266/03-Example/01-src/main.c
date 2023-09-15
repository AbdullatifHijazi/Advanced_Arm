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

#include "MUSART1_interface.h"
#include "HESP8266_interface.h"

u8 LOC_u8Data ;

int main (void){

	/*  Initializing RCC With HSE Crystal Oscillator 8MHZ */
	MRCC_enumInitSysClock();
	/* Enable The Clock Of GPIOA */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_GPIOA );
	/* Enable The Clock Of SPI1 */
	MRCC_enumEnablePerClock( MRCC_APB2 , MRCC_USART1 );
	/* Initialize EXTI PIN0 as Input Floating */
	MPORT_voidInit();
	/* Initialize NVIC */
	MNVIC_voidInit();
	/* Enable USART1 From NVIC */
	MNVIC_voidEnablePeripheral( MNVIC_USART1 );
	/* Initialize USART1 */
	MUSART1_voidInit();
	/* Initialize ESP8266 */
	HESP8266_voidInit();
	/* Connecting To Wifi Network */
	HESP8266_voidConnectToWiFi((u8 *)"IMT Staff",(u8 *)"Imt.Sch@Dokki_HQ2021");

	while(1){

		HESP8266_voidConnectToSrvTcp((u8 *)"162.253.155.226" , (u8 *)"80");
		LOC_u8Data = HESP8266_u8ReceiveHttpReq( (u8 *)"imttest.freevar.com" , (u8 *)"43" ) ;
		MGPIO_enumSetPinValue( MGPIO_u8_PORTA , MGPIO_u8_PIN0 , LOC_u8Data - 48 );

	}

}

