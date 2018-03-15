#include "../configs/configs.h"
#include "../api/sysdata.h"
#include "gpio_config.h"
#include "gpio.h"
#include "lcd.h"
#include "i2c.h"
#include "../soc/delay.h"

volatile bool lcdBlackNightOn=false;
volatile bool kzAvddOn=false;

uint8_t volatile exFunctionSta=0;
#if HW_VER >= HWVER303
/*
void kz_qy_vcc_config(void)
{
	set_port_mode_dig(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);
	set_port_mode_out(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);
	set_port_value_hight(STATUS_MA_PORT,STATUS_MA_PINS);	
}
*/
void  kz_qy_vcc_enable(void)
{
	set_port_mode_dig(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);
	set_port_mode_out(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);	
	set_port_value_low(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);	
}
void kz_qy_vcc_disable(void)
{
	set_port_mode_an(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);
	set_port_mode_in(KZ_QY_VCC_PORT,KZ_QY_VCC_PINS);	
}
#endif	
void kz_vadd_on(void)
{
    if(kzAvddOn)return;
	//set_portg_odc_en(PIN9);
	set_portg_mode_dig(PIN9);

	set_portg_mode_out(PIN9);
	
	#if HW_VER >= HWVER303
	set_portg_value_hight(PIN9);
	#else
    set_portg_value_low(PIN9);
	#endif
	
	kzAvddOn=true;
    //delay_ms(10);
}
void kz_vadd_off(void)
{
	set_portg_mode_dig(PIN9);
	//set_portg_mode_in(PIN9);
	set_portg_mode_out(PIN9);
	#if HW_VER >= HWVER303
	set_portg_value_low(PIN9);
	#else
	set_portg_value_hight(PIN9);
	#endif
	kzAvddOn=false;
}
void back_night_on(void)
{
    if(!kzAvddOn)kz_vadd_on();
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_hight(PIN11);
	//
	lcdBlackNightOn=true;
}
void back_night_off(void)
{
	set_portb_mode_dig(PIN11);
	set_portb_mode_out(PIN11);
	set_portb_value_low(PIN11);
	//set_portb_mode_in(PIN11);
	lcdBlackNightOn=false;
}

void status_ma_mode_in(void)
{
	set_port_mode_dig(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_mode_in(STATUS_MA_PORT,STATUS_MA_PINS);
}

uint8_t  get_ex_function_status(void)
{
	uint8_t t8=0;
	if(!(get_port_value(STATUS_485_PORT,STATUS_485_PINS)))t8 |= EX_FUNCTION_485_EN;
	if(!(get_port_value(STATUS_MA_PORT,STATUS_MA_PINS)))t8 |= EX_FUNCTION_ILOOP_EN;
	if(!(get_port_value(STATUS_BJ_PORT,STATUS_BJ_PINS)))t8 |= EX_FUNCTION_BJ_EN;
	return t8;
}
void all_status_pins_mod_in(void)
{
	set_port_mode_dig(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_mode_in(STATUS_MA_PORT,STATUS_MA_PINS);
	
	set_port_mode_dig(STATUS_GSM_PORT,STATUS_GSM_PINS);
	set_port_mode_in(STATUS_GSM_PORT,STATUS_GSM_PINS);
	
	set_port_mode_dig(STATUS_BJ_PORT,STATUS_BJ_PINS);
	set_port_mode_in(STATUS_BJ_PORT,STATUS_BJ_PINS);

	set_port_mode_dig(STATUS_485_PORT,STATUS_485_PINS);
	set_port_mode_in(STATUS_485_PORT,STATUS_485_PINS);
}
void all_status_pins_mod_out(void)
{
	set_port_mode_dig(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_mode_out(STATUS_MA_PORT,STATUS_MA_PINS);
	set_port_value_hight(STATUS_MA_PORT,STATUS_MA_PINS);
	
	set_port_mode_dig(STATUS_GSM_PORT,STATUS_GSM_PINS);
	set_port_mode_out(STATUS_GSM_PORT,STATUS_GSM_PINS);
	set_port_value_hight(STATUS_GSM_PORT,STATUS_GSM_PINS);
	
	set_port_mode_dig(STATUS_BJ_PORT,STATUS_BJ_PINS);
	set_port_mode_out(STATUS_BJ_PORT,STATUS_BJ_PINS);
	set_port_value_hight(STATUS_BJ_PORT,STATUS_BJ_PINS);
	
	set_port_mode_dig(STATUS_485_PORT,STATUS_485_PINS);
	set_port_mode_out(STATUS_485_PORT,STATUS_485_PINS);
	set_port_value_hight(STATUS_485_PORT,STATUS_485_PINS);
}

void rs_485_set_rx(void)
{
	set_port_mode_dig(RS_485_RE_PORT,RS_485_RE_PINS);
	set_port_mode_out(RS_485_RE_PORT,RS_485_RE_PINS);
	set_port_value_low(RS_485_RE_PORT,RS_485_RE_PINS);
}
void rs_485_set_tx(void)
{
	set_port_mode_dig(RS_485_RE_PORT,RS_485_RE_PINS);
	set_port_mode_out(RS_485_RE_PORT,RS_485_RE_PINS);
	set_port_value_hight(RS_485_RE_PORT,RS_485_RE_PINS);
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

void ain_solor_config(void) 
{
    set_port_mode_an(ANI_SOLOR_PORT,ANI_SOLOR_PIN); 
    set_port_mode_in(ANI_SOLOR_PORT,ANI_SOLOR_PIN); 
}
void all_bj_init(void)
{
	set_port_mode_dig(BJ_PORT,ALL_BJ_PINS);
	set_port_mode_out(BJ_PORT,ALL_BJ_PINS);
	set_port_value_low(BJ_PORT,ALL_BJ_PINS);	
	set_port_value_hight(BJ_V_PORT,BJ_V_PIN);
}

void all_bj_disable(void)
{
	set_port_mode_dig(BJ_PORT,ALL_BJ_PINS);
	set_port_mode_out(BJ_PORT,ALL_BJ_PINS);
	set_port_value_low(BJ_PORT,ALL_BJ_PINS);	
	//set_port_mode_in(BJ_PORT,ALL_BJ_PINS);
}

void bj_1_on(void)
{
	set_port_value_hight(BJ_1_PORT,BJ_1_PIN);
}

void bj_2_on(void)
{
	set_port_value_hight(BJ_2_PORT,BJ_2_PIN);
}

void bj_3_on(void)
{
	set_port_value_hight(BJ_3_PORT,BJ_3_PIN);
}

void bj_4_on(void)
{
	set_port_value_hight(BJ_4_PORT,BJ_4_PIN);
}

void bj_1_off(void)
{
	set_port_value_low(BJ_1_PORT,BJ_1_PIN);
}

void bj_2_off(void)
{
	set_port_value_low(BJ_2_PORT,BJ_2_PIN);
}

void bj_3_off(void)
{
	set_port_value_low(BJ_3_PORT,BJ_3_PIN);
}

void bj_4_off(void)
{
	set_port_value_low(BJ_4_PORT,BJ_4_PIN);
}

void bj_all_on(void)
{
	set_port_value_hight(BJ_V_PORT,BJ_V_PIN);
	set_port_value_hight(BJ_PORT,ALL_BJ_PINS);
}

void bj_all_off(void)
{
	set_port_value_low(BJ_V_PORT,BJ_V_PIN);
	set_port_value_low(BJ_PORT,ALL_BJ_PINS);
}
void bj_output(void)
{
//#if BJ_BAORD_EN
    uint16_t t16;
	if(!(exFunctionSta & EX_FUNCTION_BJ_EN))return;
    t16=deviceEvent.t16;
    if(t16 & 0x0f){
        set_port_value_hight(BJ_V_PORT,BJ_V_PIN);
    }
    
    if(t16 & 0x01)bj_1_on();
    else
        bj_1_off();
    
    if(t16 & 0x02)bj_2_on();
    else
        bj_2_off(); 
    
    if(t16 & 0x04)bj_3_on();
    else
        bj_3_off();   

    if(t16 & 0x08)bj_4_on();
    else
        bj_4_off();  
//#endif
}
void run_status_init(void)
{
	set_port_mode_dig(RUN_STATUS_PORT,RUN_STATUS_PINS);
	set_port_mode_out(RUN_STATUS_PORT,RUN_STATUS_PINS);
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

void unused_pins_deinit(void)
{
	//set_port_mode_dig(FLOAT_RF7_PORT,FLOAT_RF7_PIN);
	set_port_mode_out(FLOAT_RF7_PORT,FLOAT_RF7_PIN);
	set_port_value_hight(FLOAT_RF7_PORT,FLOAT_RF7_PIN);	
	
	set_port_mode_dig(FLOAT_RD1_PORT,FLOAT_RD1_PIN);
	set_port_mode_out(FLOAT_RD1_PORT,FLOAT_RD1_PIN);
	set_port_value_hight(FLOAT_RD1_PORT,FLOAT_RD1_PIN);	
#if HW_VER >= HWVER303
	kz_qy_vcc_disable();
#else
	set_port_mode_dig(FLOAT_RB6_PORT,FLOAT_RB6_PIN);
	set_port_mode_out(FLOAT_RB6_PORT,FLOAT_RB6_PIN);
	set_port_value_hight(FLOAT_RB6_PORT,FLOAT_RB6_PIN);		
#endif
}

void gsm_en_pins_config(void)
{

	
}

void gsm_module_enable(void)
{
	set_port_mode_dig(GSM_EN_PORT,GSM_EN_PINS);
	set_port_mode_out(GSM_EN_PORT,GSM_EN_PINS);	
	set_port_value_hight(GSM_EN_PORT,GSM_EN_PINS);	
}
void gsm_module_disable(void)
{
	set_port_mode_dig(GSM_EN_PORT,GSM_EN_PINS);
	set_port_mode_in(GSM_EN_PORT,GSM_EN_PINS);		
}

void gsm_rst_pins_config(void)
{
}

void gsm_rst_enable(void)
{
	set_port_mode_dig(GSM_RST_PORT,GSM_RST_PINS);
	set_port_mode_out(GSM_RST_PORT,GSM_RST_PINS);	
	set_port_value_hight(GSM_RST_PORT,GSM_RST_PINS);	
}

void gsm_rst_release(void)
{
	set_port_mode_dig(GSM_RST_PORT,GSM_RST_PINS);
	set_port_mode_in(GSM_RST_PORT,GSM_RST_PINS);	
}

void gps_en_pins_config(void)
{
}

void gps_module_enable(void)
{
	//set_port_mode_dig(GPS_EN_PORT,GPS_EN_PINS);
	set_port_mode_out(GPS_EN_PORT,GPS_EN_PINS);
	set_port_value_hight(GPS_EN_PORT,GPS_EN_PINS);	
}

void gps_module_disable(void)
{
	//set_port_mode_dig(GPS_EN_PORT,GPS_EN_PINS);
	set_port_mode_in(GPS_EN_PORT,GPS_EN_PINS);		
}

void gps_rst_pins_config(void)
{
}

void gps_rst_enable(void)
{
	set_port_mode_dig(GPS_RST_PORT,GPS_RST_PINS);
	set_port_mode_out(GPS_RST_PORT,GPS_RST_PINS);	
	set_port_value_hight(GPS_RST_PORT,GPS_RST_PINS);		
}

void gps_rst_release(void)
{
	set_port_mode_dig(GPS_RST_PORT,GPS_RST_PINS);	
	set_port_mode_in(GPS_RST_PORT,GPS_RST_PINS);		
}

void pre_system_sleep(void)
{
	//pre_system_sleep_deinit_all_pins();
	//all_status_pins_mod_in();
	all_status_pins_mod_out();
	all_bj_disable();
	//bj_all_off();
	check_solor_set_low();
	back_night_off();
	kz_vadd_off();
    iic_pins_deinit();
    run_status_off();
    ad421_chip1_pins_deinit();
    ad421_chip0_pins_deinit();
	
	rs_485_set_rx();
	unused_pins_deinit();
    IFS0=0x00;
    IFS1=0x00;
    IFS2=0x00;
    IFS3=0x00;
    IFS4=0x00;
    IFS5=0x00;    
    IFS6=0x00;
    IFS7=0x00;        
    //lcd_off();
    //U1MODEbits.UARTEN=0;
    //U2MODEbits.UARTEN=0;
    asm("NOP");
    asm("NOP");   
}