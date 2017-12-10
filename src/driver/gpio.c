#include "gpio_config.h"
#include "gpio.h"
#include "lcd.h"
#include "i2c.h"

volatile bool lcdBlackNightOn=false;
volatile bool kzAvddOn=false;
void kz_vadd_on(void)
{
    if(kzAvddOn)return;
	set_portg_mode_dig(PIN9);
	set_portg_mode_out(PIN9);
	set_portg_value_low(PIN9);
	kzAvddOn=true;
}
void kz_vadd_off(void)
{
	set_portg_mode_dig(PIN9);
	set_portg_mode_out(PIN9);
	set_portg_value_hight(PIN9);
	set_portg_odc_en(PIN9);
	kzAvddOn=false;
}
void back_night_on(void)
{
    if(!kzAvddOn)kz_vadd_on();
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_hight(PIN11);
	lcdBlackNightOn=true;
}
void back_night_off(void)
{
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_low(PIN11);
	lcdBlackNightOn=false;
}

void status_ma_mode_in(void)
{
	set_port_mode_dig(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_mode_in(STATUS_MA_PORT,STATUS_MA_PINS);
}

void gpio_status_pins_mod_in(void)
{
	set_port_mode_dig(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_mode_in(STATUS_MA_PORT,STATUS_MA_PINS);
	
	set_port_mode_dig(STATUS_GSM_PORT,STATUS_GSM_PINS);
	set_port_mode_in(STATUS_GSM_PORT,STATUS_GSM_PINS);
}

//add 
//ra9
void check_solor_set_hight(void)
{
	set_port_mode_dig(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
	set_port_mode_out(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
	set_port_value_hight(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
}

void check_solor_set_low(void)
{
	set_port_mode_dig(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
	set_port_mode_out(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
	set_port_value_low(CHECK_SOLOR_PORT,CHECK_SOLOR_PIN);
}

void all_bj_disable(void)
{
	set_port_mode_dig(BJ_PORT,ALL_BJ_PINS);
	set_port_mode_out(BJ_PORT,ALL_BJ_PINS);
	set_port_value_low(BJ_PORT,ALL_BJ_PINS);
}
//
void pre_system_sleep_deinit_all_pins(void)
{
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;
    TRISD = 0xFFFF;
    TRISE = 0xFFFF;
    TRISF = 0xFFFF;
    TRISG = 0xFFFF;        
}
void pre_system_sleep(void)
{



	gpio_status_pins_mod_in();
	all_bj_disable();
	check_solor_set_low();
	back_night_off();
	kz_vadd_off();
    iic_pins_disable();
    //lcd_off();
    asm("NOP");
    asm("NOP");   
}