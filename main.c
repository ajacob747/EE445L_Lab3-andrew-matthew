#include "Switch.h"
#include "Speaker.h"
#include "Timer.h"
#include "Face.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/st7735.h"

int time_ofst = 0;
int hour;
int minute;
int second;
int ms;

extern uint32_t time;

int main(){
	PLL_Init(Bus80MHz); 
	Switch_PortFInit();
	Speaker_Init();
	Timer_Init();
  Face_Init();
  int flip = 1;
	while(1){
		//if(Clock Mode)
    int ttime = time_ofst + time;
    ms = ttime%1000;
    second = (ttime/1000)%60;
    minute = (ttime/60000)%60;
    hour = (ttime/3600000)%24;
    
    Face_SetTime(hour,minute,second,ms);
    Face_Out();
		//if(Stopwatch Mode)		
		flip = 1 - flip;
    if (flip) ST7735_DrawPixel(1,1,ST7735_BLACK);
    else ST7735_DrawPixel(1,1,ST7735_BLUE);
		
		//if(Timer Mode)
		
		
	}
}
