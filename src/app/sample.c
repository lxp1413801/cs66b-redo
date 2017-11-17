#include "../includes/includes.h"
volatile uint8_t sampleIndex=0x00;
int16_t samlpeBuf[16];

volatile int16_t rtAdcValueDPrBridge;
volatile int16_t rtAdcValueDPrSignal;
volatile int16_t rtAdcValuePrBridge;
volatile int16_t rtAdcValuePrSignal;

volatile int16_t rtAdcValueTemperatureIn;
volatile int16_t rtAdcValueChip0Ref0;
volatile int16_t rtAdcValueChip0Ref1;

volatile int16_t rtAdcValuePrEx0Bridge;
volatile int16_t rtAdcValuePrEx0Signal;
volatile int16_t rtAdcValuePrEx1Bridge;
volatile int16_t rtAdcValuePrEx1Signal;

volatile int16_t rtAdcValueTemperatureEx;
volatile int16_t rtAdcValueChip1Ref0;
volatile int16_t rtAdcValueChip1Ref1;

int16_t samlpe_read_adc(ads1148Obj_t* obj,int16_t* buf,uint8_t len)
{
	
	uint8_t i=0;
	int16_t t16;
	int32_t	t32;
	for(i=0;i<2;i++){
		ads1148_waite_convert(obj);
		__nop();
	}
	for(i=0;i<len;i++){
		ads1148_waite_convert(obj);
		t16=ads1148_read_data(obj);
		samlpeBuf[i]=t16;
		t32+=(int32_t)t16;
	}
	t32/=i;
	if(buf){
		m_mem_cpy_len((uint8_t*)buf,(uint8_t*)samlpeBuf,len*sizeof(int16_t));
	}
	return (int16_t)t32;
}
void samlpe_chip0_channle_diff_press(void)
{
	
}

void samlpe_chip0_channle_press(void)
{
	
}

void samlpe_chip0_channle_temperature(void)
{
	//__builtin_tblwtl(0,0);
}

void samlpe_chip0_channle_ref0(void)
{
	
}

void samlpe_chip0_channle_ref1(void)
{
	
}

void samlpe_chip1_channle_press_ch0(void)
{
	
}

void samlpe_chip1_channle_press_ch1(void)
{
	
}

void samlpe_chip1_channle_temperature(void)
{
	
}

void samlpe_chip1_channle_ref0(void)
{
	
}

void samlpe_chip1_channle_ref1(void)
{
	
}

void samlpe_in_soc_battery(void)
{
	
}

void sample_post_calc(void)
{
	
}

void sample_process(void)
{
	switch(sampleIndex){
		case 0x00:samlpe_chip0_channle_diff_press();break;
		case 0x01:samlpe_chip0_channle_press();break;
		case 0x02:samlpe_chip0_channle_temperature();break;
		case 0x03:samlpe_chip0_channle_ref0();break;
		case 0x04:samlpe_chip0_channle_ref1();break;
		case 0x05:samlpe_chip1_channle_press_ch0();break;
		case 0x06:samlpe_chip1_channle_press_ch1();break;
		case 0x07:samlpe_chip1_channle_temperature();break;
		case 0x08:samlpe_chip0_channle_ref0();break;
		case 0x09:samlpe_chip0_channle_ref1();break;	
		case 0x0a:samlpe_in_soc_battery();break;
		case 0x0b:
		case 0x0c:sample_post_calc();break;
		default:sampleIndex=0;	break;
	}
	sampleIndex++;
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

