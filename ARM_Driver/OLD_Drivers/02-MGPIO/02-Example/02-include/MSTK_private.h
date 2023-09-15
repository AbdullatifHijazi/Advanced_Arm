/*
 * MSTK_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MSTK_PRIVATE_H_
#define MSTK_PRIVATE_H_

typedef struct
{
	volatile u32 CTRL  ;
	volatile u32 LOAD  ;
	volatile u32 VAL   ;
	volatile u32 CALIB ;

}MSTK_type;

#define     MSTK    ( (volatile MSTK_type *) 0xE000E010 )


#define     MSTK_SRC_AHB            0
#define     MSTK_SRC_AHB_8          1

#define     MSTK_SINGLE_INTERVAL    0
#define     MSTK_PERIOD_INTERVAL    1

#endif /* MSTK_PRIVATE_H_ */
