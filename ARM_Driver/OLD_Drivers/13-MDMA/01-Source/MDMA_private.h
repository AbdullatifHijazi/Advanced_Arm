/*
 *  MDMA_PRIVATE_
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */

#ifndef MDMA_PRIVATE_
#define MDMA_PRIVATE_

typedef struct{
	
	volatile u32 CCR      ;     
	volatile u32 CNDTR    ;
	volatile u32 CPAR     ;   
	volatile u32 CMAR     ;
	volatile u32 RESERVED ;
	
}DMA_Channel;


typedef struct{
	
	volatile u32 ISR  ;
	volatile u32 IFCR ;
	
	DMA_Channel CHANNEL[7];
	
}DMA_Type;


#define MDMA ((volatile DMA_Type*)0x40020000)

#endif
