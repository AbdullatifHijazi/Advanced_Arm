/*
 * MUSART1_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MUSART1_PRIVATE_H_
#define MUSART1_PRIVATE_H_

typedef struct{

	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;

}USART_type;


#define MUSART1 ( ( volatile USART_type * ) 0x40013800 )

#endif /* USART1_PRIVATE_H_ */
