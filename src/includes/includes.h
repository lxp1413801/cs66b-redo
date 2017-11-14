//file name :includes.h
#ifndef __includes_h__
#define __includes_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include <stdint.h>
	#include <stdbool.h>
	#include <float.h>
	#include "../../mcc_generated_files/mcc.h"
	
	#include "../configs/configs.h"
	#include "../global/globle.h"
	
	#include "../soc/soc.h"
	#include "../driver/drivers.h"
	#include "../depend/depend.h"
    #include "../api/api.h"
    #include "../app/app.h"

    #include "../../os_configs/FreeRTOSConfig.h"
    #include "../../os_kernel/include/FreeRTOS.h"
    #include "../../os_kernel/include/task.h"        
#ifdef __cplusplus
	}
#endif

#endif
