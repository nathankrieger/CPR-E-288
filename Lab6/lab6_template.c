/**
 * lab6_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
#include "uart-interrupt.h"

#include "stdio.h"


// Uncomment or add any include directives that are needed
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_interrupt_init();
	cyBOT_init_Scan(0b11);

	// YOUR CODE HERE
	cyBOT_Scan_t scan;

//	cyBOT_Scan(90, &scan);
//	cyBOT_Scan(0, &scan);



	while(1)
	{


      // YOUR CODE HERE






//	  if (uart_receive_nonblocking() == 'g') {
//
//	      printf("g");
//
//	      int i;
//          for (i = 0; i < 180; i += 4) {
//
//              if (uart_receive_nonblocking() == 's') {
//                  break;
//              }
//              cyBOT_Scan(i, &scan);
//          }
//	  }
	}

}
