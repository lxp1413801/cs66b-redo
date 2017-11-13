//file name :globle.h
#ifndef __globle_h__
#define __globle_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	extern volatile uint32_t globleTickerMs;
	extern volatile uint32_t globleTickerSec;
	#ifndef __nop
		#define __nop() asm("NOP");
	#endif

#ifdef __cplusplus
	}
#endif

#endif
