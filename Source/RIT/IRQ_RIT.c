/*-----------------------------------------------------------------------------
 * File:        IRQ_RIT.h
 * Project:     Maze Solver System on Land Tiger Board (LPC1768)
 * Course:      Computer Architecture (Master’s Program, Politecnico di Torino)
 * 
 * Description:
 * This header file declares functions and macros for handling the 
 * Repetitive Interrupt Timer (RIT) interrupt in the Maze Solver System.
 * The RIT is used for button debouncing to ensure accurate input processing.
 * 
 * Functionality:
 * - Initializes the RIT for periodic interrupt generation.
 * - Handles debouncing logic for button presses.
 * - Provides an interrupt service routine (ISR) to process button events.
 * 
 * Technologies Used:
 * - **Languages**: C
 * - **Hardware**: LPC1768 (ARM Cortex-M3)
 * - **Development Tools**: Keil uVision
 * - **Peripheral Handling**: RIT for button debouncing
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


#include "LPC17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "button.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>


int iteration;


int number_of_clicks = 0;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

//#define TILE_WIDTH  (SCREEN_WIDTH / C_NUM_COLUMNS)  // Tile width
//#define TILE_HEIGHT ((SCREEN_HEIGHT - 20) / C_NUM_ROWS)  // Tile height, leaving space for text

#define TILE_WIDTH  (SCREEN_WIDTH / visible_cols)  
#define TILE_HEIGHT ((SCREEN_HEIGHT - 21) / visible_rows) 

#define FONT_WIDTH  (TILE_WIDTH - 6)   // Leave 1px padding on each side
#define FONT_HEIGHT (TILE_HEIGHT - 6)  // Leave 1px padding on top and bottom

/* 
 * Function to draw a filled rectangle on the LCD with a border.
 * Used for displaying text within a dedicated area.
 */
void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint16_t borderColor) {
    for (uint16_t i = 0; i < height; i++) {  // Iterate over rows
        for (uint16_t j = 0; j < width; j++) { // Iterate over columns
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                LCD_SetPoint(x + j, y + i, borderColor); // Draw border
            } else {
                LCD_SetPoint(x + j, y + i, color); // Fill inner area
            }
        }
    }
}

// External function for solving the maze
extern void mazeSolver(int, int, char *, int *);
extern void Change_case(int, int, char *, int *);


// Maze grid dimensions
//const int C_NUM_ROWS = 19;
//const int C_NUM_COLUMNS = 19;

const int C_NUM_ROWS = 30;
const int C_NUM_COLUMNS = 30;

int visible_rows = 18;  // Default visible maze size
int visible_cols = 18;
//char **mymatrix;  // Pointer to dynamically allocated maze  ++

// Maze representation and iteration counter
char mymatrix[C_NUM_ROWS][C_NUM_COLUMNS];

void DisplayMazeSize(int rows, int cols) {
    uint16_t text_x = 5;  
    uint16_t text_y = C_NUM_ROWS * TILE_HEIGHT + 5;  // Fix position below the maze
    uint16_t text_width = SCREEN_WIDTH - 10;  
    uint16_t text_height = 16;  
    uint16_t border_thickness = 2;  

//    if (text_y + text_height + (2 * border_thickness) > SCREEN_HEIGHT) {
        text_y = SCREEN_HEIGHT - text_height - (2 * border_thickness);
//    }

    // Draw text background and border
    LCD_FillRect(text_x - border_thickness, text_y - border_thickness, 
                 text_width + (2 * border_thickness), text_height + (2 * border_thickness), White, White);
    LCD_FillRect(text_x, text_y, text_width, text_height, Black, Black);

    // Display the maze size
    char sizeMessage[50];  
    sprintf(sizeMessage, "Current Maze Size: %dx%d", rows, cols);
    GUI_Text(text_x + 5, text_y + (text_height / 2) - 8, (uint8_t*)sizeMessage, White, Black);
}

void DisplaySizeChangeMessage(char *change) {
    uint16_t text_x = 5;  
    uint16_t text_y = C_NUM_COLUMNS * TILE_HEIGHT + 5;  // Fixed below the maze
    uint16_t text_width = SCREEN_WIDTH - 10;  
    uint16_t text_height = 16;  
    uint16_t border_thickness = 2;  

    // Ensure text remains within screen bounds
    if (text_y + text_height + (2 * border_thickness) > SCREEN_HEIGHT) {
        text_y = SCREEN_HEIGHT - text_height - (2 * border_thickness);
    }

    // Draw text background and border
    LCD_FillRect(text_x - border_thickness, text_y - border_thickness, 
                 text_width + (2 * border_thickness), text_height + (2 * border_thickness), White, White);
    LCD_FillRect(text_x, text_y, text_width, text_height, Black, Black);  

    // Display updated maze size and index change
    char sizeMessage[50];  
    sprintf(sizeMessage, "New size: %dx%d (%s)", visible_rows, visible_cols, change);
    GUI_Text(text_x + 5, text_y + (text_height / 2) - 8, (uint8_t*)sizeMessage, White, Black);
}



/* 
 * Function to render the maze on the LCD.
 * Uses different colors or characters to represent walls, paths, and exits.
 */
void DrawMaze(char mymatrix[C_NUM_ROWS][C_NUM_COLUMNS]) {
    for (int i = 0; i < visible_rows; i++) {  // Use `visible_rows`
        for (int j = 0; j < visible_cols; j++) {  // Use `visible_cols`
            uint16_t x = j * TILE_WIDTH;
            uint16_t y = i * TILE_HEIGHT;

            switch (mymatrix[i][j]) {
                case '*':   LCD_FillRect(x, y, TILE_WIDTH, TILE_HEIGHT, Blue, White); break;
                case 'n':   PutChar2(x, y, 'n', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'N':   PutChar2(x, y, 'N', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'W':   PutChar2(x, y, 'W', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'w':   PutChar2(x, y, 'w', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 's':   PutChar2(x, y, 's', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'S':   PutChar2(x, y, 'S', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'e':   PutChar2(x, y, 'e', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case 'E':   PutChar2(x, y, 'E', White, Black, FONT_WIDTH, FONT_HEIGHT); break;
                case ' ':   LCD_FillRect(x, y, TILE_WIDTH, TILE_HEIGHT, Black, Black); break;
                default:    LCD_FillRect(x, y, TILE_WIDTH, TILE_HEIGHT, Red, Yellow); break;
            }
        }
    }
}


// Interrupt flags and timing variable
volatile int INT0 = 0;
volatile int KEY1 = 0; 
volatile int KEY2 = 0;
volatile uint32_t value;

/* 
 * RIT (Repetitive Interrupt Timer) Handler
 * - Manages button inputs (INT0, KEY1, KEY2)
 * - Generates the maze and solves it upon button press
 */
void RIT_IRQHandler(void) {

    if (INT0 >= 1) { 
        if ((LPC_GPIO2->FIOPIN & (1 << 10)) == 0) {    
            switch (INT0) {                
                case 2: 
                    Change_case(C_NUM_ROWS, C_NUM_COLUMNS, mymatrix, &number_of_clicks);
                    DrawMaze(mymatrix);

                    // Place the case change message exactly in the same space as DisplaySizeChangeMessage
                uint16_t text_x = 5;  
                uint16_t text_y = C_NUM_COLUMNS * TILE_HEIGHT + 5;  // Fixed below the maze
                uint16_t text_width = SCREEN_WIDTH - 10;  
                uint16_t text_height = 16;  
                uint16_t border_thickness = 2;  

                // Ensure text remains within screen bounds
//                if (text_y + text_height + (2 * border_thickness) > SCREEN_HEIGHT) {
                    text_y = SCREEN_HEIGHT - text_height - (2 * border_thickness);
//                }

                // Draw text background and border
                LCD_FillRect(text_x - border_thickness, text_y - border_thickness, 
                             text_width + (2 * border_thickness), text_height + (2 * border_thickness), White, White);
                LCD_FillRect(text_x, text_y, text_width, text_height, Black, Black);  

                // Display the case change message
                char Message[50];
                sprintf(Message, "Changed to %sCase", (number_of_clicks % 2 == 0) ? "Lower" : "Upper");
                GUI_Text(text_x + 5, text_y + (text_height / 2) - 8, (uint8_t*)Message, White, Black);
                break;
                default:
                    break;
            }
            INT0++;
        } else { 
            INT0 = 0;
            NVIC_EnableIRQ(EINT0_IRQn);
            LPC_PINCON->PINSEL4 |= (1 << 20); 
        }
    }

    // **Key 1: Generates a new random maze**
    if (KEY1 >= 1) {  
        if ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0) {    
            if (KEY1 == 2) { // Execute only once per press
                LCD_Clear(Black);
                value = LPC_TIM0->TC;  // Read Timer 0 for randomness

                // Initialize maze borders
                for (int i = 0; i < visible_cols; i++) {
                    mymatrix[0][i] = '*';
                    mymatrix[visible_rows - 1][i] = '*';
                }
                for (int i = 0; i < visible_rows; i++) {
                    mymatrix[i][0] = '*';
                    mymatrix[i][visible_cols - 1] = '*';
                }

                // Generate walls and exits randomly
                for (int i = 1; i < visible_cols - 1; i++) {
                    value = (value * 18) % 101;  
                    mymatrix[0][i] = (value < 90) ? '*' : 'n';
                }
                for (int i = 1; i < visible_rows - 1; i++) {
                    value = (value * 18) % 101;  
                    mymatrix[i][0] = (value < 90) ? '*' : 'w';
                }
                for (int i = 1; i < visible_cols - 1; i++) {
                    value = (value * 18) % 101;  
                    mymatrix[visible_rows - 1][i] = (value < 90) ? '*' : 's';
                }
                for (int i = 1; i < visible_rows - 1; i++) {
                    value = (value * 18) % 101;  
                    mymatrix[i][visible_cols - 1] = (value < 90) ? '*' : 'e';
                }
                for (int i = 1; i < visible_rows - 1; i++) {  
                    for (int j = 1; j < visible_cols - 1; j++) {
                        value = (value * 18) % 101;  
                        mymatrix[i][j] = (value <= 60) ? ' ' : '*';  
                    }
                }

                // Draw the generated maze
                DrawMaze(mymatrix);
								DisplayMazeSize(visible_rows, visible_cols);

            }
            KEY1++;
        } else {  
            KEY1 = 0;            
            NVIC_EnableIRQ(EINT1_IRQn);         
            LPC_PINCON->PINSEL4 |= (1 << 22);  
        }
    }

    // **Key 2: Solve the maze and display iteration count**
    if (KEY2 >= 1) {
				number_of_clicks = 0;
        if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0) {     
            if (KEY2 == 2) { 
                mazeSolver(C_NUM_ROWS, C_NUM_COLUMNS, mymatrix, &iteration);
                DrawMaze(mymatrix);

                // Display iteration count
                uint16_t text_x = 5;  
                uint16_t text_y = C_NUM_ROWS * TILE_HEIGHT + 5;  
                uint16_t text_width = SCREEN_WIDTH - 10;  
                uint16_t text_height = 16;  
                uint16_t border_thickness = 2;  

//                if (text_y + text_height + (2 * border_thickness) > SCREEN_HEIGHT) {
                    text_y = SCREEN_HEIGHT - text_height - (2 * border_thickness);
//                }

                LCD_FillRect(text_x - border_thickness, text_y - border_thickness, 
                             text_width + (2 * border_thickness), text_height + (2 * border_thickness), White, White);
                LCD_FillRect(text_x, text_y, text_width, text_height, Black, Black);  

                char iterationText[50];  
                sprintf(iterationText, "Algorithm executed %d times", iteration);
                GUI_Text(text_x + 5, text_y + (text_height / 2) - 8, (uint8_t*)iterationText, White, Black);
            }
            KEY2++;
        } else { 
            KEY2 = 0;            
            NVIC_EnableIRQ(EINT2_IRQn);         
            LPC_PINCON->PINSEL4 |= (1 << 24); 
        }
    }

    // **Handle Joystick Inputs for Resizing**
    static int up = 0, down = 0 , right=0 , left= 0;    

    if ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0 && up == 0) {  
        if (visible_rows < C_NUM_ROWS) {  
            visible_rows++;
					DisplaySizeChangeMessage("Row+1");  // Show which index changed
        }
        up = 1;
    } else if ((LPC_GPIO1->FIOPIN & (1 << 29)) != 0) {
        up = 0;
    }
		
		    if ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0 && right == 0) {  
        if (visible_cols < C_NUM_COLUMNS) {  
            visible_cols++;
					DisplaySizeChangeMessage("Column+1");  // Show which index changed
        }
        right = 1;
    } else if ((LPC_GPIO1->FIOPIN & (1 << 28)) != 0) {
        right = 0;
    }
		
		 if ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0 && left == 0) {  
        if (visible_cols > 0) {  
            visible_cols--;
					DisplaySizeChangeMessage("Column-1");  // Show which index changed
        }
        left = 1;
    } else if ((LPC_GPIO1->FIOPIN & (1 << 27)) != 0) {
        left = 0;
    }

    if ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0 && down == 0) {  
        if (visible_rows > 0) {  
            visible_rows--;
					DisplaySizeChangeMessage("Row-1");  // Show which index changed
        }
        down = 1;
    } else if ((LPC_GPIO1->FIOPIN & (1 << 26)) != 0) {
        down = 0;
    }

    reset_RIT();
}
