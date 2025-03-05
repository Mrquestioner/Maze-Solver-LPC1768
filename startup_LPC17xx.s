;/*****************************************************************************
; * @file:    startup_LPC17xx.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File 
; *           for the NXP LPC17xx Device Series 
; * @version: V1.01
; * @date:    21. December 2009
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2009 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
				DCD		USBActivity_IRQHandler    ; USB Activity interrupt to wakeup
				DCD		CANActivity_IRQHandler    ; CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


				
;NUM_ROW EQU 9          ; Number of rows in the maze
;NUM_COL EQU 9          ; Number of columns in the maze

; Define the initial maze
		AREA initialMap, DATA, READONLY
maze            DCB "*", "n", "*", "*", "*", "*", "*", "*", "*"
                DCB "*", " ", " ", " ", "*", " ", "*", " ", "*"
                DCB "*", " ", "*", "*", "*", "*", "*", " ", "*"
                DCB "*", " ", "*", " ", "*", " ", " ", " ", "*"
                DCB "*", " ", "*", " ", "*", "*", "*", " ", "*"
                DCB "*", " ", " ", " ", "*", " ", " ", " ", "*"
                DCB "*", "*", "*", "*", "*", " ", "*", " ", "*"
                DCB "*", " ", " ", " ", " ", " ", "*", " ", "*"
                DCB "*", "*", "*", "*", "*", "*", "*", "s", "*"

; Define writable area for maze directions
;		AREA currentMap, DATA, READWRITE
;maze_directions SPACE NUM_ROW * NUM_COL  ; Space for the output maze

		AREA |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
				IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
				
;; Copy the initial maze into the maze_directions
;                LDR R0, =maze                   ; Source address (initial maze)
;                LDR R1, =maze_directions        ; Destination address (maze directions)
;                MOV R2, #NUM_ROW * NUM_COL      ; Number of bytes to copy
;loopCopyData    LDRB R3, [R0], #1               ; Load byte from source and increment
;                STRB R3, [R1], #1               ; Store byte to destination and increment
;                SUBS R2, R2, #1                 ; Decrement counter
;                BNE loopCopyData                ; Repeat until all bytes are copied

;                ; Call mazeSolver
;                MOV R0, #NUM_ROW                ; Number of rows
;                MOV R1, #NUM_COL                ; Number of columns
;                LDR R2, =maze_directions        ; Address of the maze
;                BL mazeSolver                   ; Call mazeSolver

stop            B stop                          ; Infinite loop after execution
                ENDP
					
Change_case PROC
                EXPORT Change_case               ; Make the subroutine callable from C

                ; Save callee-saved registers and link register
                PUSH {R4-R12, LR}

                ; Parameters:
                ; R0 = C_NUM_ROWS (number of rows)
                ; R1 = C_NUM_COLUMNS (number of columns)
                ; R2 = Address of the maze matrix (&mymatrix)
                ; R3 = Address of iteration (pointer to store iteration count)

                MOV R12, #0                      ; Initialize index counter to 0
                MUL R11 , R1, R0                 ; Calculate total number of cells in the maze (rows * columns)
                LDR R9, [R3]                     ; Load current iteration count
                MOV R7, #2                       ; Load value 2 for division
                UDIV R8, R9, R7                  ; Divide iteration count by 2 (check if even or odd)
                MUL R8, R7                       ; Multiply back to check divisibility
                SUB R8, R9, R8                   ; R8 = R9 % 2 (remainder)
                CMP R8, #0                       ; Check if remainder is 0 (even number)
                BEQ EVEN                         ; If even, convert lowercase to uppercase
                BNE ODD                          ; If odd, convert uppercase to lowercase

;------------------------------------------------------------------------------
; Convert lowercase exits (n, e, s, w) to uppercase (N, E, S, W)
;------------------------------------------------------------------------------
EVEN                
E_Next_index      
                LDRB R4, [R2 , R12]              ; Load the character at index R12

                CMP R4 , #' '                    ; If empty space, skip
                BEQ E_SKIP
                CMP R4 , #'*'                    ; If wall, skip
                BEQ E_SKIP

Check_n         
                MOV R5, #'n'                     ; Check for 'n'
                CMP R4, R5
                BNE Check_e
                BL Uppercase                     ; Convert to uppercase and return

Check_e         
                MOV R5, #'e'                     ; Check for 'e'
                CMP R4, R5
                BNE Check_s
                BL Uppercase

Check_s
                MOV R5, #'s'                     ; Check for 's'
                CMP R4, R5
                BNE Check_w
                BL Uppercase

Check_w    
                MOV R5, #'w'                     ; Check for 'w'
                CMP R4, R5
                BNE E_SKIP
                BL Uppercase

E_SKIP
                ADD R12, #1                      ; Move to the next cell
                CMP R12, R11                     ; Check if all cells have been processed
                BNE E_Next_index                 ; Continue the loop if cells remain
                ADD R9, #1                       ; Increment iteration count
                STR R9, [R3]                     ; Store updated iteration count
                POP {R4-R12, PC}                 ; Restore registers and return
                ENDP

;------------------------------------------------------------------------------
; Convert uppercase exits (N, E, S, W) to lowercase (n, e, s, w)
;------------------------------------------------------------------------------
ODD PROC
O_Next_index          
                LDRB R4, [R2 , R12]              ; Load the character at index R12

                CMP R4 , #' '                    ; If empty space, skip
                BEQ O_SKIP
                CMP R4 , #'*'                    ; If wall, skip
                BEQ O_SKIP

Check_N         
                MOV R5, #'N'                     ; Check for 'N'
                CMP R4, R5
                BNE Check_E
                BL Lowercase                     ; Convert to lowercase and return

Check_E         
                MOV R5, #'E'                     ; Check for 'E'
                CMP R4, R5
                BNE Check_S
                BL Lowercase

Check_S
                MOV R5, #'S'                     ; Check for 'S'
                CMP R4, R5
                BNE Check_W
                BL Lowercase

Check_W    
                MOV R5, #'W'                     ; Check for 'W'
                CMP R4, R5
                BNE O_SKIP
                BL Lowercase

O_SKIP
                ADD R12, #1                      ; Move to the next cell
                CMP R12, R11                     ; Check if all cells have been processed
                BNE O_Next_index                 ; Continue the loop if cells remain
                ADD R9, #1                       ; Increment iteration count
                STR R9, [R3]                     ; Store updated iteration count
                POP {R4-R12, PC}                 ; Restore registers and return
                ENDP

;------------------------------------------------------------------------------
; Subroutine to convert lowercase character to uppercase
;------------------------------------------------------------------------------
Uppercase PROC
                SUB R5, #32                      ; Convert lowercase to uppercase (ASCII offset)
                STRB R5, [R2, R12]               ; Store updated value in maze matrix
                BX LR                            ; Return from function
                ENDP

;------------------------------------------------------------------------------
; Subroutine to convert uppercase character to lowercase
;------------------------------------------------------------------------------
Lowercase PROC
                ADD R5, #32                      ; Convert uppercase to lowercase (ASCII offset)
                STRB R5, [R2, R12]               ; Store updated value in maze matrix
                BX LR                            ; Return from function
                ENDP


				
            



mazeSolver PROC
                EXPORT mazeSolver               ; Make the subroutine callable from C

                ; Save callee-saved registers and link register
                PUSH {R4-R11, LR}

                ; Parameters:
                ; R0 = C_NUM_ROWS (number of rows)
                ; R1 = C_NUM_COLUMNS (number of columns)
                ; R2 = Address of the maze matrix (&mymatrix)
                ; R3 = Address of iteration (pointer to store iteration count)

                ; Initialize iteration counter and update flag
                MOV R9, #0                      ; Iteration counter (R9), starts at 0
                MOV R12, #1                     ; Update flag (1 = changes made, 0 = no changes)
				MUL R11 , R1, R0                 ; Calculate total number of cells in the maze (rows * columns)


main_loop       
                CMP R12, #0                     ; Check if any updates were made in the last pass
                BEQ exit_solver                 ; Exit the solver if no updates

                MOV R12, #0                     ; Reset update flag
                MOV R10, #0                     ; Start processing from the first cell (index 0)

phase_1_loop    
                ; Check if the current cell is a space (' ')
                LDRB R4, [R2, R10]               ; Load the current cell from the maze
                CMP R4, #' '                    ; Compare with ASCII space (' ')
                BNE phase_1_next_cell           ; Skip if the cell is not a space

                ; Check and update neighbors in priority order
                BL TopNeighbourCheck            ; Check the top neighbor
                BL RightNeighbourCheck          ; Check the right neighbor
                BL BotNeighbourCheck            ; Check the bottom neighbor
                BL LeftNeighbourCheck           ; Check the left neighbor

phase_1_next_cell
                ADD R10, #1                  ; Move to the next cell
                CMP R10, R11      			 ; Check if all cells have been processed
                BNE phase_1_loop             ; Continue the loop if cells remain

increment_counter
                ADD R9, R9, #1                  ; Increment the iteration counter
                B main_loop                     ; Continue the main loop

exit_solver
                ; Store the iteration counter at the address pointed to by R3
                STRB R9, [R3]
                ; Restore saved registers and return
                POP {R4-R11, PC}
                ENDP

; Top neighbor checking subroutine
TopNeighbourCheck PROC  
                SUB R6, R10, R1           		; Calculate the index of the top neighbor
                CMP R6, #0                      ; Check if the index is out of bounds
                BLT top_end                     ; Skip if out of bounds
                LDRB R4, [R2, R6]               ; Load the value of the top neighbor
                CMP R4, #'a'                    ; Check if the neighbor is a valid direction
                BLT top_end                     ; Skip if the neighbor is not valid
                MOV R5, #'n'                    ; Update the current cell to 'N' (North)
                STRB R5, [R2, R10]               ; Store the updated value in the maze
                MOV R12, #1                     ; Mark as updated
top_end
                BX LR                           ; Return from the subroutine
                ENDP

; Right neighbor checking subroutine
RightNeighbourCheck PROC  
                ADD R6, R10, #1                  ; Calculate the index of the right neighbor
                CMP R6, R11    ; Check if the index is out of bounds
                BHS right_end                   ; Skip if out of bounds
                LDRB R4, [R2, R6]               ; Load the value of the right neighbor
                CMP R4, #'a'                    ; Check if the neighbor is a valid direction
                BLT right_end                   ; Skip if the neighbor is not valid
                MOV R5, #'e'                    ; Update the current cell to 'E' (East)
                STRB R5, [R2, R10]               ; Store the updated value in the maze
                MOV R12, #1                     ; Mark as updated
right_end
                BX LR                           ; Return from the subroutine
                ENDP

; Bottom neighbor checking subroutine
BotNeighbourCheck PROC  
                ADD R6, R10, R1          ; Calculate the index of the bottom neighbor
                CMP R6, R11    ; Check if the index is out of bounds
                BHS bot_end                     ; Skip if out of bounds
                LDRB R4, [R2, R6]               ; Load the value of the bottom neighbor
                CMP R4, #'a'                    ; Check if the neighbor is a valid direction
                BLT bot_end                     ; Skip if the neighbor is not valid
                MOV R5, #'s'                    ; Update the current cell to 'S' (South)
                STRB R5, [R2, R10]               ; Store the updated value in the maze
                MOV R12, #1                     ; Mark as updated
bot_end
                BX LR                           ; Return from the subroutine
                ENDP

; Left neighbor checking subroutine
LeftNeighbourCheck PROC  
                SUB R6, R10, #1                  ; Calculate the index of the left neighbor
                CMP R6, #0                      ; Check if the index is out of bounds
                BLT left_end                    ; Skip if out of bounds
                LDRB R4, [R2, R6]               ; Load the value of the left neighbor
                CMP R4, #'a'                    ; Check if the neighbor is a valid direction
                BLT left_end                    ; Skip if the neighbor is not valid
                MOV R5, #'w'                    ; Update the current cell to 'W' (West)
                STRB R5, [R2, R10]               ; Store the updated value in the maze
                MOV R12, #1                     ; Mark as updated
left_end
                BX LR                           ; Return from the subroutine
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
				EXPORT  USBActivity_IRQHandler    [WEAK]
				EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler           
TIMER0_IRQHandler         
TIMER1_IRQHandler         
TIMER2_IRQHandler         
TIMER3_IRQHandler         
UART0_IRQHandler          
UART1_IRQHandler          
UART2_IRQHandler          
UART3_IRQHandler          
PWM1_IRQHandler           
I2C0_IRQHandler           
I2C1_IRQHandler           
I2C2_IRQHandler           
SPI_IRQHandler            
SSP0_IRQHandler           
SSP1_IRQHandler           
PLL0_IRQHandler           
RTC_IRQHandler            
EINT0_IRQHandler          
EINT1_IRQHandler          
EINT2_IRQHandler          
EINT3_IRQHandler          
ADC_IRQHandler            
BOD_IRQHandler            
USB_IRQHandler            
CAN_IRQHandler            
DMA_IRQHandler          
I2S_IRQHandler            
ENET_IRQHandler       
RIT_IRQHandler          
MCPWM_IRQHandler             
QEI_IRQHandler            
PLL1_IRQHandler           
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
