#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Speaker.h"

void Speaker_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R&0x10)==0){}
	GPIO_PORTE_DEN_R |= 0x1;
}
