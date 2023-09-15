/*
 * HTFT_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "MSPI1_interface.h"
#include "MSTK_interface.h"

#include "HTFT_interface.h"
#include "HTFT_private.h"
#include "HTFT_config.h"


void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	MGPIO_enumSetPinValue ( HTFT_RST_PIN , MGPIO_u8_HIGH );
	MSTK_voidSetBusyWait  ( 100 );
	MGPIO_enumSetPinValue ( HTFT_RST_PIN , MGPIO_u8_LOW );
	MSTK_voidSetBusyWait  ( 1 );
	MGPIO_enumSetPinValue ( HTFT_RST_PIN , MGPIO_u8_HIGH );
	MSTK_voidSetBusyWait  ( 100 );
	MGPIO_enumSetPinValue ( HTFT_RST_PIN , MGPIO_u8_LOW );
	MSTK_voidSetBusyWait  ( 100 );
	MGPIO_enumSetPinValue ( HTFT_RST_PIN , MGPIO_u8_HIGH );
	MSTK_voidSetBusyWait  ( 120000 );

	/* Sleep Out Command */
	/* take display out of sleep mode */
	Write_voidCommand( HTFT_SLPOUT );

	/* Wait 150 ms for TFT driver circuits */
	MSTK_voidSetBusyWait( 150000 );

	/* Color Mode Command */
	Write_voidCommand( HTFT_COLMOD );
	/* mode 5 = 16bit pixels (RGB565) */
	Write_voidData   (0x05);

	/* Display On Command */
	/* turn display on! */
	Write_voidCommand( HTFT_DISPON );
	MSTK_voidSetBusyWait( 1000 );

	/* Remap TFT addresses ( x = 0 , y = 0 Start From The Left Top Of The TFT ) */
	Write_voidCommand( HTFT_MADCTL );
	Write_voidData   ( 0xC0 );

}


void HTFT_voidDisplayImage ( const u16 * Copy_u16Image )
{

	u16 LOC_u16Counter ;
	u8  LOC_u8Data     ;

	/* Set X Address */
	Write_voidCommand( HTFT_CASET );
	/* Start */
	Write_voidData(0);
	Write_voidData(0);
	/* End */
	Write_voidData(0);
	Write_voidData(127);

	/* Set Y Address */
	Write_voidCommand( HTFT_RASET );
	/* Start */
	Write_voidData(0);
	Write_voidData(0);
	/* End */
	Write_voidData(0);
	Write_voidData(159);

	/* RAM Write */
	Write_voidCommand( HTFT_RAMWR );

	for( LOC_u16Counter  = 0 ; LOC_u16Counter < 20480 ; LOC_u16Counter++ )
	{

		/* Write the high byte */
		LOC_u8Data      = Copy_u16Image[LOC_u16Counter ] >> 8;
		Write_voidData(LOC_u8Data     );

		/* Write the low byte */
		LOC_u8Data      = Copy_u16Image[LOC_u16Counter ] & 0x00ff;
		Write_voidData(LOC_u8Data     );
	}


}


void HTFT_voidFillColor ( u16 Copy_u16Color )
{

	u16 LOC_u16Counter ;

	/* Set X Address */
	Write_voidCommand( HTFT_CASET );
	/* Start */
	Write_voidData(0);
	Write_voidData(0);
	/* End */
	Write_voidData(0);
	Write_voidData(127);

	/* Set Y Address */
	Write_voidCommand( HTFT_RASET );
	/* Start */
	Write_voidData(0);
	Write_voidData(0);
	/* End */
	Write_voidData(0);
	Write_voidData(159);

	/* RAM Write */
	Write_voidCommand( HTFT_RAMWR );

	for( LOC_u16Counter  = 0 ; LOC_u16Counter < 20480 ; LOC_u16Counter++ )
	{

		/* Write the high byte */
		Write_voidData( Copy_u16Color >> 8 );
		/* Write the low byte */
		Write_voidData( Copy_u16Color & 0x00FF );
	}


}



void HTFT_voidDrawRect ( u8 Copy_u8X1 , u8 Copy_u8X2 , u8 Copy_u8Y1 , u8 Copy_u8Y2 , u16 Copy_u16Color )
{

	u16 LOC_u16Counter ;

	u16 LOC_u8Size = ( Copy_u8X2 - Copy_u8X1 ) * ( Copy_u8Y2 - Copy_u8Y1 );

	/* Set X Address */
	Write_voidCommand( HTFT_CASET );
	/* Start */
	Write_voidData(0);
	Write_voidData( Copy_u8X1 );
	/* End */
	Write_voidData(0);
	Write_voidData( Copy_u8X2 - 1 );

	/* Set Y Address */
	Write_voidCommand( HTFT_RASET );
	/* Start */
	Write_voidData(0);
	Write_voidData( Copy_u8Y1 );
	/* End */
	Write_voidData(0);
	Write_voidData( Copy_u8Y2 - 1 );

	/* RAM Write */
	Write_voidCommand( HTFT_RAMWR );

	for( LOC_u16Counter  = 0 ; LOC_u16Counter < LOC_u8Size ; LOC_u16Counter++ )
	{

		/* Write the high byte */
		Write_voidData( Copy_u16Color >> 8 );
		/* Write the low byte */
		Write_voidData( Copy_u16Color & 0x00FF );
	}


}


void HTFT_voidDisplayChar( u16 * Copy_u8Char , u8 Copy_Xaxis , u8 Copy_Yaxis , u16 Copy_u16Color ){

	u16 LOC_u8Mask = 0x01  ;
	u16 LOC_u8Pixel       ;
	u16 LOC_u8DataMasked   ;

	for(u8 LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 15 ; LOC_u8Iterator1++ ){

		for(u8 LOC_u8Iterator2 = 0 ; LOC_u8Iterator2 < 15 ; LOC_u8Iterator2++ ){

			Write_voidCommand( HTFT_CASET );

			Write_voidData( 0 );
			Write_voidData( Copy_Xaxis +  LOC_u8Iterator1 );
			Write_voidData( 0 );
			Write_voidData( Copy_Xaxis +  LOC_u8Iterator1 );

			Write_voidCommand( HTFT_RASET );

			Write_voidData( 0 );
			Write_voidData( Copy_Yaxis +  LOC_u8Iterator2 );
			Write_voidData( 0 );
			Write_voidData( Copy_Yaxis +  LOC_u8Iterator2 );

			Write_voidCommand( HTFT_RAMWR );

			LOC_u8DataMasked = Copy_u8Char[ LOC_u8Iterator1 ] & LOC_u8Mask ;

			if( LOC_u8DataMasked == 0  ) { LOC_u8Pixel = 0x0000        ; }
			else                         { LOC_u8Pixel = Copy_u16Color ; }

			Write_voidData ( LOC_u8Pixel >> 8   ); // write hi byte
			Write_voidData ( LOC_u8Pixel & 0xFF ); // write lo byte

			LOC_u8Mask <<= 1 ;


		}

		LOC_u8Mask = 0x01 ;

	}


}


static void Write_voidCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp;

	/* Set A0 Pin to Low */
	MGPIO_enumSetPinValue( HTFT_A0_PIN , MGPIO_u8_LOW );

	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch( Copy_u8Command , &Local_u8Temp );
}

static void Write_voidData   (u8 Copy_u8Data)
{
	u8 Local_u8Temp;

	/* Set A0 Pin to High */
	MGPIO_enumSetPinValue( HTFT_A0_PIN , MGPIO_u8_HIGH );

	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch( Copy_u8Data , &Local_u8Temp );
}
