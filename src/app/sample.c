#include "../includes/includes.h"
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