#include "../includes/includes.h"

void ui_disp_start_cs600(uint8_t dly)
{
	uint8_t t8;
	uint8_t buf[6]="-00-";
	lcd_disp_clear_buffer();
	lcd_show_string_l0((uint8_t*)"cs66");
	//lcd_disp_logo(true);
	t8=dly;
	if(t8<1)t8=1;
	while(t8){
		m_int8_2_hex(buf+1,t8-1);
		buf[4]='\0';
		lcd_show_string_l1(buf);
        //lcd_disp_level(60);
		lcd_disp_refresh();
		//ticker_dly(1000);
		osDelay(1000);
		t8--;
	}
}