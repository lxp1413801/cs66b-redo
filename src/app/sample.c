#include "../includes/includes.h"
volatile uint8_t sampleIndex=0x00;
int16_t samlpeBuf[32];

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

int16_t samlpe_get_adc_average_value(int16_t* buf,uint8_t len)
{
    uint8_t maxIndex,minIndex;
    uint8_t i,j;
    int32_t ret=0;
    int16_t max=0,min;
    for(j=0;j<8;j++){
        ret=0;
        max=INT16_MIN;
        min=INT16_MAX;
        maxIndex=0;
        minIndex=0;
        for(i=0;i<len;i++){
            if(max<buf[i]){
                max=buf[i];
                maxIndex=i;
            }
            if(min>buf[i]){
                min=buf[i];
                minIndex=i;
            }
            ret+=buf[i];
        }
        ret=ret-max;
        ret=ret-min;
        ret=ret/(len-2);
        buf[maxIndex]=(int16_t)ret;
        buf[minIndex]=(int16_t)ret;
    }
    return (int16_t)ret;    
}
int16_t samlpe_read_adc(ads1148Obj_t* obj,int16_t* buf,uint8_t len)
{
	
	uint8_t i=0;
	int16_t t16;
	int32_t	t32=0;
    ads1148_start_convert(obj);
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
//ads1148Chip0
void samlpe_chip0_ch_diff_pr_bridge(void)
{
	
	ads1148_set_idac12_pins(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_250uA);
    
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_2000SPS);
    
    ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);
    ads1148_set_channle_normal(&ads1148Chip0,AIN1P,AIN0N);
    ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
	rtAdcValueDPrBridge=samlpe_read_adc(&ads1148Chip0,NULL,8);
	__nop();
	__nop();
}

void samlpe_chip0_ch_diff_pr_signal(void)
{
	ads1148_set_channle_normal(&ads1148Chip0,AIN5P,AIN4N);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_500uA);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_64);
    ads1148_get_all_register(&ads1148Chip0);
	samlpe_read_adc(&ads1148Chip0,samlpeBuf,24);
    rtAdcValueDPrSignal=samlpe_get_adc_average_value(samlpeBuf,24);
	__nop();
	__nop();
}

void samlpe_chip0_ch_diff_pr_ref0(void)
{
    ads1148_set_channle_normal(&ads1148Chip0,AIN0P,AIN6N);
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
    rtAdcValueChip0Ref0=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
    ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);
}

/*
void samlpe_chip0_ch_diff_pr_ref0(void)
{
    ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_REF0_MONITOR);
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    //ads1148_get_all_register(&ads1148Chip0);
    rtAdcValueChip0Ref0=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);
    ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);
}
*/

void samlpe_chip0_ch_pr_bridge(void)
{
	ads1148_set_idac12_pins(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_250uA);
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_2000SPS);
    ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);
    ads1148_set_channle_normal(&ads1148Chip0,AIN7P,AIN6N);
    ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
	rtAdcValuePrBridge=samlpe_read_adc(&ads1148Chip0,NULL,8);
	__nop();
	__nop();
}

void samlpe_chip0_ch_pr_signal(void)
{
	ads1148_set_channle_normal(&ads1148Chip0,AIN3P,AIN2N);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_500uA);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_64);
    ads1148_get_all_register(&ads1148Chip0);
	samlpe_read_adc(&ads1148Chip0,samlpeBuf,24);
    rtAdcValuePrSignal=samlpe_get_adc_average_value(samlpeBuf,24);
	__nop();
	__nop();
}

void samlpe_chip0_ch_pr_ref1(void)
{
    ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_REF1_MONITOR);
	//ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    //ads1148_get_all_register(&ads1148Chip0);
    rtAdcValueChip0Ref1=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);
    //ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);
}

void samlpe_chip0_ch_temperature_in(void)
{
    ads1148_set_channle_normal(&ads1148Chip0,AIN6P,AIN0N);
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
    rtAdcValueTemperatureIn=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
    ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);	
}


void samlpe_chip1_ch_expr0_bridge(void)
{
	
}

void samlpe_chip1_ch_expr0_signal(void)
{
	
}

void samlpe_chip1_ch_ex0_temperature(void)
{
	
}

void samlpe_chip1_ch_expr0_ref0(void)
{
	
}

void samlpe_chip1_ch_expr1_bridge(void)
{
	
}

void samlpe_chip1_ch_expr1_signal(void)
{
	
}

void samlpe_chip1_ch_ex1_temperature(void)
{
	
}

void samlpe_chip1_ch_expr1_ref1(void)
{
	
}

void sample_in_soc_solar(void)
{

}

void samlpe_in_soc_battery(void)
{
	
}

void samlpe_in_soc_ref(void)
{
	
}

void sample_post_calc(void)
{
	
}

void sample_process(void)
{
	switch(sampleIndex){
		case 0x00:samlpe_chip0_ch_diff_pr_bridge();		break;
		case 0x01:samlpe_chip0_ch_diff_pr_signal();		break;
		case 0x02:samlpe_chip0_ch_diff_pr_ref0();		break;
		case 0x03:break;
		case 0x04:samlpe_chip0_ch_pr_bridge();			break;
		case 0x05:samlpe_chip0_ch_pr_signal();			break;
		case 0x06:samlpe_chip0_ch_pr_ref1();			break;
		case 0x07:samlpe_chip0_ch_temperature_in();	break;
		case 0x08:break;
		case 0x09:samlpe_chip1_ch_expr0_bridge();		break;
		case 0x0a:samlpe_chip1_ch_expr0_signal();		break;
		case 0x0b:samlpe_chip1_ch_ex0_temperature();	break;
		case 0x0c:samlpe_chip1_ch_expr0_ref0();			break;	
		case 0x0d:break;
		case 0x0e:samlpe_chip1_ch_expr1_bridge();		break;
		case 0x0f:samlpe_chip1_ch_expr1_signal();		break;
		case 0x10:samlpe_chip1_ch_ex1_temperature();	break;
		case 0x11:samlpe_chip1_ch_expr1_ref1();			break;
		case 0x12:break;
		case 0x13:samlpe_in_soc_battery();				break;
		case 0x14:sample_in_soc_solar();				break;
		case 0x15:samlpe_in_soc_ref();					break;
		case 0x16:break;
		default:	break;
	}
	sampleIndex++;
    if(sampleIndex>0x16)sampleIndex=0;
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

