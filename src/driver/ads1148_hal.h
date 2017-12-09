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
	//rd8
	#define ADS1148_DIN_PIN		PIN8
	#define ADS1148_DIN_PORT 	portd
	//rd9
	#define ADS1148_DOUT_PIN	PIN9
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
	#define ADS1148_START_1_PORT 	porta		
	//#define ADS1148_POR_
	#define ADS1148_PWR_PIN			PIN9
	#define ADS1148_PWR_PORT		portg
	
	//common pins
	extern void ads1148_hal_sck_set_hight(void);
	extern void ads1148_hal_sck_set_low(void);
	extern void ads1148_hal_dout_set_hight(void);
	extern void ads1148_hal_dout_set_low(void);
	extern uint16_t ads1148_hal_din_get(void);
	//chip0
	extern void ads1148_hal_cs_0_set_hight(void);
	extern void ads1148_hal_cs_0_set_low(void);
	
	extern void ads1148_hal_start_0_set_hight(void);
	extern void ads1148_hal_start_0_set_low(void);
	
	extern uint16_t ads1148_hal_drdy_0_get(void);
    //extern void ads1148_hal_port_deinit_chip0(void);
	extern void ads1148_hal_port_init_chip0(void);
    extern void ads1148_hal_port_deinit_chip0(void);
	//chip1
	extern void ads1148_hal_cs_1_set_hight(void);
	extern void ads1148_hal_cs_1_set_low(void);
	
	extern void ads1148_hal_start_1_set_hight(void);
	extern void ads1148_hal_start_1_set_low(void);
	
	extern uint16_t ads1148_hal_drdy_1_get(void);
	extern void ads1148_hal_port_init_chip1(void);
    extern void ads1148_hal_port_deinit_chip1(void);
    //
    extern volatile uint8_t ads1148_hal_write_read_byte(volatile uint8_t x);
	//
	extern void ads1148_hal_pwr_off(void);
	extern void ads1148_hal_pwr_on(void);
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
