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

void sample_fast_mode(void)
{
	uint8_t t8;
	t8=sampleIndex;
	switch(t8){
		case 0x00:samlpe_chip0_channle_diff_press();break;
		case 0x01:samlpe_chip0_channle_press();break;
		case 0x03:samlpe_chip0_channle_temperature;break;
		default:break;
	}
}

void thread_sample( void * pvParameters )
{
	
	while(1){
		osDelay(100);
		__nop();
		__nop();
	}
}
void thread_sample_void(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
		thread_sample, 
		"samlpe", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		1, 
		&xHandle );	
}
