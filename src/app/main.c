#include "../includes/includes.h"


void m_system_init(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    //TMR2_Initialize();
    RTCC_Initialize();
    //TMR1_Initialize();    
}
/*
void thread_main( void * pvParameters )
{
    //configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    kz_vadd_on();
	thread_sample_void();
    for( ;; )
    {

        //task_delay_ms(500);
        osDelay(500);
        back_night_off();
        //task_delay_ms(500);
        osDelay(500);
        back_night_on();
    }
}
void thread_main_create(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;


    xReturned = xTaskCreate(
		thread_main, 
		"NAME", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		tskIDLE_PRIORITY, 
		&xHandle );
}
*/
void event_proess(void)
{
	if(event | flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		sample_process();
	}
}
int main(void)
{
    uint8_t str[4]={0};
    uint8_t i=0,j=0;
    // initialize the device
    SYSTEM_Initialize();
    //m_system_init();
    lcd_init();
    lcd_disp_clear_buffer();
    lcd_show_string((uint8_t*)"77777777");
    lcd_show_string_sm((uint8_t*)"123");
    lcd_show_string_ex((uint8_t*)"123");
    lcd_disp_refresh();
    // thread_main_create();
     // vTaskStartScheduler();
     
	asm("NOP");
    ads1148_init_all_obj();
	ads1148_init_device();

    while (1){
		if(event | flg_TICKER_10MS_PER){
			event &= ~flg_TICKER_10MS_PER;
			sample_process();
		}
        
    }
    return -1;
}
/*
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    
}   
void vApplicationIdleHook( void )
{
    
}
*/
/**
 End of File
*/