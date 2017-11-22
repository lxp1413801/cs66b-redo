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
    
    extern uint32_t  tickerMsPer10Ms;
    extern uint32_t ticker_10ms_per_get(void);
    extern void ticker_10ms_per_set(uint32_t tick);
    
    extern void ticker_ms_delay(uint16_t ms);
    
#ifdef __cplusplus
}
#endif
#endif
//file end
