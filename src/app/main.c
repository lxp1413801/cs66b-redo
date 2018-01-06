#include "../includes/includes.h"
//EventGroupHandle_t threadMainEvent;
//#define main_delay_ms(ms) ticker_ms_delay(ms)

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
    ticker_ms_delay(1000);
	data_init_all();    
    //
     //ui_disp_all_off();
    // main_delay_ms(1000);

	//ui_disp_start_cs600(6);

	//
	
	//gpio_status_pins_mod_in();
    all_status_pins_mod_in();
	run_status_init();
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
	if(stSysData.sleepPeriod>0 && menu==0)return;

	noEventTimeOut=NO_EVENT_TIME_MAX;
	if(event & flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		ads1148_post_sleep();
		if(!kzAvddOn){
			kz_vadd_on();
			delay_ms(30);
		}
		sample_process();			
	}
    if( !T2CONbits.TON )TMR2_Start();
}
/*
void event_sample_sleep_wake_mode(void)
{
    uint8_t t8=0;
    uint32_t t32=0;
	if(stSysData.sleepPeriod==0 || menu!=0)return;

	if(sleepHalfSec<(stSysData.sleepPeriod)*2)return ;
    if( !T1CONbits.TON )TMR1_Start();
    ticker_ms_set(0);
	sleepHalfSec=0;
	
	ads1148_post_sleep();
    kz_vadd_on();
	delay_ms(30);
	do{
		t8=sample_process();
	}while(t8!=0);
	ads1148_pre_sleep();
	t32=ticker_ms_get();
    //if(event &  flg_RTC_SECOND)event &=  ~flg_RTC_SECOND;
    __nop();
    __nop();
}
*/
volatile lpwSampleStatus=0;
void event_sample_sleep_wake_mode(void)
{
    uint8_t t8=0;
    uint32_t t32=0;
	if(stSysData.sleepPeriod==0 || menu!=0)return;

	if(sleepHalfSec<(stSysData.sleepPeriod)*2)return ;
    if( !T1CONbits.TON )TMR1_Start();
    ticker_ms_set(0);
	sleepHalfSec=0;
	
	ads1148_post_sleep();
    kz_vadd_on();
	delay_ms(30);
	do{
		
		t8=sample_process();
		#if ADS1148_CHIP_OTRHER_ONE_ENABLE 
		if(t8==0 || t8==0x0c)break;
		#else
		if(t8==0)break;	
		#endif

	}while(1);
	ads1148_pre_sleep();
	t32=ticker_ms_get();
    //if(event &  flg_RTC_SECOND)event &=  ~flg_RTC_SECOND;
    __nop();
    __nop();
}
void event_iloop_out_put(void)
{
	#if I_LOOP_BOARD
	uint16_t t16;
	uint32_t t32;
	if(stSysData.sleepPeriod>0)return;
	t32=globleHalfSec;
	if(t32 & 0x07ul)return;
	t16=calc_dpr_iloop_out_put();
	ad421ObjChip0.pins_init();
	ad421_chip0_set_idac_value(t16);
	
	t16=calc_pr_iloop_out_put();
	ad421ObjChip1.pins_init();
	ad421_chip1_set_idac_value(t16);	
	#endif
}
void event_enter_sleep(void)
{
	if(menu!=0)return;
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
    SYSTEM_Initialize(); 

    //m_system_init();
    //pre_system_sleep_deinit_all_pins();
	#if BJ_BAORD_EN
	all_bj_init();
	bj_all_on();
	#endif
    thread_main_pre();
	
	all_bj_disable();
	
    ads1148_init_all_obj();
	ads1148_init_device(); 
    blShowTime=stSysData.lcdShowTm;
	blShowTime*=2;
	#if I_LOOP_BOARD 
    ad421_all_obj_init();
    //ad421_test();
	#endif
     //ui_disp_all_off();
    // main_delay_ms(1000);

	ui_disp_start_cs600(6);
    while (1){
		if(event & flg_KEY_DOWN){
			//event &= ~flg_KEY_DOWN;
            noEventTimeOut=NO_EVENT_TIME_MAX;
            if( !T1CONbits.TON )TMR1_Start();
			key_process();
		}
		if(event &  flg_RTC_SECOND){
			event &=  ~flg_RTC_SECOND;

			if(lcdTwinkle>0)lcdTwinkle--;
			if(blShowTime>0)blShowTime--;
			if(blShowTime==0){
				back_night_off();
			}
            if(noEventTimeOut)noEventTimeOut--;
            if(noEventTimeOut<blShowTime)noEventTimeOut=blShowTime;
            if(stSysData.sleepPeriod)sleepHalfSec++;
            
			run_status_on();
            ui_disp_menu();
            /*
            if((stSysData.sleepPeriod==0 || noEventTimeOut || sampleFreashFlg)){
                ui_disp_menu();
                sampleFreashFlg=false;
            }else{
                delay_us(100);
            }
             * */
			run_status_off();            
            event_iloop_out_put();
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