#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Switch.h"


int PF4Flag = 0;
int PF0Flag = 0;

void EnableInterrupts(void);

void Switch_PortFInit(void){ 
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
	GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4/F1 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4/F1 is not both edges
  GPIO_PORTF_IEV_R |= 0x11;    //     PF4/F1 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flag4/flag0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4/PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Enable global Interrupt flag (I)
}

void GPIOPortF_Handler(void){
	if((GPIO_PORTF_RIS_R & 0x10)){
			PF4Flag = 1;
			GPIO_PORTF_ICR_R |= 0x10;
	}
	if((GPIO_PORTF_RIS_R & 0x1)){
			PF0Flag = 1;
			GPIO_PORTF_ICR_R |= 0x1;
	}
}
