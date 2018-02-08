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
	
    #define ANI_SOLOR_PIN   PIN9
    #define ANI_SOLOR_PORT  porta
    extern void ain_solor_config(void);

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
	
	#define STATUS_BJ_PINS	PIN3
	#define STATUS_BJ_PORT	portc
	
	#define STATUS_485_PINS	PIN4
	#define STATUS_485_PORT	portc
	
	extern void status_ma_mode_in(void);
	extern void all_status_pins_mod_in(void);
	
	extern void all_bj_init(void);
	//#define all_bj_disable() all_bj_pins_init()
	extern void all_bj_disable(void);
	extern void bj_1_on(void);
	extern void bj_2_on(void);
	extern void bj_3_on(void);
	extern void bj_4_on(void);

	extern void bj_1_off(void);
	extern void bj_2_off(void);
	extern void bj_3_off(void);
	extern void bj_4_off(void);
	extern void bj_all_on(void);
	extern void bj_all_off(void);
    
    extern void bj_output(void);	
    
	#define RUN_STATUS_PINS PIN12
	#define RUN_STATUS_PORT	portd
	
	extern void run_status_init(void);
	//extern void run_status_on(void);
	#define run_status_on() set_port_value_hight(RUN_STATUS_PORT,RUN_STATUS_PINS);
	#define run_status_off() set_port_value_low(RUN_STATUS_PORT,RUN_STATUS_PINS);
	
	extern void pre_system_sleep(void);
    extern void pre_system_sleep_deinit_all_pins(void);
	
	#define FLOAT_RF7_PIN	PIN7
	#define FLOAT_RF7_PORT	portf
	
	#define FLOAT_RD1_PIN	PIN1
	#define FLOAT_RD1_PORT	portd

	#define FLOAT_RB6_PIN	PIN6
	#define FLOAT_RB6_PORT	portd	
	extern void unused_pins_deinit(void);
	
		//定义外部功能板的状态
	#define EX_FUNCTION_485_EN 		(1<<0)
	#define EX_FUNCTION_BJ_EN		(1<<1)
	#define EX_FUNCTION_ILOOP_EN	(1<<2)
	extern uint8_t  get_ex_function_status(void);
	extern uint8_t volatile exFunctionSta; 
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
