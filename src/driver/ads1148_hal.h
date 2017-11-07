//file name :ads1148_hal.h
#ifndef __ads1148_hal_h__
#define __ads1148_hal_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include "gpio_config.h"
	#include "gpio.h"
	
	//rd10
	#define ADS1148_SCK_PIN		PIN10
	#define ADS1148_SCK_PORT	portd
	//rd9
	#define ADS1148_DIN_PIN		PIN9
	#define ADS1148_DIN_PORT 	portd
	//rd8
	#define ADS1148_DOUT_PIN	PIN8
	#define ADS1148_DOUT_PORT 	portd
	//ra15 ADS1-DRDY
	#define ADS1148_DRDY_0_PIN		PIN15
	#define ADS1148_DRDY_0_PORT 	porta	
	//ra15 ADS1-CS
	#define ADS1148_CS_0_PIN		PIN14
	#define ADS1148_CS_0_PORT 		porta	
	//ra5 ADS1-START
	#define ADS1148_START_0_PIN		PIN5
	#define ADS1148_START_0_PORT 	porta	
	//ra4 ADS2-DRDY	
	#define ADS1148_DRDY_1_PIN		PIN4
	#define ADS1148_DRDY_1_PORT 	porta	
	//ra3 ADS2-CS
	#define ADS1148_CS_1_PIN		PIN3
	#define ADS1148_CS_1_PORT 	porta		
	//rg2 ADS2-START
	#define ADS1148_START_1_PIN		PIN2
	#define ADS1148_START_1_PORT 	portg		
#ifdef __cplusplus
	}
#endif

#endif
//file end
