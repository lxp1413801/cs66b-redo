#include "gpio_config.h"
void kz_vadd_on(void)
{
	set_portg_mode_dig(PIN9);
	set_portg_mode_out(PIN9);
	set_portg_value_low(PIN9);
}
void kz_vadd_off(void)
{
	set_portg_mode_dig(PIN9);
	set_portg_mode_out(PIN9);
	set_portg_value_hight(PIN9);
}
void back_night_on(void)
{
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_hight(PIN11);
}
void back_night_off(void)
{
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_low(PIN11);
}
