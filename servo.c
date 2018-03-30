/********************
* servo.c
* Implements counting functionality
*
* University of Strathclyde, 2018
*
* Created by Taisija Treikale
* 26.02.2018 - simple 180 degress rotation

********************/

#include "servo.h"

void initializeServo()
{
  P1DIR = BIT7 | BIT0;                    // P1.7 (PWM), P1.0 (green LED) set as outputs
  P4DIR = BIT0;                           // P4.0 (green LED) set as output
  P1OUT |= BIT0;                          // set P1.0 high (LED on)
  P4OUT &= ~BIT0;                         // set P4.0 low (LED off)
}

void delay (unsigned long ms)
{
  unsigned int i;
  for (i = ms; i > 0; i--)
  {
    __delay_cycles(1000);		// set for 16Mhz, change it to 1000 for 1 Mhz
  }
}

void servo_reset()
{
  servo_rotate(ROTATE_RESET);
}