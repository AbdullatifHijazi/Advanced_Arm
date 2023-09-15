/*
 *  HDAC_program.c
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MSTK_interface.h"

#include "HDAC_interface.h"
#include "HDAC_private.h"
#include "HDAC_config.h"

#include "MGPIO_interface.h"

volatile u32 Song_Counter = 0;
const    u8 * Song        = NULL ;

void ( *HDAC_CallBack )(void) = NULL;

void HDAC_voidCallBack( void ){

	MGPIO_enumSetPortValue( DAC_PORT , DAC_PORT_LH , Song[ Song_Counter ] );
	Song_Counter++;

	if( Song_Counter == Song_Length ){
		Song_Counter = 0;
	}

}

void HDAC_voidInit( void ){

	MSTK_voidInit();

}

void HDAC_voidPlay( const u8 * Copy_ptrSong ){

	if( Copy_ptrSong != NULL ){

		Song = Copy_ptrSong ;
		MSTK_voidSetIntervalPeriodic( 125 , HDAC_voidCallBack );

	}

}

