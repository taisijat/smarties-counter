/********************
* servo.h
* Operates the servo motor
*
* University of Strathclyde, 2018
*
* Created by Taisija Treikale
* 26.02.2018 - simple 180 degress rotation

********************/

#include <msp430.h>
#define ROTATE_RESET	        0
#define ROTATE_0		600
#define ROTATE_90		1650
#define ROTATE_180		2700

// 1. set P1.7 high -> motor moving
// 2. hold for as long as determined by arg1
// 3. set P1.7 low -> motor stationary
#define servo_rotate(arg1) \
  for (int i=0; i<30; i++) {	        \
          P1OUT |= BIT7;		\
          __delay_cycles(arg1);	        \
          P1OUT &= ~BIT7;		\
          __delay_cycles(20000);	\
  }

extern void initializeServo ();
extern void delay (unsigned long);
extern void servo_reset ();