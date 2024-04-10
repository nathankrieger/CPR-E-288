/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021, 2/17/2022
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "uart.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors



#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for UART init part of lab)
	 cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code

	 uart_init();

//	 Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
//      SYSCTL_RCGCGPIO_R |= BIT1;
//      while ((SYSCTL_PRGPIO_R & BIT1) == 0) {};
//      GPIO_PORTB_DEN_R |= 0x3;
//      GPIO_PORTB_AFSEL_R |= 0x3;
//      GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the desired locations
//      GPIO_PORTB_PCTL_R |= 0x11;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)
		 cyBot_uart_init_last_half();  // Complete the UART device configuration

		// Initialize the scan
	   cyBOT_init_Scan(0b11);
		// Remember servo calibration function and variables from Lab 3

	// YOUR CODE HERE
//	   char c = cyBot_getByte_blocking();
//	   timer_waitMillis(1000);
//	   cyBot_sendByte(c);

//	   char c = uart_receive();
//       timer_waitMillis(1000);
//       uart_sendChar(c);

//       char data[] = "String";
//       uart_sendStr(data);

    char data[21] = {0};

    int i = 0;

	while(1)
	{
	  char c = uart_receive();
	  if(i == 20 || c == '\r') {
	      lcd_printf(data);

	      uart_sendStr(data);

	      lcd_setCursorPos(0,1);
	      char length[] = {0};
	      sprintf(length, "%d", strlen(data));
	      lcd_puts(length);
	      i = 0;
	  }
	  else {
	      data[i] = c;
	  }

	  i++;

//	    if (c == '\r') {
//	        uart_sendChar('\n');
//	    }
	}

}
