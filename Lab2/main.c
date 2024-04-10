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
#include "movement.h"
#include "open_interface.h"





int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen.

	// Print "Hello, world" on the LCD
	//	lcd_puts("Hello, world");


	oi_t *sensor_data = oi_alloc();
	oi_init(sensor_data);


//	move_forward(sensor_data, 2000);

//	move_forward(sensor_data, 500);

	/*turn_right(sensor_data, -90.0);

	move_forward(sensor_data, 500);

	turn_left(sensor_data, 90.0);*/

//	// Square - left
//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90.0);
//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90.0);
//	move_forward(sensor_data, 500);
//	turn_left(sensor_data, 90.0);
//	move_forward(sensor_data, 500);


	// Square
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90.0);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90.0);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, 90.0);
//    move_forward(sensor_data, 500);

	move_forward(sensor_data, 2000);







	oi_free(sensor_data); // do this once at end of main()


	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
