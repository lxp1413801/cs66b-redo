#include "../includes/includes.h"
//EventGroupHandle_t threadMainEvent;
#define main_delay_ms(ms) ticker_ms_delay(ms)

volatile uint8_t blShowTime=60;
volatile uint16_t sleepHalfSec=1000;
volatile bool sampling=true;

void m_system_init(void)
{
	PIN_MANAGER_Initialize();
	OSCILLATOR_Initialize();
	INTERRUPT_Initialize();
	TMR2_Initialize();
	TMR1_Initialize();
	RTCC_Initialize();  
}

void thread_main_pre(void)
{
    
    kz_vadd_on();
    key_init();

    lcd_init();
    ui_disp_all_on();
    __nop();
    __nop();
    main_delay_ms(1000);
    // ui_disp_all_off();
    // main_delay_ms(1000);

	//ui_disp_start_cs600(4);

	data_init_all();    
	
	gpio_status_pins_mod_in();
}

/*
void event_proess(void)
{
	if(event | flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		sample_process();
	}
}
*/
void event_sample_real_time_mode(void)
{
	if(stSysData.sleepPeriod>0)return;

	noEventTimeOut=NO_EVENT_TIME_MAX;
	if(event & flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		ads1148_post_sleep();
		kz_vadd_on();
		sample_process();			
	}             

}

void event_sample_sleep_wake_mode(void)
{
    uint8_t t8=0;
    uint32_t t32=0;
	if(stSysData.sleepPeriod==0)return;
	if(sleepHalfSec<(stSysData.sleepPeriod)*2)return ;
    //if( !T1CONbits.TON )TMR1_Start();
    //ticker_ms_set(0);
	sleepHalfSec=0;
	kz_vadd_on();
	ads1148_post_sleep();
	delay_ms(1);
	do{
		t8=sample_process();
	}while(t8!=0);
	ads1148_pre_sleep();
	//t32=ticker_ms_get();
    if(event &  flg_RTC_SECOND)event &=  ~flg_RTC_SECOND;
    __nop();
    __nop();
}

void event_enter_sleep(void)
{
	if(noEventTimeOut==0 && stSysData.sleepPeriod>0){
		__nop();
		__nop();
		//pre_system_sleep_deinit_all_pins();
		
		pre_system_sleep();
		ads1148_pre_sleep();
		
		TMR1_Stop();
		TMR2_Stop();	
		
		Sleep();
		__nop();
		__nop();              
	}   
}
int main(void)
{

    
    //SYSTEM_Initialize(); 
    m_system_init();
    pre_system_sleep_deinit_all_pins();
    thread_main_pre();

    ads1148_init_all_obj();
	ads1148_init_device(); 
    blShowTime=stSysData.lcdShowTm;
	blShowTime*=2;

    while (1){

		
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
        
		event_sample_real_time_mode();
		event_sample_sleep_wake_mode();		
        event_enter_sleep();
    }
    return -1;
}
/*
int main(void)
{

    uint8_t t8=0;
    //SYSTEM_Initialize(); 
    m_system_init();
    pre_system_sleep_deinit_all_pins();
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
                ads1148_post_sleep();
                kz_vadd_on();
                sample_process();			
            }             
        }else{
            if(sleepHalfSec>(stSysData.sleepPeriod)*2){
                sleepHalfSec=0;
                kz_vadd_on();
                ads1148_post_sleep();
                delay_ms(1);
                do{
                    t8=sample_process();
                }while(t8!=0);
                ads1148_pre_sleep();
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
			//ui_disp_menu();
			if(lcdTwinkle>0)lcdTwinkle--;
			if(blShowTime>0)blShowTime--;
			if(blShowTime==0){
				back_night_off();
			}
            if(noEventTimeOut)noEventTimeOut--;
            if(noEventTimeOut<blShowTime)noEventTimeOut=blShowTime;
            if(stSysData.sleepPeriod)sleepHalfSec++;
		}
		event_enter_sleep();
    }
    return -1;
}
*/
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