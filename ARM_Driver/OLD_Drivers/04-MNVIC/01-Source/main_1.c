/*
 * Main_program.c
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */
#include <AVR_UART.h>
#include <UART_Confg.h>
#include <asf.h>
#include <AVR_I_O.h>
#include <AVR_PORTS.h>
#include <GPIO_functions.h>

#define F_CPU 4000000ul
#include<util/delay.h>


int main (void)
{    char x ;
	 Pin_Direction (A ,0, output);
	 Pin_write (A , 0, 0 );
     UART_INIT();
	 
   while(1){
	   UART_Transmit_string ("Hello UART");
	   x = UART_Read();
       if(x=='0')
	    Pin_write (A , 0, 1 ); 
	   if(x=='1')
	    Pin_write (A , 0, 0 );  
   }
}
