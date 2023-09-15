/*
 * MSTP_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MPORT_interface.h"
#include "MGPIO_interface.h"
#include "MSTK_interface.h"

#include "HSTP_interface.h"
#include "HSTP_private.h"
#include "HSTP_config.h"

void HSTP_voidSendByteSynchronous( u8 Copy_u8DataToSend ){

	s8 LOC_s8Counter ;
	u8 LOC_u8Bit     ;

	/* Send Bit By Bit Starting From MSB */
	for( LOC_s8Counter = 7 ; LOC_s8Counter >= 0 ; LOC_s8Counter-- ){

		LOC_u8Bit = GET_BIT( Copy_u8DataToSend , LOC_s8Counter );

		MGPIO_enumSetPinValue( HSTP_SERIAL_DATA , LOC_u8Bit );

		/* Send Pulse To Shift Clock */
		MGPIO_enumSetPinValue( HSTP_SHIFT_CLOCK , MGPIO_u8_HIGH );
		MSTK_voidSetBusyWait(1);
		MGPIO_enumSetPinValue( HSTP_SHIFT_CLOCK , MGPIO_u8_LOW );
		MSTK_voidSetBusyWait(1);

	}

	/* Send Pulse To Shift Clock */
	MGPIO_enumSetPinValue( HSTP_STORAGE_CLOCK , MGPIO_u8_HIGH );
	MSTK_voidSetBusyWait(1);
	MGPIO_enumSetPinValue( HSTP_STORAGE_CLOCK , MGPIO_u8_LOW );
	MSTK_voidSetBusyWait(1);

}


void HSTP_voidSendHalfWordSynchronous( u16 Copy_u8DataToSend ){

	s8 LOC_s8Counter ;
	u8 LOC_u8Bit     ;

	/* Send Bit By Bit Starting From MSB */
	for( LOC_s8Counter = 15 ; LOC_s8Counter >= 0 ; LOC_s8Counter-- ){

		LOC_u8Bit = GET_BIT( Copy_u8DataToSend , LOC_s8Counter );

		MGPIO_enumSetPinValue( HSTP_SERIAL_DATA , LOC_u8Bit );

		/* Send Pulse To Shift Clock */
		MGPIO_enumSetPinValue( HSTP_SHIFT_CLOCK , MGPIO_u8_HIGH );
		MSTK_voidSetBusyWait(1);
		MGPIO_enumSetPinValue( HSTP_SHIFT_CLOCK , MGPIO_u8_LOW );
		MSTK_voidSetBusyWait(1);

	}

	/* Send Pulse To Shift Clock */
	MGPIO_enumSetPinValue( HSTP_STORAGE_CLOCK , MGPIO_u8_HIGH );
	MSTK_voidSetBusyWait(1);
	MGPIO_enumSetPinValue( HSTP_STORAGE_CLOCK , MGPIO_u8_LOW );
	MSTK_voidSetBusyWait(1);

}
