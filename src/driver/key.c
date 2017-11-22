#include "drivers.h"
#include"../global/globle.h"
#include "../app/event.h"
//keyDef_t keyValue={0x00};
//keyDef_t preKeyValue={0xff};
//keyDef_t KeyValue={0xff};
volatile uint8_t keyValue=0;
uint8_t  get_key_value(void)
{
	uint8_t tmp;
	tmp=0x00;
	if(!get_port_value(KEY_UP_PORT,KEY_UP_PINS))tmp |= KEY_VALUE_UP;
	if(!get_port_value(KEY_DOWN_PORT,KEY_DOWN_PINS))tmp |= KEY_VALUE_DOWN;
	if(!get_port_value(KEY_SET_PORT,KEY_SET_PINS))tmp |= KEY_VALUE_SET;

	return tmp;
}

void key_init(void)
{
    set_port_mode_dig(KEY_UP_PORT,KEY_UP_PINS);
	set_port_mode_in(KEY_UP_PORT,KEY_UP_PINS);	
	
    //set_port_mode_dig(KEY_DOWN_PORT,KEY_DOWN_PINS);
	set_port_mode_in(KEY_DOWN_PORT,KEY_DOWN_PINS);

    //set_port_mode_dig(KEY_SET_PORT,KEY_SET_PINS);
	set_port_mode_in(KEY_SET_PORT,KEY_SET_PINS);

	KEY_UP_PINS_CNEN=1;
	KEY_DOWN_PINS_CNEN=1;
	KEY_SET_PINS_CNEN=1;

	KEY_UP_PINS_CNPU=1;
	KEY_DOWN_PINS_CNPU=1;
	KEY_SET_PINS_CNPU=1;	
	
	CNIF=0;
	
	CNIE=1;	

}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CNInterrupt ()
{
	CNIF=0;
	__nop();
	//keyValue=get_key_value();
    send_thread_main_event(flg_KEY_DOWN);
	__nop();
	__nop();
}