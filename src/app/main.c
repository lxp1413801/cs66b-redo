#include "../includes/includes.h"
//EventGroupHandle_t threadMainEvent;
//#define main_delay_ms(ms) ticker_ms_delay(ms)
volatile uint16_t lcdOnTime=60;
volatile uint8_t blShowTime=60;
volatile uint16_t sleepSec=1000;
volatile bool sampling=true;

void m_system_init(void)
{
    //PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    //INTERRUPT_Initialize();
    //UART2_Initialize();
    //UART1_Initialize();
    //ADC1_Initialize();
    //TMR2_Initialize();
    //RTCC_Initialize();
    //TMR1_Initialize();
}

void thread_main_pre(void)
{
	all_status_pins_mod_in();
	exFunctionSta=get_ex_function_status();
	//#if BJ_BAORD_EN
	all_bj_init();
	bj_all_off();
	//#endif
	
	
    kz_vadd_on();
    key_init();
    lcd_init();
    __nop();
    __nop();
    ticker_ms_delay(1000);

	  
	ui_disp_start_cs600(6);
	data_init_all();  
	__nop();
	__nop();
    all_status_pins_mod_in();
	run_status_init();
	__nop();
	__nop();
	
	//all_bj_disable();
	
    ads1148_init_all_obj();
	ads1148_init_device(); 
	
    blShowTime=stSysData.blOnTm;
	blShowTime*=2;
	
	//#if I_LOOP_BOARD 
    ad421_all_obj_init();
    ad421ObjChip0.pins_deinit();
    ad421ObjChip1.pins_deinit();
	//#endif	
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
	if(stSysData.sleepPeriod>0 && menu==0 )return;
	ads1148_post_sleep();
	//noEventTimeOut=NO_EVENT_TIME_MAX;
	if(event & flg_TICKER_10MS_PER){
		event &= ~flg_TICKER_10MS_PER;
		ads1148_post_sleep();
		if(!kzAvddOn){
			kz_vadd_on();
			delay_ms(30);
		}
		sample_process();			
	}
    TMR2_Start();
}
/*
void event_sample_sleep_wake_mode(void)
{
    uint8_t t8=0;
    uint32_t t32=0;
	if(stSysData.sleepPeriod==0 || menu!=0)return;

	if(sleepSec<(stSysData.sleepPeriod)*2)return ;
    if( !T1CONbits.TON )TMR1_Start();
    ticker_ms_set(0);
	sleepSec=0;
	
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

void event_sample_sleep_wake_mode(void)
{
    uint8_t t8=0;
    uint32_t t32=0;
	//return;
    if(stSysData.sleepPeriod == WAKE_UP_SAMPLE_FORBID)return;
	if(stSysData.sleepPeriod==0 || menu!=0 )return;
    //if(stSysData.sleepPeriod)sleepSec++;
    sleepSec++;
	if(sleepSec<(stSysData.sleepPeriod))return ;
	
    if( !T1CONbits.TON )TMR1_Start();
    ticker_ms_set(0);
	sleepSec=0;
	
	//delay_ms(30);
    kz_vadd_on();
    ads1148_post_sleep();
	delay_ms(30);    
	do{
		t8=sample_process();
		// #if ADS1148_CHIP_OTRHER_ONE_ENABLE 
		// if(t8==0 || t8==0x0c)break;
		// #else
		// if(t8==0)break;	
		// #endif
		if(t8==0)break;	

	}while(1);   
	ads1148_pre_sleep();
	t32=ticker_ms_get();
    TMR1_Stop();
    if(blShowTime==0)kz_vadd_off();
    //if(event &  flg_RTC_SECOND)event &=  ~flg_RTC_SECOND;
    __nop();
    __nop();
}
void event_iloop_out_put_adj(void)
{
	//#if I_LOOP_BOARD
	int32_t ad421value;
	//uint32_t t32;
	int16_t t16;
	if(!(exFunctionSta & EX_FUNCTION_ILOOP_EN))return;
	if(stSysData.sleepPeriod>0){
		return;
	};
	if(menu!=MENU_SET_ILOOP_ADJUST)return;
	t16=*((int16_t*)(&adjValue));
	
	switch(subMenu){
		case sub_MENU_SET_ILP_ADJUST_CH0_Lo:ad421value=0x4000+t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH0_Hi:ad421value=0x14000+t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Lo:ad421value=0x4000+t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Hi:ad421value=0x14000+t16;break;
		default:break;
	}
	switch(subMenu){
		case sub_MENU_SET_ILP_ADJUST_CH0_Lo:
		case sub_MENU_SET_ILP_ADJUST_CH0_Hi:ad421_chip0_set_idac_value_ex(ad421value);break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Lo:
		case sub_MENU_SET_ILP_ADJUST_CH1_Hi:ad421_chip1_set_idac_value_ex(ad421value);break;
		default:break;
	}  	
	//#endif
}
void event_iloop_out_put(void)
{
	//#if I_LOOP_BOARD
	int32_t ad421value;
	uint32_t t32;
    //int16_t t16;
	if(!(exFunctionSta & EX_FUNCTION_ILOOP_EN))return;
	if(stSysData.sleepPeriod>0){
        return;
    };
	if(menu==MENU_SET_ILOOP_ADJUST)return;
	t32=globleHalfSec;
	if((t32 & 0x07ul)==0x00ul ){

	ad421value=calc_dpr_iloop_out_put_ex();
    __nop();
    __nop();
	ad421ObjChip0.pins_init();
	//ad421_chip0_set_idac_value_ex(0x14000);
    ad421_chip0_set_idac_value(0x8000);
	ad421value=calc_pr_iloop_out_put_ex();
    __nop();
    __nop();    
	ad421ObjChip1.pins_init();
	//ad421_chip1_set_idac_value_ex(0x14000);
    ad421_chip0_set_idac_value(0x8000);
    __nop();
    __nop();
    }
	//#endif
}
void event_enter_sleep(void)
{
	if(menu!=0){
        //Idle();
        return;
    }
	if(noEventTimeOut==0 && stSysData.sleepPeriod>0){
		__nop();
		__nop();
		//pre_system_sleep_deinit_all_pins();
		ads1148_pre_sleep();
		pre_system_sleep();
		
		
		TMR1_Stop();
		TMR2_Stop();	
		//lcd_off();
		Sleep();
		__nop();
		__nop();    
		//delay_ms(10);
		
	}else{
        //Idle();
    }
}
uint8_t dispIndex=0x00;
void event_call_disp(void)
{	
    uint16_t t16=stSysData.sleepPeriod;
    t16<<=1;
    if(t16==0 || menu!=0 || noEventTimeOut>0){
        ui_disp_menu();
    }
    else{
        dispIndex++;
        if(dispIndex>=t16){
            dispIndex=0;
            //run_status_on();
            //ui_disp_menu();
            //run_status_off();
        }
        lcd_disp_refresh();
    }

}
void event_rtc_bl_off(void)
{
    if(blShowTime>0){
        blShowTime--;
        //if(blShowTime==0 && stSysData.blOnTm>0 && exFunctionSta==0)back_night_off();
        //不关闭被关的条件
		if(stSysData.blOnTm==0 && exFunctionSta!=0){
			return;
		}else{
			//关闭背光的条件
			if(blShowTime==0)back_night_off();
		}
    }    
}

void event_rtc_no_operation_tm_out(void)
{
	if(noEventTimeOut){
		noEventTimeOut--;
		if(noEventTimeOut==0)no_operation_save_exit();
	}
}

void event_rtc_lcd_off(void)
{
	if(lcdOnTime>0 &&  menu==0){
        lcdOnTime--;
        //lcdOnTime=(stSysData.lcdOnTime)*60;
        if(stSysData.lcdOnTime>0 && lcdOnTime==0 && exFunctionSta==0 ){
            lcd_off();
        }
    }
}
uint8_t uartTestStr[]="UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
int main(void)
{
	
    //m_system_init();
    //pre_system_sleep_deinit_all_pins();
    uint16_t t16;
    SYSTEM_Initialize(); 
    thread_main_pre();	
    while (1){
		if(event & flg_KEY_DOWN){
			//event &= ~flg_KEY_DOWN;
            noEventTimeOut=NO_EVENT_TIME_MAX;
            if( !T1CONbits.TON )TMR1_Start();
			key_process();
		}
		if(event &  flg_RTC_HALF_SECOND){
			event &=  ~flg_RTC_HALF_SECOND;

			if(lcdTwinkle>0)lcdTwinkle--;
            
            if(globleHalfSec & 0x01ul)event |= flg_RTC_SECOND;
            if(LCDCONbits.LCDEN)ui_disp_menu();
        }
        if(event & flg_RTC_SECOND){
            event &= ~flg_RTC_SECOND;
            event_rtc_bl_off();
			event_rtc_no_operation_tm_out();
			event_rtc_lcd_off();
			
            //if(noEventTimeOut<blShowTime)noEventTimeOut=blShowTime;
			event_sample_sleep_wake_mode();	
            
            
            //ui_disp_all_on();
            //lcd_disp_refresh();
            //event_call_disp();
			//run_status_off();
			if(menu!=MENU_SET_ILOOP_ADJUST){
				event_iloop_out_put();
			}else{
				event_iloop_out_put_adj();
			}
		}
        if(event & flg_MODBUS_RECEIVED){
            event &= ~flg_MODBUS_RECEIVED;
            t16=uart1ReceivedCount;
            m_mem_cpy_len(globleBuffer,uart1ReceivedBuf,t16);
            uart1ReceivedCount=0;
            modbus_response_process(globleBuffer,t16);
        }
		event_sample_real_time_mode();
		//event_sample_sleep_wake_mode();		
        event_enter_sleep();
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