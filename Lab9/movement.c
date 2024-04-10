/*
 * movement.c
 *
 *  Created on: Feb 1, 2024
 *      Author: iannels
 */
#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"

double move_forward (oi_t  *sensor_data, double distance_mm) {

    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(500,500); //move forward at full speed

    while (sum < distance_mm) {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer

        if (detect(sensor_data) != 0) {
            return detect(sensor_data);
        }

        oi_setWheels(300,300);
        lcd_printf("%f", sum);
    }

//    lcd_init();
//    lcd_printf("Distance: %f", sum);

    oi_setWheels(0,0); //stop

    return sum;
}

double move_backward (oi_t  *sensor_data, double distance_mm) {

    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-300,-300); //move forward at full speed

    while (sum < distance_mm) {
        oi_update(sensor_data);
        sum -= sensor_data -> distance; // use -> notation since pointer
    }

//    lcd_init();
//    lcd_printf("Distance: %f", sum);

    oi_setWheels(0,0); //stop

    return sum;
}


void turn_right(oi_t *sensor, double degrees) {
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(-50,50); //move forward at full speed

    while (sum > degrees) {
        oi_update(sensor);
        sum += sensor -> angle; // use -> notation since pointer
//        sum += oi_getDegrees(sensor);
    }

    oi_setWheels(0,0); //stop
}

void turn_left(oi_t *sensor, double degrees) {
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(50,-50); //move forward at full speed

    while (sum < degrees) {
        oi_update(sensor);
        sum += sensor -> angle; // use -> notation since pointer
//        sum += oi_getDegrees(sensor);
    }

    oi_setWheels(0,0); //stop
}


double detect(oi_t *sensor) { //  make sure to add 15 cm

//    oi_update(sensor);

    if (sensor->bumpRight) {

//        oi_update(sensor);
        move_backward(sensor, 250);
        turn_left(sensor, 45);
        move_forward(sensor, 300);
        turn_right(sensor, -65);
        return 1;

    } else if (sensor->bumpLeft) {

//        oi_update(sensor);
        move_backward(sensor, 250);
        turn_right(sensor, -45);
        move_forward(sensor, 300);
        turn_left(sensor, 65);
        return 1;

    }

    return 0.0;
}





