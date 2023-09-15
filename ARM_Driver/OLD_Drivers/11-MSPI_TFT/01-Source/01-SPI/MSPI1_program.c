/*
 * MSPI_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"

#include "MSPI1_interface.h"
#include "MSPI1_private.h"
#include "MSPI1_config.h"


void (*MSPI1_CallBack) (void);

void MSPI1_voidInit ( void ){

	#if   MSPI1_STATUS == MSPI1_ENABLE

		#if		MSPI1_CLOCK_MODE == MSPI1_MODE0

			CLR_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

		#elif	MSPI1_CLOCK_MODE == MSPI1_MODE1

			SET_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

		#elif	MSPI1_CLOCK_MODE == MSPI1_MODE2

			CLR_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

		#elif	MSPI1_CLOCK_MODE == MSPI1_MODE3

			SET_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

		#endif

		#if    MSPI1_MASTER_SLAVE == MSPI1_MASTER

			SET_BIT( MSPI1 -> CR1 , 2 );

		#elif  MSPI1_MASTER_SLAVE == MSPI1_SLAVE

			CLR_BIT( MSPI1 -> CR1 , 2 );

		#endif

		#if   MSPI1_DATA_ORDER == MSPI1_MSB_FIRST

			CLR_BIT( MSPI1 -> CR1 , 7 );

		#elif MSPI1_DATA_ORDER == MSPI1_LSB_FIRST

			SET_BIT( MSPI1 -> CR1 , 7 );

		#endif

		#if   MSPI1_NSS_MANAGE  == MSPI1_HW_SLAVE_MANAGEMENT

			CLR_BIT( MSPI1 -> CR1 , 9 );

		#elif MSPI1_NSS_MANAGE == MSPI1_SW_SLAVE_MANAGEMENT

			#if    MSPI1_MASTER_SLAVE == MSPI1_MASTER

				SET_BIT( MSPI1 -> CR1 , 8 );

			#endif

			SET_BIT( MSPI1 -> CR1 , 9 );

		#endif

		#if   MSPI1_DATA_SIZE == MSPI1_8BIT_DATA

			CLR_BIT( MSPI1 -> CR1 , 11 );

		#elif MSPI1_DATA_SIZE == MSPI1_16BIT_DATA

			SET_BIT( MSPI1 -> CR1 , 11 );

		#endif

		#if   MSPI1_INTERRUPT_STATUS == MSPI1_INTERRUPT_DISABLE

			MSPI1 -> CR2 = 0 ;

		#elif MSPI1_INTERRUPT_STATUS == MSPI1_TXE_INTERRUPT_ENABLE

			SET_BIT( MSPI1 -> CR2 , 7 );

		#elif MSPI1_INTERRUPT_STATUS == MSPI1_RXNE_INTERRUPT_ENABLE

			SET_BIT( MSPI1 -> CR2 , 6 );

		#endif

		MSPI1 -> CR1 &= 0xFFC7 ;
		MSPI1 -> CR1 |= ( MSPI1_PRESCALLER << 3 ) ;

		SET_BIT( MSPI1 -> CR1 , 6 );

	#elif MSP1_STATUS == MSPI_DISABLE

		CLR_BIT( MSPI1 -> CR1 , 6 );

	#endif

}

void MSPI1_voidSendReceiveSynch( u8 Copy_u8DataToTransmit, u8 * Copy_DataToReceive ){

	/* Clear For Slave Select Pin */
	MGPIO_enumSetPinValue( MSPI1_SLAVE_PIN , MGPIO_u8_LOW );

	/* Send Data */
	MSPI1 -> DR = Copy_u8DataToTransmit;

	/* Wait Busy Flag to finish */
	while ( GET_BIT( MSPI1 -> SR , 7 ) == 1 );

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI1 -> DR ;

	/* Set Salve Select Pin */
	MGPIO_enumSetPinValue( MSPI1_SLAVE_PIN , MGPIO_u8_HIGH );

}

void MSPI1_voidSetCallBack( void (*ptr) (void) ){

	MSPI1_CallBack = ptr;

}

void SPI1_IRQHandler(void){

	MSPI1_CallBack();

}


