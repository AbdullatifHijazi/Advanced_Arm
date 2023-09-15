/*
 * HTFT_INTERFACE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_


// ST7735 ROUTINES
#define HTFT_SWRESET 		0x01 // software reset
#define HTFT_SLPOUT 		0x11 // sleep out
#define HTFT_DISPOFF 		0x28 // display off
#define HTFT_DISPON 		0x29 // display on
#define HTFT_CASET 			0x2A // column address set
#define HTFT_RASET 			0x2B // row address set
#define HTFT_RAMWR 			0x2C // RAM write
#define HTFT_MADCTL 		0x36 // axis control
#define HTFT_COLMOD 		0x3A // color mode

// 1.8" TFT display constants
#define HTFT_XSIZE 			128
#define HTFT_YSIZE 			160
#define HTFT_XMAX 			XSIZE-1
#define HTFT_YMAX 			YSIZE-1


// Color constants
#define HTFT_BLACK 			0x0000
#define HTFT_BLUE 			0x001F
#define HTFT_RED 			0xF800
#define HTFT_GREEN 			0x0400
#define HTFT_LIME 			0x07E0
#define HTFT_CYAN 			0x07FF
#define HTFT_MAGENTA 		0xF81F
#define HTFT_YELLOW 		0xFFE0
#define HTFT_WHITE 			0xFFFF

void HTFT_voidInitialize   (void);
void HTFT_voidDisplayImage (const u16 * Copy_u16Image);
void HTFT_voidFillColor    ( u16 Copy_u16Color );
void HTFT_voidDrawRect     ( u8 Copy_u8X1 , u8 Copy_u8X2 , u8 Copy_u8Y1 , u8 Copy_u8Y2 , u16 Copy_u16Color );
void HTFT_voidDisplayChar  ( u16 * Copy_u8Char , u8 Copy_Xaxis , u8 Copy_Yaxis , u16 Copy_u16Color );

#endif /* HTFT_INTERFACE_H_ */
