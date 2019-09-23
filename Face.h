// Face.c
// This progam manages the clock face display output to the ST7735 screen.
// Matthew Jiang
// Septermber 18th, 2019

#ifndef FACE
#define FACE


// --------Face_Init--------
// Initializes clock face, clears screen, draws clock
// Input:   none
// Output:  none
void Face_Init(void);

// --------Face_SetLabel--------
// Sets label at top of screen
// Input:   n   String that will be displayed at top of screen
// Output:  none
void Face_SetLabel(char* n);

// --------Face_ShowAlarm--------
// Sets whether alarm hand is shown on clock or not
// Input:   on  Boolean (true to show)
// Output:  none
void Face_ShowAlarm(int on);

// --------Face_SetAlarm--------
// Sets current alarm time, expects 24 hr time
// Input:   h     hour
//          m     minute
//
// Output:  none
void Face_SetAlarm(int h, int m);

// --------Face_Ring--------
// Sets whether the clock is ringing (timer and alarm)
// Input:   on   Boolean (true to ring)
// Output:  none
void Face_Ring(int on);

// --------Face_SetTime--------
// Sets current time for face to display, expects 24 hr time
// Input:   h     hour
//          m     minute
//          s     second
//          ms    milisecond
// Output: none       

void Face_SetTime(int h, int m, int s, int ms);

// --------Face_SetTimeMS--------
// Sets current time for face to display, takes in one input (MS) and converts to HMS/MS
// Input:   milss    milisecond
// Output:  none
void Face_SetTimeMS(int mils);

// --------Face_Set24--------
// Sets face to 24 hr mode (uses 00-23 hour display instead of 12-11 with AM/PM dot)
// Input:   on true to turn on 24 hr mode, false to use 12 hr
// Output:  none

void Face_Set24(int on);


// --------Face_ShowDet--------
// Shows detailed second/millisecond view
// Input:   on true to turn on detailed view
// Output:  none

void Face_ShowDet(int on);

// --------Face_Out--------
// Prints to screen
// Input:   clear   Whether or not screen needs to be cleared first (if transitioning in from a menu)
// Output:  none

void Face_Out(int clear);

#endif
