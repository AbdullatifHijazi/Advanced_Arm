/*
 * MNVIC_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_

#define NVIC_ISER0 *((u32*) 0xE000E100) /* Enable External Interrupt from 0- 31 */

#define NVIC_ISER1 *((u32*) 0xE000E104) /* Enable External Interrupt from 32- 63 */

#define NVIC_ICER0 *((u32*) 0xE000E180) /* Disable External Interrupt from 0- 31 */

#define NVIC_ICER1 *((u32*) 0xE000E184) /* Disable External Interrupt from 32- 63 */

#define NVIC_ISPR0 *((u32*) 0xE000E200) /* Disable External Interrupt from 0- 31 */
			  
#define NVIC_ISPR1 *((u32*) 0xE000E204) /* Disable External Interrupt from 32- 63 */

#define NVIC_ICPR0 *((u32*) 0xE000E280) /* Disable External Interrupt from 0- 31 */
			   
#define NVIC_ICPR1 *((u32*) 0xE000E284) /* Disable External Interrupt from 32- 63 */

#define NVIC_IABR0 *((volatile u32*) 0xE000E280) /* Disable External Interrupt from 0- 31 */
			  
#define NVIC_IABR1 *((volatile u32*) 0xE000E284) /* Disable External Interrupt from 32- 63 */
//NVIC
typedef struct{

	volatile u32 ISER    [ 32 ];
	volatile u32 ICER    [ 32 ];
	volatile u32 ISPR    [ 32 ];
	volatile u32 ICPR    [ 32 ];
	volatile u32 IAPR    [ 32 ];
	volatile u32 RESERVED[ 32 ];
	volatile u8  IPR     [ 128];

}NVIC_type;

#define MNVIC       ( ( volatile NVIC_type *)0xE000E100 )

#define MNVIC_STIR *( ( volatile u32  *)0xE000EF00 )

//SCB
typedef struct{

    volatile u32 ACTLR    ;
	volatile u32 RESERVED ;
	volatile u32 CPUID    ;
	volatile u32 ICSR     ;
	volatile u32 VTOR     ;
	volatile u32 AIRCR    ;
	volatile u32 SCR      ;
	volatile u32 CCR      ;
	volatile u32 SHPR1    ;
	volatile u32 SHPR2    ;
	volatile u32 SHPR3    ;
	volatile u32 SHCSR    ;
	volatile u32 CFSR     ;
	volatile u32 HFSR     ;
	volatile u32 RESERVED ;
	volatile u32 MMFAR    ;
	volatile u32 BFAR     ;

}SCB_Type;

#define SCB ((volatile SCB_Type *) 0xE000ED00 )

#endif /* MNVIC_PRIVATE_H_ */
