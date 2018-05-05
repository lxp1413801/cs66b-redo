//file name :ticker.h
#ifndef __ticker_h__
#define __ticker_h__

#ifdef __cplusplus
extern "C"{
#endif
    
    #include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	extern uint32_t  tickerMs;
	extern uint32_t  tickerSec;    
    extern uint32_t ticker_ms_get(void);
    extern void ticker_ms_set(uint32_t tick);
    
    extern uint32_t  tickerMsPer10Ms;
    extern uint32_t ticker_10ms_per_get(void);
    extern void ticker_10ms_per_set(uint32_t tick);
    
    extern void ticker_ms_delay(uint16_t ms);
    extern void rtcc_interupt_disable(void);
    extern void rtcc_interupt_enable(void);
    

    extern volatile uint8_t timerUsedFlg;
    #define UART1_USED_TIMER2 (0x01<<0)
    #define UART2_USED_TIMER2 (0x01<<1)

    #define timer2_used_by_uart1() do{timerUsedFlg |= UART1_USED_TIMER2;}while(0);
    #define timer2_used_by_uart2() do{timerUsedFlg |= UART2_USED_TIMER2;}while(0);
    #define timer2_release_by_uart1() do{timerUsedFlg &= ~UART1_USED_TIMER2;}while(0);
    #define timer2_release_by_uart2() do{timerUsedFlg &= ~UART2_USED_TIMER2;}while(0);
    #define fi_timer_uase_by_uart() (timerUsedFlg & (UART1_USED_TIMER2| UART2_USED_TIMER2))

    extern void api_timer2_start(void);
    extern void api_timer2_stop(void);
    
#ifdef __cplusplus
}
#endif
#endif
//file end
