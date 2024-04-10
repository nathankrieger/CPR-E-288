/*
 * servo.c
 *
 *  Created on: Apr 4, 2024
 *      Author: iannels
 */
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "timer.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

void servo_init(void) {


    // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x2; // enable port B clock
    while((SYSCTL_RCGCGPIO_R & 0x02) == 0){}; //wait for port B to be ready
    SYSCTL_RCGCTIMER_R |= 0x02; //enable clock to Timer 1
    while((SYSCTL_PRTIMER_R & 0x02) == 0) {}; //wait for Timer 1 to be ready

    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;  // set as output

    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0b11100000000000000000000;

    TIMER1_CTL_R &= ~0x100; //disable the timer while it is being configured
    TIMER1_CFG_R |= 0x4; // set the time to 16-bit mode
    TIMER1_TBMR_R = 0xA; //Edge-time mode & periodic mode & PWM mode
    TIMER1_TBMR_R &= ~0x4;

    TIMER1_TBILR_R = 0xE200; // 0xFFFF; //sets a 16-bit max value              COULD BE WRONG NOT SURE WHAT MAX VALUE IS NEEDED
    TIMER1_TBPR_R = 0x04; //sets 8-bit max value for the prescaler
    TIMER1_CTL_R &= ~0x4000;



    TIMER1_TBMATCHR_R = (0x4E200) & 0xFFFF;
    TIMER1_TBPMR_R = (0x4E200) >> 16;

    // Configure and enable the timer
    TIMER1_CTL_R |= 0x100;
}


void servo_move(uint16_t degrees) {

//    GPIO_PORTB_DATA_R &= 0xF7; // low

    double pw = (0.00555556 * degrees * 1.0) + 1.0;

    int cycles = (pw * 320000) / 20;

//    char s[20] = {0};
//
//    sprintf(s, "moving to %d degrees", pw);

//    uart_sendStr(*s);

    TIMER1_TBMATCHR_R = (0x4E200 - cycles) & 0xFFFF;
    TIMER1_TBPMR_R = (0x4E200 - cycles) >> 16;

//    timer_waitMillis(500);
}
