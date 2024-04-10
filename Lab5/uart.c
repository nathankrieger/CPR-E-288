/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart.h"
#include "stdio.h"

#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80
#define SYSCLOCK    16000000
#define CLCDIV      16
#define BAUDRATE    115200

void uart_init(void){

  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= BIT1;

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= BIT1;

  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRGPIO_R & BIT1) == 0) {};
  while ((SYSCTL_PRUART_R & BIT1) == 0) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0x3;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0x3;

  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R = 0x11;

  //calculate baud rate
  uint16_t iBRD = SYSCLOCK / (CLCDIV * BAUDRATE); //use equations
  uint16_t fBRD = (int)((SYSCLOCK / (CLCDIV * BAUDRATE)) % iBRD * 64 + .5); //use equations

  //turn off UART1 while setting it up
  UART1_CTL_R &= BIT0;

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0x60;

  //use system clock as source
  //note from the datasheet UARTCCC register description:
  //field is 0 (system clock) by default on reset
  //Good to be explicit in your code
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //note from the datasheet UARTCTL register description:
  //RX and TX are enabled by default on reset
  //Good to be explicit in your code
  //Be careful to not clear RX and TX enable bits
  //(either preserve if already set or set them)
  UART1_CTL_R |= BIT0;


}

void uart_sendChar(char data){

    while(UART1_FR_R & BIT5) {}

    UART1_DR_R = data;
}

char uart_receive(void){

    while(UART1_FR_R & UART_FR_RXFE) {}

    return (char)UART1_DR_R;
}

void uart_sendStr(const char *data){

    int i;
    for (i = 0; i < strlen(data); i++) {
        uart_sendChar(data[i]);
    }

    uart_sendChar('\n');
    uart_sendChar('\r');
}
