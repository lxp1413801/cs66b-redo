//file name :gpio.h
#ifndef __gpio_h__
#define __gpio_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	extern void kz_vadd_on(void);
	extern void kz_vadd_off(void);
	extern void back_night_on(void);
	extern void back_night_off(void);
#ifdef __cplusplus
	}
#endif

#endif
//file end
