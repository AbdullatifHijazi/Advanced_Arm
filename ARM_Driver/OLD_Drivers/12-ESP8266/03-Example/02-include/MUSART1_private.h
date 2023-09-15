/*
 *  USART1_PRIVATE_H_
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */

#ifndef USART1_PRIVATE_H_
#define USART1_PRIVATE_H_

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