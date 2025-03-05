

#ifndef BUTTON_H
#define BUTTON_H

#include "LPC17xx.h"


void BUTTON_init(void);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

extern volatile int INT0;  
extern volatile int KEY1;	  
extern volatile int KEY2;  






#endif  
