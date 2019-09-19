// Face.c
// This progam manages the clock face display output to the ST7735 screen.
// Matthew Jiang
// Septermber 18th, 2019
#include "../inc/ST7735.h"
#include "Face.h"
#include "string.h"

// redraw item flags
static short refreshLabel;
static short refreshHour;
static short refreshMin;
static short refreshSec;
static short refreshAlarm;
static short refreshAMPM;
static short refreshFace;

// current clock data
static char label[19];
static int hour;
static int min;
static int sec;
static int ms;
static short alarm;
static short twentyFourHour;

// current clock colors
static int clock_bg = ST7735_BLUE;
static int clock_outline = ST7735_RED;
static int clock_hand = ST7735_BLACK;
static int clock_alarm = ST7735_RED;



// --------Face_Init--------
// Initializes clock face, clears screen, draws clock
// Input:   none
// Output:  none
void Face_Init(void){
  refreshLabel = 1;
  refreshHour = 1;
  refreshMin = 1;
  refreshSec = 1;
  refreshAlarm = 1;
  refreshAMPM = 1;
  refreshFace = 1;
  label[18] = '\0';
  ST7735_InitR(INITR_REDTAB);
  Output_Clear();
}

// --------Face_SetLabel--------
// Sets label at top of screen
// Input:   n   String that will be displayed at top of screen
// Output:  none
void Face_SetLabel(char* n){
  int i = 0;
  while (i < 18 && n[i] != '\0'){
    label[i] = n[i];
    i++;
  }
  while (i < 18){
    label[i] = ' ';
  }
}

// --------Face_ShowAlarm--------
// Sets whether alarm hand is shown on clock or not
// Input:   on  Boolean (true to show)
// Output:  none
void Face_ShowAlarm(int on){
}

// --------Face_SetTime--------
// Sets current time for face to display
// Input:   h     hour
//          m     minute
//          s     second
//          ms    milisecond
// Output: none       

void Face_SetTime(int h, int m, int s, int millis){
  hour = h * 6 + m / 10;
  min = m * 6 + s / 10;
  sec = s * 6;
  ms = millis;
}

// --------Face_Set24--------
// Sets face to 24 hr mode (uses 00-23 hour display instead of 12-11 with AM/PM dot)
// Input:   on true to turn on 24 hr mode, false to use 12 hr
// Output:  none

void Face_Set24(int on){
}


// --------Face_ShowDet--------
// Shows detailed second/millisecond view
// Input:   on true to turn on detailed view
// Output:  none

void Face_ShowDet(int on){
}

// Draws label
static void draw_label(void){
  if(refreshLabel){
    ST7735_SetCursor(1, 1);
    ST7735_OutString(label);
    refreshLabel = 0;
  }
}


#define c_x 64
#define c_y 72
// below was calculated using matlab and bresenham's circle algorithm
// It is an array of x (and y) coordinates on the perimeter
// (left to right is x, right to left is y)

//radius 60
// const int bc[] = {60 ,60 ,60 ,60 ,60 ,60 ,59 ,59 ,59 ,59 ,59 ,59 ,58 ,58 ,58 ,58 ,57 ,57 ,57 ,56 ,56 ,55 ,55 ,54 ,54 ,53 ,53 ,52 ,52 ,51 ,51 ,50 ,49 ,49 ,48 ,47 ,46 ,45 ,44 ,43 ,42 ,41 ,40 ,39 ,38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,29 ,28 ,27 ,26 ,25 ,24 ,23 ,22 ,21 ,20 ,19 ,18 ,17 ,16 ,15 ,14 ,13 ,12 ,11 ,10 ,9 ,8 ,7 ,6 ,5 ,4 ,3 ,2 ,1 ,0, -1};

// radius 55
const char bc[] = {55 ,55 ,55 ,55 ,55 ,55 ,54 ,54 ,54 ,54 ,54 ,53 ,53 ,53 ,53 ,52 ,52 ,52 ,51 ,51 ,50 ,50 ,49 ,49 ,48 ,48 ,47 ,47 ,46 ,45 ,45 ,44 ,43 ,42 ,41 ,40 ,39 ,38 ,37 ,36 ,35 ,34 ,33 ,32 ,31 ,30 ,29 ,28 ,27 ,26 ,25 ,24 ,23 ,22 ,21 ,20 ,19 ,18 ,17 ,16 ,15 ,14 ,13 ,12 ,11 ,10 ,9 ,8 ,7 ,6 ,5 ,4 ,3 ,2 ,1 ,0, -1};
void draw_face(void){
  if (refreshFace || 1){
    int x = 0;
    int y = strlen(bc);
    int limit = y;
    while(x <= limit){
      // fill w/ horizontal line (unless on same horizontal line as before
      if (bc[y] != bc[y+1]){
        ST7735_DrawFastHLine(c_x - bc[x], c_y - bc[y], bc[x] * 2 + 1, clock_bg);
        ST7735_DrawFastHLine(c_x - bc[x], c_y + bc[y], bc[x] * 2 + 1, clock_bg);
      }
      // outline
      ST7735_DrawPixel(c_x - bc[x], c_y - bc[y], clock_outline);
      ST7735_DrawPixel(c_x + bc[x], c_y - bc[y], clock_outline);
      ST7735_DrawPixel(c_x - bc[x], c_y + bc[y], clock_outline);
      ST7735_DrawPixel(c_x + bc[x], c_y + bc[y], clock_outline);
      x++;
      y--;
    }
  }
}

// Precalculated hand positions - done via trigonometry. There are 91 entries in the array, for 0 - 90 degrees.
// To calculate a hand position: given a degree between 0 and 90, 
// the y position is arr[deg]
// the x position is arr[90 - deg]

// If degree is between 90 and 180, use 180 - deg for x and y
// If degree is between 180 and 270, use deg - 180
// If degree is between 270 and 360, use 360 - deg

// If degree is between 90 and 270, flip the x coord
// If degree is between 180 and 360, (un)flip the y coord
static const char h_arr[] = {0 ,0 ,1 ,1 ,2 ,2 ,3 ,3 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,6 ,7 ,7 ,8 ,8 ,9 ,9 ,9 ,10 ,10 ,11 ,11 ,11 ,12 ,12 ,13 ,13 ,13 ,14 ,14 ,14 ,15 ,15 ,15 ,16 ,16 ,16 ,17 ,17 ,17 ,18 ,18 ,18 ,19 ,19 ,19 ,19 ,20 ,20 ,20 ,20 ,21 ,21 ,21 ,21 ,22 ,22 ,22 ,22 ,22 ,23 ,23 ,23 ,23 ,23 ,23 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,24 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25 ,25};
static const char m_arr[] = {0 ,1 ,1 ,2 ,2 ,3 ,4 ,4 ,5 ,5 ,6 ,7 ,7 ,8 ,8 ,9 ,10 ,10 ,11 ,11 ,12 ,13 ,13 ,14 ,14 ,15 ,15 ,16 ,16 ,17 ,18 ,18 ,19 ,19 ,20 ,20 ,21 ,21 ,22 ,22 ,22 ,23 ,23 ,24 ,24 ,25 ,25 ,26 ,26 ,26 ,27 ,27 ,28 ,28 ,28 ,29 ,29 ,29 ,30 ,30 ,30 ,31 ,31 ,31 ,31 ,32 ,32 ,32 ,32 ,33 ,33 ,33 ,33 ,33 ,34 ,34 ,34 ,34 ,34 ,34 ,34 ,35 ,35 ,35 ,35 ,35 ,35 ,35 ,35 ,35 ,35};
static const char s_arr[] = {0 ,1 ,1 ,2 ,3 ,3 ,4 ,5 ,6 ,6 ,7 ,8 ,8 ,9 ,10 ,10 ,11 ,12 ,12 ,13 ,14 ,14 ,15 ,16 ,16 ,17 ,18 ,18 ,19 ,19 ,20 ,21 ,21 ,22 ,22 ,23 ,24 ,24 ,25 ,25 ,26 ,26 ,27 ,27 ,28 ,28 ,29 ,29 ,30 ,30 ,31 ,31 ,32 ,32 ,32 ,33 ,33 ,34 ,34 ,34 ,35 ,35 ,35 ,36 ,36 ,36 ,37 ,37 ,37 ,37 ,38 ,38 ,38 ,38 ,38 ,39 ,39 ,39 ,39 ,39 ,39 ,40 ,40 ,40 ,40 ,40 ,40 ,40 ,40 ,40 ,40};


static void hand_helper(const char* arr, int deg, int color){
  deg = deg % 360;
  int x, y;
  if (deg < 90) {
    x = arr[deg];
    y = - arr[90 - deg];
  } else if (deg < 180) {
    x = arr[180 - deg];
    y = arr[deg - 90];
  } else if (deg < 270) {
    x = - arr[deg - 180];
    y = arr[270 - deg];
  } else {
    x = - arr[360 - deg];
    y = - arr[deg - 270];
  }
  ST7735_Line(c_x,c_y,c_x + x, c_y + y, color);
}

int lastHour = 0;
int lastMin = 0;
int lastSec = 0;
int lastAlarm = 0;

#define overlap(a,b) ((a - b) < 10 && (a - b) > -10)

static void draw_hands(void){
  if (refreshAlarm || alarm != lastAlarm){
    if (overlap(lastAlarm, lastHour)) refreshHour = 1;
    if (overlap(lastAlarm, lastMin)) refreshMin = 1;
    if (overlap(lastAlarm, lastSec)) refreshSec = 1;
    hand_helper(s_arr, lastAlarm, clock_bg);
    hand_helper(s_arr, alarm, clock_alarm);
    lastAlarm = alarm;
    refreshAlarm = 0;
  }
  if (refreshSec || sec != lastSec){
    if (overlap(lastSec, lastHour)) refreshHour = 1;
    if (overlap(lastSec, lastMin)) refreshMin = 1;
    if (overlap(lastSec, lastAlarm)) refreshAlarm = 1;
    hand_helper(s_arr, lastSec, clock_bg);
    hand_helper(s_arr, sec, clock_hand);
    lastSec = sec;
    refreshSec = 0;
  }
  if (refreshMin || min != lastMin){
    if (overlap(lastMin, lastHour)) refreshHour = 1;
    if (overlap(lastMin, lastAlarm)) refreshAlarm = 1;
    if (overlap(lastMin, lastSec)) refreshSec = 1;
    hand_helper(m_arr, lastMin, clock_bg);
    hand_helper(m_arr, min, clock_hand);
    lastMin = min;
    refreshMin = 0;
  }
  if (refreshHour || hour != lastHour){
    if (overlap(lastHour, lastAlarm)) refreshAlarm = 1;
    if (overlap(lastHour, lastMin)) refreshMin = 1;
    if (overlap(lastHour, lastSec)) refreshSec = 1;
    hand_helper(h_arr, lastHour, clock_bg);
    hand_helper(h_arr, hour, clock_hand);
    lastHour = hour;
    refreshHour = 0;
  }
}

void draw_7seg(void){
  sec = 85;
  min = 0;
  hour = 0;
  alarm = 45;
  while(1){
    sec++;
    if (sec%2) min++;
    if (min%3 == 1) hour = (hour + 1) % 360;
    sec = sec%360;
    min = min%360;
    draw_hands();
    //refreshSec = 1;
    //refreshMin = 1;
    //refreshHour = 1;
    //refreshAlarm = 1;
  }
}

static void draw_seconds(void) {
}

// --------Face_Out--------
// Prints to screen
// Input:   none
// Output:  none

void Face_Out(void){
  draw_label();
  draw_face();
  draw_hands();
  draw_7seg();
  draw_seconds();
}
