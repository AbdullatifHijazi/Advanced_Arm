/*
 * MPORT_CONFIG_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MPORT_CONFIG_H_
#define MPORT_CONFIG_H_

/* Options:    1-  MPORT_OUTPUT_SPEED_2MHZ_PP
               2-  MPORT_OUTPUT_SPEED_2MHZ_OD
               3-  MPORT_OUTPUT_SPEED_2MHZ_AFPP
               4-  MPORT_OUTPUT_SPEED_2MHZ_AFOD
               5-  MPORT_OUTPUT_SPEED_10MHZ_PP
               6-  MPORT_OUTPUT_SPEED_10MHZ_OD
               7-  MPORT_OUTPUT_SPEED_10MHZ_AFPP
               8-  MPORT_OUTPUT_SPEED_10MHZ_AFOD
               9-  MPORT_OUTPUT_SPEED_50MHZ_PP
               10- MPORT_OUTPUT_SPEED_50MHZ_OD
               11- MPORT_OUTPUT_SPEED_50MHZ_AFPP
               12- MPORT_OUTPUT_SPEED_50MHZ_AFOD
               13- MPORT_INPUT_ANLOG
               14- MPORT_INPUT_FLOATING
               15- MPORT_INPUT_PULLUP_PULLDOWN   */


#define PORTA_PIN0_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN1_DIR		MPORT_INPUT_PULLUP_PULLDOWN
#define PORTA_PIN2_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN3_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN4_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN5_DIR		MPORT_OUTPUT_SPEED_2MHZ_AFPP
#define PORTA_PIN6_DIR		MPORT_INPUT_FLOATING
#define PORTA_PIN7_DIR		MPORT_OUTPUT_SPEED_2MHZ_AFPP
#define PORTA_PIN8_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN9_DIR		MPORT_OUTPUT_SPEED_2MHZ_AFPP
#define PORTA_PIN10_DIR		MPORT_INPUT_FLOATING
#define PORTA_PIN11_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN12_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN13_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN14_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTA_PIN15_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP


#define PORTB_PIN0_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN1_DIR		MPORT_INPUT_PULLUP_PULLDOWN
#define PORTB_PIN2_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN3_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN4_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN5_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN6_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN7_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN8_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN9_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN10_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN11_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN12_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN13_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN14_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTB_PIN15_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP


#define PORTC_PIN13_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTC_PIN14_DIR		MPORT_OUTPUT_SPEED_2MHZ_PP
#define PORTC_PIN15_DIR		MPORT_INPUT_FLOATING


/* Options:    1- 1 (For HIGH Or Pullup  in input case )
               2- 0 (For LOW Or Pulldown in input case  )
                                */



#define PORTA_PIN0_INITIAL_VALUE		0
#define PORTA_PIN1_INITIAL_VALUE		1
#define PORTA_PIN2_INITIAL_VALUE		0
#define PORTA_PIN3_INITIAL_VALUE		0
#define PORTA_PIN4_INITIAL_VALUE		0
#define PORTA_PIN5_INITIAL_VALUE		0
#define PORTA_PIN6_INITIAL_VALUE		0
#define PORTA_PIN7_INITIAL_VALUE		0
#define PORTA_PIN8_INITIAL_VALUE		0
#define PORTA_PIN9_INITIAL_VALUE		0
#define PORTA_PIN10_INITIAL_VALUE		0
#define PORTA_PIN11_INITIAL_VALUE		0
#define PORTA_PIN12_INITIAL_VALUE		0
#define PORTA_PIN13_INITIAL_VALUE		0
#define PORTA_PIN14_INITIAL_VALUE		0
#define PORTA_PIN15_INITIAL_VALUE		0



#define PORTB_PIN0_INITIAL_VALUE		0
#define PORTB_PIN1_INITIAL_VALUE		1
#define PORTB_PIN2_INITIAL_VALUE		0
#define PORTB_PIN3_INITIAL_VALUE		0
#define PORTB_PIN4_INITIAL_VALUE		0
#define PORTB_PIN5_INITIAL_VALUE		0
#define PORTB_PIN6_INITIAL_VALUE		0
#define PORTB_PIN7_INITIAL_VALUE		0
#define PORTB_PIN8_INITIAL_VALUE		0
#define PORTB_PIN9_INITIAL_VALUE		0
#define PORTB_PIN10_INITIAL_VALUE		0
#define PORTB_PIN11_INITIAL_VALUE		0
#define PORTB_PIN12_INITIAL_VALUE		0
#define PORTB_PIN13_INITIAL_VALUE		0
#define PORTB_PIN14_INITIAL_VALUE		0
#define PORTB_PIN15_INITIAL_VALUE		0


#define PORTC_PIN13_INITIAL_VALUE		1
#define PORTC_PIN14_INITIAL_VALUE		0
#define PORTC_PIN15_INITIAL_VALUE		0

#endif /* MPORT_CONFIG_H_ */
