#include "Switch.h"
#include "Speaker.h"
#include "Timer.h"
#include "Face.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"

#define PF2   (*((volatile uint32_t *)0x40025010))

int main(){
	PLL_Init(Bus80MHz); 
	Switch_PortFInit();
	Speaker_Init();
	Timer_Init();
	//LCD_Init(); //Init clock stuff here
	while(1){
		//if(Clock Mode)

		
		//if(Stopwatch Mode)		
		
		
		//if(Timer Mode)
		
		
	}
}
