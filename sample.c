/*-----------------------------------------------------------------------------
 * Project:    Maze Solver System on Land Tiger Board (LPC1768)
 * Course:     Computer Architecture (Master’s Program, Politecnico di Torino)
 * 
 * Description:
 * This project implements a real-time maze generation and solving system 
 * on the Land Tiger Board (LPC1768) using an ARM Cortex-M3 microcontroller.
 * 
 * Functionality:
 * - **Key 1**: Generates a new random maze using Timer0 as a seed.
 * - **Key 2**: Solves the maze, finding the shortest path to an exit, 
 *              and displays the iteration count.
 * - **INT0**: Toggles between uppercase and lowercase directional indicators.
 * - **RIT (Repetitive Interrupt Timer)**: Handles button debouncing to ensure 
 *              accurate input processing.
 * 
 * Technologies Used:
 * - **Languages**: C, ARM Assembly
 * - **Hardware**: LPC1768 (ARM Cortex-M3), LCD Display (ILI9325)
 * - **Development Tools**: Keil uVision
 * - **Peripheral Handling**: RIT for button debouncing, Timer0 for randomness
 * 
 * Notes:
 * Developed as part of an embedded systems project, combining C and ARM Assembly 
 * to optimize execution on embedded hardware.
 * 
 * Author:     		Amirhossein Shirvani Dastgerdi
 * Student ID: 		338942
 * Created:    		24/02/2025
 * Last Modified: 05/03/2025
 * Version:    		1.0
 *-----------------------------------------------------------------------------
 * License:
 * This software is provided "as-is," without any express or implied warranties, 
 * including but not limited to implied warranties of merchantability and 
 * fitness for a particular purpose. The author assumes no liability for any 
 * damages or data loss resulting from the use of this software.
 *
 * Copyright (c) 2025 Amirhossein Shirvani Dastgerdi. All rights reserved.
 * 
 * Contact:		
 * - Email:    amirhoseinshirvani@gmail.com
 * - GitHub:   https://github.com/Mrquestioner
 * - LinkedIn: https://www.linkedin.com/in/amirhossein-shirvani-dastgerdi-358136219/
 * - YouTube:  https://www.youtube.com/@amir_shirvani
 *----------------------------------------------------------------------------*/



/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "button.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"


int main(void)
{
		SystemInit();  // Initialize system clock and peripherals
    joystick_init();

    LCD_Initialization();  // Initialize the LCD display
	
    DisplayWelcomeMessage();
	
    BUTTON_init();  // Configure hardware buttons for user input
    
    init_timer(0);  // Initialize Timer 0 for system timing control
    enable_timer(0);  // Start Timer 0
    
    init_RIT(0x004C4B40);  // Initialize Repetitive Interrupt Timer (RIT) for button debouncing
    enable_RIT();  				// Enable RIT to process button inputs precisely
	
		
    
    while (1)	
    {
        __ASM("wfi");  // Enter low-power mode, waiting for interrupts (efficient power usage)
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
