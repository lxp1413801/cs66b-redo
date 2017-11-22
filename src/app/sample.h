//file name :sample.h
#ifndef __sample_h__
#define __sample_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	//extern void thread_sample_void(void);
	extern volatile int16_t rtAdcValueDPrBridge;
	extern volatile int16_t rtAdcValueDPrSignal;
	extern volatile int16_t rtAdcValuePrBridge;
	extern volatile int16_t rtAdcValuePrSignal;
	
	extern volatile int16_t rtAdcValueTemperatureIn;
	extern volatile int16_t rtAdcValueChip0Ref0;
	extern volatile int16_t rtAdcValueChip0Ref1;

	extern volatile int16_t rtAdcValuePrEx0Bridge;
	extern volatile int16_t rtAdcValuePrEx0Signal;
	extern volatile int16_t rtAdcValuePrEx1Bridge;
	extern volatile int16_t rtAdcValuePrEx1Signal;
	
	extern volatile int16_t rtAdcValueTemperatureEx;
	extern volatile int16_t rtAdcValueChip1Ref0;
	extern volatile int16_t rtAdcValueChip1Ref1;	
	
	extern void thread_sample_create(void);

#ifdef __cplusplus
	}
#endif

#endif
//file end