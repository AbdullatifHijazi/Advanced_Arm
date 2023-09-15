/*
 * MAFIO_PRIVATE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MAFIO_PRIVATE_H_
#define MAFIO_PRIVATE_H_

typedef struct{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICRx[4];
	volatile u32 MAPR2;

}AFIO_type;


#define MAFIO ((volatile AFIO_type *) 0x40010000)

#endif /* MAFIO_PRIVATE_H_ */
