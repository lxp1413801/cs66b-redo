//file name :configs.h
#ifndef __configs_h__
#define __configs_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	#define NO_EVENT_TIME_MAX 30


	#ifndef EEPROM_PER_VIA_IO
		#define EEPROM_PER_VIA_IO 0
	#endif	
	
	#ifndef UART_1_REC_IDLE_TIME_OUT 
		#define UART_1_REC_IDLE_TIME_OUT 400
	#endif
	
	#ifndef UART_2_REC_IDLE_TIME_OUT 
		#define UART_2_REC_IDLE_TIME_OUT 1000
	#endif	
	
	
	#ifndef ADS1148_CHIP_OTRHER_ONE_ENABLE
		#define ADS1148_CHIP_OTRHER_ONE_ENABLE 1
	#endif
	
	#ifndef BJ_BAORD_EN
		#define BJ_BAORD_EN 1
	#endif
	
	#ifndef I_LOOP_BOARD
		#define I_LOOP_BOARD 1
	#endif
	
	#ifndef DEBUG_EX_TEMP_EN
		#define DEBUG_EX_TEMP_EN 0
	#endif
	
	#ifndef SOFTWARE_VER
		#define SOFTWARE_VER " uer 30 "
	#endif
	

	
	#ifndef LCD_TEST_EX_EN
	
		#define LCD_TEST_EX_EN 0
		
	#endif
#ifdef __cplusplus
	}
#endif

#endif
