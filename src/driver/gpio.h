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
	
	extern volatile bool lcdBlackNightOn;
	extern volatile bool kzAvddOn;
	
	//
	#define CHECK_SOLOR_PIN 	PIN9
	#define CHECK_SOLOR_PORT 	porta
	extern void check_solor_set_hight(void);
	extern void check_solor_set_low(void);
	
	#define BJ_1_PIN		PIN4
	#define BJ_1_PORT		portd

	#define BJ_2_PIN		PIN5
	#define BJ_2_PORT		portd	
	
	#define BJ_3_PIN		PIN6
	#define BJ_3_PORT		portd		
	
	#define BJ_4_PIN		PIN7
	#define BJ_4_PORT		portd	
	
	
	#define BJ_V_PIN		PIN13
	#define BJ_V_PORT		portd		
	
	#define BJ_PORT			portd
	#define ALL_BJ_PINS		(BJ_1_PIN | BJ_2_PIN | BJ_3_PIN | BJ_4_PIN | BJ_V_PIN)
	
	#define STATUS_MA_PINS	PIN6
	#define STATUS_MA_PORT	portg
	
	#define STATUS_GSM_PINS	PIN7
	#define STATUS_GSM_PORT	portg
	
	extern void status_ma_mode_in(void);
	extern void gpio_status_pins_mod_in(void);
	
	extern void all_bj_disable(void);
	extern void pre_system_sleep(void);
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
