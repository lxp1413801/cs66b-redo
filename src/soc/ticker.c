#include "../includes/includes.h"
uint32_t  tickerMs=0x00ul;
uint32_t  tickerSec=0x00ul;
uint32_t  tickerMsPer10Ms=0x00ul;

volatile uint8_t timerUsedFlg=0x00; 

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
//
void api_timer2_start(void)
{
    TMR2_Start();
}
void api_timer2_stop(void)
{
    if(!fi_timer_uase_by_uart()){
        TMR2_Stop();
    }
}
void TMR2_CallBack(void)
{
    TMR2_Stop();
    if(1){
        //sample tesk used timer 2
        tickerMsPer10Ms++;
	}
    if(1){
        event |=  flg_TICKER_10MS_PER;
    }
    
	if(uart1RecIdleTime>0){
        //uart time out used timer 2;
		uart1RecIdleTime+=20;
		if(uart1RecIdleTime>10000)uart1RecIdleTime=10000;
		if(uart1RecIdleTime>UART_1_REC_IDLE_TIME_OUT){
            uart1RecIdleTime=0;
			event |= flg_MODBUS_RECEIVED;
            timer2_release_by_uart1();
		}
	}
    
	if(uart2RecIdleTime>0){
        //uart 2 used timer 2
		uart2RecIdleTime+=20;
		if(uart2RecIdleTime>10000)uart2RecIdleTime=10000;
		if(uart2RecIdleTime > UART_2_REC_IDLE_TIME_OUT){
            uart2RecIdleTime=0;
			event |= flg_NB_GPS_RECEIVED;
            timer2_release_by_uart2();
		}
	}	
    if(fi_timer_uase_by_uart()){
        TMR2_Start();
    }
}

uint32_t ticker_10ms_per_get(void)
{
    return tickerMsPer10Ms;
}

void ticker_10ms_per_set(uint32_t tick)
{
    tickerMsPer10Ms=tick;
}
void rtcc_interupt_disable(void)
{
    IFS3bits.RTCIF = 0;
    IEC3bits.RTCIE = 0;
}
void rtcc_interupt_enable(void)
{
    IEC3bits.RTCIE = 1;
}
void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )
{
    /* TODO : Add interrupt handling code */
    
    IFS3bits.RTCIF = false;
    event |=  flg_RTC_HALF_SECOND;
	globleHalfSec++;
}