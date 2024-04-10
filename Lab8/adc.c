/*
 * adc.c
 *
 *  Created on: Mar 21, 2024
 *      Author: iannels
 */

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart-interrupt.h"

#include "stdio.h"
#include <string.h>

#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80

void adc_init (void) {

    SYSCTL_RCGCADC_R |= BIT0;  // // clock enable for ADC0

    SYSCTL_RCGCGPIO_R |= 0x2;  // clock for port B

    GPIO_PORTB_DIR_R &= ~0x10; // 4) make PB4 input
//    GPIO_PORTB_AFSEL_R |= 0x10; // 5) enable alternate function on PB4
    GPIO_PORTB_DEN_R &= ~0x10; // 6) disable digital I/O on PB4
    GPIO_PORTB_AMSEL_R |= 0x10; // 7) enable analog functionality on PB4

    while((SYSCTL_PRGPIO_R & 0x2) != 0x2){};  // wait for port B

    while ((SYSCTL_PRADC_R & BIT0) != BIT0) {};  // busy wait on bit0 to be 1


    GPIO_PORTB_ADCCTL_R = 0x0;

    SYSCTL_RCGCADC_R |= 0x1;

    GPIO_PORTB_ADCCTL_R |= 0b00010000;

    ADC0_ACTSS_R &= 0xFFFE;

    ADC0_EMUX_R &= 0xFFF0;

    ADC0_SSMUX0_R |= 0xA;

    ADC0_SSCTL0_R = 0x0;

    ADC0_SSCTL0_R |= 0x6;

    ADC0_SAC_R = 0x4;

    ADC0_ACTSS_R |= 0x1;



//    // initialize ss0
//    ADC0_PSSI_R |= BIT0;
//
//    // disabling interrupts
//    ADC0_IM_R &= 0xFFF0FFF0;
//
//    // enabling gpio AINx to trigger ss0
//    ADC0_EMUX_R |= BIT2;
//
//    // setting all samples to be taken from index 10 in the MUX
//    ADC0_SSMUX10_R = 0xAAAAAAAA;
//
//    ADC0_ACTSS_R |= BIT0;  // SS enable for just BIT0
//
//    ADC0_PC_R &= ~0xF;
//    ADC0_PC_R |= 0x1; // 8) configure for 125K samples/sec
//    ADC0_SSPRI_R = 0x0123; // 9) Sequencer 3 is highest priority


//    ADC0_ACTSS_R &= ~0x0008; // 10) disable sample sequencer 3
//    ADC0_EMUX_R = 0x0; // 11) seq3 is software trigger
//    ADC0_SSMUX3_R &= ~0x000F;
//    ADC0_SSMUX3_R |= 0xA; // 12) set channel
//    ADC0_SSCTL3_R = 0x0006; // 13) no TS0 D0, yes IE0 END0
////    ADC0_IM_R &= ~0x0008; // 14) disable SS3 interrupts
//    ADC0_ACTSS_R |= 0x0008; // 15) enable sample sequencer 3
}



uint16_t adc_read (void) {

    ADC0_PSSI_R = 0x0001; // 1) initiate    SS3
    while((ADC0_RIS_R & 0x01) == 0){}; // 2) wait for    conversion done

    ADC0_ISC_R = 0x0001; // 4)    acknowledge completion


    uint16_t result = ADC0_SSFIFO0_R; // 3) read    result
    return result;
}



