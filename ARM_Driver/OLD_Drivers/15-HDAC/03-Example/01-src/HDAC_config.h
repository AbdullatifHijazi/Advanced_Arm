/*
 *  HDAC_CONFIG_H_
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */


#ifndef HDAC_CONFIG_H_
#define HDAC_CONFIG_H_

/*
 Options :-

	1-MGPIO_u8_PORTA
	2-MGPIO_u8_PORTB
	3-MGPIO_u8_PORTC
	4-MGPIO_u8_PORTD

 */

#define DAC_PORT       MGPIO_u8_PORTA

/*
 Options:-

	1- MGPIO_u8_HIGH
	2- MGPIO_u8_LOW

 */
#define DAC_PORT_LH    MGPIO_u8_LOW

#define Song_Length 24242UL

#endif
