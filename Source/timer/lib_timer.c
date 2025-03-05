/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <LPC17xx.h>
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer(uint8_t timer_num)
{
    if (timer_num == 0)
    {
        LPC_TIM0->TCR = 1;     // Enable Timer 0
    }
    else if (timer_num == 1)
    {
        LPC_TIM1->TCR = 1;     // Enable Timer 1
    }
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0;
  }
  else
  {
	LPC_TIM1->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer(uint8_t timer_num)
{
    if (timer_num == 0)
    {
        LPC_TIM0->TCR |= 0x02;    // Reset Timer 0
        LPC_TIM0->TCR &= ~0x02;   // Clear reset bit
    }
    else if (timer_num == 1)
    {
        LPC_TIM1->TCR |= 0x02;    // Reset Timer 1
        LPC_TIM1->TCR &= ~0x02;   // Clear reset bit
    }
}

//uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval )
uint32_t init_timer ( uint8_t timer_num)
{
  if ( timer_num == 0 )
  {

		
//LPC_TIM0->MCR = 1;	
// Enable interrupt generation on a match event with Match Register 0 (MR0) for Timer 0.
// The Timer Counter (TC) will continue counting without resetting or stopping.

		
//LPC_TIM0->MCR = 2;
// Configure Timer 0 to reset the Timer Counter (TC) to 0 on a match event with Match Register 0 (MR0).
// No interrupt will be generated, and the timer will continue running.
		
//LPC_TIM0->MCR = 3;
// Enable interrupt generation and reset the Timer Counter (TC) to 0 on a match event with Match Register 0 (MR0) for Timer 0.
// This creates a periodic timer that generates interrupts at regular intervals.

		
// 	LPC_TIM0->MCR = 0;		
// Disable all match-related actions (interrupts, timer reset, and stop) for Timer 0.
// Disable all match-related actions for Timer 0:
// - No interrupt generation on match events.
// - No reset of the Timer Counter (TC) on match.
// - The timer will continue running without stopping or resetting on a match.


//	LPC_TIM0->MR0 = TimerInterval;


	LPC_TIM0->MCR = 0;

		
		
		
//NVIC_EnableIRQ(TIMER0_IRQn);
	return (1);
  }
  else if ( timer_num == 1 )
  {
//	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 2;				/* Interrupt and Reset on MR1 */

	//NVIC_EnableIRQ(TIMER1_IRQn);
	return (1);
  }
  return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
