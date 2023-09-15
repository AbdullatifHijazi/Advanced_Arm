/*
 * MEXTI_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_

typedef	struct
{
	volatile	u32		IMR   ;
	volatile	u32		EMR   ;
	volatile	u32		RTSR  ;
	volatile	u32		FTSR  ;
	volatile	u32		SWIER ;
	volatile	u32		PR    ;

}EXTI_type;

#define	MEXTI		((volatile EXTI_type * ) 0x40010400 )

static u8 MEXTI_CallBackNumber  = 16 ;

#endif /* MEXTI_PRIVATE_H_ */
