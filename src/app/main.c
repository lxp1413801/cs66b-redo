#include "../includes/includes.h"
//EventGroupHandle_t threadMainEvent;
#define main_delay_ms(ms) ticker_ms_delay(ms)

volatile uint8_t blShowTime=60;
volatile uint16_t sleepHalfSec=1000;
volatile bool sampling=true;

void m_system_init(void)
{
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    TMR2_Initialize();
    RTCC_Initialize();
    TMR1_Initialize();    
}

void thread_main_pre(void)
{
    kz_vadd_on();
    key_init();
    
    lcd_init();
    ui_disp_all_on();
    //while(1);
    __nop();
    __nop();
    main_delay_ms(1000);
    ui_disp_all_off();
    main_delay_ms(1000);

	//ui_disp_start_cs600(4);
	data_init_all();    
	
	gpio_status_pins_mod_in();
}
/*
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
    //uint8_t str[4]={0x11,0x22,0x33,0x44};
    //uint8_t i=0,j=0;
    // initialize the device
    uint8_t t8=0;
    SYSTEM_Initialize();
    //m_system_init();

	//thread_main_create();
	//vTaskStartScheduler();
	
    thread_main_pre();
	
    ads1148_init_all_obj();
	ads1148_init_device(); 

	
    blShowTime=stSysData.lcdShowTm;
	blShowTime*=2;
    while (1){
        if(stSysData.sleepPeriod==0){
            noEventTimeOut=NO_EVENT_TIME_MAX;
            if(event & flg_TICKER_10MS_PER){
                event &= ~flg_TICKER_10MS_PER;
                kz_vadd_on();
                ads1148_post_sleep();
                sample_process();			
            }             
        }else{
            if(sleepHalfSec>(stSysData.sleepPeriod)*2){
                sleepHalfSec=0;
                kz_vadd_on();
                ads1148_post_sleep();
                do{
                    t8=sample_process();
                }while(t8!=0);
            }
            if(noEventTimeOut==0){
                __nop();
                __nop();
                ads1148_pre_sleep();
                pre_system_sleep();
                Sleep();
                __nop();
                __nop();                
            }            
        }
		if(event & flg_KEY_DOWN){
			//event &= ~flg_KEY_DOWN;
            noEventTimeOut=NO_EVENT_TIME_MAX;
            if( !T1CONbits.TON )TMR1_Start();
			key_process();
		}
		if(event &  flg_RTC_SECOND){
			event &=  ~flg_RTC_SECOND;
			ui_disp_menu();
			if(lcdTwinkle>0)lcdTwinkle--;
			if(blShowTime>0)blShowTime--;
			if(blShowTime==0){
				back_night_off();
			}
            if(noEventTimeOut)noEventTimeOut--;
            if(noEventTimeOut<blShowTime)noEventTimeOut=blShowTime;
            if(stSysData.sleepPeriod)sleepHalfSec++;
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