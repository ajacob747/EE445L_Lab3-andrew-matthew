#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Speaker.h"

void DisableInterrupts(void); 
void EnableInterrupts(void);

int onflag;

#define PE0   (*((volatile uint32_t *)0x40024000))

void Speaker_Init(void){
	SYSCTL_RCGC2_R |= 0x10;
	while((SYSCTL_PRGPIO_R&0x10)==0){}
	GPIO_PORTE_DIR_R |= 0x1;
	GPIO_PORTE_DEN_R |= 0x1;
}

void Speaker_TimerInit(void){
	volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer1
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER1_CTL_R &= ~TIMER_CTL_TAEN; // disable timer1A during setup
  TIMER1_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER1_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER1_TAILR_R = 181818;         // start value for 440 Hz interrupts
  TIMER1_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// clear timer1A timeout flag
  TIMER1_CTL_R |= TIMER_CTL_TAEN;  // enable timer1A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer1A=priority 2
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R |= 1<<21;              // enable interrupt 19 in NVIC
	onflag = 0;
	EnableInterrupts();
	
}

void Timer1A_Handler(void){
	if(onflag)
		PE0 ^= 0x02;
}

void Speaker_On(void){
		onflag = 1;
}

void Speaker_Off(void){
		onflag = 0;
		PE0 = 0;
}