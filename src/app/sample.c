#include "../includes/includes.h"

#define sample_delay_ms(ms) delay_ms(ms)
volatile bool sampleFreashFlg=false;
volatile bool firstSampleFlg=true;
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


// volatile int32_t rtAdcValueTemperatureEx0A;
// volatile int32_t rtAdcValueTemperatureEx0B;
// volatile int32_t rtAdcValueTemperatureEx1A;
// volatile int32_t rtAdcValueTemperatureEx1B;
volatile int32_t rtTempRes0;
volatile int32_t rtTempRes1;

//volatile int16_t rtAdcValueChip1Ref0;
//volatile int16_t rtAdcValueChip1Ref1;
volatile int16_t rtValueBat;
volatile uint8_t batLevel=0;
volatile int16_t rtValueSolor;
volatile uint8_t solorLevel=0;


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
		ret=t32/i;
		if((t32%i) >= (i/2)){
			ret++;
		}
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
volatile int32_t samlpe_read_adc_ex(ads1148Obj_t* obj,volatile int16_t* buf,uint8_t len)
{
	
	volatile uint8_t i=0;
	volatile int16_t t16;
	volatile int32_t	t32=0;
    ads1148_start_convert(obj);
	for(i=0;i<6;i++){
		ads1148_waite_convert(obj);
		__nop();
	}
	for(i=0;i<len;i++){
		ads1148_waite_convert(obj);
		t16=ads1148_read_data(obj);
		samlpeBuf[i]=t16;
		t32+=(int32_t)t16;
	}
	//t32/=i;
	if(buf){
		m_mem_cpy_len((uint8_t*)buf,(uint8_t*)samlpeBuf,len*sizeof(int16_t));
	}
	return t32;
}
//ads1148Chip0

void samlpe_chip0_ch_diff_pr_bridge(void)
{
	/*
    ads1148_set_vref(&ads1148Chip0,ADS1148_REFSELT_INREF);
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_NORMAL); 
	
	ads1148_set_idac12_pins(&ads1148Chip0,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	ads1148_set_imag_idac(&ads1148Chip0,ADS1148_IMAG_250uA);
    
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_640SPS);
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
	if(rtAdcValueDPrBridge>0x7f00){
		hardStatus.bits.bDprSensor=0;
	}else{
		hardStatus.bits.bDprSensor=1;
	}
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
/*
void samlpe_chip0_ch_diff_pr_ref0(void)
{
	//ads1148_start_convert(&ads1148Chip0);
	//ads1148_set_ready(&ads1148Chip0);
    

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
*/
/*
int32_t sample_calc_calib_x_2nd(int32_t in,st_2ndCalibDef* tb)
{
	float y,x;
	y=(float)(tb[1].realValue-tb[0].realValue);
    x=(float)(tb[1].oringinValue-tb[0].oringinValue);
    
    if(x<1)x=1;
    y=y/x;
    
    x=(float)(in)-tb[0].oringinValue;
    y=y*x;
    y=y+(float)tb[0].realValue;
    return (int32_t)y;
}
*/
int32_t sample_calc_calib_dpr_2nd(int32_t in,st_2ndCalibDef* tb)
{
	float y,x;
	y=(float)(tb[1].realValue-tb[0].realValue);
    x=(float)(tb[1].oringinValue-tb[0].oringinValue);
    
    if(x<1)x=1;
    y=y/x;
    
    x=(float)(in)-tb[0].oringinValue;
    y=y*x;
    y=y+(float)tb[0].realValue;
    return (int32_t)y;
}
int32_t sample_calc_calib_x_2nd(int32_t in,st_2ndCalibDef* tb)
{
	int32_t t32;
	/*
	float y,x;
	y=(float)(tb[1].realValue-tb[0].realValue);
    x=(float)(tb[1].oringinValue-tb[0].oringinValue);
    
    if(x<1)x=1;
    y=y/x;
    
    x=(float)(in)-tb[0].oringinValue;
    y=y*x;
    y=y+(float)tb[0].realValue;
    return (int32_t)y;*/
	
	t32=tb[0].oringinValue;
	return in-t32;
}
int32_t sample_calc_diff_press_fliter(int32_t t32)
{

	
	float f1,f2;
	uint8_t i;
	rtDiffPrBuf[3]=rtDiffPrBuf[2];
	rtDiffPrBuf[2]=rtDiffPrBuf[1];
	rtDiffPrBuf[1]=rtDiffPrBuf[0];
	rtDiffPrBuf[0]=t32;
	f1=0;
	for(i=0;i<4;i++){
		f2=(float)(stSysData.ployCoeffic[i]);
		f2=f2*rtDiffPrBuf[i];
		f1=f1+f2;
	}
	f1=f1/1000;
    //rtDiffPrBuf[0]=(int32_t)f1;	
    return (int32_t)f1;	
}

int32_t sample_calc_diff_press_static_err(int32_t in)
{
	int32_t t32;
	float x,y;
	y=(float)(calibTab0.staticPreAdj1.diffPrZero-calibTab0.staticPreAdj0.diffPrZero);
    if(y>100)return in;
    x=(float)(calibTab0.staticPreAdj1.pr-calibTab0.staticPreAdj0.pr);
    if(x<1)x=1;
    y=y/x;//y为斜率
    x=(float)(rtPressure-calibTab0.staticPreAdj0.pr);
    y=y*x;
    y=y+(float)calibTab0.staticPreAdj0.diffPrZero;

    t32=(int32_t)y;
    t32=in-t32;
	return t32;
}


void sample_calc_diff_press(void)
{
    //uint8_t i;
    int32_t t32;
	x_prDiffData.sigAdcValue=rtAdcValueDPrSignal;
    x_prDiffData.tAdcValue=rtAdcValueDPrBridge;
    x_prDiffData.value=0;                                           
    t32=calculate_and_compensate(diffPrCalibDataObj.calibTab,&x_prDiffData);
    //rtDiffPressure=t32;
    rtDiffPrOriginal=sample_calc_diff_press_fliter(t32);
    /*
	
	
	t32=sample_calc_calib_dpr_2nd(rtDiffPrOriginal,(st_2ndCalibDef*)(stSysData._2ndPrDiffCalib));
    
	if(hardStatus.bits.bDprSensor==1){
		rtDiffPressure=sample_calc_diff_press_static_err(t32);
	}else{
		rtDiffPressure=0;
	}
	*/
	if(hardStatus.bits.bPrSensor==1){
		t32=sample_calc_diff_press_static_err(rtDiffPrOriginal);
	}else{
		//t32=0;
	}
    rtDiffPressure=sample_calc_calib_dpr_2nd(t32,(st_2ndCalibDef*)(stSysData._2ndPrDiffCalib));
    //
	t32=cal_diff_p_to_h(rtDiffPressure);
	t32=t32-stSysData.baseZero;
	rtHight=t32;
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
    ads1148_set_data_rate(&ads1148Chip0,ADS1148_SYS0_DR_640SPS);
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
	if(rtAdcValuePrBridge>0x7f00){
		hardStatus.bits.bPrSensor=0;
	}else{
		hardStatus.bits.bPrSensor=1;
	}		
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


/*
void samlpe_chip0_ch_pr_ref1(void)
{
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_2uA0,AIN1P,AIN0N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_REF1_MONITOR);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	
	ads1148_set_config_ex(&ads1148Chip0);		
    rtAdcValueChip0Ref1=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
	__nop();
	__nop();
    __nop();
}
*/
/*
void samlpe_chip0_ch_temperature_in(void)
{

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
*/
void samlpe_chip0_ch_temperature_in(void)
{
	if(hardStatus.bits.bInTempSensor==0)return;	
	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_OFF,AIN6P,AIN0N);
	ads1148_set_vbias_ex(&ads1148Chip0,0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_2,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_1000uA);
	//ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	//下面这个代码比较诡异 ，把第一路的idac连接到IEXC2上
	//ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_IEXC2,IDAC_OUT_NC);
	ads1148_set_idac1_ex(&ads1148Chip0,ADS1148_IDAC_OUT_PINS_AIN6,ADS1148_IDAC_OUT_PINS_AIN0);
	ads1148_set_config_ex(&ads1148Chip0);	
	
	rtAdcValueTemperatureIn=samlpe_read_adc(&ads1148Chip0,samlpeBuf,16);
    //rtAdcValueTemperatureIn=samlpe_get_adc_average_value_ex(samlpeBuf,32);
	__nop();
	__nop();
    __nop();

}

void samlpe_chip0_ch_diff_pr_ref0(void)
{
	//ads1148_start_convert(&ads1148Chip0);
	//ads1148_set_ready(&ads1148Chip0);
    

	ads1148_set_mux0_ex(&ads1148Chip0,ADS1148_BCS_2uA0,AIN0P,AIN6N);
	ads1148_set_vbias_ex(&ads1148Chip0,0+0);
	ads1148_set_mux1_ex(&ads1148Chip0,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip0,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip0,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_OFF);
	ads1148_set_idac1_ex(&ads1148Chip0,IDAC_OUT_NC,IDAC_OUT_NC);
	
	ads1148_set_config_ex(&ads1148Chip0);	
	
	//rtAdcValueChip0Ref0=samlpe_read_adc(&ads1148Chip0,samlpeBuf,8);
    //rtAdcValueChip0Ref0=samlpe_get_adc_average_value_ex(samlpeBuf,32);
    //ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_OFF);
	
	//ads1148_send_cmd(&ads1148Chip0,ADS1148_CMD_SLEEP);
	__nop();
	__nop();
    __nop();
    //ads1148_stop_convert(&ads1148Chip0);
}

void sample_calc_press(void)
{
    int32_t t32;
	x_prData.sigAdcValue=rtAdcValuePrSignal;
    x_prData.tAdcValue=rtAdcValuePrBridge;
    x_prData.value=0;                                           
    t32=calculate_and_compensate(prPrCalibDataObj.calibTab,&x_prData);
    rtPrOriginal=t32;
	t32=sample_calc_calib_x_2nd(rtPrOriginal,(st_2ndCalibDef*)(stSysData._2ndPrCalib));
	if(hardStatus.bits.bPrSensor==1 && hardStatus.bits.bInTempSensor==1){
		rtPressure=t32;
	}else{
		rtPressure=0;
	}
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
	//x=800.0;
	if(hardStatus.bits.bInTempSensor==0)return;	
	y=(float)rtAdcValueTemperatureIn;
    y=y/32;
	//y=y*100;
	//转换为温度
	if(firstSampleFlg){
		if(y<10.000 || y>300)hardStatus.bits.bInTempSensor=0;
	}	
    x=calc_res_2_temp(y);
    x=x*100;
	rtTemperatureIn=(int32_t)x;
	//rtTemperatureIn=cal_smoothing_filter(rtTemperatureInBuf,(int32_t)x,4);
	__nop();
	__nop();
}



void samlpe_chip1_ch_expr0_signal(void)
{
	
	if(hardStatus.bits.bEx0PrEeprom==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;
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
	if(hardStatus.bits.bEx0PrEeprom==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;
	x_ex0prData.sigAdcValue=rtAdcValuePrEx0Signal;
	x_ex0prData.tAdcValue=0;
	x_ex0prData.value=0;                                           
    t32=calculate_and_compensate(ex0PrCalibDataObj.calibTab,&x_ex0prData);
	rtEx0PrOriginal=t32;
	t32=sample_calc_calib_x_2nd(rtEx0PrOriginal,(st_2ndCalibDef*)(stSysData._2ndPrEx0));
    rtEx0Pressure=t32;
    __nop();
    __nop();
}
/*
void samlpe_chip1_ch_ex0_temperature_A(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN2P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	//ads1148_set_idac1_ex(&ads1148Chip1,ADS1148_IDAC_OUT_PINS_AIN2,IDAC_OUT_NC);
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx0A=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	
	__nop();
	__nop();		
}
*/
void samlpe_chip1_ch_ex0_temperature_A(void)
{
	if(hardStatus.bits.bEx0TempSensor==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN2P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_4,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_1000uA);
	//ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	ads1148_set_idac1_ex(&ads1148Chip1,ADS1148_IDAC_OUT_PINS_AIN2,ADS1148_IDAC_OUT_PINS_AIN3);
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx0A=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	
	__nop();
	__nop();		
}
/*
void samlpe_chip1_ch_ex0_temperature_B(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN3P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	//ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_IEXC1,IDAC_OUT_NC);
	ads1148_set_idac1_ex(&ads1148Chip1,ADS1148_IDAC_OUT_PINS_AIN2,IDAC_OUT_NC);
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx0B=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	
	__nop();
	__nop();		
}
*/
void samlpe_chip1_ch_ex0_temperature_B(void)
{
	if(hardStatus.bits.bAdcChip1==0)return;
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN3P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_NC);
	//ads1148_set_idac1_ex(&ads1148Chip1,ADS1148_IDAC_OUT_PINS_AIN2,IDAC_OUT_NC);
	ads1148_set_config_ex(&ads1148Chip1);	
	
	//samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	//rtAdcValueTemperatureEx0B=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	
	__nop();
	__nop();		
}
/*
void sample_calc_temperature_ex0(void)
{
	float x,y;
	x=(float)rtAdcValueTemperatureEx0A;
	y=(float)rtAdcValueTemperatureEx0B;
	x=x-y-y;
	y=x*2.048/32767/5.0e-4;
    rtTempRes0=(int32_t)(y*1000);

    x=calc_res_2_temp(y);	
    x=x*1000;
	rtTemperatureEx0=(int32_t)x;
	__nop();
	__nop();
}
*/

void sample_calc_temperature_ex0(void)
{
	int32_t t32;
	float x,y;    
	if(hardStatus.bits.bEx0TempSensor==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;
	t32=(int32_t)(stSysData.tempCalibEx0[1].adcValue-stSysData.tempCalibEx0[0].adcValue);
	if(t32==0)t32=1;
	x=(float)t32;

	t32=(int32_t)(stSysData.tempCalibEx0[1].resValue-stSysData.tempCalibEx0[0].resValue);
	y=(float)t32;

	//t32=(int32_t)(rtAdcValueTemperatureEx0A-rtAdcValueTemperatureEx0B-rtAdcValueTemperatureEx0B);
    t32=(int32_t)(rtAdcValueTemperatureEx0A);
    __nop();
    y=y/x;
    x=(float)(t32-stSysData.tempCalibEx0[0].adcValue);
    y=y*x;
	y=y+(float)(stSysData.tempCalibEx0[0].resValue);

	rtTempRes0=(int32_t)(y);
	if(firstSampleFlg){
		if(rtTempRes0<10000)hardStatus.bits.bEx0TempSensor=0;
	}
	
	x=calc_res_2_temp(y/1000);	
	x=x*1000;
	rtTemperatureEx0=(int32_t)x;
	__nop();
	__nop();

}


void samlpe_chip1_ch_expr1_signal(void)
{
	if(hardStatus.bits.bAdcChip1==0)return;
	if(hardStatus.bits.bEx1PrEeprom==0)return;
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
	if(hardStatus.bits.bEx1PrEeprom==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;
	x_ex1prData.sigAdcValue=rtAdcValuePrEx1Signal;
	x_ex1prData.tAdcValue=0;
	x_ex1prData.value=0;                                           
    t32=calculate_and_compensate(ex1PrCalibDataObj.calibTab,&x_ex1prData);
	rtEx1PrOriginal=t32;
	t32=sample_calc_calib_x_2nd(rtEx1PrOriginal,(st_2ndCalibDef*)(stSysData._2ndPrEx1));
    rtEx1Pressure=t32;
    __nop();
    __nop();
}
/*
void samlpe_chip1_ch_ex1_temperature_A(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN4P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);

	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx1A=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();		
}
*/
void samlpe_chip1_ch_ex1_temperature_A(void)
{
	if(hardStatus.bits.bEx1TempSensor==0)return;	
	if(hardStatus.bits.bAdcChip1==0)return;
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN4P,AIN5N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_4,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_1000uA);
	//ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);
	ads1148_set_idac1_ex(&ads1148Chip1,ADS1148_IDAC_OUT_PINS_AIN4,ADS1148_IDAC_OUT_PINS_AIN5);
	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx1A=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();		
}
/*
void samlpe_chip1_ch_ex1_temperature_B(void)
{
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN5P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_IEXC2);

	ads1148_set_config_ex(&ads1148Chip1);	
	
	samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	rtAdcValueTemperatureEx1B=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();		
}
*/
void samlpe_chip1_ch_ex1_temperature_B(void)
{
	if(hardStatus.bits.bAdcChip1==0)return;
	
	ads1148_set_mux0_ex(&ads1148Chip1,ADS1148_BCS_OFF,AIN5P,AIN3N);
	ads1148_set_vbias_ex(&ads1148Chip1,0);
	ads1148_set_mux1_ex(&ads1148Chip1,ADS1148_VREFCON_INREF_ON,ADS1148_REFSELT_INREF,ADS1148_MUXCAL_NORMAL);
	
	ads1148_set_sys0_ex(&ads1148Chip1,ADS1148_PGA_1,ADS1148_SYS0_DR_640SPS);
	
	ads1148_set_idac0_ex(&ads1148Chip1,ADS1148_DRDY_VIA_DRDY,ADS1148_IMAG_500uA);
	ads1148_set_idac1_ex(&ads1148Chip1,IDAC_OUT_NC,IDAC_OUT_NC);

	ads1148_set_config_ex(&ads1148Chip1);	
	
	//samlpe_read_adc(&ads1148Chip1,samlpeBuf,SAMPLE_ADC_BUF_LEN);
	//rtAdcValueTemperatureEx1B=samlpe_get_adc_average_value_ex(samlpeBuf,SAMPLE_ADC_BUF_LEN);
	__nop();
	__nop();		
}
/*
void sample_calc_temperature_ex1(void)
{
	float x,y;
	x=(float)rtAdcValueTemperatureEx1A;
	y=(float)rtAdcValueTemperatureEx1B;
	x=x-y-y;
	y=x*2.048/32767/5.0e-4;
    rtTempRes1=(int32_t)(y*1000);

    x=calc_res_2_temp(y);	
    x=x*1000;
	rtTemperatureEx1=(int32_t)x;
	__nop();
	__nop();
}
 */
 
void sample_calc_temperature_ex1(void)
{
	//tempCalibEx0
	int32_t t32;
	float x,y;    
	if(hardStatus.bits.bEx1TempSensor==0)return;
	if(hardStatus.bits.bAdcChip1==0)return;	
	t32=(int32_t)(stSysData.tempCalibEx1[1].adcValue-stSysData.tempCalibEx1[0].adcValue);
	if(t32==0)t32=1;
	x=(float)t32;

	t32=(int32_t)(stSysData.tempCalibEx1[1].resValue-stSysData.tempCalibEx1[0].resValue);
	y=(float)t32;

	//t32=(int32_t)(rtAdcValueTemperatureEx1A-rtAdcValueTemperatureEx1B-rtAdcValueTemperatureEx1B);
    t32=(int32_t)(rtAdcValueTemperatureEx1A);
    y=y/x;
    x=(float)(t32-stSysData.tempCalibEx1[0].adcValue);
    y=y*x;
    
	y=y+stSysData.tempCalibEx1[0].resValue;

	rtTempRes1=(int32_t)(y);
	if(firstSampleFlg){
		if(rtTempRes1<10000)hardStatus.bits.bEx1TempSensor=0;
	}
	x=calc_res_2_temp(y/1000);	
	x=x*1000;
	rtTemperatureEx1=(int32_t)x;
	__nop();
	__nop();
}
void ain_ref_config(void){
    set_port_mode_an(AIN_REF_P_PORT,AIN_REF_P_PIN); 
    set_port_mode_in(AIN_REF_P_PORT,AIN_REF_P_PIN); 
    //set_port_value_hight(AIN_REF_P_PORT,AIN_REF_P_PIN); 
}
	
void ain_bat_config(void) {
    set_port_mode_an(AIN_BAT_PORT,AIN_BAT_PIN); 
    set_port_mode_in(AIN_BAT_PORT,AIN_BAT_PIN); 
}

void sample_in_soc_solar(void)
{
	uint32_t t32;
	uint16_t t16;
	uint8_t  i;

	ain_ref_config();
	//ain_bat_config();
    ain_solor_config();
    check_solor_set_hight();
    
	ADC1_Initialize();
	ADC1_ChannelSelect(ADC1_CHANNEL_SOLAR);
    //ADC1_Stop();
	t32=0;
	for(i=0;i<16;i++){
		ADC1_Start();
		delay_ms(1);
		ADC1_Stop();
		while(!ADC1_IsConversionComplete())	{
			__nop();
		}
		t16=ADC1_ConversionResultGet();
		t32+=t16;
	}
    check_solor_set_low();
    t16=(uint16_t)(t32/i);
    t32=IN_SOC_VREF_VALUE;
    t32=t32*t16*12/4095;    
    
	rtValueSolor=(uint16_t)(t32/i);
    if(rtValueSolor>9000){
        solorLevel=1;
    }else{
        solorLevel=0;
    }
	__nop();
	__nop();	
}



void samlpe_in_soc_battery(void)
{
	uint32_t t32;
	uint16_t t16;
	uint8_t  i;

	ain_ref_config();
	ain_bat_config();
	ADC1_Initialize();
	ADC1_ChannelSelect(ADC1_CHANNEL_BAT);
    //ADC1_Stop();
	t32=0;
	for(i=0;i<16;i++){
		ADC1_Start();
		delay_ms(1);
		ADC1_Stop();
		while(!ADC1_IsConversionComplete())	{
			__nop();
		}
		t16=ADC1_ConversionResultGet();
		t32+=t16;
	}
    t16=(uint16_t)(t32/i);
    t32=IN_SOC_VREF_VALUE;
    t32=t32*t16*6/4095;
	rtValueBat=(uint16_t)t32;
    if(rtValueBat>3500){
		batLevel=3;
	}else if(rtValueBat>3300){
		batLevel=2;
	}else if(rtValueBat>3000){
		batLevel=1;
	}else{
		batLevel=0;
	}
	__nop();
	__nop();	
}

void samlpe_in_soc_ref(void)
{
	
}

uint8_t sample_process(void)
{
	switch(sampleIndex){
		
		case 0x00:samlpe_chip0_ch_diff_pr_bridge();		break;
		case 0x01:samlpe_chip0_ch_diff_pr_signal();		break;

		case 0x02:samlpe_chip0_ch_pr_bridge();			break;
		case 0x03:samlpe_chip0_ch_pr_signal();			break;

		
		case 0x04:samlpe_chip0_ch_temperature_in();		break;
		case 0x05:samlpe_chip0_ch_diff_pr_ref0();		break;
		
		case 0x06:sample_calc_press();					break;
		case 0x07:sample_calc_diff_press();             break;				
		

        case 0x08:sample_calc_temperature_in();         break; 
		
		case 0x09:samlpe_in_soc_battery();				break;
		//case 0x0a:sample_in_soc_solar();				break;
		case 0x0a:break;
		case 0x0b:samlpe_in_soc_ref();					break;		
		
#if ADS1148_CHIP_OTRHER_ONE_ENABLE 
		case 0x0c:samlpe_chip1_ch_expr0_signal();		break;
		case 0x0d:sample_calc_press_ex0();				break;
		case 0x0e:samlpe_chip1_ch_ex0_temperature_A();	break;
		case 0x0f:samlpe_chip1_ch_ex0_temperature_B();	break;
		case 0x10:sample_calc_temperature_ex0();		break;
		
		case 0x11:samlpe_chip1_ch_expr1_signal();		break;	
		case 0x12:sample_calc_press_ex1();				break;
		case 0x13:samlpe_chip1_ch_ex1_temperature_A();	break;
		case 0x14:samlpe_chip1_ch_ex1_temperature_B();	break;
		case 0x15:sample_calc_temperature_ex1();		break;			
#endif
		default:	break;
	}
	sampleIndex++;
#if ADS1148_CHIP_OTRHER_ONE_ENABLE==1
    if(sampleIndex>0x15){
        sampleIndex=0;
        sampleFreashFlg=true;
		firstSampleFlg=false;
    }
#else
    if(sampleIndex>0x0b){
        sampleIndex=0;
        sampleFreashFlg=true;
    }
#endif
    if(stSysData.sleepPeriod==0){
        calc_warning_pr_dpr();
        bi_output();
        TMR2_Start();
    }
    return sampleIndex;
}


