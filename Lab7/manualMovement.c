/*
 * manualMovement.c
 *
 *  Created on: Mar 5, 2024
 *      Author: iannels
 */


#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include "uart.h"

void move(void) {

    char c = uart_receive();

    while (c != 'k') {


        c = uart_receive();

        if (c == 'w') { // move forward
            oi_setWheels(500,500);

        }


        else if (c == 's') { // move backward
            oi_setWheels(-500,-500);

        }


        else if (c == 'd') {// turn right
            oi_setWheels(-100,100);

        }


        else if (c == 'a') {// turn
            oi_setWheels(100,-100);

        } else if (c == 't') {
            return;
        }

        timer_waitMillis(100);
        oi_setWheels(0,0);

    }
}
