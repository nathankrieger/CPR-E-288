/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"




int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen.

	// Print "Hello, world" on the LCD
	//	lcd_puts("Hello, world");


	int i = 0;

	char str[] = "Microcontrollers are lots of fun!"; //updates 33 + 20 times

	while (true) {

	    for (i = 0; i < strlen(str) + 20; i++) {  // number of times it needs to update - strlen(str) + 20

            int j = 0;
            int k = 0;

	        // build row to be displayed

	        char result[20];

	        result[0] = 0;


	        //if at the start
	        if (i <= 19) {

	            for (j = 19 - i; j > 0; j--) {
	                strcat(result, " ");
	            }


	            for (k = 0; k < i + 1; k++) {
	                result[strlen(result)] = str[k];
	            }
	        }

	        // middle
	        else if (i <= strlen(str))  {

	            for (k = i - 19; k < i; k++) {
                    result[strlen(result)] = str[k];
                }

	        }

	        // end
	        else {

	            for (k = i - 19; k < strlen(str); k++) {
                    result[strlen(result)] = str[k];
                }


	            for (j = 0; j < i - strlen(str); j++) {
	                strcat(result, " ");
                }
	        }



	        lcd_printf(result);
	        timer_waitMillis(300);

	        int c = 0;
	        for (c = 0; c<20; c++) {
	            result[c] = '\0';
	        }
	    }
	}




	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
