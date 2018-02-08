#ifndef __event_h__
#define __event_h__

#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	extern volatile uint16_t event;
	extern volatile uint8_t keyEventCount;
	//extern EventGroupHandle_t eventGroup;
   
    //extern void send_event_group_isr(EventGroupHandle_t eventGroup,EventBits_t bits);
    //extern send_event_group(EventGroupHandle_t eventGroup,EventBits_t bits);
	extern void send_thread_main_event(uint16_t bits);
	#define flg_RTC_HALF_SECOND		(1<<0)
	#define flg_TICKER_10MS_PER	(1<<1)
    #define flg_KEY_DOWN        (1<<2)
    #define flg_RTC_SECOND		(1<<3)

    #define flg_ALL_BITS (flg_RTC_SECOND | flg_TICKER_10MS_PER | flg_KEY_DOWN)

    extern volatile uint16_t noEventTimeOut;
    
	extern void send_thread_main_event_key_down(void);

#ifdef __cplusplus
	}
#endif

#endif