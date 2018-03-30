/********************
* counter.c
* Implements counting functionality
*
* University of Strathclyde, 2018
*
* Created by Taisija Treikale
* 25.01.2018 - implement counting functionality controlled by a switch

********************/

#include "counter.h"

void initializeCounter()
{
  
  // Switches
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
  // Configure interrupts
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4);
  GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN6);
  GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6);
  
}

unsigned int count(unsigned int current_)
{
  
  if (current_ < 1000)
  {
  current_++;                                   // Increment current value
  }
  
  return current_;                              // Return updated value
     
}