//file name :configs.h
#ifndef __configs_h__
#define __configs_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	#define HWVER301 301
	#define HWVER302 302
	#define HWVER303 303
	
	#ifndef HW_VER
		#define HW_VER HWVER303
	#endif

	#define NO_EVENT_TIME_MAX 30

	//V303的板子都是通过io口向eeprom供电的，301之前的只有一块板子使用io供电
	#ifndef EEPROM_PER_VIA_IO
		#if HW_VER>= HWVER303
			#define EEPROM_PER_VIA_IO 1
		#else
			#define EEPROM_PER_VIA_IO 0
		#endif
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
		#define SOFTWARE_VER " uer 331"
	#endif
	
	
	#define WAKE_UP_SAMPLE_FORBID 0xffff
    #define RF_SEND_OFF     0xffff
	
	#ifndef LCD_TEST_EX_EN
	
		#define LCD_TEST_EX_EN 0
		
	#endif
#ifdef __cplusplus
	}
#endif

#endif
