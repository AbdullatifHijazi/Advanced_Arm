/*
 *  BIT_MATH_H_
 *  Created on: Jul 28, 2015
 *  Author: Abdo_Hijazi
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BITNO) (REG |=  (1<<BITNO))
#define CLR_BIT(REG,BITNO) (REG &= ~(1<<BITNO))
#define TOG_BIT(REG,BITNO) (REG ^= (1<<BITNO) )
#define GET_BIT(REG,BITNO) ((REG >> (BITNO))&1)

#define NULL 0

typedef enum{

	NOK,
	OK,

}error_status;

#endif
