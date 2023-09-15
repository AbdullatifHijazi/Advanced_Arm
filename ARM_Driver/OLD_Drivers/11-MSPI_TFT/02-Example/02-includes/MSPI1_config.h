/*
 * MSPI_CONFIG_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */

#ifndef MSPI_CONFIG_H_
#define MSPI_CONFIG_H_



#define MSPI1_SLAVE_PIN            MGPIO_u8_PORTA,MGPIO_u8_PIN0

/* Options:

 	 	 	   MSPI1_DISABLE
               MSPI1_ENABLE
                 			     */

#define MSPI1_STATUS               MSPI1_ENABLE

/* Options:

 	 	 	   MSPI1_MODE0
               MSPI1_MODE1
               MSPI1_MODE2
               MSPI1_MODE3
                 			     */

#define MSPI1_CLOCK_MODE           MSPI1_MODE3

/* Options:

 	 	 	   MSPI1_MASTER
               MSPI1_SLAVE

                 			     */

#define MSPI1_MASTER_SLAVE         MSPI1_MASTER


/* Options:

 	 	 	   MSPI1_FPCLK_DIVIDED_BY_2
               MSPI1_FPCLK_DIVIDED_BY_4
               MSPI1_FPCLK_DIVIDED_BY_8
               MSPI1_FPCLK_DIVIDED_BY_16
               MSPI1_FPCLK_DIVIDED_BY_32
               MSPI1_FPCLK_DIVIDED_BY_64
               MSPI1_FPCLK_DIVIDED_BY_128
               MSPI1_FPCLK_DIVIDED_BY_256

                 			                  */

#if MSPI1_MASTER_SLAVE == MSPI1_MASTER

#define MSPI1_PRESCALLER           MSPI1_FPCLK_DIVIDED_BY_4

#endif

/* Options:

 	 	 	   MSPI1_MSB_FIRST
               MSPI1_LSB_FIRST

                 			     */

#define MSPI1_DATA_ORDER           MSPI1_MSB_FIRST

/* Options:

 	 	 	   MSPI1_HW_SLAVE_MANAGEMENT
               MSPI1_SW_SLAVE_MANAGEMENT

                 			                */

#define MSPI1_NSS_MANAGE           MSPI1_SW_SLAVE_MANAGEMENT

/* Options:

 	 	 	   MSPI1_8BIT_DATA
               MSPI1_16BIT_DATA

                 			                */

#define MSPI1_DATA_SIZE            MSPI1_8BIT_DATA

/* Options:

 	 	 	   MSPI1_INTERRUPT_DISABLE
               MSPI1_TXE_INTERRUPT_ENABLE
               MSPI1_RXNE_INTERRUPT_ENABLE

                 			                */

#define MSPI1_INTERRUPT_STATUS     MSPI1_INTERRUPT_DISABLE


#endif /* MSPI_CONFIG_H_ */
