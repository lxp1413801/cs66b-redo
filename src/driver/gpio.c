#include "gpio_config.h"
volatile bool lcdBlackNightOn=false;
volatile bool kzAvddOn=false;
void kz_vadd_on(void)
{
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
