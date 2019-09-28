# EE 445L Lab 3 Report

- Andrew Jacob apj543
- Matthew Jiang myj99

Objectives
----------

-   What did you do to complete this lab?
    - Created a schematic for our hardware
    - Created 4 modules for our alarm clock
    - Used BJT transistor in conjunction with a speaker
-   What components were you learning about?
    - BJT transistor, we use it in this lab mainly to amplify current that is drawn by the speaker because the TM4C pins do not output enough current
-   Why do you think we made you do this lab?
    - Practice decent software fundamentals with modular programming.
    - Once again hammer the fact that critical sections are important
    - Use a BJT transistor

Preparation Questions
---------------------

-   *Power budget*

    The amount of power (Wattage) the device can consume

-   *Device driver*

    set of software functions that facilitate the use of an I/O port

-   *Critical section*

    Locations within a software module where an interrupt can cause unintended errors due to both the interrupt and main program accessing the same place in memory.

-   *Latency*

    Response time to a certain event.

-   *Time jitter*

    Difference in time that a interrupt takes to execute due to the interrupt being triggered in instructions that take a while to execute compared to the expected time.

-   *Modular programming*
    Separating functionality of the program into modules which are independent to each other and could be changed out easily.
    

Hardware Design
---------------


![image](circuit.png)

Software Design
---------------

Our call graph is the same. Well the LCD Driver is called face, and our sound driver is called Speaker, and we don't use systick but just a timer driver called Timer.

Measurement Data
----------------

// Note: image names and extensions should be changed to match your
files

### Power noise

// O-scope capture of the 5V and 3.3V power coming out of Launchpad

![image](33V.png)
RMS Value: 0.41V
![image](5V.png)
RMS Value: 0.33V

### Speaker output

// O-scope capture of audio signal coming out of speaker pin on
Launchpad

![image](speaker1.png)

### Current measurements

Without speaker: .86A

With speaker on: .128A

Analysis and Discussion
-----------------------

1.  *Give two ways to remove a critical section.*

    Disable interrupts while the main accesses the critical section or just use bit banded I/O.

2.  *How long does it take to update the LCD with a new time?*
    Our measured time was 5.678ms however this can change depending on how many interrupts occur between the time updating. 
	

3.  *What would be the disadvantage of updating the LCD in the
    background ISR?* 
    Updating the LCD is where majority of the time is spent in the programming, so the isr would have to be pretty low priority to allow the speaker and the I/O to work properly. Synchronizing everything would be more difficult.
	

4.  *Did you redraw the entire clock for each output? If so, how could
    you have redesigned the LCD update to run much faster, and create a
    lot less flicker?*
	No, not the entire thing.

5.  *Assuming the system were battery powered, list three ways you could
    have saved power.*
    We could have used interrupts for buttons instead of polling constantly. 
    