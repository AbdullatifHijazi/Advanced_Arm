/*
 * MSPI_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_


typedef struct {

	volatile u32 CR1     ;
	volatile u32 CR2     ;
	volatile u32 SR      ;
	volatile u32 DR      ;
	volatile u32 CRCPR   ;
	volatile u32 RXCRCR  ;
	volatile u32 TXCRCR  ;
	volatile u32 I2SCFGR ;
	volatile u32 I2SPR   ;

}SPI_type;

#define MSPI1 ( ( volatile SPI_type* ) 0x40013000 )


#endif /* MSPI_PRIVATE_H_ */
