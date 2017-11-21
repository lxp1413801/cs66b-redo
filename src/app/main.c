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

void thread_main( void * pvParameters )
{
    //configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    EventBits_t event;
    kz_vadd_on();
	
    ui_disp_start_cs600(4);
    thread_sample_void();
    while(1) {
        event=xEventGroupWaitBits(threadMainEvent,flg_ALL_BITS,pdTRUE,pdFALSE,portMAX_DELAY);
        if(event | flg_RTC_SECOND){
            __nop();
            __nop();    
        }
        if(event | flg_KEY_DOWN){
            __nop();
            __nop();
        }

        osDelay(500);
        back_night_off();
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
    
    threadMainEvent = xEventGroupCreate();
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
    key_init();
    lcd_init();
    lcd_disp_clear_buffer();
    lcd_show_string((uint8_t*)"77777777");
    lcd_show_string_sm((uint8_t*)"123");
    lcd_show_string_ex((uint8_t*)"123");
    lcd_disp_refresh();
     thread_main_create();
      vTaskStartScheduler();
    m_flash_erase(user_FLASH_ADDR_START,4);
    m_flash_write(user_FLASH_ADDR_START,str,4);
    m_flash_read(user_FLASH_ADDR_START,str,4);
	__nop();
    __nop();
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

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    
}   
void vApplicationIdleHook( void )
{
    
}

/**
 End of File
*/