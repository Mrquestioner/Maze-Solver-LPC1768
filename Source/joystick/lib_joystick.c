/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	  /* Joystick UP (P1.29) */
    LPC_PINCON->PINSEL3 &= ~(3 << 26);  // Configure P1.29 as GPIO
    LPC_GPIO1->FIODIR   &= ~(1 << 29);  // Set P1.29 as input
	
		/* Joystick RIGHT (P1.28) */
    LPC_PINCON->PINSEL3 &= ~(3 << 24);  // Configure P1.28 as GPIO
    LPC_GPIO1->FIODIR   &= ~(1 << 28);  // Set P1.28 as input
	
    /* Joystick LEFT (P1.27) */
    LPC_PINCON->PINSEL3 &= ~(3 << 22);  // Configure P1.27 as GPIO
    LPC_GPIO1->FIODIR   &= ~(1 << 27);  // Set P1.27 as input
	
    /* Joystick DOWN (P1.26) */
    LPC_PINCON->PINSEL3 &= ~(3 << 20);  // Configure P1.26 as GPIO
    LPC_GPIO1->FIODIR   &= ~(1 << 26);  // Set P1.26 as input
	
    /* Joystick SELECT (P1.25) */
    LPC_PINCON->PINSEL3 &= ~(3 << 18);  // Configure P1.25 as GPIO
    LPC_GPIO1->FIODIR   &= ~(1 << 25);  // Set P1.25 as input
  
}
