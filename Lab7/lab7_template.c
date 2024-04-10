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
#include "uart.h"
#include "uart-interrupt.h"
#include "manualMovement.h"
#include "median.h"

#include "stdio.h"


// Uncomment or add any include directives that are needed
 #include "open_interface.h"
 #include "movement.h"
// #include "button.h"

#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
//	uart_interrupt_init();
	uart_init();
	cyBOT_init_Scan(0b111);

	oi_t *sensor_data = oi_alloc(); // oi initiation
    oi_init(sensor_data);

    oi_setWheels(0,0);

	// YOUR CODE HERE
	cyBOT_Scan_t scan;

//	cyBOT_Scan(90, &scan);
//	cyBOT_Scan(0, &scan);


//	cyBOT_SERVO_cal();

//	right_calibration_value = 285250;
//	left_calibration_value = 1261750;

	// cybot-15
//	right_calibration_value = 248500;
//	left_calibration_value = 1272250;

	// cybot-7
	right_calibration_value = 227500;
	left_calibration_value = 1246000;


	//cybot 3
//	right_calibration_value = 274750;
//	left_calibration_value = 1235500;



//	move();


//
//	move_forward(sensor_data, 500);
//    turn_right(sensor_data, -90.0);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, -90.0);
//    move_forward(sensor_data, 500);
//    turn_right(sensor_data, -90.0);
//    move_forward(sensor_data, 500);


	int irDistArr[91] = {0};

	int doAgain = 0;

	int avg[3] = {0};

	int onObject = 0;
	int onObjectArr[91] = {0};

	int prevDist = 0;


	while(doAgain < 2)
	{


	    cyBOT_Scan(0, &scan);
	    timer_waitMillis(500);

	    char outputString[20];

	    int i;
	    for (i=0; i<=180; i += 2) { // IR


	        cyBOT_Scan(i, &scan);
            avg[0] = scan.IR_raw_val;

            cyBOT_Scan(i, &scan);
            avg[1] = scan.IR_raw_val;

            cyBOT_Scan(i, &scan);
            avg[2] = scan.IR_raw_val;

            sort(avg, 3);

            int median = avg[1];

            irDistArr[i / 2] = median;


            sprintf(outputString, "%d \t \t %d", i, median);

            uart_sendStr(outputString);



            if (median > 500 && i > 5) { // cutting out anything less than 400
                if (median > prevDist + 150) { // jumped mroe tha 150

                    onObject = 1;

                } else if (median < prevDist - 150) { // jumped bakc down

                    onObject = 0;

                }
            } else {
                onObject = 0;
            }

            onObjectArr[i / 2] = onObject;


            prevDist = median;
	    }

	    //distance and onObject array
	    for (i = 0; i < 91; i++) {
            char c =(char)onObjectArr[i] + '0';
            uart_sendChar(c);
            uart_sendChar(' ');
        }
	    uart_sendChar('\n');
	    uart_sendChar('\r');



	    onObjectArr[0] = 0;
        onObjectArr[1] = 0;
        onObjectArr[2] = 0;
        onObjectArr[3] = 0;
        onObjectArr[4] = 0;
        onObjectArr[8] = 0;


        for (i = 4; i < 90; i++) {

            if (onObjectArr[i] == 1) {

                if (onObjectArr[i - 1] == 0 && onObjectArr[i + 1] == 0) {
                    onObjectArr[i] = 0;
                }

            }
        }



        int smallestObjectCenterAngle = 0;
        float smallestObjectWidthCM = 92;
        float smallestObjectDistance = 0;


        int objectCount = 0;

        float objectDistance = 0;
        int objectWidth = 0;

        char objectString[70] = {0};
        float avgDist[5] = {0};

        for (i = 0; i < 91; i++) {

            if (onObjectArr[i] == 1) {
                objectWidth++;
            } else {

                if (objectWidth > 0) {
                    objectCount++;
                    int objectCenterAngle = (i - (objectWidth / 2) - 1) * 2;


                    timer_waitMillis(1000);


                    cyBOT_Scan(objectCenterAngle, &scan);
                    avgDist[0] = scan.sound_dist;

                    cyBOT_Scan(objectCenterAngle, &scan);
                    avgDist[1] = scan.sound_dist;

                    cyBOT_Scan(objectCenterAngle, &scan);
                    avgDist[2] = scan.sound_dist;

                    cyBOT_Scan(objectCenterAngle, &scan);
                    avgDist[3] = scan.sound_dist;

                    cyBOT_Scan(objectCenterAngle, &scan);
                    avgDist[4] = scan.sound_dist;



                    sortFloat(avgDist, 5);

                    objectDistance = avgDist[2];

//                    objectDistance = (avgDist[0] + avgDist[1] + avgDist[2]) / 3;

                    float objectWidthCM = 2.0 * 3.14159 * objectDistance * ((objectWidth * 2.0) / 360.0);

                    if(objectWidthCM < smallestObjectWidthCM) {
                        smallestObjectWidthCM = objectWidthCM;
                        smallestObjectCenterAngle = objectCenterAngle;
                        smallestObjectDistance = objectDistance;
                    }



                    sprintf(objectString, "Object: %d \t \t Angle: %d \t \t Width: %.2f \t \t Distance: %.2f", objectCount, objectCenterAngle, objectWidthCM, objectDistance);

                    uart_sendStr(objectString);

                }
                objectWidth = 0;
            }

        }


        if (smallestObjectCenterAngle >  90) {
            turn_left(sensor_data, smallestObjectCenterAngle - 100.0);
        } else {
            turn_right(sensor_data, smallestObjectCenterAngle - 80.0);
        }

        sprintf(objectString, "Moving towards smallest object #%d with distance %f", objectCount, objectDistance);

        uart_sendStr(objectString);

        move_forward(sensor_data, smallestObjectDistance * 10.0 - ((smallestObjectDistance * 10.0) / 5.0));




        onObject = 0;
//        onObjectArr[91] = {0};

        for (i = 0; i < 91; i++) {
            onObjectArr[i] = 0;
        }

        prevDist = 0;

        doAgain++;
	}



}
