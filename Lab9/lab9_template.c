/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();


	ping_trigger();
	int i = 0;
	for(;i < 100000;++i);
	ping_getClockCycles();

	// YOUR CODE HERE

	while(1)
	{

	    ping_trigger();
        timer_waitMillis(350);

	    float f = 10.0;
	    float pw = ping_getClockCycles();
	    float pwms = pw * 0.0000625;
        f = ping_getDistance();
	    char s[100] = {0};

	    sprintf(s, "%.2f cm \n %.2f cycles \n %.2f ms", f, pw, pwms);
	    lcd_printf(s);



	}

}
