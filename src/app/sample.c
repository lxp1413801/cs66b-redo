#include "../includes/includes.h"

#define sample_delay_ms(ms) delay_ms(ms)
volatile uint8_t sampleIndex=0x00;
volatile int16_t samlpeBuf[SAMPLE_ADC_BUF_LEN];

volatile int16_t rtAdcValueDPrBridge;
volatile int16_t rtAdcValueDPrSignal;
volatile int16_t rtAdcValuePrBridge;
volatile int16_t rtAdcValuePrSignal;

volatile int16_t rtAdcValueTemperatureIn;
volatile int16_t rtAdcValueChip0Ref0;
volatile int16_t rtAdcValueChip0Ref1;

//volatile int16_t rtAdcValuePrEx0Bridge;
volatile int16_t rtAdcValuePrEx0Signal;
//volatile int16_t rtAdcValuePrEx1Bridge;
volatile int16_t rtAdcValuePrEx1Signal;

volatile int16_t rtAdcValueTemperatureEx0A;
volatile int16_t rtAdcValueTemperatureEx0B;
volatile int16_t rtAdcValueTemperatureEx1A;
volatile int16_t rtAdcValueTemperatureEx1B;
//volatile int16_t rtAdcValueChip1Ref0;
//volatile int16_t rtAdcValueChip1Ref1;
int16_t abs_diff(uint16_t a,uint16_t b)
{
	if(a>b){
		return(a-b);
	}else{
		return (b-a);
	}
}
int16_t samlpe_get_adc_average_value_ex(volatile int16_t* buf,uint8_t len)
{
    uint8_t maxIndex[2];
    uint8_t i,j;
    int32_t t32,ret;
    int16_t max[2];
	int16_t absdiff;
    for(j=0;j<8;j++){
        

		t32=0;
		for(i=0;i<len;i++){
			t32+=buf[i];
		}
		t32/=i;
		
		ret=t32;
		max[0]=0;max[1]=1;
		maxIndex[0]=0;maxIndex[1]=1;		
		for(i=0;i<len;i++){
			absdiff=abs_diff((uint16_t)t32,buf[i]);
			if(absdiff>max[1]){
				max[0]=max[1];maxIndex[0]=maxIndex[1];
				max[1]=absdiff;maxIndex[1]=i;
			}else if(absdiff>max[0]){
				max[0]=absdiff;maxIndex[0]=i;
			}
		}
		buf[maxIndex[0]]=(uint16_t)ret;
		buf[maxIndex[1]]=(uint16_t)ret;
    }
    return (int16_t)ret;    
}
/*
int16_t samlpe_get_adc_average_value(volatile int16_t* buf,uint8_t len)
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
*/

volatile int16_t samlpe_read_adc(ads1148Obj_t* obj,volatile int16_t* buf,uint8_t len)
{
	
	volatile uint8_t i=0;
	volatile int16_t t16;
	volatile int32_t	t32=0;
    ads1148_start_convert(obj);
	for(i=0;i<4;i++){
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
	/*
    ads1148_set_vref(&ads1148Chip0,ADS1148_REFSELT_INREF);
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL); 
	
	ads1148_set_idac12_pins(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_250uA);
    
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_2000SPS);
    //ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);  
    ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
	
	ads1148_set_channle_normal(&ads1148Chip0,AIN1P,AIN0N);
	*/
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_OFF,AIN1P,AIN0N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_250uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip0);
	
    //ads1148_get_all_register(&ads1148Chip0);
	rtAdcValueDPrBridge=samlpe_read_adc(&ads1148Chip0,NULL,8);
    //ads1148_stop_convert(&ads1148Chip0);
	//ads1148_send_cmd(&ads1148Chip0,ADS1148_CMD_SLEEP);
	__nop();
	__nop();
}

void samlpe_chip0_ch_diff_pr_signal(void)
{
	//ads1148_start_convert(&ads1148Chip0);
	//ads1148_set_ready(&ads1148Chip0);
	
    /*
    ads1148_set_vref(&ads1148Chip0,ADS1148_REFSELT_INREF);
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL); 
    
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_500uA);
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_640SPS);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_64);
	
	ads1148_set_channle_normal(&ads1148Chip0,AIN5P,AIN4N);
	
    ads1148_get_all_register(&ads1148Chip0);
	*/
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_OFF,AIN5P,AIN4N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_32,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	samlpe_read_adc(&ads1148Chip0,samlpeBuf,SAMPLE_ADC_BUF_LEN);
    
	//rtAdcValueDPrSignal=samlpe_get_adc_average_value(samlpeBuf,SAMPLE_ADC_BUF_LEN);
    rtAdcValueDPrSignal=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	//ads1148_stop_convert(&ads1148Chip0);
	//ads1148_send_cmd(&ads1148Chip0,ADS1148_CMD_SLEEP);
	__nop();
	__nop();
}

void samlpe_chip0_ch_diff_pr_ref0(void)
{
	//ads1148_start_convert(&ads1148Chip0);
	//ads1148_set_ready(&ads1148Chip0);
    
	/*
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_2000SPS);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    //ads1148_get_all_register(&ads1148Chip0);
	
	ads1148_set_channle_normal(&ads1148Chip0,AIN0P,AIN6N);
	*/	
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_2uA0,AIN0P,AIN6N);
	ads1148_set_vbias_ex(&ads1148Chip0,0+0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	rtAdcValueChip0Ref0=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
    //rtAdcValueChip0Ref0=samlpe_get_adc_average_value_ex(samlpeBuf,32);
    ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);
	
	//ads1148_send_cmd(&ads1148Chip0,ADS1148_CMD_SLEEP);
	__nop();
	__nop();
    __nop();
    //ads1148_stop_convert(&ads1148Chip0);
}
void sample_calc_diff_press(void)
{
    int32_t t32;
	x_prDiffData.sigAdcValue=rtAdcValueDPrSignal;
    x_prDiffData.tAdcValue=rtAdcValueDPrBridge;
    x_prDiffData.value=0;                                           
    t32=calculate_and_compensate(diffPrCalibDataObj.calibTab,&x_prDiffData);
    rtDiffPressure=t32;
	cal_diff_p_to_h(t32);
    __nop();
    __nop();
    //rtPressure=t32;
    //rtHight=rtAdcValueDPrSignal;
	if(stSysData.pos==HOTIZONTAL){
        t32=cal_diff_hight_to_vol_h(rtHight);
        rtVolume=t32;
    }else{
        rtVolume=cal_diff_hight_to_vol_v(rtHight);
    }
	rtWeight=cal_diff_vol_to_t(rtVolume);
	//
	rtLevel=cal_diff_hight_level();
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
	/*
	ads1148_set_idac12_pins(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_250uA);
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_2000SPS);
    ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL);
    ads1148_set_channle_normal(&ads1148Chip0,AIN7P,AIN6N);
    ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
	*/
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_OFF,AIN7P,AIN6N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_250uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	rtAdcValuePrBridge=samlpe_read_adc(&ads1148Chip0,NULL,8);
	__nop();
	__nop();
}

void samlpe_chip0_ch_pr_signal(void)
{
	/*
	ads1148_set_channle_normal(&ads1148Chip0,AIN3P,AIN2N);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_500uA);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_64);
    ads1148_get_all_register(&ads1148Chip0);
	*/
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_OFF,AIN3P,AIN2N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_64,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);	
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	samlpe_read_adc(&ads1148Chip0,samlpeBuf,SAMPLE_ADC_BUF_LEN);
    //rtAdcValuePrSignal=samlpe_get_adc_average_value(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValuePrSignal=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();
}



void samlpe_chip0_ch_pr_ref1(void)
{
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_2uA0,AIN1P,AIN0N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_REF1_MONITOR);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_2000SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip0);		
    rtAdcValueChip0Ref1=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
}


void samlpe_chip0_ch_temperature_in(void)
{
	/*
    ads1148_set_channle_normal(&ads1148Chip0,AIN6P,AIN0N);
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_2uA0);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    ads1148_get_all_register(&ads1148Chip0);
	*/
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_2uA0,AIN6P,AIN0N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	//ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	//下面这个代码比较诡异 ，把第一路的idac连接到IEXC2上
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_IEXC2,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	rtAdcValueTemperatureIn=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
    //rtAdcValueTemperatureIn=samlpe_get_adc_average_value_ex(samlpeBuf,32);
	__nop();
	__nop();
    __nop();

}
void sample_calc_press(void)
{
    int32_t t32;
	x_prData.sigAdcValue=rtAdcValuePrSignal;
    x_prData.tAdcValue=rtAdcValuePrBridge;
    x_prData.value=0;                                           
    t32=calculate_and_compensate(prPrCalibDataObj.calibTab,&x_prData);
    rtPressure=t32;
	//cal_diff_p_to_h(t32);
    __nop();
    __nop();
    //rtPressure=t32;
    //rtHight=rtAdcValueDPrSignal;
}

void sample_calc_temperature_in(void)
{
	float x,y;
	//x=(float)rtAdcValueChip0Ref0;
	x=800.0;
	y=(float)rtAdcValueTemperatureIn;
	y=(y/x-1.0)*100;
	//转换为温度
    x=calc_res_2_temp(y);
    x=x*100;
	rtTemperatureIn=(int32_t)x;
	//rtTemperatureIn=cal_smoothing_filter(rtTemperatureInBuf,(int32_t)x,4);
	__nop();
	__nop();
}

void samlpe_chip1_ch_expr0_bridge(void)
{
	
}

void samlpe_chip1_ch_expr0_signal(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN6P,AIN7N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_32,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValuePrEx0Signal=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();	
}
void sample_calc_press_ex0(void)
{
    int32_t t32;
	x_ex0prData.sigAdcValue=rtAdcValuePrEx0Signal;
	x_ex0prData.tAdcValue=0;
	x_ex0prData.value=0;                                           
    t32=calculate_and_compensate(ex0PrCalibDataObj.calibTab,&x_ex0prData);
    rtEx0Pressure=t32;
    __nop();
    __nop();
}

void samlpe_chip1_ch_ex0_temperature_A(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN2P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_2000SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	rtAdcValueTemperatureEx0A=samlpe_read_adc(&ads1148Chip1,samlpeBuf,8);
	__nop();
	__nop();		
}
void samlpe_chip1_ch_ex0_temperature_B(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN3P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_2000SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	rtAdcValueTemperatureEx0B=samlpe_read_adc(&ads1148Chip1,samlpeBuf,8);
	__nop();
	__nop();		
}

void sample_calc_temperature_ex0(void)
{
	float x,y;
	x=(float)rtAdcValueTemperatureEx0A;
	y=(float)rtAdcValueTemperatureEx0B;
	x=x-y-y;
	y=x*2.048/32767/5.0e-4;
	//y=(y/x-1.0)*100;
	//转换为温度
    x=calc_res_2_temp(y);	
	rtTemperatureEx0=(int32_t)x;
	__nop();
	__nop();
}

void samlpe_chip1_ch_expr0_ref0(void)
{
	
}

void samlpe_chip1_ch_expr1_bridge(void)
{
	
}

void samlpe_chip1_ch_expr1_signal(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN0P,AIN1N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_32,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValuePrEx1Signal=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();		
}

void sample_calc_press_ex1(void)
{
    int32_t t32;
	x_ex1prData.sigAdcValue=rtAdcValuePrEx1Signal;
	x_ex1prData.tAdcValue=0;
	x_ex1prData.value=0;                                           
    t32=calculate_and_compensate(ex1PrCalibDataObj.calibTab,&x_ex1prData);
    rtEx1Pressure=t32;
    __nop();
    __nop();
}

void samlpe_chip1_ch_ex1_temperature_A(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN4P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_2000SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	rtAdcValueTemperatureEx1A=samlpe_read_adc(&ads1148Chip1,samlpeBuf,8);
	__nop();
	__nop();		
}

void samlpe_chip1_ch_ex1_temperature_B(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN5P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_2000SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip1);	
	
	rtAdcValueTemperatureEx1B=samlpe_read_adc(&ads1148Chip1,samlpeBuf,8);
	__nop();
	__nop();		
}

void sample_calc_temperature_ex1(void)
{
	float x,y;
	x=(float)rtAdcValueTemperatureEx1A;
	y=(float)rtAdcValueTemperatureEx1B;
	x=x-y-y;
	y=x*2.048/32767/5.0e-4;
	//y=(y/x-1.0)*100;
	//转换为温度
    x=calc_res_2_temp(y);	
	rtTemperatureEx1=(int32_t)x;
	__nop();
	__nop();
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
        
		case 0x03:sample_calc_diff_press();             break;
        //case 0x03:break;
		case 0x04:samlpe_chip0_ch_pr_bridge();			break;
		case 0x05:samlpe_chip0_ch_pr_signal();			break;
		//case 0x06:samlpe_chip0_ch_pr_ref1();			break;
		case 0x06:samlpe_chip0_ch_temperature_in();		break;
		case 0x07:sample_calc_press();					break;

        case 0x08:sample_calc_temperature_in();         break; 
		
		case 0x09:samlpe_chip1_ch_expr0_signal();		break;
		case 0x0a:sample_calc_press_ex0();				break;
		case 0x0b:samlpe_chip1_ch_ex0_temperature_A();	break;
		case 0x0c:samlpe_chip1_ch_ex0_temperature_B();	break;
		case 0x0d:sample_calc_temperature_ex0();		break;
		
		case 0x0e:samlpe_chip1_ch_expr1_signal();		break;	
		case 0x0f:sample_calc_press_ex1();				break;
		case 0x10:samlpe_chip1_ch_ex1_temperature_A();	break;
		case 0x11:samlpe_chip1_ch_ex1_temperature_B();	break;
		case 0x12:sample_calc_temperature_ex0();		break;		

		case 0x13:samlpe_in_soc_battery();				break;
		case 0x14:sample_in_soc_solar();				break;
		case 0x15:samlpe_in_soc_ref();					break;
		case 0x16:break;
		default:	break;
	}
	sampleIndex++;
    if(sampleIndex>0x16)sampleIndex=0;
    TMR2_Start();
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
*/
/*
void thread_sample( void * pvParameters )
{
    ads1148_init_all_obj();
	ads1148_init_device();

	while(1){
        sample_process();
        sample_delay_ms(10);
        __nop();
        __nop();
	}
}

void thread_sample_create(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;


    xReturned = xTaskCreate(
		thread_sample, 
		"samlpe", 
		configMINIMAL_STACK_SIZE*2, 
		NULL, 
		1, 
		&xHandle );	
}
*/

