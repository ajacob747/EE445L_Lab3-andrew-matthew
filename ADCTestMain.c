
// ADCTestMain.c
// Runs on TM4C123
// This program periodically samples ADC channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.
// Daniel Valvano
// September 5, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// center of X-ohm potentiometer connected to PE3/AIN0
// bottom of X-ohm potentiometer connected to ground
// top of X-ohm potentiometer connected to +3.3V 
/*
#include <stdint.h>
#include "../inc/ADCSWTrigger.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/ST7735.h"
#include "face.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
int32_t PMF[4096];
int32_t time_difference[999];
volatile uint32_t ADCvalue[1000];
volatile uint32_t time[1000];
volatile uint32_t used = 0;
// This debug function initializes Timer0A to request interrupts
// at a 100 Hz frequency.  It is similar to FreqMeasure.c.


void Timer0A_Init100HzInt(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = 799999;         // start value for 100 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
}

void Timer2A_Init100HzInt(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x04;      // activate timer2
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER2_CTL_R &= ~TIMER_CTL_TAEN; // disable timer2A during setup
  TIMER2_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer2A initialization ****
                                   // configure for periodic mode
  TIMER2_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER2_TAILR_R = 793999;         // start value for 99 Hz interrupts
  TIMER2_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;// clear timer2A timeout flag
  TIMER2_CTL_R |= TIMER_CTL_TAEN;  // enable timer2A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer2A=priority 2
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x20000000; // top 3 bits
  NVIC_EN0_R = 1<<23;              // enable interrupt 23 in NVIC
}

void Timer1_Init(void){ volatile uint32_t delay;
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  delay = SYSCTL_RCGCTIMER_R;   // allow time to finish activating
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, down-count 
  TIMER1_TAILR_R = 0xFFFFFFFF;  // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
  PF2 ^= 0x04;                   // profile
  PF2 ^= 0x04;                   // profile
	if (used < 1000){
		ADCvalue[used] = ADC0_InSeq3();
		time[used] = TIMER1_TAR_R;
		used++;
	}
  PF2 ^= 0x04;                   // profile
}

void Timer2A_Handler(void){
	TIMER2_ICR_R = TIMER_ICR_TATOCINT;
	int i = 0;
	i = i * 5 + (i + 3) / 17;
	
}
*/
/*int uselessMethodCall(int x){
	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;
	int e = 4;
	for (int i = 0; i < 100; i++){
		x++;
		a++;
		b++;
		c++;
		d++;
		e++;
	}
	return x + a + b + c + d + e;
}
*/


/*
=======
void draw_face(void);
void draw_7seg(void);
>>>>>>> dca9375009caedd444cf12f8feec92f1262d6f82
int main(void){
//int test = uselessMethodCall(100);
	PLL_Init(Bus80MHz);                   // 80 MHz
  SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F
	
  ADC0_InitSWTriggerSeq3_Ch9();         // allow time to finish activating

	
  GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x06;          // disable alt funct on PF2, PF1
  GPIO_PORTF_DEN_R |= 0x06;             // enable digital I/O on PF2, PF1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
  PF2 = 0;                      // turn off LED

	Timer1_Init();
	Timer0A_Init100HzInt();               // set up Timer0A for 100 Hz interrupts
	//Timer2A_Init100HzInt();								// set up 2A for 99Hz interrupts
  EnableInterrupts();
	
  while(used < 1000){
    PF1 ^= 0x02;  // toggles when running in main
		//PF1 = (PF1*12345678)/1234567+0x02;  // this line causes jitter
		//GPIO_PORTF_DATA_R ^= 0x02;  // toggles when running in main
  }
	int32_t maxTD = -1;
	int32_t minTD = 999999;
	for (int i = 0; i < 999; i++){
		time_difference[i] = time[i] - time[i + 1];
		if (time_difference[i] > maxTD){
			maxTD = time_difference[i];
		}
		if (time_difference[i] < minTD){
			minTD = time_difference[i];
		}
	}
	
	
	for (int i = 0; i < 4096; i++){
		PMF[i] = 0;
	}
	for (int i = 0; i < 1000; i++){
		PMF[ADCvalue[i]]++;
	}
	
	int PMFPeak = 0;
	for (int i = 0; i < 4096; i++){
		if (PMF[i] > PMF[PMFPeak]) PMFPeak = i;
	}
	
	ST7735_InitR(INITR_REDTAB);
	ST7735_PlotClear(0, PMF[PMFPeak]);
	for (int i = PMFPeak - 64; i < PMFPeak + 64; i++){
		ST7735_PlotBar(PMF[i]);
		ST7735_PlotNext();
	}
	
	
}
*/

