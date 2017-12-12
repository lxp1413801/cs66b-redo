#include "drivers.h"

ad421Obj_t ad421ObjChip0;
ad421Obj_t ad421ObjChip1;

void ad421_chip0_pins_init(void)
{
	set_port_mode_dig(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	set_port_mode_out(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	set_port_value_low(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	
	set_port_mode_dig(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
	set_port_mode_out(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
	set_port_value_low(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);	
	
	set_port_mode_dig(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);
	set_port_mode_out(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);
	set_port_value_low(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);	
}

void ad421_chip1_pins_init(void)
{
	set_port_mode_dig(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	set_port_mode_out(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	set_port_value_low(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	
	set_port_mode_dig(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
	set_port_mode_out(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
	set_port_value_low(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);	
	
	set_port_mode_dig(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);
	set_port_mode_out(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);
	set_port_value_low(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);	
}

void ad421_chip0_pins_deinit(void)
{
	// set_port_mode_dig(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	// set_port_mode_out(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	set_port_value_hight(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
	
	// set_port_mode_dig(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
	// set_port_mode_out(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
	set_port_value_hight(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);	
	
	// set_port_mode_dig(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);
	// set_port_mode_out(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);
	set_port_value_hight(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);	
}

void ad421_chip1_pins_deinit(void)
{
	// set_port_mode_dig(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	// set_port_mode_out(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	set_port_value_hight(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
	
	// set_port_mode_dig(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
	// set_port_mode_out(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
	set_port_value_hight(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);	
	
	// set_port_mode_dig(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);
	// set_port_mode_out(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);
	set_port_value_hight(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);	
}

void ad421_chip0_set_idac_value(uint16_t x)
{
	uint16_t i;
	ad421_chip0_pins_init();
	for(i=0;i<16;i++){
		if(x&0x8000){
			set_port_value_hight(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
		}else{
			set_port_value_low(AD421_DATA_1_PORT,AD421_DATA_1_PIN);
		}
		set_port_value_low(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
		set_port_value_hight(AD421_CLOCK_1_PORT,AD421_CLOCK_1_PIN);
		x<<=1;
	}
	set_port_value_hight(AD421_LATCH_1_PORT,AD421_LATCH_1_PIN);	
	ad421_chip0_pins_deinit();
}

void ad421_chip1_set_idac_value(uint16_t x)
{
	uint16_t i;
	ad421_chip1_pins_init();
	for(i=0;i<16;i++){
		if(x&0x8000){
			set_port_value_hight(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
		}else{
			set_port_value_low(AD421_DATA_2_PORT,AD421_DATA_2_PIN);
		}
		set_port_value_low(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
		set_port_value_hight(AD421_CLOCK_2_PORT,AD421_CLOCK_2_PIN);
		x<<=1;
	}
	set_port_value_hight(AD421_LATCH_2_PORT,AD421_LATCH_2_PIN);	
	ad421_chip1_pins_deinit();
}

void ad421_all_obj_init(void)
{
	ad421ObjChip0.pins_init=ad421_chip0_pins_init;
	ad421ObjChip0.pins_deinit=ad421_chip0_pins_deinit;
	ad421ObjChip0.set_idac_value=ad421_chip0_set_idac_value;
	
	ad421ObjChip1.pins_init=ad421_chip1_pins_init;
	ad421ObjChip1.pins_deinit=ad421_chip1_pins_deinit;
	ad421ObjChip1.set_idac_value=ad421_chip1_set_idac_value;	
}

void ad421_test(void)
{
	ad421ObjChip0.pins_init();
	ad421ObjChip0.set_idac_value(0x8000);
	asm("NOP");
	asm("NOP");
	
	ad421ObjChip1.pins_init();
	ad421ObjChip1.set_idac_value(0x8000);	
	asm("NOP");
	asm("NOP");	
}
