//file name :gpio_config.h
#ifndef __gpio_config_h__
#define __gpio_config_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	
    #define GPIO_PIN_DIR_OUT    0
    #define GPIO_PIN_DIR_IN     1
	
	#define GPIO_PIN_MODE_AN	1
	#define GPIO_PIN_MODE_DIG	0
	
	#define GPIO_PIN_ODC_EN		1
	#define GPIO_PIN_ODC_DIS	0

    #define     PIN0    (1<<0)
    #define     PIN1    (1<<1)
    #define     PIN2    (1<<2)
    #define     PIN3    (1<<3)
    #define     PIN4    (1<<4)
    #define     PIN5    (1<<5)
    #define     PIN6    (1<<6)
    #define     PIN7    (1<<7)
    #define     PIN8    (1<<8)
    #define     PIN9    (1<<9)
    #define     PIN10    (1<<10)
    #define     PIN11    (1<<11)
    #define     PIN12    (1<<12)
    #define     PIN13    (1<<13)
    #define     PIN14    (1<<14)
    #define     PIN15    (1<<15)	
    //port a
	#define set_porta_mode_an(pin) 		do{ANSA |= pin;}while(0);
	#define set_porta_mode_dig(pin)		do{ANSA &= ~pin;}while(0);
	#define set_porta_odc_en(pin) 		do{ODCA |= pin;}while(0);
	#define set_porta_odc_dis(pin)		do{ODCA &= ~pin;}while(0);
	#define set_porta_value_toggle(pin)	do{LATA ^= pin;}while(0);	
	
    #define set_porta_mode_out(pin)     do{TRISA &= ~pin;}while(0);
    #define set_porta_mode_in(pin)      do{TRISA |= pin;}while(0);
    #define set_porta_value_hight(pin)	do{LATA  |= pin;}while(0);
    #define set_porta_value_low(pin)	do{LATA  &= ~pin;}while(0);
    #define get_porta_value(pin)        (PORTA & pin)
    //port b
	#define set_portb_mode_an(pin) 		do{ANSB |= pin;}while(0);
	#define set_portb_mode_dig(pin)		do{ANSB &= ~pin;}while(0);
	#define set_portb_odc_en(pin) 		do{ODCB |= pin;}while(0);
	#define set_portb_odc_dis(pin)		do{ODCB &= ~pin;}while(0);
	#define set_portb_value_toggle(pin)	do{LATB ^= pin;}while(0);	
	
    #define set_portb_mode_out(pin)		do{TRISB &= ~pin;}while(0);
    #define set_portb_mode_in(pin)		do{TRISB |= pin;}while(0);
    #define set_portb_value_hight(pin)	do{LATB  |= pin;}while(0);
    #define set_portb_value_low(pin)	do{LATB  &= ~pin;}while(0);
    #define get_portb_value(pin)		(PORTB & pin)
    //port c
	#define set_portc_mode_an(pin) 		do{ANSC |= pin;}while(0);
	#define set_portc_mode_dig(pin)		do{ANSC &= ~pin;}while(0);
	#define set_portc_odc_en(pin) 		do{ODCC |= pin;}while(0);
	#define set_portc_odc_dis(pin)		do{ODCC &= ~pin;}while(0);
	#define set_portc_value_toggle(pin)	do{LATC ^= pin;}while(0);	
	
    #define set_portc_mode_out(pin)		do{TRISC &= ~pin;}while(0);
    #define set_portc_mode_in(pin)		do{TRISC |= pin;}while(0);
    #define set_portc_value_hight(pin)	do{LATC  |= pin;}while(0);
    #define set_portc_value_low(pin)	do{LATC  &= ~pin;}while(0);
    #define get_portc_value(pin)		(PORTC & pin)
    //port d
	#define set_portd_mode_an(pin) 		do{ANSD |= pin;}while(0);
	#define set_portd_mode_dig(pin)		do{ANSD &= ~pin;}while(0);
	#define set_portd_odc_en(pin) 		do{ODCD |= pin;}while(0);
	#define set_portd_odc_dis(pin)		do{ODCD &= ~pin;}while(0);
	#define set_portd_value_toggle(pin)	do{LATD ^= pin;}while(0);	
	
    #define set_portd_mode_out(pin)		do{TRISD &= ~pin;}while(0);
    #define set_portd_mode_in(pin)		do{TRISD |= pin;}while(0);
    #define set_portd_value_hight(pin)	do{LATD  |= pin;}while(0);
    #define set_portd_value_low(pin)	do{LATD  &= ~pin;}while(0);
    #define get_portd_value(pin)		(PORTD & pin)
    //port e
	#define set_porte_mode_an(pin) 		do{ANSE |= pin;}while(0);
	#define set_porte_mode_dig(pin)		do{ANSE &= ~pin;}while(0);
	#define set_porte_odc_en(pin) 		do{ODCE |= pin;}while(0);
	#define set_porte_odc_dis(pin)		do{ODCE &= ~pin;}while(0);
	#define set_porte_value_toggle(pin)	do{LATE ^= pin;}while(0);	
	
    #define set_porte_mode_out(pin)		do{TRISE &= ~pin;}while(0);
    #define set_porte_mode_in(pin)		do{TRISE |= pin;}while(0);
    #define set_porte_value_hight(pin)	do{LATE  |= pin;}while(0);
    #define set_porte_value_low(pin)	do{LATE  &= ~pin;}while(0);
    #define get_porte_value(pin)		(PORTE & pin)
    //port f
	#define set_portf_mode_an(pin) 		do{ANSF |= pin;}while(0);
	#define set_portf_mode_dig(pin)		do{ANSF &= ~pin;}while(0);
	#define set_portf_odc_en(pin) 		do{ODCF |= pin;}while(0);
	#define set_portf_odc_dis(pin)		do{ODCF &= ~pin;}while(0);
	#define set_portf_value_toggle(pin)	do{LATF ^= pin;}while(0);	
	
    #define set_portf_mode_out(pin)		do{TRISF &= ~pin;}while(0);
    #define set_portf_mode_in(pin)		do{TRISF |= pin;}while(0);
    #define set_portf_value_hight(pin)	do{LATF  |= pin;}while(0);
    #define set_portf_value_low(pin)	do{LATF  &= ~pin;}while(0);
    #define get_portf_value(pin)		(PORTF & pin)	
    //port g
	#define set_portg_mode_an(pin) 		do{ANSG |= pin;}while(0);
	#define set_portg_mode_dig(pin)		do{ANSG &= ~pin;}while(0);
	#define set_portg_odc_en(pin) 		do{ODCG |= pin;}while(0);
	#define set_portg_odc_dis(pin)		do{ODCG &= ~pin;}while(0);
	#define set_portg_value_toggle(pin)	do{LATG ^= pin;}while(0);	
	
    #define set_portg_mode_out(pin)     do{TRISG &= ~pin;}while(0);
    #define set_portg_mode_in(pin)      do{TRISG |= pin;}while(0);
    #define set_portg_value_hight(pin)  do{LATG  |= pin;}while(0);
    #define set_portg_value_low(pin)    do{LATG  &= ~pin;}while(0);
    #define get_portg_value(pin)     PORTG & pin
	/*
    //port h
    #define set_porth_mode_out(pin)     do{TRISH &= ~pin;}while(0);
    #define set_porth_mode_in(pin)      do{TRISH |= pin;}while(0);
    #define set_porth_value_hight(pin)  do{LATH  |= pin;}while(0);
    #define set_porth_value_low(pin)    do{LATH  &= ~pin;}while(0);
    #define get_porth_value(pin)     PORTH & pin
    //port j
    #define set_portj_mode_out(pin)     do{TRISJ &= ~pin;}while(0);
    #define set_portj_mode_in(pin)      do{TRISJ |= pin;}while(0);
    #define set_portj_value_hight(pin)  do{LATJ  |= pin;}while(0);
    #define set_portj_value_low(pin)    do{LATJ  &= ~pin;}while(0);
    #define get_portj_value(pin)     PORTJ & pin	
	*/
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
