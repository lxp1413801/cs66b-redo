//file name :key.h
#ifndef __key_h__
#define __key_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>

	#include "gpio_config.h"
	#define KEY_UP_PINS		PIN1
	#define KEY_UP_PORT		porta
	
	#define KEY_DOWN_PINS	PIN13
	#define KEY_DOWN_PORT	portf
	
	#define KEY_SET_PINS	PIN0
	#define KEY_SET_PORT	portf
	
	#define KEY_UP_PINS_CNEN		CNEN3bits.CN34IE
	#define KEY_DOWN_PINS_CNEN		CNEN5bits.CN76IE
	#define KEY_SET_PINS_CNEN		CNEN5bits.CN68IE
	
	#define KEY_UP_PINS_CNPU    	CNPU3bits.CN34PUE
	#define KEY_DOWN_PINS_CNPU    	CNPU5bits.CN76PUE       
	#define KEY_SET_PINS_CNPU    	CNPU5bits.CN68PUE  	
	
	
	//#define KEY_UP_PINS_CNIF    	CN3IFbits.CN34PUE
	//#define KEY_DOWN_PINS_CNIF    	CN5IFbits.CN76PUE       
	//#define KEY_SET_PINS_CNIF    	CN5IFbits.CN68PUE  
	#define CNIF	IFS1bits.CNIF 
	
	// #define KEY_UP_PINS_CNIE    	CN3IEbits.CN34IE
	// #define KEY_DOWN_PINS_CNIE    	CN5IEbits.CN76IE       
	// #define KEY_SET_PINS_CNIe    	CN5IEbits.CN68IE  	
	#define CNIE IEC1bits.CNIE
	
	#define KEY_VALUE_DOWN 	(0x01<<0x0)
	#define KEY_VALUE_UP 	(0x01<<0x01)
	#define KEY_VALUE_SET	(0x01<<0x02)
	#define KEY_VALUE_NONE	(0x0)
	#define KEY_VALUE_MASK	(KEY_VALUE_UP | KEY_VALUE_DOWN | KEY_VALUE_SET)
	/*
	typedef union{
		uint8_t b;
		struct{
			uint8_t keyUp:1;
			uint8_t keyDown:1;
			uint8_t keySet:1;
			uint8_t:5;
		}bits;
	}st_keyDef,keyDef_t;
	*/
	extern volatile uint8_t keyValue;
	extern void key_init(void);
    extern uint8_t  get_key_value(void);
#ifdef __cplusplus
	}
#endif

#endif
