/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"
#include "servo.h"
#include <string.h>
#include <stdio.h>

// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();
	servo_init();

	timer_waitMillis(1000);

	while (1) {


        servo_move(90);

        timer_waitMillis(500);

        servo_move(30);

        timer_waitMillis(500);

        servo_move(150);

        timer_waitMillis(500);

        servo_move(90);

        timer_waitMillis(500);
	}

	// YOUR CODE HERE

}
