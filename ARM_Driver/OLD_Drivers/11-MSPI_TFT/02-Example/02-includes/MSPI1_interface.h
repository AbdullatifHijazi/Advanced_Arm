/*
 * MSPI_INTERFACE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_


#define MSPI1_DISABLE                 0
#define MSPI1_ENABLE                  1

#define MSPI1_MODE0                   0
#define MSPI1_MODE1                   1
#define MSPI1_MODE2                   2
#define MSPI1_MODE3                   3

#define MSPI1_MASTER                  0
#define MSPI1_SLAVE                   1

#define MSPI1_FPCLK_DIVIDED_BY_2      0b000
#define MSPI1_FPCLK_DIVIDED_BY_4      0b001
#define MSPI1_FPCLK_DIVIDED_BY_8      0b010
#define MSPI1_FPCLK_DIVIDED_BY_16     0b011
#define MSPI1_FPCLK_DIVIDED_BY_32     0b100
#define MSPI1_FPCLK_DIVIDED_BY_64     0b101
#define MSPI1_FPCLK_DIVIDED_BY_128    0b110
#define MSPI1_FPCLK_DIVIDED_BY_256    0b111

#define MSPI1_MSB_FIRST                0
#define MSPI1_LSB_FIRST 			   1

#define MSPI1_HW_SLAVE_MANAGEMENT      0
#define MSPI1_SW_SLAVE_MANAGEMENT      1

#define MSPI1_8BIT_DATA                0
#define MSPI1_16BIT_DATA               1

#define MSPI1_INTERRUPT_DISABLE        0
#define MSPI1_TXE_INTERRUPT_ENABLE     1
#define MSPI1_RXNE_INTERRUPT_ENABLE    2


void MSPI1_voidInit             ( void               ) ;
void MSPI1_voidSendReceiveSynch (u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive);
void MSPI1_voidSetCallBack      ( void (*ptr) (void) ) ;


#endif /* MSPI_INTERFACE_H_ */
