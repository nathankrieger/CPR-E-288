/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping.h"
#include "Timer.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

volatile uint32_t lastTime = 0;
volatile uint32_t currentTime = 0;
volatile long timerCycles = 0;
volatile long timeDiff = 0;

void ping_init (void){

  // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x2; // enable port B clock
    while((SYSCTL_RCGCGPIO_R & 0x02) == 0){}; //wait for port B to be ready
    SYSCTL_RCGCTIMER_R |= 0x08; //enable clock to Timer 3
    while((SYSCTL_PRTIMER_R & 0x08) == 0) {}; //wait for Timer 3 to be ready


    GPIO_PORTB_DEN_R |= 0x8;
    GPIO_PORTB_AFSEL_R |= 0x8;
    GPIO_PORTB_PCTL_R |= 0b111000000000000;

    TIMER3_CTL_R &= ~0x100; //disable the timer while it is being configured
    TIMER3_CFG_R |= 0x4; // set the time to 16-bit mode
    TIMER3_TBMR_R |= 0x7; //Edge-time mode & capture mode
    TIMER3_TBMR_R &= 0xEF; //count down
    TIMER3_TBILR_R |= 0xFFFF; //sets a 16-bit max value
    TIMER3_TBPR_R |= 0xFF; //sets 8-bit max value for the prescaler
    TIMER3_CTL_R |= 0xC00; // TBevents

    TIMER3_ICR_R |= 0x400; //Clear capture interrupt flag
    TIMER3_IMR_R |= 0x400; //Enable TB capture interrupt
    NVIC_PRI9_R = (NVIC_PRI9_R & 0xFFFFFF0F) | 0x20; //set the priority to T3CCP1
    NVIC_EN1_R |= 0x10; //set bit 4


    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

    // Configure and enable the timer
    TIMER3_CTL_R |= 0x100;
}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x8;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE

    GPIO_PORTB_DIR_R |= 0x8; // set as output

    GPIO_PORTB_DATA_R &= 0xF7; // low
    GPIO_PORTB_DATA_R |= 0x8; // high
    timer_waitMicros(5); // hold high

    GPIO_PORTB_DIR_R &= 0xF7; // set as input

    GPIO_PORTB_DATA_R &= 0xF7; // low



    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x8;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
}

void TIMER3B_Handler(void){

  // YOUR CODE HERE
  // As needed, go back to review your interrupt handler code for the UART lab.
  // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
  // includes checking the source of the interrupt and clearing the interrupt status bit.
  // Checking the source: test the MIS bit in the MIS register (is the ISR executing
  // because the input capture event happened and interrupts were enabled for that event?
  // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
  // The rest of the code in the ISR depends on actions needed when the event happens.


    if (TIMER3_MIS_R & 0x400){
        lastTime = currentTime;
        currentTime = TIMER3_TBR_R;
//        timerCycles++;
        TIMER3_ICR_R |= 0x400; //Clear capture interrupt flag
    }


}

long ping_getClockCycles(void){

//    long clock_cycles;
    if (lastTime < currentTime){
        timeDiff = 16777216 + lastTime - currentTime;//overflow has occured
    }
    else{
        timeDiff = lastTime - currentTime; //calculate the time difference  ((unsigned long) overflow << 24)+
    }
    timerCycles = timeDiff;
    return timerCycles;
}

float ping_getDistance (void){

    float distance;
    distance = 0.0343*(((float)timeDiff/16.0F)/2.0F); //distance in centimeters
    return distance;
}
