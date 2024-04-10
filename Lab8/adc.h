/*
 * adc.h
 *
 *  Created on: Mar 21, 2024
 *      Author: iannels
 */

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart-interrupt.h"

#include "stdio.h"
#include <string.h>

#ifndef ADC_H_
#define ADC_H_


    void adc_init (void);
    uint16_t adc_read (void);

#endif /* ADC_H_ */
