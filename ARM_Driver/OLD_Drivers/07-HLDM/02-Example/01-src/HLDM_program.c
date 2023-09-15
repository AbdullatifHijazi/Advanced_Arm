/*
 * HLDM_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "MPORT_interface.h"
#include "MSTK_interface.h"

#include "HLDM_interface.h"
#include "HLDM_private.h"
#include "HLDM_config.h"

void HLDM_voidInit( void ){

	/* Set The Direction Of Led Matrix ROWS and COLS Based On The Value That Configured In HLDM_config.h */
	MPORT_enumSetPinDirection( HLDM_ROW0_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW1_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW2_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW3_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW4_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW5_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW6_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_ROW7_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );

	MPORT_enumSetPinDirection( HLDM_COL0_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL1_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL2_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL3_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL4_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL5_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL6_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );
	MPORT_enumSetPinDirection( HLDM_COL7_PIN , MGPIO_OUTPUT_SPEED_2MHZ_PP );

}


void HLDM_voidDisplay ( u8 * Copy_ptrData ){

	/* Enable Each COL after 2.5 millisecond */
	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[0] );
	MGPIO_enumSetPinValue( HLDM_COL0_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[1] );
	MGPIO_enumSetPinValue( HLDM_COL1_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[2] );
	MGPIO_enumSetPinValue( HLDM_COL2_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[3] );
	MGPIO_enumSetPinValue( HLDM_COL3_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[4] );
	MGPIO_enumSetPinValue( HLDM_COL4_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[5] );
	MGPIO_enumSetPinValue( HLDM_COL5_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[6] );
	MGPIO_enumSetPinValue( HLDM_COL6_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

	HLDM_voidDisableAllCols();
	HLDM_voidSetRowValues( Copy_ptrData[7] );
	MGPIO_enumSetPinValue( HLDM_COL7_PIN , MGPIO_u8_LOW );

	MSTK_voidSetBusyWait(2500);

}

void HLDM_voidDisableAllCols(void){

	MGPIO_enumSetPinValue( HLDM_COL0_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL1_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL2_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL3_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL4_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL5_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL6_PIN , MGPIO_u8_HIGH );
	MGPIO_enumSetPinValue( HLDM_COL7_PIN , MGPIO_u8_HIGH );

}

static void HLDM_voidSetRowValues( u8 Copy_u8Value ){

	u8 LOC_u8Value = 0 ;

	LOC_u8Value = GET_BIT( Copy_u8Value , 0 );
	MGPIO_enumSetPinValue( HLDM_ROW0_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 1 );
	MGPIO_enumSetPinValue( HLDM_ROW1_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 2 );
	MGPIO_enumSetPinValue( HLDM_ROW2_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 3 );
	MGPIO_enumSetPinValue( HLDM_ROW3_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 4 );
	MGPIO_enumSetPinValue( HLDM_ROW4_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 5 );
	MGPIO_enumSetPinValue( HLDM_ROW5_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 6 );
	MGPIO_enumSetPinValue( HLDM_ROW6_PIN , LOC_u8Value );

	LOC_u8Value = GET_BIT( Copy_u8Value , 7 );
	MGPIO_enumSetPinValue( HLDM_ROW7_PIN , LOC_u8Value );

}
