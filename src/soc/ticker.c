#include <stdint.h>
#include "ticker.h"

uint32_t  tickerMs=0x00ul;
uint32_t  tickerSec=0x00ul;

void  TMR1_CallBack(void)
{
	tickerMs++;
}

void ticker_ms_set(uint32_t tick)
{
	tickerMs=tick;
}

uint32_t ticker_ms_get(void)
{
	return tickerMs;
}

void ticker_ms_delay(uint16_t ms)
{
	uint32_t t32=0,tm=0;
	t32=ticker_ms_get();
	if(t32 & 0x80000000){
		ticker_ms_set(0);
		t32=0;
	}
	t32+=(uint32_t)ms;
	while(tm<t32){
		tm=ticker_ms_get();
	}
}
