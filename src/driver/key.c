#include "drivers.h"
#include"../global/globle.h"
#include "../app/event.h"
keyDef_t keyValue={0x00};
//keyDef_t preKeyValue={0xff};
//keyDef_t KeyValue={0xff};

uint8_t  get_key_value(void)
{
	keyDef_t tmp;
	tmp.b=0x00;
	if(get_port_value(KEY_UP_PORT,KEY_UP_PINS))tmp.bits.keyUp=1;
	if(get_port_value(KEY_DOWN_PORT,KEY_DOWN_PINS))tmp.bits.keyDown=1;
	if(get_port_value(KEY_SET_PORT,KEY_SET_PINS))tmp.bits.keySet=1;
    tmp.b= ~ tmp.b;
	return tmp.b;
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
	keyValue.b=get_key_value();
    send_thread_main_event(flg_KEY_DOWN);
	__nop();
	__nop();
}