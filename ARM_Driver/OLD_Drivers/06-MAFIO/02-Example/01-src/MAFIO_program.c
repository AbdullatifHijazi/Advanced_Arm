/*
 * MAFIO_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MAFIO_interface.h"
#include "MAFIO_private.h"
#include "MAFIO_config.h"

void MAFIO_voidInit(void){

	MAFIO -> EXTICRx[0] = MAFIO_EXTERNAL_INTERRUPT_MAP ;
	MAFIO -> EXTICRx[1] = MAFIO_EXTERNAL_INTERRUPT_MAP ;
	MAFIO -> EXTICRx[2] = MAFIO_EXTERNAL_INTERRUPT_MAP ;
	MAFIO -> EXTICRx[3] = MAFIO_EXTERNAL_INTERRUPT_MAP ;

}

void MAFIO_voidSetExternalInterruptConfiguration( u8 Copy_u8Line , u8 LOC_u8PortMap ){

	/* Clear The 4 Bits For Re-mapping Before Accessing Them */
	MAFIO -> EXTICRx[ Copy_u8Line / 4 ] &= ~ ( ( 0b1111 )      << ( ( Copy_u8Line % 4 ) * 4 ));
	/* Re-mapping EXTI Line */
	MAFIO -> EXTICRx[ Copy_u8Line / 4 ] |=   ( LOC_u8PortMap ) << ( ( Copy_u8Line % 4 ) * 4 );

}

