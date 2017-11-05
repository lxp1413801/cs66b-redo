//file name :delay.h
#ifndef __delay_h__
#define __delay_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	extern void delay_us(uint16_t us);
	extern void delay_ms(uint16_t ms);
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
