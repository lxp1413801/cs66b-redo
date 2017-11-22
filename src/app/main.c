#include "../includes/includes.h"
EventGroupHandle_t threadMainEvent;

void m_system_init(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    //TMR2_Initialize();
    RTCC_Initialize();
    //TMR1_Initialize();    
}
void thread_main_pre(void)
{
    kz_vadd_on();
    key_init();
    
    lcd_init();
    ui_disp_all_on();
    osDelay(1000);
    ui_disp_all_off();
    osDelay(1000);
    
    
}
void thread_main( void * pvParameters )
{
    //configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    EventBits_t event;
    thread_main_pre();
    
	ui_disp_start_cs600(4);
	data_init_all();
    thread_sample_create();
    while(1) {
        event=xEventGroupWaitBits(threadMainEvent,flg_ALL_BITS,pdTRUE,pdFALSE,portMAX_DELAY);
        if(event | flg_RTC_SECOND){
            __nop();
            __nop();    
        }
        if(event | flg_KEY_DOWN){
            key_process();
        }
    }
}
void thread_main_create(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;
 threadMainEvent = xEventGroupCreate();

    xReturned = xTaskCreate(thread_main, "NAME", configMINIMAL_STACK_SIZE*4, 	NULL, 	tskIDLE_PRIORITY, 	&xHandle );
    
   
    if(threadMainEvent== NULL){
        while(1){
            __nop();
            __nop();
        }
    }
}

void event_proess(void)
{
	if(event | flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		sample_process();
	}
}

int main(void)
{
    uint8_t str[4]={0x11,0x22,0x33,0x44};
    uint8_t i=0,j=0;
    // initialize the device
    //SYSTEM_Initialize();
    m_system_init();

     thread_main_create();
      vTaskStartScheduler();

    while (1){
        __nop();
         __nop();
    }
    return -1;
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    
}   
void vApplicationIdleHook( void )
{
    
}

/**
 End of File
*/