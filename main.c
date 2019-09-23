#include "Switch.h"
#include "Speaker.h"
#include "Timer.h"
#include "Face.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/st7735.h"


int time_ofst = 0;
int showAlarm;
int is24Hr;

int mode;
int refresh;
int delay;

int setPhase;     //phase of time adjustment

int alarmH;       //alarm time
int alarmM;
int alarmPhase;   //phase of alarm adjustment

int sw_start;     //stopwatch start time
int sw_show;      //stopwatch show time
int sw_on;

int tm_start;     //timer start time
int tm_end;  //timer duration
int tm_set;       //is currently setting timer
int tm_h;         //variables used in setting the timer
int tm_m;
int tm_on;

int ring;


int button1;
int button2;
int button3;

extern uint32_t time;

#define PF2   (*((volatile uint32_t *)0x40025010))

int main(){
	PLL_Init(Bus80MHz); 
	Switch_PortInits();
<<<<<<< HEAD
	Switch_TimerInit();
=======
>>>>>>> c1fe5720445802a964127ee935359a94169d03c2
	Speaker_Init();
	Timer_Init();
  Face_Init();
  mode = 0;
  delay = -1;
  refresh = 1;
  showAlarm = 0;
  is24Hr = 0;
  ring = 0;
	while(1){
<<<<<<< HEAD
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
=======
    PF2 ^= PF2;
    if (showAlarm){
      if (alarmH == (time+time_ofst)%3600000 && alarmM == (time+time_ofst)%60000 && (time+time_ofst)%1000 < 500)
        ring = 1;
    }
    if (tm_on){
      if ((tm_start + tm_end)/10 == time)
        ring = 1;
    }
    if (ring && (button1 || button2 || button3)){
      ring = 0;
      Face_Ring(0);
    }
    if (ring){
      Face_Ring(time%1000 < 500);
    }
    if (button3){
      mode = (mode + 1)%5;
      delay = 100000;
      refresh = 1;
    }
    if (delay == 0){
      mode = 0;
      refresh = 1;
    } else delay--;
    //return to main clock if uninteractive
    int displayTime;
    switch(mode){
      case 0: // main clock
        if (refresh){
          Face_Set24(is24Hr);
          Face_ShowAlarm(showAlarm);
          Face_SetLabel("Clock");
          refresh = 0;
        }
        displayTime = time_ofst + time;
        Face_SetTimeMS(displayTime);
        Face_Out(0);
        break;
      case 1: // set time
        if (refresh){
          setPhase = 0;
          refresh = 0;
          Face_SetLabel("Set Hour");
        }
        switch(setPhase){
          case 0: //set hour
            if (button1) time_ofst += 3600000;
            if (button2){
              setPhase++;
              Face_SetLabel("Set Minute");
            }
            break;
          case 1: //set min
            if (button1) time_ofst += 60000;
            if (button2){
              setPhase++;
              Face_SetLabel("Set Second to 0");
            }
            break;
          case 2: //reset sec to 0
            if (button1) time_ofst %= 60000;
            if (button2){
              setPhase++;
            }
            break;
          case 3: //24 hr time or ampm
            if (is24Hr){
              Face_SetLabel("Show 24h time? (Y)");
            } else Face_SetLabel("Show 24h time? (N)");
            if (button1){
              is24Hr = !is24Hr;
              Face_Set24(is24Hr);
            }
            if (button2){
              setPhase = 0;
              Face_SetLabel("Set Hour");
            }
            break;
        }
        Face_SetTimeMS(time_ofst + time);
        Face_Out(0);
        break;
      case 2: // alarm 
        if(refresh){
          if (showAlarm) Face_SetLabel("Alarm on");
          else Face_SetLabel("Alarm off");
          alarmPhase = 0;
        }
        switch(alarmPhase){
          case 0:
            if (button1){
              showAlarm = !showAlarm;
              if (showAlarm) Face_SetLabel("Alarm on");
              else Face_SetLabel("Alarm off");
            }
            if (button2){
              alarmPhase++;
              Face_SetLabel("Set Alarm Hour");
            }
            break;
          case 1:
            if (button1){
              alarmH = alarmH % 24;
            }
            if (button2){
              alarmPhase++;
              Face_SetLabel("Set Alarm Min");
            }
            break;
          case 2:
            if (button1){
              alarmM = alarmM % 60;
            }
            break;
        }
        Face_SetTime(alarmH,alarmM,0,0);
        Face_Out(0);
        break;
      case 3:
        if (refresh){
          if (tm_on){
            Face_SetLabel("Timer On");
            tm_start = time;
          }
          else Face_SetLabel("Timer Off");
          Face_ShowAlarm(0);
          setPhase = 0;
        }
        switch(setPhase){
          case 0: //toggle timer
            if (button1){
              tm_on = !tm_on;
              if (tm_on)
                Face_SetLabel("Timer On");
              else{
                Face_SetLabel("Timer Off");
              }
              tm_end = tm_h * 3600000 + tm_m * 60000;
            }
            if (button2){
              setPhase++;
              Face_SetLabel("Set Timer H");
            }
            break;
          case 1:
            if (button1){
              tm_h = tm_h%24;
            }
            if (button2){
              setPhase++;
              Face_SetLabel("Set Timer Hour");
            }
            tm_end = tm_h * 3600000 + tm_m * 60000;
            break;
          case 2:
            if (button1){
              tm_m = tm_m%60;
            }
            if (button2) {
              setPhase++;
              Face_SetLabel("Set Timer Minute");
            }
            tm_end = tm_h * 3600000 + tm_m * 60000;
            break;
        }
        Face_SetTimeMS(time - (tm_start + tm_end));
        break;
      case 4: 
        if (refresh){
          Face_SetLabel("Stopwatch");
          Face_ShowAlarm(0);
        }
        if (button1){
          if (sw_on){
            sw_on = 0;
            sw_show = time - sw_start;
            Face_SetTimeMS(sw_show);
          } else {
            sw_start = time;
            
          }
        }
        if (sw_on){
          Face_SetTimeMS(time - sw_start);
        } else {
          Face_SetTimeMS(sw_show);
        }
        
        break;
    }
    
		//if(Stopwatch Mode)
>>>>>>> c1fe5720445802a964127ee935359a94169d03c2
		
		//if(Timer Mode)
    
    
    
		
		
	}
}
