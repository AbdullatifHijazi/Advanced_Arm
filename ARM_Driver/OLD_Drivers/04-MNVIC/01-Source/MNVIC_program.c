/*
 * MNVIC_Program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MNVIC_interface.h"
#include "MNVIC_private.h"
#include "MNVIC_config.h"

void MNVIC_voidInit(void){

	SCB->AIRCR = MNVIC_GROUP_SUB_DISTRIBUTION;

}
/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ISER0 Or 32-63 is found in ISER1 */
void MNVIC_voidEnablePeripheral ( u8 Copy_u8INTID ){

	MNVIC->ISER[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;

}
/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ICER0 Or 32-63 is found in ICER1 */
void MNVIC_voidDisablePeripheral ( u8 Copy_u8INTID ){

	MNVIC->ICER[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;

}

/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ISPR0 Or 32-63 is found in ISPR1 */
void MNVIC_voidSetPending ( u8 Copy_u8INTID ){

	MNVIC->ISPR[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;


}
/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ICPR0 Or 32-63 is found in ICPR1 */
void MNVIC_voidClearPending ( u8 Copy_u8INTID ){

	MNVIC->ICPR[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;

}

/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ISER0 Or 32-63 is found in ISER1 */
u8   MNVIC_u8GetActive( u8 Copy_u8INTID ){

	u8 LOC_u8Active = GET_BIT( (MNVIC->IAPR[ Copy_u8INTID/32 ]) , ( Copy_u8INTID % 32 ) );
	return LOC_u8Active ;

}

/* Copy_u8INTID is Interrupt_Number if from 0-31 found in ISER0 Or 32-63 is found in ISER1 */
void MNVIC_voidSetPriority( s8 Copy_u8PeripheralID , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority , u32 Copy_u8GroupLevels ){

	u8 Priority =  Copy_u8SubPriority | ( Copy_u8GroupPriority << ( (Copy_u8GroupLevels - 0x05FA0300) / 256 ) ) ;
	/*Core Peripheral*/
	if( Copy_u8PeripheralID < 0  ){

		if( Copy_u8PeripheralID == MNVIC_MEMORY_MANAGE || Copy_u8PeripheralID == MNVIC_BUS_FAULT || Copy_u8PeripheralID == MNVIC_USAGE_FAULT ){

			Copy_u8PeripheralID += 3;
			SCB->SHPR1 = ( ) << ( (8 * Copy_u8PeripheralID) + 4 );

		}
		else if ( Copy_u8PeripheralID == MNVIC_SV_CALL ){

			Copy_u8PeripheralID += 7;
			SCB->SHPR2 = ( Priority ) << ( (8 * Copy_u8PeripheralID) + 4 );

		}
		else if( Copy_u8PeripheralID == MNVIC_PEND_SV || Copy_u8PeripheralID == MNVIC_SYSTICK ){

			Copy_u8PeripheralID += 8;

			SCB->SHPR3 = ( Priority ) << ( (8 * Copy_u8PeripheralID) + 4 );

		}

	}
	/*External Peripheral*/
	else if( Copy_u8PeripheralID >= 0 ){

		MNVIC->IPR[ Copy_u8PeripheralID ] = Priority << 4 ;

	}

	SCB->AIRCR = Copy_u8GroupLevels ;

}


