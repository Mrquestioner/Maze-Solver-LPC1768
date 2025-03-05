/*----------------------------------------------------------------------------
 * File:        IRQ_Button.c
 * Project:     Maze Solver System on Land Tiger Board (LPC1768)
 * Course:      Computer Architecture (Master’s Program, Politecnico di Torino)
 * Description: 
 *              This file manages external interrupts triggered by hardware buttons 
 *              on the Land Tiger Board. It handles:
 *              - **EINT0**: Toggles between uppercase and lowercase maze labels.
 *              - **EINT1**: Generates a new random maze.
 *              - **EINT2**: Solves the maze and displays the iteration count.
 *              
 *              Each interrupt is disabled upon activation to prevent re-entry, 
 *              and the corresponding flag is set for processing in the main program.
 *
 * Technologies Used:
 *              - Programming Language: C
 *              - Hardware: LPC1768 (ARM Cortex-M3)
 *              - Interrupt Handling: External Interrupts (EINT0, EINT1, EINT2)
 * 
 * Author:      Amirhossein Shirvani Dastgerdi
 * Created:     24/02/2025
 * Last Modified: 26/02/2025
 * Version:     v1.0
 *
 *----------------------------------------------------------------------------
 * License:
 * This software is provided "AS IS" without any express or implied warranties, 
 * including but not limited to the implied warranties of merchantability and 
 * fitness for a particular purpose. The author is not responsible for any damages 
 * or data loss resulting from the use of this software.
 *
 * Copyright (c) 2025 Amirhossein Shirvani Dastgerdi. All rights reserved.
 * 
 * Contact:
 * GitHub:    https://github.com/[YourGitHubUsername]
 * LinkedIn:  https://www.linkedin.com/in/[YourLinkedInUsername]
 *----------------------------------------------------------------------------*/

#include "button.h"
#include <LPC17xx.h>
#include "button.h"  

void EINT0_IRQHandler(void)  
{
    NVIC_DisableIRQ(EINT0_IRQn);  // Disable external interrupt 0 to prevent re-entry
    LPC_PINCON->PINSEL4 &= ~(1 << 20);  // Clear pin function selection for EINT0
    INT0 = 1;  // Set flag to indicate interrupt was triggered
    LPC_SC->EXTINT |= (1 << 0);  // Clear interrupt flag for EINT0
}

void EINT1_IRQHandler(void)  
{
    NVIC_DisableIRQ(EINT1_IRQn);  // Disable external interrupt 1
    LPC_PINCON->PINSEL4 &= ~(1 << 22);  // Clear pin function selection for EINT1
    KEY1 = 1;  // Set flag to indicate Key 1 press
    LPC_SC->EXTINT |= (1 << 1);  // Clear interrupt flag for EINT1
}

void EINT2_IRQHandler(void)  
{
    NVIC_DisableIRQ(EINT2_IRQn);  // Disable external interrupt 2
    LPC_PINCON->PINSEL4 &= ~(1 << 24);  // Clear pin function selection for EINT2
    KEY2 = 1;  // Set flag to indicate Key 2 press
    LPC_SC->EXTINT |= (1 << 2);  // Clear interrupt flag for EINT2
}




