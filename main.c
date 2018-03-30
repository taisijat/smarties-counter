/********************
* 'Smarties or M&M's counter'
* Group 9
*
* University of Strathclyde, 2018
*
* Created by Taisija Treikale
* 25.01.2018 - implement counting functionality controlled by a switch
* 13.03.2018 - show total count on LCD
*
********************/

#include <msp430.h>
#include <driverlib.h>
#include "counter.h"
#include "hal_LCD.h"
#include "servo.h"

unsigned int count_ = 0;                                // Holds total current count
unsigned int countBlue_, countBrown_, countGreen_,
             countOrange_, countPink_, countPurple_,
             countRed_, countYellow_, countReject_ = 0; // Current count in each cup

bool SW1_interruptFlag;
bool SW2_interruptFlag;
bool PAUSE_interruptFlag;
bool RST_interruptFlag;
short showCol = 0;                                      // Determines which count to show

/*
Execute interrupt service routine if a switch is pressed
*/
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  switch (__even_in_range(P1IV,P1IV_P1IFG7))
  {
    
  case P1IV_P1IFG2:                                     // Pause
    PAUSE_interruptFlag ^= BIT0;                        // Toggle flag
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2);       // Clear interrupt
    break;
  
  case P1IV_P1IFG3:                                     // SW1
    SW1_interruptFlag = 1;                              // Set flag
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);       // Clear interrupt
    break;
    
  case P1IV_P1IFG4:                                     // SW2
    SW2_interruptFlag = 1;                              // Set flag
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);       // Clear interrupt
    break;
    
  }
}
#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  switch (__even_in_range(P2IV,P2IV_P2IFG7))
  {
    
  case P2IV_P2IFG6:                                     // Reset
    RST_interruptFlag = 1;                              // Set flag
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN6);       // Clear interrupt
    break;
    
  }
}

void showCount(char char1, char char2, char char3, unsigned int c)
{
  unsigned short cNum1, cNum2, cNum3;
  char c1, c2, c3;
  
  // Get count number by digits
  cNum1 = c / 100;
  cNum2 = (c - cNum1*100) / 10;
  cNum3 = c - cNum1*100 - cNum2*10;
  // Convert to char
  c1 = cNum1 + '0';
  c2 = cNum2 + '0';
  c3 = cNum3 + '0';
  // Show count on LCD as "***###"
  showChar(char1, pos1);
  showChar(char2, pos2);
  showChar(char3, pos3);
  showChar(c1, pos4);
  showChar(c2, pos5);
  showChar(c3, pos6);
}

void readCount()
{
  if (showCol == 0) {
    showCount('A', 'L', 'L', count_);
  }
  else if (showCol == 1) {
    showCount('B', 'L', 'U', countBlue_);
  }
  else if (showCol == 2) {
    showCount('B', 'R', 'O', countBrown_);
  }
  else if (showCol == 3) {
    showCount('G', 'R', 'E', countGreen_);
  }
  else if (showCol == 4) {
    showCount('O', 'R', 'A', countOrange_);
  }
  else if (showCol == 5) {
    showCount('P', 'I', 'N', countPink_);
  }
  else if (showCol == 6) {
    showCount('P', 'U', 'R', countPurple_);
  }
  else if (showCol == 7) {
    showCount('R', 'E', 'D', countRed_);
  }
  else if (showCol == 8) {
    showCount('Y', 'E', 'L', countYellow_);
  }
  else if (showCol == 9) {
    showCount('R', 'E', 'J', countReject_);
  }
}

void warn()
{
  clearLCD();
  showChar('F', pos2);
  showChar('U', pos3);
  showChar('L', pos4);
  showChar('L', pos5);
}

int main(void)
{
  /*
  Setup
  */

  WDTCTL = WDTPW | WDTHOLD;                                     // Stop watchdog timer
  
  initializeCounter();
  initializeServo();
  Init_LCD();
  clearLCD();
  __enable_interrupt();                                         // Enable interrupts

  // Disable the GPIO power-on default high-impedance mode
  // to activate previously configured port settings
  PMM_unlockLPM5();
  
  /*
  Execution
  */

  while(1) {

          servo_rotate(ROTATE_0);
          servo_rotate(ROTATE_90);
          servo_rotate(ROTATE_180);

          P1OUT ^= BIT0;                  // toggle P1.0
          P4OUT ^= BIT0;                  // toggle P4.0

          delay(5000);                    // pause

  }
        
  /*while(1)
  {
    
    // Reset all counts to zero
    if (RST_interruptFlag == 1)
    {
      count_ = 0;
      countBlue_ = 0;
      countBrown_ = 0;
      countGreen_ = 0;
      countOrange_ = 0;
      countPink_ = 0;
      countPurple_ = 0;
      countRed_ = 0;
      countYellow_ = 0;
      countReject_ = 0;
      RST_interruptFlag = 0;
    }
    
    // Cycle through colours: next or previous
    if (SW1_interruptFlag == 1)
    {
      showCol--;
      if (showCol < 0)
      {
        showCol = 9;
      }
      SW1_interruptFlag = 0;
    }
    
    if (SW2_interruptFlag == 1)
    {
      showCol++;
      if (showCol > 9)
      {
        showCol = 0;
      }
      SW2_interruptFlag = 0;
    }
    
    // Show count or warn about overflow
    if (count_ <= 999)
    {
      readCount();
    }
    else
    {
      warn();
    }
    
    // Proceed only if not paused
    if (PAUSE_interruptFlag == 0) {
    
      countReject_ = count(countReject_);
      count_ = count(count_);
      __delay_cycles(100000);
      
      }
  }*/
  
}