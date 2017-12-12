//file name :configs.h
#ifndef __configs_h__
#define __configs_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	#define NO_EVENT_TIME_MAX 10*2
	
	#ifndef ADS1148_CHIP_OTRHER_ONE_ENABLE
		#define ADS1148_CHIP_OTRHER_ONE_ENABLE 0
	#endif
#ifdef __cplusplus
	}
#endif

#endif
