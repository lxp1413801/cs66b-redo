#include "../includes/includes.h"
volatile uint8_t sampleIndex=0x00;

void samlpe_chip0_channle_diff_press(void)
{
	
}

void samlpe_chip0_channle_press(void)
{
	
}
void samlpe_chip0_channle_temperature(void)
{
	
}
/*
void samlpe_chip0_channle_gain_calib(void)
{
	uint32_t tm;
    volatile int32_t t32=0;
    volatile int16_t t16;
	uint8_t i;
	tm=xTaskGetTickCount();
	ads1148_start_convert(&ads1148Chip1);
	delay_us(5);
	for(i=0;i<8;i++){
		ads1148_waite_convert(&ads1148Chip1);
        //delay_us(5);
        vPortEnterCritical();
		t16=ads1148_read_data(&ads1148Chip1);
        vPortExitCritical();
        t32=t32+(int32_t)t16;
        __nop();
        __nop();        
	}
	t32/=i;
	ads1148_stop_convert(&ads1148Chip1);
	tm=xTaskGetTickCount()-tm;
	__nop();
	__nop();
}
void sample_fast_mode(void)
{
	uint8_t t8;
	t8=sampleIndex;
	switch(t8){
		case 0x00:samlpe_chip0_channle_diff_press();break;
		case 0x01:samlpe_chip0_channle_press();break;
		case 0x03:samlpe_chip0_channle_temperature();break;
		default:break;
	}
}

void thread_sample( void * pvParameters )
{
	ads1148_init_all_obj();
	ads1148_init_chip_regs(&ads1148Chip0);
	ads1148_init_chip_regs(&ads1148Chip1);
	while(1){
		osDelay(10);
		samlpe_chip0_channle_gain_calib();
		__nop();
		__nop();
	}
}
void thread_sample_void(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;


    xReturned = xTaskCreate(
		thread_sample, 
		"samlpe", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		1, 
		&xHandle );	
}
*/
