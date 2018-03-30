/********************
* counter.h
* Implements counting functionality
*
* University of Strathclyde, 2018
*
* Created by Taisija Treikale
* 25.01.2018 - implement counting functionality controlled by a switch

********************/

#include <msp430.h>
#include <driverlib.h>
#define PORT1_VECTOR (47 * 2u)                          // 0xFFE6 Port 1

extern void initializeCounter();                        // Configure counter input
extern unsigned int count(unsigned int);                // Call counter