#ifndef __event_h__
#define __event_h__

#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	extern volatile uint16_t event;
	#define flg_RTC_SECOND		(1<<0)
	#define flg_TICKER_10MS_PER	(1<<1)
    
	

#ifdef __cplusplus
	}
#endif

#endif