#include "drivers.h"
#include "ads1148.h"
#include "../soc/delay.h"
#include "../global/globle.h"
//rd10
/*
#define __some_nop() do{ \
	__nop();__nop();__nop();__nop();__nop();__nop(); \
	__nop();__nop();__nop();__nop();__nop();__nop(); \
}while(0);
*/	
/*
#define __some_nop() do{ \
	__nop();__nop();__nop();__nop();__nop();__nop(); \
}while(0);
*/
#define __some_nop() do{ \
	__nop(); \
}while(0);
void ads1148_hal_sck_mod_out(void)
{
    set_port_mode_dig(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	set_port_mode_out(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	#if ADS1148_SCK_IDLE_STATUE==0
	set_port_value_low(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	#else
	set_port_value_hight(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	#endif
}

void ads1148_hal_sck_set_hight(void)
{
	set_port_value_hight(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
}

void ads1148_hal_sck_set_low(void)
{
	set_port_value_low(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
}

void ads1148_hal_sck_mod_in(void)
{
    set_port_mode_dig(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	set_port_mode_in(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	//set_port_value_hight(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
}


void ads1148_hal_din_mod_out(void)
{
    set_port_mode_dig(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	set_port_mode_out(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	//set_port_value_hight(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
}

void ads1148_hal_din_set_hight(void)
{
	set_port_value_hight(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
}

void ads1148_hal_din_set_low(void)
{
	set_port_value_low(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
}

void ads1148_hal_din_mod_in(void)
{
    set_port_mode_dig(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	set_port_mode_in(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	//set_port_value_hight(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
}

uint16_t ads1148_hal_din_get(void)
{
	volatile uint16_t t16;
	t16=get_port_value(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	return t16;
}

void ads1148_hal_dout_mod_out(void)
{
    set_port_mode_dig(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
	set_port_mode_out(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
	set_port_value_hight(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
}

void ads1148_hal_dout_set_hight(void)
{
	set_port_value_hight(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
}

void ads1148_hal_dout_set_low(void)
{
	set_port_value_low(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
}

void ads1148_hal_dout_mod_in(void)
{
    set_port_mode_dig(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
	set_port_mode_in(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
	//set_port_value_hight(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
}


void ads1148_hal_drdy_0_mod_out(void)
{
    //set_port_mode_dig(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
	set_port_mode_out(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
	set_port_value_hight(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
}

void ads1148_hal_drdy_0_set_hight(void)
{
	set_port_value_hight(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
}



void ads1148_hal_drdy_0_set_low(void)
{
	set_port_value_low(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
}

void ads1148_hal_drdy_0_mod_in(void)
{
    set_port_mode_dig(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
	set_port_mode_in(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
	//set_port_value_hight(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
}

uint16_t ads1148_hal_drdy_0_get(void)
{
	volatile uint16_t t16;
	t16=get_port_value(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
    asm("nop");
	return t16;
}

void ads1148_hal_cs_0_mod_out(void)
{
    set_port_mode_dig(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	set_port_mode_out(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	set_port_value_hight(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
}

void ads1148_hal_cs_0_mod_in(void)
{
    set_port_mode_dig(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	set_port_mode_in(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	//set_port_value_hight(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
}

void ads1148_hal_cs_0_set_hight(void)
{
	set_port_value_hight(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
}

void ads1148_hal_cs_0_set_low(void)
{
	set_port_value_hight(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	delay_us(10);
	set_port_value_low(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
}

void ads1148_hal_start_0_mod_out(void)
{
    set_port_mode_dig(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
	set_port_mode_out(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
	set_port_value_hight(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
}

void ads1148_hal_start_0_set_hight(void)
{
	set_port_value_hight(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
}

void ads1148_hal_start_0_set_low(void)
{
	set_port_value_low(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
}


void ads1148_hal_start_0_mod_in(void)
{
    set_port_mode_dig(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
	set_port_mode_in(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
	//set_port_value_hight(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
}

void ads1148_hal_drdy_1_mod_out(void)
{
    //set_port_mode_dig(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	set_port_mode_out(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	set_port_value_hight(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
}

void ads1148_hal_drdy_1_set_hight(void)
{
	set_port_value_hight(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
}

void ads1148_hal_drdy_1_set_low(void)
{
	set_port_value_low(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
}


void ads1148_hal_drdy_1_mod_in(void)
{
    set_port_mode_dig(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	set_port_mode_in(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	//set_port_value_hight(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
}

uint16_t ads1148_hal_drdy_1_get(void)
{
	volatile uint16_t t16;
	t16=get_port_value(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	return t16;
}

void ads1148_hal_cs_1_mod_out(void)
{
    set_port_mode_dig(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	set_port_mode_out(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	set_port_value_hight(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
}

void ads1148_hal_cs_1_set_hight(void)
{
	set_port_value_hight(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
}

void ads1148_hal_cs_1_set_low(void)
{
	set_port_value_hight(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	delay_us(10);
	set_port_value_low(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
}


void ads1148_hal_cs_1_mod_in(void)
{
    set_port_mode_dig(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	set_port_mode_in(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	//set_port_value_hight(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
}


void ads1148_hal_start_1_mod_out(void)
{
    set_port_mode_dig(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
	set_port_mode_out(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
	set_port_value_hight(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
}

void ads1148_hal_start_1_set_hight(void)
{
	set_port_value_hight(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
}

void ads1148_hal_start_1_set_low(void)
{
	set_port_value_low(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
}


void ads1148_hal_start_1_mod_in(void)
{
    set_port_mode_dig(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
	set_port_mode_in(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
	//set_port_value_hight(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
}

void ads1148_hal_port_mode_dig_all(void)
{
	
	set_port_mode_dig(ADS1148_SCK_PORT,ADS1148_SCK_PIN);
	set_port_mode_dig(ADS1148_DIN_PORT,ADS1148_DIN_PIN);
	set_port_mode_dig(ADS1148_DOUT_PORT,ADS1148_DOUT_PIN);
	set_port_mode_dig(ADS1148_DRDY_0_PORT,ADS1148_DRDY_0_PIN);
	set_port_mode_dig(ADS1148_CS_0_PORT,ADS1148_CS_0_PIN);
	set_port_mode_dig(ADS1148_START_0_PORT,ADS1148_START_0_PIN);
	set_port_mode_dig(ADS1148_DRDY_1_PORT,ADS1148_DRDY_1_PIN);
	set_port_mode_dig(ADS1148_CS_1_PORT,ADS1148_CS_1_PIN);
	set_port_mode_dig(ADS1148_START_1_PORT,ADS1148_START_1_PIN);
	
}

void ads1148_hal_port_init_chip0(void)
{
	ads1148_hal_sck_mod_out();
	ads1148_hal_din_mod_in();
	ads1148_hal_dout_mod_out();
	ads1148_hal_cs_0_mod_out();
	ads1148_hal_start_0_mod_out();
	ads1148_hal_drdy_0_mod_in();
}

void ads1148_hal_port_deinit_chip0(void)
{
	
	// ads1148_hal_sck_mod_in();
	// ads1148_hal_din_mod_in();
	// ads1148_hal_dout_mod_in();
	/*
	ads1148_hal_sck_mod_out();
	ads1148_hal_sck_set_low();
	
	ads1148_hal_din_mod_out();
	ads1148_hal_din_set_low();
	
	ads1148_hal_dout_mod_out();
	ads1148_hal_dout_set_low();
    
	ads1148_hal_cs_0_mod_in();
	ads1148_hal_start_0_mod_in();
	ads1148_hal_drdy_0_mod_in();
	*/
	
	
	ads1148_hal_sck_mod_out();
	ads1148_hal_sck_set_low();
	
	ads1148_hal_din_mod_out();
	ads1148_hal_din_set_low();
	
	ads1148_hal_dout_mod_out();
	ads1148_hal_dout_set_low();
	
	ads1148_hal_cs_0_mod_out();
	//ads1148_hal_cs_0_set_low();
	
	ads1148_hal_start_0_mod_out();
	ads1148_hal_start_0_set_low();
	
	ads1148_hal_drdy_0_mod_out();
	ads1148_hal_drdy_0_set_low();
	
	
}

void ads1148_hal_port_init_chip1(void)
{
	
	ads1148_hal_sck_mod_out();
	ads1148_hal_din_mod_in();
	ads1148_hal_dout_mod_out();
	ads1148_hal_cs_1_mod_out();
	ads1148_hal_start_1_mod_out();
	ads1148_hal_drdy_1_mod_in();
}

void ads1148_hal_port_deinit_chip1(void)
{
	
	//ads1148_hal_sck_mod_in();
	//ads1148_hal_din_mod_in();
	//ads1148_hal_dout_mod_in();
    /*
	ads1148_hal_cs_1_mod_in();
	ads1148_hal_start_1_mod_in();
	ads1148_hal_drdy_1_mod_in();	
	*/

	
	ads1148_hal_cs_1_mod_out();
	//ads1148_hal_cs_1_set_low();
	
	ads1148_hal_start_1_mod_out();
	ads1148_hal_start_1_set_low();
	
	ads1148_hal_drdy_1_mod_out();
	ads1148_hal_drdy_1_set_low();	


}
/*

*/
#if( ADS1148_SCK_IDLE_STATUE == 0)
volatile uint8_t ads1148_hal_write_read_byte(volatile uint8_t x)
{
	volatile uint8_t i,ret=0;
	//ads1148_hal_sck_set_low();
	for(i=0;i<8;i++){
		//delay_us(1);
        __some_nop();
        __some_nop();
		ret<<=1;
		ads1148_hal_sck_set_hight();
		if(ads1148_hal_din_get()){
			ret|=1;
		}
		//delay_us(1);
        //__some_nop();
		__some_nop();
		if(x&0x80){
			ads1148_hal_dout_set_hight();
		}else{
			ads1148_hal_dout_set_low();
		}
		x<<=1;
        __some_nop();
		//__some_nop();
		ads1148_hal_sck_set_low();
	}
	ads1148_hal_sck_set_low();
	return ret;
}
#else
volatile uint8_t ads1148_hal_write_read_byte(uint8_t x)
{
	volatile uint8_t i,ret=0;
	ads1148_hal_sck_set_hight();
	for(i=0;i<8;i++){
		if(x&0x80){
			ads1148_hal_dout_set_hight();
		}else{
			ads1148_hal_dout_set_low();
		}
        x<<=1;
		ads1148_hal_sck_set_low();
		ret<<=1;
		ads1148_hal_sck_set_hight();
		if(ads1148_hal_din_get()){
			ret|=1;
		}
	}
	ads1148_hal_sck_set_hight();
	return ret;
}
#endif	
void ads1148_hal_pwr_off(void)
{
    set_port_mode_dig(ADS1148_PWR_PORT,ADS1148_PWR_PIN);
	set_port_mode_out(ADS1148_PWR_PORT,ADS1148_PWR_PIN);
	set_port_value_hight(ADS1148_PWR_PORT,ADS1148_PWR_PIN);	
}
void ads1148_hal_pwr_on(void)
{
    set_port_mode_dig(ADS1148_PWR_PORT,ADS1148_PWR_PIN);
	set_port_mode_out(ADS1148_PWR_PORT,ADS1148_PWR_PIN);
	set_port_value_low(ADS1148_PWR_PORT,ADS1148_PWR_PIN);	
}

