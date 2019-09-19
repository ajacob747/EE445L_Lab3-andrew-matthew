#include "Switch.h"
#include "Speaker.h"
#include "Timer.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"

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
