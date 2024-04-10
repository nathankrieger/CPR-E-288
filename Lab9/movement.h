/*
 * movement.h
 *
 *  Created on: Feb 1, 2024
 *      Author: iannels
 */
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

double  move_forward (oi_t  *sensor_data, double distance_mm);
void turn_right(oi_t *sensor, double degrees);
void turn_left(oi_t *sensor, double degrees);
double detect(oi_t *sensor);

#endif /* MOVEMENT_H_ */
