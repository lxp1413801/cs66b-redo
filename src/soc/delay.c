#include "delay.h"

void delay_us(uint16_t us)
{
	if(us>2000)us=2000;
	while(us){
		us--;
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
	}
}
void delay_ms(uint16_t ms)
{
	if(ms>30000)ms=30000;
	while(ms){
		ms--;
		delay_us(1000);
	}
}
