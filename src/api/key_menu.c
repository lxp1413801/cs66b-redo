#include "../includes/includes.h"


#define goHOME  true
#define unGoHome    false

#define LONG_PRESS_TIME		2000

bool paramChangedFlag=false;

volatile uint16_t passWord=0x00;
volatile uint8_t menu=MENU_HOME;
volatile uint8_t subMenu=0;
//volatile uint8_t keyValue=KEY_VALUE_NONE;
volatile uint8_t adjLocation=0;
volatile int32_t adjValue=0x00;
volatile int32_t tmpAdjValue=0x00;
//add lxp
st_float32_m m_floatAdj={0};
volatile uint8_t* pAdjValue;
//
volatile uint8_t  calibRow=0x00;
volatile uint8_t  calibCol=0x00;
volatile uint8_t noOporatTime=0x00;

uint16_t __exp_10(uint8_t n)
{
	switch(n){
		case 0:return 	1;
		case 1:return 	10;
		case 2:return 	100;
		case 3:return 	1000;
		default:return 	1000;		
	}
}
// uint8_t __sys_data_save_load_buf(void)
// {
	// uint8_t* buf=ldbuf;
    
	// if(sizeof(globleBuffer1)<sizeof(sysDataDef_t))return 0;
	// m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));	
	// return 1;
// }
uint8_t __sys_data_save_write_flash(void)
{
    uint8_t ret=0;
    //sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	
	sysDataDef_t* stp=&stSysData;
	uint8_t* buf=(uint8_t*)(&stSysData);
    stp->V1=data_sys_cal_v1(stp);
    stp->V2=data_sys_cal_v2(stp);
    crc_append(buf,sizeof(sysDataDef_t)-2);
    m_flash_erase(SYSTEM_DATA_ADDR,sizeof(sysDataDef_t));
    m_flash_write(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
    m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
    ret=crc_verify(buf,sizeof(sysDataDef_t));
    return ret;
}
uint16_t key_waite_release(uint16_t timeout,uint8_t* key)
{
    uint32_t tm=0;
	uint8_t t8;
    ticker_ms_set(0);
    tm=ticker_ms_get();
	while(tm<(uint32_t)timeout){
		t8=get_key_value();
		if(t8==KEY_VALUE_NONE)break;
        delay_ms(1);
        tm=ticker_ms_get();
	}
	*key=t8;
	return (uint16_t)tm;
}
//shift
void key_shift_loc(uint8_t* loc,uint8_t min,uint8_t max)
{
	uint8_t t8=*loc;
	if(min>=max){
		t8=min;
	}else{
		t8++;
		if(t8>max)t8=min;
	}
	if(m_floatAdj.stru.sign){
        if(t8==0)t8=1;
    }
	*loc=t8;
}

void key_adj_value_fixed(uint16_t* value,uint8_t loc)
{
	uint16_t dloc;
	uint16_t t16=*value;
	if(loc>3)loc=3;
	dloc=(t16/__exp_10(loc))%10;
	t16=t16-dloc*__exp_10(loc);
	dloc++;
	if(dloc>9)dloc=0;
	t16+=(dloc*__exp_10(loc));
	*value=t16;
}

void key_adj_value_fixed_t8(uint8_t* value,uint8_t loc)
{
	uint8_t dloc;
	uint16_t t8=*value;
	uint8_t exp10loc;
	if(loc==0){
		exp10loc=1;
	}else  if(loc==1){
		exp10loc=10;
	}else{
		exp10loc=100;
	}
	if(loc>2)loc=2;
	dloc=(t8/exp10loc)%10;
	t8=t8-dloc*exp10loc;
	dloc++;
	if(dloc>9)dloc=0;
	t8+=(dloc*exp10loc);
	if(t8<=255){
	*value=t8;
	}else{
		*value=0;
	}
}

//adj my float value
void key_adj_value_float(st_float32_m* mfp,uint8_t loc)
{
    uint16_t t16;
    uint8_t t8;
    t16=mfp->stru.significand;
    if(loc<4){
        key_adj_value_fixed(&t16,loc);
        mfp->stru.significand=t16;
    }else if(loc==4){
        t8=mfp->stru.exponent;
        t8++;
        if(t8>3 )t8=0;
		if(mfp->stru.sign){
			if(t8>2)t8=0;
		}
        mfp->stru.exponent=t8;
    }else{
        t8=mfp->stru.sign;
        t8++;
        if(t8>1)t8=0;

        mfp->stru.sign=t8;
    }
	paramChangedFlag=true;
}

void key_process_up_down_variable_speed_ex(
	int16_t *val, int16_t min,int16_t max, bool up) {
    bool change = true;
    uint16_t speed = 0, t32;
    uint8_t key = keyValue;
	if(min>=max)return;
    //TMR1_Stop();
    TMR1_Start();
    ticker_ms_set(0);
    do {
        noEventTimeOut=NO_EVENT_TIME_MAX;
        if (change == true) {
            change = false;
            if (up) {
                (*val) += 1;
                if (*val > max)*val = max;
            } else {
                if (*val <= min)*val = min;
                else {
                    (*val) -= 1;
                }
            }
			ui_disp_menu();//bug stack meby over flow
        }
        key=get_key_value();
        if (key != keyValue)break;
        t32 = ticker_ms_get();
        if (t32 <= 1000) {
            if (t32 - speed >= 200) {
                speed = t32;
                change = true;
            }
        } else if (t32 <= 2000) {
            if (t32 - speed >= 100) {
                speed = t32;
                change = true;
            }
        } else {
            if (t32 - speed >= 20) {
                speed = t32;
                change = true;
            }
        }
    } while (1);
}

//set long time press process
void __enter_menu_password(void)
{	
	// stSysData.bpMenu=menu;
	// stSysData.bpSubMenu=subMenu;
	
	menu=MENU_PASSWORD;
	subMenu=0x00;
	
	passWord=0x00;
	adjLocation=0x00;
}

void __enter_menu_set_density(void)
{
	uint16_t t16;
	//int32_t t32;
	menu=MENU_SET_DENSITY;
	subMenu=sub_MENU_SET_DENSITY;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	//sysDataDef_t* fps= &stSysData;
	

	t16=stSysData.matterIndex;
    if(t16>5)t16=5;
	adjValue=0x00ul;
	*((uint16_t*)(&adjValue))=(uint16_t)(t16);
	
	//t32=stSysData.matterTab[t16].density;
	//t32=__int32_2_mflot32(t32);
	//m_floatAdj.t32=t32;
	adjLocation=0;
}
//
void __enter_menu_set_pose_size(void)
{
	menu=MENU_SET_POSE_SIZE;
	subMenu=sub_MENU_SET_POSE;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	adjValue=0x00ul;
	*((uint8_t*)(&adjValue))=(uint8_t)(fps->pos);
	adjLocation=0;
}

void __enter_menu_set_d(void){
	int32_t t32;
	subMenu=sub_MENU_SET_D;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	t32=fps->d;
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;
}

void __enter_menu_set_h(void){
	int32_t t32;
	subMenu=sub_MENU_SET_L;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	t32=(fps->h);
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;
}
//
void __enter_menu_set_base_zero(void)
{
	int32_t t32;

	menu=MENU_SET_BASE_ZERO;
	subMenu=0;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	t32=(fps->baseZero);
	*((uint16_t*)(&adjValue))=(uint16_t)t32;
	/*
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	if(m_floatAdj.stru.sign){
        adjLocation=1;
    }else{
        adjLocation=0;
    }
	*/
	
}
//
/*
void __enter_menu_calib_press_diff(void)
{
	//git pressure calib data
	int32_t t32;
	xCalibTab_t* stp;    
    
	menu=MENU_DIFF_CALIB;
	subMenu=0;
	calibRow=0;
	calibCol=0;

	stp=(xCalibTab_t*)(&diff_prCalibTabDef);
	t32=stp->prCalibRow[calibRow].prCalibPoint[calibCol].pValue;
    
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;
}
*/
void __enter_menu_calib_press_diff(uint8_t row,uint8_t col)
{
	//git pressure calib data
	int32_t t32;
	xCalibTab_t* stp;    
    
	menu=MENU_DIFF_CALIB;
	subMenu=0;
	calibRow=row;
	calibCol=col;
    stp=(xCalibTab_t*)(&calibTab0);
	if(col==0){
		*((uint8_t*)(&adjValue))=stp->calibRow[row].pCount;
	}else{
        t32=stp->calibRow[calibRow].calibPoint[calibCol-1].value;
        t32=__int32_2_mflot32(t32);
        m_floatAdj.t32=t32;        
    }
	paramChangedFlag=false;
	adjLocation=0;
}

//
void __enter_menu_calib_press(uint8_t row,uint8_t col)
{
	//git pressure calib data
	int32_t t32;
	xCalibTab_t* stp;    
    
	menu=MENU_PRESSURE_CALIB;
	subMenu=0;
	calibRow=row;
	calibCol=col;
    stp=(xCalibTab_t*)(&calibTab1);
    if(col==0){
        *((uint8_t*)(&adjValue))=stp->calibRow[row].pCount;
    }else{
        t32=stp->calibRow[calibRow].calibPoint[calibCol-1].value;
        t32=__int32_2_mflot32(t32);
        m_floatAdj.t32=t32;        
    }
	paramChangedFlag=false;
	adjLocation=0;
}

void __enter_menu_ex0_pr_calib(uint8_t row,uint8_t col)
{
	int32_t t32;
	xCalibTab_t* stp;    
    
	menu=MENU_PRESSURE_CALIB_EX0;
	subMenu=0;
	calibRow=row;
	calibCol=col;
    stp=(xCalibTab_t*)(&calibTab2);
    if(col==0){
        *((uint8_t*)(&adjValue))=stp->calibRow[row].pCount;
    }else{
        t32=stp->calibRow[calibRow].calibPoint[calibCol-1].value;
        t32=__int32_2_mflot32(t32);
        m_floatAdj.t32=t32;        
    }
	adjLocation=0;	
	paramChangedFlag=false;
}

void __enter_menu_ex1_pr_calib(uint8_t row,uint8_t col)
{
	int32_t t32;
	xCalibTab_t* stp;    
    
	menu=MENU_PRESSURE_CALIB_EX1;
	subMenu=0;
	calibRow=row;
	calibCol=col;
    stp=(xCalibTab_t*)(&calibTab3);
    if(col==0){
        *((uint8_t*)(&adjValue))=stp->calibRow[row].pCount;
    }else{
        t32=stp->calibRow[calibRow].calibPoint[calibCol-1].value;
        t32=__int32_2_mflot32(t32);
        m_floatAdj.t32=t32;        
    }
	paramChangedFlag=false;
	adjLocation=0;	
}
//二次标定

void __enter_menu_calib_dpr_2nd(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_CALIB_DPR_2ND;
	if(__subMenu>sub_MENU_CALIB_DPR_2ND_P1)__subMenu=sub_MENU_CALIB_DPR_2ND_P1;
	subMenu=__subMenu;

	t32=stSysData._2ndPrDiffCalib[subMenu].realValue;

	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;	
}
/*
void __enter_menu_calib_pr_2nd(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_CALIB_PR_2ND;
	if(__subMenu>sub_MENU_CALIB_DPR_2ND_P1)__subMenu=sub_MENU_CALIB_DPR_2ND_P1;
	subMenu=__subMenu;

	t32=stSysData._2ndPrCalib[subMenu].realValue;

	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}

void __enter_menu_calib_epr0_2nd(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_CALIB_EPR0_2ND;
	if(__subMenu>sub_MENU_CALIB_EPR0_2ND_P1)__subMenu=sub_MENU_CALIB_EPR0_2ND_P1;
	subMenu=__subMenu;

	t32=stSysData._2ndPrEx0[subMenu].realValue;

	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}

void __enter_menu_calib_epr1_2nd(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_CALIB_EPR1_2ND;
	if(__subMenu>sub_MENU_CALIB_EPR1_2ND_P1)__subMenu=sub_MENU_CALIB_EPR1_2ND_P1;
	subMenu=__subMenu;

	t32=stSysData._2ndPrEx1[subMenu].realValue;

	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}
*/
/*
void __enter_menu_calib_dpr_2nd(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_CALIB_DPR_2ND;
	if(__subMenu>sub_MENU_CALIB_DPR_2ND_P1)__subMenu=sub_MENU_CALIB_DPR_2ND_P1;
	subMenu=__subMenu;

	// t32=stSysData._2ndPrDiffCalib[subMenu].realValue;

	// t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;	
}
*/
void __enter_menu_calib_pr_2nd(uint8_t __subMenu)
{
	int32_t t32=0;
	menu=MENU_CALIB_PR_2ND;
	if(__subMenu>sub_MENU_CALIB_DPR_2ND_P1)__subMenu=sub_MENU_CALIB_DPR_2ND_P1;
	subMenu=__subMenu;

	// t32=stSysData._2ndPrCalib[subMenu].realValue;

	// t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}

void __enter_menu_calib_epr0_2nd(uint8_t __subMenu)
{
	int32_t t32=0;
	menu=MENU_CALIB_EPR0_2ND;
	if(__subMenu>sub_MENU_CALIB_EPR0_2ND_P1)__subMenu=sub_MENU_CALIB_EPR0_2ND_P1;
	subMenu=__subMenu;

	// t32=stSysData._2ndPrEx0[subMenu].realValue;

	// t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}

void __enter_menu_calib_epr1_2nd(uint8_t __subMenu)
{
	//int32_t t32;
	menu=MENU_CALIB_EPR1_2ND;
	if(__subMenu>sub_MENU_CALIB_EPR1_2ND_P1)__subMenu=sub_MENU_CALIB_EPR1_2ND_P1;
	subMenu=__subMenu;

	// t32=stSysData._2ndPrEx1[subMenu].realValue;

	// t32=__int32_2_mflot32(t32);
	//m_floatAdj.t32=t32;
	adjLocation=0;		
}
void __enter_menu_set_temp_ex0(uint8_t __subMenu)
{
    menu=MENU_SET_TMEP_EX0;
    subMenu=__subMenu;	
	//adjValue=(int32_t)(stSysData.tempCalibEx0[__subMenu].tempRes);
    adjLocation=0;      
    paramChangedFlag=false;	
}

void __enter_menu_set_temp_ex1(uint8_t __subMenu)
{
    menu=MENU_SET_TMEP_EX1;
    subMenu=__subMenu;
	//adjValue=(int32_t)(stSysData.tempCalibEx1[__subMenu].tempRes);
    adjLocation=0;    
	paramChangedFlag=false;
}

void __enter_menu_poly_coeffic(uint8_t __subMenu)
{
    menu=MENU_POLY_COEFFIC;
    subMenu=__subMenu;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	//adjValue=0x00ul;
	adjValue=(int32_t)(fps->ployCoeffic[subMenu]);
	adjLocation=0;   
	paramChangedFlag=false;	
}

void __enter_menu_poly_coeffic_mod(void)
{
    menu=MENU_POLY_COEFFIC_MOD;
    subMenu=sub_MENU_POLY_COEFFIC_MOD;

	//adjValue=(int32_t)(fps->ployCoeffic[subMenu]);
	
	if(stSysData.ployCoeffic[0]==1000){
		adjValue=0;
	}else if(stSysData.ployCoeffic[0]==400){
		adjValue=1;
	}else{
		adjValue=2;
	}
	adjLocation=0;   
	paramChangedFlag=false;		
}

void __enter_menu_warn_type(uint8_t __subMenu)
{
	menu=MENU_SET_WARN_TYPE;
	subMenu=__subMenu;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	adjValue=0x00ul;
	*((uint8_t*)(&adjValue))=(uint8_t)(fps->dprWarnSet[subMenu].type);
	adjLocation=0;	
}

void __enter_menu_warn_value(uint8_t __subMenu)
{
	uint8_t t8;
	int32_t t32;
	menu=MENU_SET_WARN_VALUE;
	subMenu=__subMenu;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	/*
	if(subMenu>=4){
		t32=fps->diffPressureWarnSet[subMenu-4].warnValueHi;
	}else{
		t32=fps->diffPressureWarnSet[subMenu].warnValueLo;
	}
	*/
	t8=subMenu >>1;
	if(subMenu & 0x01){
		//value hight
		t32=fps->dprWarnSet[t8].warnValueOop;
	}else{
		t32=fps->dprWarnSet[t8].warnValue;
	}
	
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;
}
/*
void __enter_menu_epr_calib(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_SET_EPR_ZERO_LINE;
	subMenu=__subMenu;
	//if(subMenu>sub_MENU_SET_EPR_LINE_1)subMenu=sub_MENU_SET_EPR_LINE_1;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
    sysDataDef_t* fps= &stSysData;
	switch(subMenu){
		case sub_MENU_SET_EPR_CH0_P0:t32=fps->exPr0Calib[0].value;break;
		case sub_MENU_SET_EPR_CH0_P1:t32=fps->exPr0Calib[1].value;break;
		case sub_MENU_SET_EPR_CH1_P0:t32=fps->exPr1Calib[0].value;break;
		case sub_MENU_SET_EPR_CH1_P1:t32=fps->exPr1Calib[1].value;break;
		default:return;
	}

	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;	
}
*/
/*
void __enter_menu_etemp_calib(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_SET_ETMEP_ZERO_LINE;
	subMenu=__subMenu;
	//sysDataDef_t* fps= &stSysData;
	if(subMenu>1){
		subMenu=0;
	}
    if(subMenu==0){
        t32=18520;
    }else if(subMenu==1){
        t32=100000;
    }
	//t32=fps->exTempCalib[subMenu].value;
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;		
}
*/

void __enter_menu_ilp_scale(uint8_t __subMenu)
{
	menu=MENU_SET_ILOOP_SCALE;
	subMenu=__subMenu;
    int32_t t32=0;
    sysDataDef_t* fps= &stSysData;
	switch(subMenu)
	{
		case sub_MENU_SET_ILP_CH0_Lo:t32=fps->IpScaleCh0.ilpLow;break;
		case sub_MENU_SET_ILP_CH0_Hi:t32=fps->IpScaleCh0.ilpHi;break;
		case sub_MENU_SET_ILP_CH1_Lo:t32=fps->IpScaleCh1.ilpLow;break;
		case sub_MENU_SET_ILP_CH1_Hi:t32=fps->IpScaleCh1.ilpHi;break;
		default:return;
	}
    
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;	
}

void __enter_menu_ilp_adjust(uint8_t __subMenu)
{
    int16_t t16=0;    
	menu=MENU_SET_ILOOP_ADJUST;
	subMenu=__subMenu;

    //sysDataDef_t* fps= &stSysData;
	switch(subMenu)
	{
		case sub_MENU_SET_ILP_ADJUST_CH0_Lo:t16=stSysData.ilpAdjustCh0.valueLo;break;
		case sub_MENU_SET_ILP_ADJUST_CH0_Hi:t16=stSysData.ilpAdjustCh0.valueHi;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Lo:t16=stSysData.ilpAdjustCh1.valueLo;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Hi:t16=stSysData.ilpAdjustCh1.valueHi;break;

		default:break;
	}
    *((int16_t*)(&adjValue))=t16;
	adjLocation=0;	
}

void __enter_menu_bar_scale(void)
{
	menu=MENU_SET_BAR_LEVEL_SCALE;
	subMenu=sub_MENU_SET_BAR_LEVEL_SCALE;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	adjValue=fps->barScale;
	adjLocation=0;
}

void __enter_menu_work_mode(void)
{
	menu=MENU_SET_WORK_MODE;
	subMenu=sub_MENU_SET_WORK_MODE;
	*((uint8_t*)(&adjValue))=dwm;
	adjLocation=0;
}

void __enter_menu_set_ext_show_mode(void)
{
	menu=MENU_SET_EX_PR_TEMP_SHOW;
	subMenu=sub_MENU_SET_EX_PR_TEMP_SHOW;
	*((uint8_t*)(&adjValue))=stSysData.exPrTempShowEn;
	adjLocation=0;	
}



void __enter_menu_set_wakeup_period(void)
{
	menu=MENU_SET_WAKEUP_PERIOD;
	subMenu=sub_MENU_SET_WAKEUP_PERIOD;
	adjValue=0;
	*((uint16_t*)(&adjValue))=stSysData.sleepPeriod;
	adjLocation=0;	
}

void __enter_menu_set_rf_send_period(void)
{
	menu=MENU_SET_RF_SEND_PERIOD;
	subMenu=sub_MENU_SET_RF_SEND_PERIOD;
	adjValue=0;
	*((uint16_t*)(&adjValue))=stSysData.rfSendPeriod;
	adjLocation=0;		
}

void __enter_menu_set_bl_on_tm(void)
{
	menu=MENU_PSW_SET_BL_ON_TM;
	subMenu=sub_MENU_PSW_SET_BL_ON_TM;
	*((uint8_t*)(&adjValue))=stSysData.blOnTm;
	adjLocation=0;		
}

void __enter_menu_set_lcd_on_tm(void)
{
	menu=MENU_PSW_SET_LCD_ON_TM;
	subMenu=sub_MENU_PSW_SET_LCD_ON_TM;
	*((uint8_t*)(&adjValue))=stSysData.lcdOnTime;
	adjLocation=0;		
}

void __enter_menu_set_modbus_addr(void)
{
	menu=MENU_PSW_SET_MODBUS_ID;
	subMenu=sub_MENU_PSW_SET_MODBUS_ID;
	*((uint8_t*)(&adjValue))=stSysData.ModbusId;
	adjLocation=0;		
}
void __exit_menu_to_home_unsave(void)
{
	//menu=MENU_HOME;
	//subMenu=0x00;
	
	menu=stSysData.bpMenu;
	subMenu=stSysData.bpSubMenu;
	
	adjValue=0;
	m_floatAdj.t32=0;
	adjLocation=0x00;
	
	calibRow=0;
	calibCol=0;
	passWord=0x00;
}

void __down_base_zero_adj(void)
{
	//key_adj_value_float(&m_floatAdj,adjLocation);
	//int16_t *val, int16_t min,int16_t max, bool up)
	int32_t t32=0;
	int16_t max,min;
	if(stSysData.pos==HOTIZONTAL){
        if(t32>(int32_t)(stSysData.d))t32=(int32_t)(stSysData.d);
    }else{
        if(t32>(int32_t)(stSysData.h + (stSysData.d * 2)))t32=(int32_t)(stSysData.h + (stSysData.d * 2));
    }		
	if(t32>32767)t32=32767;
	if(t32<1000)t32=1000;
	max=(int16_t)t32;
	min=(0-max);
	key_process_up_down_variable_speed_ex((int16_t*)(&adjValue),min,max,true);
}

void __down_pose_size(void)
{
	switch(subMenu){
	case sub_MENU_SET_L:
	case sub_MENU_SET_D:
		key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
	default:break;
	}
}

void __down_density(void)
{
	if(subMenu==sub_MENU_SET_DENSITY_CUSTOM){
		key_shift_loc((uint8_t*)(&adjLocation),0,3);
	}
}

void __down_dpr_calib(void)
{
	if(calibCol){
		key_shift_loc((uint8_t*)(&adjLocation),0,4);
	}
}

void __down_ex0_pr_calib(void)
{
	if(calibCol){
		key_shift_loc((uint8_t*)(&adjLocation),0,4);
	}    
}

void __down_ex1_pr_calib(void)
{
	if(calibCol){
		key_shift_loc((uint8_t*)(&adjLocation),0,4);
	}    
}

void __down_pr_calib(void)
{
	if(calibCol){
		key_shift_loc((uint8_t*)(&adjLocation),0,4);
	}
}

void __down_home_adj(void)
{
	uint8_t t8;
    //t8=(subMenu & 0xf0);
    //t8>>=4;
	t8=subMenu & 0x0f;
    t8++;
	#if DEBUG_EX_TEMP_EN
	if(t8>3)t8=0;
	#else
    if(t8>2)t8=0;
	#endif
    //t8<<=4;
    subMenu &= 0xf0;
    subMenu |= t8;	
	
	stSysData.bpMenu=menu;
	stSysData.bpSubMenu=subMenu;	
	__sys_data_save_write_flash();
	
}

void __down_home_adj_test(void)
{
	uint8_t t8;
    //t8=(subMenu & 0xf0);
    //t8>>=4;
	t8=subMenu & 0x0f;
    t8++;
    if(t8>10)t8=0;
    //t8<<=4;
    subMenu &= 0xf0;
    subMenu |= t8;		
}
void __down_ilp_adjust_value_adj(void)
{
	
	key_process_up_down_variable_speed_ex((int16_t*)(&adjValue),-500,1000,false);
}

void __down_poly_coefic_adj_mod(void)
{

	if(adjValue==0)adjValue=2;
	else{
		adjValue--;
	}
	
	if(adjValue>2)adjValue=0;
	
	if(adjValue==0){
		stSysData.ployCoeffic[0]=1000;
		stSysData.ployCoeffic[1]=0;
		stSysData.ployCoeffic[2]=0;
		stSysData.ployCoeffic[3]=0;
	}else if(adjValue==1){
		
		stSysData.ployCoeffic[0]=400;
		stSysData.ployCoeffic[1]=300;
		stSysData.ployCoeffic[2]=200;
		stSysData.ployCoeffic[3]=100;	
	}else{
		stSysData.ployCoeffic[0]=600;
		stSysData.ployCoeffic[1]=200;
		stSysData.ployCoeffic[2]=100;
		stSysData.ployCoeffic[3]=100;			
	}

}
/*
key_shift_loc(*loc,min,max)
loc:up键修改的位置;0-3表示(个位到千位)数位级，4表示小数点，5表示符号
*/
void key_process_down(void)
{
	switch(menu){
		#if LCD_TEST_EX_EN==1
		case MENU_HOME:__down_home_adj_test();break;
		#else 
		case MENU_HOME:__down_home_adj();break;
		#endif
		case MENU_PASSWORD:key_shift_loc((uint8_t*)(&adjLocation),0,3);break;
		case MENU_SET_DENSITY:__down_density();break;
		case MENU_SET_POSE_SIZE:__down_pose_size();break;
		//case MENU_SET_BASE_ZERO:key_shift_loc((uint8_t*)(&adjLocation),0,5);break;
		case MENU_SET_BASE_ZERO:__down_base_zero_adj();break;

		case MENU_DIFF_CALIB:__down_dpr_calib();break;
		case MENU_PRESSURE_CALIB:__down_pr_calib();break;
		case MENU_POLY_COEFFIC:key_shift_loc((uint8_t*)(&adjLocation),0,3);break;
		case MENU_SET_WARN_TYPE:break;
		case MENU_SET_WARN_VALUE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		//case MENU_SET_EPR_ZERO_LINE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
        case MENU_PRESSURE_CALIB_EX0:__down_ex0_pr_calib();break;
        case MENU_PRESSURE_CALIB_EX1:__down_ex1_pr_calib();break;
		//case MENU_SET_ETMEP_ZERO_LINE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_SET_TMEP_EX0:
		case MENU_SET_TMEP_EX1:			paramChangedFlag=!(paramChangedFlag);break;

		case MENU_SET_ILOOP_SCALE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		//case MENU_SET_BAR_LEVEL_SCALE:key_shift_loc((uint8_t*)(&adjLocation),0,2);break;
		//
		case MENU_SET_ILOOP_ADJUST:__down_ilp_adjust_value_adj();break;
		case MENU_POLY_COEFFIC_MOD:__down_poly_coefic_adj_mod();			break;
		case MENU_CALIB_DPR_2ND:	key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_CALIB_PR_2ND:
		case MENU_CALIB_EPR0_2ND:
		case MENU_CALIB_EPR1_2ND:	
		//key_shift_loc((uint8_t*)(&adjLocation),0,4);
		//paramChangedFlag=false;
		break;
		case MENU_PSW_SET_LCD_ON_TM:key_shift_loc((uint8_t*)(&adjLocation),0,2);break;
		case MENU_PSW_SET_MODBUS_ID:key_shift_loc((uint8_t*)(&adjLocation),0,2);break;	
		default:break;
	}	
}

void __up_home_adj(void)
{
    uint8_t t8;
	//st_homeSubMenu sub;
	//sub.t8=subMenu;
    //t8=sub.stru.upLineMenu;
    t8=(subMenu & 0xf0);
    t8>>=4;
    t8++;
	#if DEBUG_EX_TEMP_EN
	if(t8>3)t8=0;
	#else
    if(t8>2)t8=0;
	#endif
    t8<<=4;
    subMenu &= 0x0f;
    subMenu |= t8;
    
	stSysData.bpMenu=menu;
	stSysData.bpSubMenu=subMenu;
	__sys_data_save_write_flash();
	//if(subMenu>sub_MENU_HOME_02)subMenu=sub_MENU_HOME_00;
}

void __up_psw_adj(void)
{
	key_adj_value_fixed((uint16_t*)(&passWord),adjLocation);
}

void __up_density_adj_sel_matter(void)
{
	uint32_t t32;
	//uint16_t *p16;
	//*p16=(uint16_t*)(&adjValue);
	//(*p16)++;
	//if(*p16>5)*p16=0;
	adjValue++;
    if(adjValue>5)adjValue=0;
	t32=stSysData.matterTab[adjValue].density;
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;	
	adjLocation=0;
}
void __up_density_adj(void)
{
	//key_adj_value_float(&m_floatAdj,adjLocation);
	
	switch(subMenu){
		case sub_MENU_SET_SEL_MATTER:__up_density_adj_sel_matter();break;
		case sub_MENU_SET_DENSITY_CUSTOM:key_adj_value_fixed((uint16_t*)&adjValue,adjLocation);break;
		default:break;
	}
}

void __up_pose_size_adj(void)
{
	uint8_t* p;
	switch(subMenu){
		case sub_MENU_SET_POSE:
			p=(uint8_t*)(&adjValue);
			(*p)=(*p)+1;
			if(*p>VERTICAL)*p=HOTIZONTAL;
			break;
		case sub_MENU_SET_L:
		case sub_MENU_SET_D:
			key_adj_value_float(&m_floatAdj,adjLocation);
			break;
		default:break;
	}
}

void __up_base_zero_adj(void)
{
	//key_adj_value_float(&m_floatAdj,adjLocation);
	//int16_t *val, int16_t min,int16_t max, bool up)
	int32_t t32=0;
	int16_t max,min;
	if(stSysData.pos==HOTIZONTAL){
        if(t32>(int32_t)(stSysData.d))t32=(int32_t)(stSysData.d);
    }else{
        if(t32>(int32_t)(stSysData.h + (stSysData.d * 2)))t32=(int32_t)(stSysData.h + (stSysData.d * 2));
    }			
	if(t32>32767)t32=32767;
	if(t32<1000)t32=1000;
	max=(int16_t)t32;
	min=(0-max);	
	key_process_up_down_variable_speed_ex((int16_t*)(&adjValue),min,max,false);
}



void __up_diff_calib_adj(void)
{
	uint8_t t8;
	if(calibCol==0){
		t8=*(uint8_t*)(&adjValue);
		t8++;
		if(t8>=6)t8=0;
		if(t8==1)t8=2;
		*(uint8_t*)(&adjValue)=t8;
	}else{
		key_adj_value_float(&m_floatAdj,adjLocation);
		paramChangedFlag=true;
	}
	
}

void __up_pr_calib_adj(void)
{
	uint8_t t8;
	if(calibCol==0){
		t8=*(uint8_t*)(&adjValue);
		t8++;
		if(t8>=6)t8=0;
		if(t8==1)t8=2;
		*(uint8_t*)(&adjValue)=t8;
	}else{	
		key_adj_value_float(&m_floatAdj,adjLocation);
		paramChangedFlag=true;
	}
}
//__up_ex0_pr_calib_adj
void __up_ex0_pr_calib_adj(void)
{
	uint8_t t8;
	if(calibCol==0){
		t8=*(uint8_t*)(&adjValue);
		t8++;
		if(t8>=6)t8=0;
		if(t8==1)t8=2;
		*(uint8_t*)(&adjValue)=t8;
	}else{	
		key_adj_value_float(&m_floatAdj,adjLocation);
		paramChangedFlag=true;
	}
}
void __up_ex1_pr_calib_adj(void)
{
	uint8_t t8;
	if(calibCol==0){
		t8=*(uint8_t*)(&adjValue);
		t8++;
		if(t8>=6)t8=0;
		if(t8==1)t8=2;
		*(uint8_t*)(&adjValue)=t8;
	}else{	
		key_adj_value_float(&m_floatAdj,adjLocation);
		paramChangedFlag=true;
	}
}
void __up_poly_coefic_adj(void)
{
	key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
}

void __up_poly_coefic_adj_mod(void)
{
	adjValue++;
	if(adjValue>2)adjValue=0;
	if(adjValue==0){
		stSysData.ployCoeffic[0]=1000;
		stSysData.ployCoeffic[1]=0;
		stSysData.ployCoeffic[2]=0;
		stSysData.ployCoeffic[3]=0;
	}else if(adjValue==1){
		
		stSysData.ployCoeffic[0]=400;
		stSysData.ployCoeffic[1]=300;
		stSysData.ployCoeffic[2]=200;
		stSysData.ployCoeffic[3]=100;	
	}else{
		stSysData.ployCoeffic[0]=600;
		stSysData.ployCoeffic[1]=200;
		stSysData.ployCoeffic[2]=100;
		stSysData.ployCoeffic[3]=100;			
	}

}



void __up_warn_type_adj(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	(*p)=(*p)+1;
	if(*p>PRESSURE_LO)*p=HIGHT_HI;
}

void __up_warn_value_adj(void)
{
	key_adj_value_float(&m_floatAdj,adjLocation);
}
/*
void __up_epr_calib_adj(void)
{
	switch(subMenu){
		case sub_MENU_SET_EPR_CH0_P0:
		case sub_MENU_SET_EPR_CH0_P1:
			// key_adj_value_float(&m_floatAdj,adjLocation);
			// break;
		case sub_MENU_SET_EPR_CH1_P0:
		case sub_MENU_SET_EPR_CH1_P1:
			//key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
			key_adj_value_float(&m_floatAdj,adjLocation);
			break;
		default:break;
	}
}
*/
void __up_etemp_calib_adj(void)
{
	key_adj_value_float(&m_floatAdj,adjLocation);
}

void __up_epr_ilp_scale_adj(void)
{
	//key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
	key_adj_value_float(&m_floatAdj,adjLocation);
}

void __up_ilp_adjust_value_adj(void)
{
	key_process_up_down_variable_speed_ex((int16_t*)(&adjValue),-500,1000,true);
}

//-----------------------------------------------------
/*
void __up_adj_bar_level_scale(void)
{
	key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
}
*/
void __up_adj_bar_level_scale(void)
{
	uint16_t t16;
	//t16=*((uint16_t*)(&adjValue));
	t16=(uint16_t)adjValue;
	if(t16==900){
		t16=950;
	}else if(t16==950){
		t16=1000;
	}else{
		t16=900;
	}
	adjValue=t16;
}
void __up_adj_work_mode(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	if(*p==TEST_MODE){
		*p=WORK_MODE;
	}else{
		*p=TEST_MODE;
	}
}

void __up_adj_ext_show_mode(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	if(*p!=0){
		*p=0;
	}else{
		*p=1;
	}		
}



void __up_adj_wakeup_period(void)
{
	uint16_t t16;
	t16=(*(uint16_t*)(&adjValue));
	switch(t16){
		case 0:t16=2;break;
		case 2:t16=4;break;
		case 4:t16=6;break;
		case 6:t16=10;break;
		
		case 10:t16=20;break;
		case 20:t16=40;break;
		case 40:t16=60;break;
		case 60:t16=100;break;
		/*
		case 100:t16=200;break;
		case 200:t16=400;break;
		case 400:t16=600;break;
		case 600:t16=1000;break;	
		*/
		default:t16=0;break;
	}
	(*(uint16_t*)(&adjValue))=t16;
}

void __up_adj_rf_send_period(void)
{
	uint16_t t16;
	t16=(*(uint16_t*)(&adjValue));
	switch(t16){
		case 1:t16=2;break;
		case 2:t16=4;break;
		case 4:t16=6;break;
		case 6:t16=10;break;
		
		case 10:t16=20;break;
		case 20:t16=40;break;
		case 40:t16=60;break;
		case 60:t16=100;break;	
		default:t16=1;break;
	}
	(*(uint16_t*)(&adjValue))=t16;	
}

void __up_adj_bl_on_tm(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	if(*p==0){
		*p=10;
	}else if(*p==10){
		*p=30;
	}else if(*p==30){
		*p=60;
	}else{
		*p=0;
	}		

}

void __up_adj_lcd_on_tm(void)
{
	key_adj_value_fixed_t8((uint8_t*)(&adjValue),adjLocation);
}

void __up_adj_modbus_id(void)
{
	key_adj_value_fixed_t8((uint8_t*)(&adjValue),adjLocation);
}

void key_process_up(void)
{
	switch(menu){
		case MENU_HOME:					__up_home_adj();				break;
		case MENU_PASSWORD:				__up_psw_adj();					break;
		case MENU_SET_DENSITY:			__up_density_adj();				break;
		case MENU_SET_POSE_SIZE:		__up_pose_size_adj();			break;
		case MENU_SET_BASE_ZERO:		__up_base_zero_adj();			break;
		case MENU_DIFF_CALIB:			__up_diff_calib_adj();			break;
		case MENU_PRESSURE_CALIB:		__up_pr_calib_adj();			break;
		case MENU_POLY_COEFFIC:			__up_poly_coefic_adj();			break;
		case MENU_SET_WARN_TYPE:		__up_warn_type_adj();			break;
		case MENU_SET_WARN_VALUE:		__up_warn_value_adj();			break;
		//case MENU_SET_EPR_ZERO_LINE:	__up_epr_calib_adj();			break;
        case MENU_PRESSURE_CALIB_EX0:   __up_ex0_pr_calib_adj();			break;
        case MENU_PRESSURE_CALIB_EX1:   __up_ex1_pr_calib_adj();			break;
		//case MENU_SET_ETMEP_ZERO_LINE:	__up_etemp_calib_adj();			break;
		case MENU_SET_TMEP_EX0:
		case MENU_SET_TMEP_EX1:			paramChangedFlag=!(paramChangedFlag);break;
		
		
		case MENU_SET_ILOOP_SCALE:		__up_epr_ilp_scale_adj();		break;
		
		case MENU_SET_BAR_LEVEL_SCALE:	__up_adj_bar_level_scale();	break;
		case MENU_SET_WORK_MODE:        __up_adj_work_mode();		break;
		//case 
		//改版后增加
		case MENU_SET_EX_PR_TEMP_SHOW:__up_adj_ext_show_mode();break;
		
		//
		case MENU_SET_WAKEUP_PERIOD:__up_adj_wakeup_period();break;
		case MENU_SET_RF_SEND_PERIOD:__up_adj_rf_send_period();break;
		case MENU_SET_ILOOP_ADJUST:__up_ilp_adjust_value_adj();break;
		//修改滤波多现实
		case MENU_POLY_COEFFIC_MOD:__up_poly_coefic_adj_mod();			break;
		//二次修正
		case MENU_CALIB_DPR_2ND:	key_adj_value_float(&m_floatAdj,adjLocation);break;
		case MENU_CALIB_PR_2ND:
		case MENU_CALIB_EPR0_2ND:
		case MENU_CALIB_EPR1_2ND:	
			paramChangedFlag=!paramChangedFlag;
			//key_adj_value_float(&m_floatAdj,adjLocation);break;
			break;
		case MENU_PSW_SET_BL_ON_TM:__up_adj_bl_on_tm();break;
		case MENU_PSW_SET_LCD_ON_TM:__up_adj_lcd_on_tm();break;
		case MENU_PSW_SET_MODBUS_ID:__up_adj_modbus_id();break;
		default:break;
	}		
}


void key_process_set_up_long(void)
{
	if(menu==MENU_PASSWORD){
		switch(passWord){
		case PSW_SET_DENSITY:           __enter_menu_set_density();             break;
		case PSW_SET_POSE_SIZE:         __enter_menu_set_pose_size();           break;  
		case PSW_SET_BASE_ZERO:         __enter_menu_set_base_zero();           break;
		case PSW_CALIB_DIFF_PRESSURE:   __enter_menu_calib_press_diff(0,0);     break;
		case PSW_CALIB_PRESSURE:        __enter_menu_calib_press(0,0);          break;   
		case PSW_SET_POLY_COEFFIC:		__enter_menu_poly_coeffic(0);			break;
		case PSW_SET_WARN_TYPE:			__enter_menu_warn_type(0);				break;
		case PSW_SET_WARN_VALUE:		__enter_menu_warn_value(0);				break;
		//case PSW_SET_EPR_ZERO_LINE:		__enter_menu_epr_calib(0);			break;
		case PSW_CALIB_PRESSURE_EX0:	__enter_menu_ex0_pr_calib(0,0);     	break;
		case PSW_CALIB_PRESSURE_EX1:	__enter_menu_ex1_pr_calib(0,0);     	break;
		
		//case PSW_SET_ETMEP_ZERO_LINE:	__enter_menu_etemp_calib(0);			break;
		case PSW_SET_TMEP_EX0:			__enter_menu_set_temp_ex0(0);			break;
		case PSW_SET_TMEP_EX1:			__enter_menu_set_temp_ex1(0);			break;
		
		case PSW_SET_ILOOP_SCALE:       __enter_menu_ilp_scale(0);				break;
		case PSW_SET_BAR_LEVEL_SCALE:	__enter_menu_bar_scale();				break;
		case PSW_SET_WORK_MODE:			__enter_menu_work_mode();				break;
		
		//
		case PSW_SET_EX_PR_TEMP_SHOW:	__enter_menu_set_ext_show_mode();		break;
		case PSW_SET_BL_ON_TM:			__enter_menu_set_bl_on_tm();			break;
		//
		case PSW_SET_WAKEUP_PERIOD:		__enter_menu_set_wakeup_period();		break;
		case PSW_SET_RF_SEND_PERIOD:	__enter_menu_set_rf_send_period();		break;
		case PSW_SET_ILOOP_ADJUST:		__enter_menu_ilp_adjust(0);				break;
		//修改滤波多项式
		case PSW_SET_POLY_COEFFIC_MOD:	__enter_menu_poly_coeffic_mod();		break;
		//二次 标定
		case PSW_CALIB_DPR_2ND:			__enter_menu_calib_dpr_2nd(0);			break;
		case PSW_CALIB_PR_2ND:			__enter_menu_calib_pr_2nd(0);			break;
		
		case PSW_CALIB_EPR0_2ND:		__enter_menu_calib_epr0_2nd(0);			break;
		case PSW_CALIB_EPR1_2ND:		__enter_menu_calib_epr1_2nd(0);			break;
		//2018.02.08增加
		case PSW_SET_LCD_ON_TM:			__enter_menu_set_lcd_on_tm();			break;
		case PSW_SET_MODBUS_ID:			__enter_menu_set_modbus_addr();			break;
		default:break;
		}
	}	
}
/*
void key_process_set_down_long(void)
{
	if(menu==MENU_PASSWORD){
		switch(passWord){
		case PSW_SET_DENSITY:           __enter_menu_set_density();             break;
		case PSW_SET_POSE_SIZE:         __enter_menu_set_pose_size();           break;  
		case PSW_SET_BASE_ZERO:         __enter_menu_set_base_zero();           break;
		case PSW_CALIB_DIFF_PRESSURE:   __enter_menu_calib_press_diff(0,0);     break;
		case PSW_CALIB_PRESSURE:        __enter_menu_calib_press(0,0);          break;   
		case PSW_SET_POLY_COEFFIC:		__enter_menu_poly_coeffic(0);			break;
		case PSW_SET_WARN_TYPE:			__enter_menu_warn_type(0);				break;
		case PSW_SET_WARN_VALUE:		__enter_menu_warn_value(0);				break;
		case PSW_SET_EPR_ZERO_LINE:		__enter_menu_epr_calib(0);			break;
		case PSW_SET_EPR_ILOOP_SCALE:	__enter_menu_epr_ilp_scale(0);			break;
		case PSW_SET_BAR_LEVEL_SCALE:	__enter_menu_bar_scale();				break;
		case PSW_SET_WORK_MODE:			__enter_menu_work_mode();				break;
		default:break;
		}
	}
}
*/
//============================================================================


//============================================================================
void __set_short_density(void)
{
	//int32_t t32;
	if(subMenu==sub_MENU_SET_SEL_MATTER){
		//if(adjValue==0x05){
			tmpAdjValue=adjValue;
			adjValue=stSysData.matterTab[tmpAdjValue].density;
			adjLocation=0;
			subMenu=sub_MENU_SET_DENSITY_CUSTOM;
		//}
	}else{
		
		stSysData.matterTab[tmpAdjValue].density=adjValue;
		stSysData.matterIndex=(uint16_t)tmpAdjValue;
		__sys_data_save_write_flash();	
		adjValue=tmpAdjValue;
		tmpAdjValue=0;
		adjLocation=0;
		
		subMenu=sub_MENU_SET_SEL_MATTER;
	}
}

void __set_short_pose_size(bool gohome)
{
	uint8_t* p;
	int32_t t32;
	//sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	//m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));
	sysDataDef_t* stp=&stSysData;
	switch(subMenu){
        case sub_MENU_SET_POSE:
            p=(uint8_t*)(&adjValue);
			stp->pos=(*p);
			break;
		case sub_MENU_SET_L:
			t32=__mflot32_2_int32(m_floatAdj.t32);
			stp->h=t32;
            break;
		case sub_MENU_SET_D:
            t32=__mflot32_2_int32(m_floatAdj.t32);
            stp->d=t32;
			break;
    }
	__sys_data_save_write_flash();
	if(gohome){__exit_menu_to_home_unsave(); return;}
    subMenu++;
    if(subMenu>sub_MENU_SET_D)subMenu=sub_MENU_SET_POSE;
    switch(subMenu){
        case sub_MENU_SET_POSE: __enter_menu_set_pose_size();   break;
        case sub_MENU_SET_L:    __enter_menu_set_h();           break;
        case sub_MENU_SET_D:    __enter_menu_set_d();           break;
        default:break;
    }
}
extern st_iicDeviceObj* pdiff_prEepromObj;
extern st_iicDeviceObj* p_prEepromObj;
/*
void __set_short_calib_x(calibDataObj_t* calibobj,__xDataStruct_t* xdata,bool gohome)
{
	xCalibTab_t* calibCol=calibobj->calibTab;
	iicDeviceObj_t* eep24c02=calibobj->eep24c02;
    bool saveFlg=false;
    uint8_t t8,adjv;
	uint16_t t16;
    uint32_t t32,pra;
    if(calibCol==0){
        t8=calib->calibRow[calibRow].pCount;
        adjv=*(uint8_t*)(&adjValue);
        if(t8!=adjv){
            saveFlg=true;
            calib->calibRow[calibRow].pCount=adjv;
        }
    }else{
        t32=__mflot32_2_int32(m_floatAdj.t32);
        pra=calib->calibRow[calibRow].calibPoint[calibCol-1].value;
        if(pra!=t32 || paramChangedFlag){
            calib->calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calib->calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=x_prDiffData.sigAdcValue;
            calib->calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=x_prDiffData.tAdcValue;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(xCalibTab_t);
		crc_append((uint8_t*)calib,t16-2);
		at24c02_write_n_byte(eep24c02,0,(uint8_t*)calib,t16);     
        at24c02_read_n_byte(eep24c02,0,globleBuffer,t16);
        if(!m_str_cmp_len((uint8_t*)calib,globleBuffer,t16)){
            __nop();
        }
		 paramChangedFlag=0;
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol > calib->calibRow[calibRow].pCount){
        calibCol=0;
        calibRow++;
        if(calibRow>2)calibRow=0;
    }
    //__enter_menu_calib_press_diff(calibRow,calibCol);
	
}
*/
void __set_short_diff_calib(bool gohome)
{
    bool saveFlg=false;
    uint8_t t8,adjv;
	uint16_t t16;
    uint32_t t32,pra;
    if(calibCol==0){
        t8=calibTab0.calibRow[calibRow].pCount;
        adjv=*(uint8_t*)(&adjValue);
        if(t8!=adjv){
            saveFlg=true;
            calibTab0.calibRow[calibRow].pCount=adjv;
        }
    }else{
        t32=__mflot32_2_int32(m_floatAdj.t32);
        pra=calibTab0.calibRow[calibRow].calibPoint[calibCol-1].value;
        if(pra!=t32 || paramChangedFlag){
            calibTab0.calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calibTab0.calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=x_prDiffData.sigAdcValue;
            calibTab0.calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=x_prDiffData.tAdcValue;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(calibTab0);
		crc_append((uint8_t*)&calibTab0,t16-2);
		at24c02_write_n_byte(&at24c02Obj0,0,(uint8_t*)&calibTab0,t16);     
        at24c02_read_n_byte(&at24c02Obj0,0,globleBuffer,t16);
        if(!m_str_cmp_len((uint8_t*)&calibTab0,globleBuffer,t16)){
            __nop();
        }
		//标定数据的时候清除HB
		stSysData.baseZero=0;
		__sys_data_save_write_flash();
		paramChangedFlag=0;
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol>calibTab0.calibRow[calibRow].pCount){
        calibCol=0;
        calibRow++;
        if(calibRow>2)calibRow=0;
    }
    __enter_menu_calib_press_diff(calibRow,calibCol);
	
}

void __set_short_pr_calib(bool gohome)
{
    bool saveFlg=false;
    uint8_t t8,adjv;
	uint16_t t16;
    uint32_t t32,pra;
    if(calibCol==0){
        t8=calibTab1.calibRow[calibRow].pCount;
        adjv=*(uint8_t*)(&adjValue);
        if(t8!=adjv){
            saveFlg=true;
            calibTab1.calibRow[calibRow].pCount=adjv;
        }
    }else{
        t32=__mflot32_2_int32(m_floatAdj.t32);
        pra=calibTab1.calibRow[calibRow].calibPoint[calibCol-1].value;
        if(pra!=t32 || paramChangedFlag){
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=x_prData.sigAdcValue;
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=x_prData.tAdcValue;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(calibTab1);
		crc_append((uint8_t*)&calibTab1,t16-2);
		at24c02_write_n_byte(&at24c02Obj1,0,(uint8_t*)&calibTab1,t16);  
		at24c02_read_n_byte(&at24c02Obj1,0,globleBuffer,t16);
		paramChangedFlag=0;	
    }
    //保存静压误差
    if(saveFlg){
        saveFlg=0;
        if(calibRow==0){
            if(calibCol==1){
                calibTab0.staticPreAdj0.pr=t32;
                calibTab0.staticPreAdj0.diffPrZero=rtDiffPrOriginal;
                saveFlg=1;
            }
            if(calibCol==calibTab1.calibRow[calibRow].pCount){
                calibTab0.staticPreAdj1.pr=t32;
                calibTab0.staticPreAdj1.diffPrZero=rtDiffPrOriginal;                
                saveFlg=1;
            }
        }
    }
    if(saveFlg){
        t16=sizeof(calibTab0);
        crc_append((uint8_t*)&calibTab0,t16-2);
        at24c02_write_n_byte(&at24c02Obj0,0,(uint8_t*)&calibTab0,t16);     
        at24c02_read_n_byte(&at24c02Obj0,0,globleBuffer,t16);
        if(!m_str_cmp_len((uint8_t*)&calibTab0,globleBuffer,t16)){
            __nop();
        }
		paramChangedFlag=0;            
    }	
	saveFlg=0;
    //保存静压误差 end
	paramChangedFlag=0; 
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol>calibTab1.calibRow[calibRow].pCount){
        calibCol=0;
        calibRow++;
        if(calibRow>2)calibRow=0;
    }
    __enter_menu_calib_press(calibRow,calibCol);
	
}

void __set_short_ex0_pr_calib(bool gohome)
{
    bool saveFlg=false;
    uint8_t t8,adjv;
	uint16_t t16;
    uint32_t t32,pra;
	// calibTab1
	// at24c02Obj1
	// x_prData
    if(calibCol==0){
        t8=calibTab2.calibRow[calibRow].pCount;
        adjv=*(uint8_t*)(&adjValue);
        if(t8!=adjv){
            saveFlg=true;
            calibTab2.calibRow[calibRow].pCount=adjv;
        }
    }else{
        t32=__mflot32_2_int32(m_floatAdj.t32);
        pra=calibTab2.calibRow[calibRow].calibPoint[calibCol-1].value;
        if(pra!=t32 || paramChangedFlag){
            calibTab2.calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calibTab2.calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=x_ex0prData.sigAdcValue;
            calibTab2.calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=x_ex0prData.tAdcValue;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(calibTab2);
		crc_append((uint8_t*)&calibTab2,t16-2);
		at24c02_write_n_byte(&at24c02Obj2,0,(uint8_t*)&calibTab2,t16);   
		at24c02_read_n_byte(&at24c02Obj2,0,globleBuffer,t16);	
		paramChangedFlag=0;	
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol>calibTab2.calibRow[calibRow].pCount){
        calibCol=0;
        calibRow++;
        if(calibRow>2)calibRow=0;
    }
    __enter_menu_ex0_pr_calib(calibRow,calibCol);
	
}

void __set_short_ex1_pr_calib(bool gohome)
{
    bool saveFlg=false;
    uint8_t t8,adjv;
	uint16_t t16;
    uint32_t t32,pra;
	// calibTab2
	// at24c02Obj2
	// x_ex0prData
    if(calibCol==0){
        t8=calibTab3.calibRow[calibRow].pCount;
        adjv=*(uint8_t*)(&adjValue);
        if(t8!=adjv){
            saveFlg=true;
            calibTab3.calibRow[calibRow].pCount=adjv;
        }
    }else{
        t32=__mflot32_2_int32(m_floatAdj.t32);
        pra=calibTab3.calibRow[calibRow].calibPoint[calibCol-1].value;
        if(pra!=t32 || paramChangedFlag){
            calibTab3.calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calibTab3.calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=x_ex1prData.sigAdcValue;
            calibTab3.calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=x_ex1prData.tAdcValue;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(calibTab3);
		crc_append((uint8_t*)&calibTab3,t16-2);
		at24c02_write_n_byte(&at24c02Obj3,0,(uint8_t*)&calibTab3,t16);   
		at24c02_read_n_byte(&at24c02Obj3,0,globleBuffer,t16);
		paramChangedFlag=0;
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol>calibTab3.calibRow[calibRow].pCount){
        calibCol=0;
        calibRow++;
        if(calibRow>2)calibRow=0;
    }
    __enter_menu_ex1_pr_calib(calibRow,calibCol);
	
}
void __set_short_ex0_etemp_calib(bool gohome)
{
	int32_t t32;
    if(paramChangedFlag){
        t32=(int32_t)(rtAdcValueTemperatureEx0A-rtAdcValueTemperatureEx0B-rtAdcValueTemperatureEx0B);
        stSysData.tempCalibEx0[subMenu].adcValue=t32;
        __sys_data_save_write_flash();
		paramChangedFlag=0;
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
    subMenu++;
    if(subMenu>sub_MENU_SET_TEMP_P1)subMenu=sub_MENU_SET_TEMP_P0;
    __enter_menu_set_temp_ex0(subMenu);
}
void __set_short_ex1_etemp_calib(bool gohome)
{
	int32_t t32;
    if(paramChangedFlag){
        t32=(int32_t)(rtAdcValueTemperatureEx1A-rtAdcValueTemperatureEx1B-rtAdcValueTemperatureEx1B);
        stSysData.tempCalibEx1[subMenu].adcValue=t32;
        __sys_data_save_write_flash();
		paramChangedFlag=0;
    }
    if(gohome){__exit_menu_to_home_unsave(); return;}
    subMenu++;
    if(subMenu>sub_MENU_SET_TEMP_P1)subMenu=sub_MENU_SET_TEMP_P0;
    __enter_menu_set_temp_ex1(subMenu);
}

void __set_short_poly_coefic(bool gohome)
{
	int16_t* p;
	//int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
	//t32=adjValue;
    p=(int16_t*)(&adjValue);
    stp->ployCoeffic[subMenu]=*p;
    __sys_data_save_write_flash();
	
	if(gohome){__exit_menu_to_home_unsave(); return;}
	
    subMenu++;
    if(subMenu>sub_MENU_POLY_COEFFIC_d)subMenu=sub_MENU_POLY_COEFFIC_a;
    __enter_menu_poly_coeffic(subMenu);
}

void __set_short_warn_type(bool gohome)
{
	uint8_t* p;
	//int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
	p=(uint8_t*)(&adjValue);
	stp->dprWarnSet[subMenu].type=*p;
    __sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_WARN_TYPE_3)subMenu=sub_MENU_SET_WARN_TYPE_0;
    __enter_menu_warn_type(subMenu);  
}

void  __set_short_warn_value(bool gohome)
{
	uint8_t t8;
	//uint8_t* p;
	int32_t t32;

	sysDataDef_t* stp=&stSysData;
	t32=__mflot32_2_int32(m_floatAdj.t32);	

	t8=subMenu>>1;
	if(subMenu & 0x01){
		stp->dprWarnSet[t8].warnValueOop=t32;
	}else{
		stp->dprWarnSet[t8].warnValue=t32;
	}
	//
	__sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_WARN_VALUE_7)subMenu=sub_MENU_SET_WARN_VALUE_0;
    __enter_menu_warn_value(subMenu);     
}

void __set_short_calib_dpr_2nd(bool gohome)
{
	int32_t t32;
	t32=__mflot32_2_int32(m_floatAdj.t32);	
	if(paramChangedFlag || t32!=stSysData._2ndPrDiffCalib[subMenu].realValue){
		
		stSysData._2ndPrDiffCalib[subMenu].realValue=t32;
		stSysData._2ndPrDiffCalib[subMenu].oringinValue=rtDiffPrOriginal;
		stSysData.baseZero=0x00;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_CALIB_DPR_2ND_P1)subMenu=sub_MENU_CALIB_DPR_2ND_P0;
    __enter_menu_calib_dpr_2nd(subMenu);   
}
/*
void __set_short_calib_pr_2nd(bool gohome)
{
	int32_t t32;
	if(paramChangedFlag){
		t32=__mflot32_2_int32(m_floatAdj.t32);	
		stSysData._2ndPrCalib[subMenu].realValue=t32;
		stSysData._2ndPrCalib[subMenu].oringinValue=rtPrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_CALIB_PR_2ND_P1)subMenu=sub_MENU_CALIB_PR_2ND_P0;
    __enter_menu_calib_pr_2nd(subMenu);   
}

void __set_short_calib_epr0_2nd(bool gohome)
{
	int32_t t32;
	if(paramChangedFlag){
		t32=__mflot32_2_int32(m_floatAdj.t32);	
		stSysData._2ndPrEx0[subMenu].realValue=t32;
		stSysData._2ndPrEx0[subMenu].oringinValue=rtEx0PrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_CALIB_EPR0_2ND_P1)subMenu=sub_MENU_CALIB_EPR0_2ND_P0;
    __enter_menu_calib_epr0_2nd(subMenu);   
}

void __set_short_calib_epr1_2nd(bool gohome)
{
	int32_t t32;
	if(paramChangedFlag){
		t32=__mflot32_2_int32(m_floatAdj.t32);	
		stSysData._2ndPrEx1[subMenu].realValue=t32;
		stSysData._2ndPrEx1[subMenu].oringinValue=rtEx1PrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_CALIB_EPR1_2ND_P1)subMenu=sub_MENU_CALIB_EPR1_2ND_P0;
    __enter_menu_calib_epr1_2nd(subMenu);   
}
*/
/*
void __set_short_calib_dpr_2nd(bool gohome)
{
	int32_t t32;
	if(paramChangedFlag){
		t32=__mflot32_2_int32(m_floatAdj.t32);	
		//stSysData._2ndPrDiffCalib[subMenu].realValue=t32;
		stSysData._2ndPrDiffCalib[subMenu].oringinValue=rtDiffPrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
	
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    // subMenu++;
    // if(subMenu>sub_MENU_CALIB_DPR_2ND_P1)subMenu=sub_MENU_CALIB_DPR_2ND_P0;
    // __enter_menu_calib_dpr_2nd(subMenu);   
}
*/
void __set_short_calib_pr_2nd(bool gohome)
{
	//int32_t t32;
	if(paramChangedFlag){
		//t32=__mflot32_2_int32(m_floatAdj.t32);	
		//stSysData._2ndPrCalib[subMenu].realValue=t32;
		stSysData._2ndPrCalib[0].oringinValue=rtPrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    // subMenu++;
    // if(subMenu>sub_MENU_CALIB_PR_2ND_P1)subMenu=sub_MENU_CALIB_PR_2ND_P0;
    // __enter_menu_calib_pr_2nd(subMenu);   
}

void __set_short_calib_epr0_2nd(bool gohome)
{
	//int32_t t32;
	if(paramChangedFlag){
		//t32=__mflot32_2_int32(m_floatAdj.t32);	
		//stSysData._2ndPrEx0[subMenu].realValue=t32;
		stSysData._2ndPrEx0[0].oringinValue=rtEx0PrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    // subMenu++;
    // if(subMenu>sub_MENU_CALIB_EPR0_2ND_P1)subMenu=sub_MENU_CALIB_EPR0_2ND_P0;
    // __enter_menu_calib_epr0_2nd(subMenu);   
}

void __set_short_calib_epr1_2nd(bool gohome)
{
	//int32_t t32;
	if(paramChangedFlag){
		//t32=__mflot32_2_int32(m_floatAdj.t32);	
		//stSysData._2ndPrEx1[subMenu].realValue=t32;
		stSysData._2ndPrEx1[0].oringinValue=rtEx1PrOriginal;
		__sys_data_save_write_flash();
    
	}
	paramChangedFlag=false;
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    // subMenu++;
    // if(subMenu>sub_MENU_CALIB_EPR1_2ND_P1)subMenu=sub_MENU_CALIB_EPR1_2ND_P0;
    // __enter_menu_calib_epr1_2nd(subMenu);   
}
/*
void __set_short_epr_param(bool gohome)
{
	//uint8_t* p;
	int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
    t32=__mflot32_2_int32(m_floatAdj.t32);
    switch(subMenu){
		case sub_MENU_SET_EPR_CH0_P0:stp->exPr0Calib[0].value=t32;stp->exPr0Calib[0].adcValue=adc_iPrEx0;break;
		case sub_MENU_SET_EPR_CH0_P1:stp->exPr0Calib[1].value=t32;stp->exPr0Calib[1].adcValue=adc_iPrEx0;break;
		case sub_MENU_SET_EPR_CH1_P0:stp->exPr1Calib[0].value=t32;stp->exPr1Calib[0].adcValue=adc_iPrEx1;break;
		case sub_MENU_SET_EPR_CH1_P1:stp->exPr1Calib[1].value=t32;stp->exPr1Calib[1].adcValue=adc_iPrEx1;break;
		default:break;
    }
	__sys_data_save_write_flash();
	
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_EPR_CH1_P1)subMenu=sub_MENU_SET_EPR_CH0_P0;
    __enter_menu_epr_calib(subMenu);   	
}
 **/
 /*
void __set_short_etemp_param(bool gohome)
{
	//uint8_t* p;
	int32_t t32;
	sysDataDef_t* stp=&stSysData;
    t32=__mflot32_2_int32(m_floatAdj.t32);	
    stp->exTempCalib[subMenu].value=t32;
    stp->exTempCalib[subMenu].adcValue=adc_exPt100;
    __sys_data_save_write_flash();    
	if(gohome){__exit_menu_to_home_unsave(); return;}
	subMenu++;
	if(subMenu>1)subMenu=0;
	__enter_menu_etemp_calib(subMenu); 
}
*/
void __set_short_ilp_scale(bool gohome)
{
	int32_t t32;	
	sysDataDef_t* stp=&stSysData;
    t32=__mflot32_2_int32(m_floatAdj.t32);
	switch(subMenu){
		case sub_MENU_SET_ILP_CH0_Lo:stp->IpScaleCh0.ilpLow=t32;break;
		case sub_MENU_SET_ILP_CH0_Hi:stp->IpScaleCh0.ilpHi=t32;break;
		case sub_MENU_SET_ILP_CH1_Lo:stp->IpScaleCh1.ilpLow=t32;break;
		case sub_MENU_SET_ILP_CH1_Hi:stp->IpScaleCh1.ilpHi=t32;break;
		default:break;
	}
	__sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_ILP_CH1_Hi)subMenu=sub_MENU_SET_ILP_CH0_Lo;
    __enter_menu_ilp_scale(subMenu); 	
}
void __set_short_ilp_adjust_value(bool gohome)
{
    int16_t t16;
	t16=*((int16_t*)(&adjValue));
	switch(subMenu){
		case sub_MENU_SET_ILP_ADJUST_CH0_Lo:stSysData.ilpAdjustCh0.valueLo=t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH0_Hi:stSysData.ilpAdjustCh0.valueHi=t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Lo:stSysData.ilpAdjustCh1.valueLo=t16;break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Hi:stSysData.ilpAdjustCh1.valueHi=t16;break;
        default:break;
	}
	__sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_ILP_ADJUST_CH1_Hi)subMenu=sub_MENU_SET_ILP_ADJUST_CH0_Lo;
    __enter_menu_ilp_adjust(subMenu); 		
}
void __set_long_density(void)
{
	//int32_t t32;
    /*
    t32=__mflot32_2_int32(m_floatAdj.t32);	
	stSysData.density=t32;    
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();
     */
	 
	if(subMenu==sub_MENU_SET_SEL_MATTER){
		//if(adjValue <0x05){
		stSysData.matterIndex=adjValue;
		__sys_data_save_write_flash();
		__exit_menu_to_home_unsave();		
	}else{
		stSysData.matterTab[tmpAdjValue].density=adjValue;
		stSysData.matterIndex=(uint16_t)tmpAdjValue;
		__sys_data_save_write_flash();
		__exit_menu_to_home_unsave();			
	}
}

void __set_long_base_zero(void)
{
	int16_t t16;
	//uint16_t* p16;
	t16=*((int16_t*)(&adjValue));
	stSysData.baseZero=(int32_t)(t16);
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();
}

void __set_long_bar_level_scale(void)
{
	//uint16_t* p;
	//int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
    //p=(uint16_t*)(&adjValue);	
	//stp->barScale=*p;
    stp->barScale=(uint16_t)adjValue;
	
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();    
}

void __set_long_work_mode(void)
{
	uint8_t* p;
	//int32_t t32;
	//sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	//m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
    p=(uint8_t*)(&adjValue);	
	//stp->barScale=*p;
    dwm=*p;
    __exit_menu_to_home_unsave();  	
}

void __set_long_ext_show_mode(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	stSysData.exPrTempShowEn=*p;
	
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave();   	
}



void __set_long_wake_up_period(void)
{
	stSysData.sleepPeriod=*(uint16_t*)(&adjValue);
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();  
}

void __set_long_rf_send_period(void)
{
	stSysData.rfSendPeriod=*(uint16_t*)(&adjValue);
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();   
}

void __set_long_poly_coefic_adj_mod(void)
{
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave(); 
}

void __set_long_bl_on_tm(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	
	stSysData.blOnTm=*p;
	
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave(); 	
}

void __set_long_lcd_on_tm(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	
	stSysData.lcdOnTime=*p;
	
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave(); 	
}

void __set_long_modbus_id(void)
{
	uint8_t* p;
	p=(uint8_t*)(&adjValue);
	
	stSysData.ModbusId=*p;
	
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave(); 	
}
//============================================================================
void key_process_set_long(void)
{
	switch(menu){
		case MENU_HOME:
		case MENU_PASSWORD:             __exit_menu_to_home_unsave();       break;
		case MENU_SET_DENSITY:          __set_long_density();               break;
        case MENU_SET_POSE_SIZE:        __set_short_pose_size(goHOME);      break;
        case MENU_SET_BASE_ZERO:        __set_long_base_zero();             break;
		case MENU_DIFF_CALIB:			__set_short_diff_calib(goHOME);     break;
		case MENU_PRESSURE_CALIB:		__set_short_pr_calib(goHOME);		break;
 		case MENU_POLY_COEFFIC:			__set_short_poly_coefic(goHOME);	break;    
		case MENU_SET_WARN_TYPE:		__set_short_warn_type(goHOME);      break;        
        case MENU_SET_WARN_VALUE:		__set_short_warn_value(goHOME);     break;
		//case MENU_SET_EPR_ZERO_LINE:	__set_short_epr_param(goHOME);      break;
		//case MENU_SET_ETMEP_ZERO_LINE:	__set_short_etemp_param(goHOME);	break;
		case MENU_SET_TMEP_EX0:			__set_short_ex0_etemp_calib(goHOME);	break;
		case MENU_SET_TMEP_EX1:			__set_short_ex1_etemp_calib(goHOME);	break;		
		
		case MENU_PRESSURE_CALIB_EX0:	__set_short_ex0_pr_calib(goHOME);	break;
		case MENU_PRESSURE_CALIB_EX1:	__set_short_ex1_pr_calib(goHOME);	break;	
		
		case MENU_SET_ILOOP_SCALE:	__set_short_ilp_scale(goHOME);  break;    
        
		case MENU_SET_BAR_LEVEL_SCALE:	__set_long_bar_level_scale();       break;
		case MENU_SET_WORK_MODE:        __set_long_work_mode();             break;	
		//改版增加的部分
		case MENU_SET_EX_PR_TEMP_SHOW:	__set_long_ext_show_mode();break;
		
		//
		case MENU_SET_WAKEUP_PERIOD:	__set_long_wake_up_period();break;
		case MENU_SET_RF_SEND_PERIOD:	__set_long_rf_send_period();break;
		case MENU_SET_ILOOP_ADJUST:		__set_short_ilp_adjust_value(goHOME);break;
		
		case MENU_POLY_COEFFIC_MOD:		__set_long_poly_coefic_adj_mod();break;
		
		case MENU_CALIB_DPR_2ND:		__set_short_calib_dpr_2nd(goHOME);break;
		case MENU_CALIB_PR_2ND:			__set_short_calib_pr_2nd(goHOME);break;
		case MENU_CALIB_EPR0_2ND:		__set_short_calib_epr0_2nd(goHOME);break;
		case MENU_CALIB_EPR1_2ND:		__set_short_calib_epr1_2nd(goHOME);break;	
		
		case MENU_PSW_SET_BL_ON_TM:		__set_long_bl_on_tm();break;
		case MENU_PSW_SET_LCD_ON_TM:	__set_long_lcd_on_tm();break;
		case MENU_PSW_SET_MODBUS_ID:	__set_long_modbus_id();break;
		default:break;
	}
}

//============================================================================
void key_process_set(void)
{
	switch(menu){
		case MENU_HOME:             	__enter_menu_password();	break;
		case MENU_PASSWORD:				break;
		case MENU_SET_DENSITY:			__set_short_density();		break;
		case MENU_SET_POSE_SIZE:		__set_short_pose_size(unGoHome);	break;
		case MENU_SET_BASE_ZERO:		break;
		case MENU_DIFF_CALIB:			__set_short_diff_calib(unGoHome);	break;
		case MENU_PRESSURE_CALIB:		__set_short_pr_calib(unGoHome);		break;
		
		case MENU_POLY_COEFFIC:			__set_short_poly_coefic(unGoHome);	break;
		case MENU_SET_WARN_TYPE:		__set_short_warn_type(unGoHome);	break;
		
		case MENU_SET_WARN_VALUE:		__set_short_warn_value(unGoHome);	break;
		//case MENU_SET_EPR_ZERO_LINE:	__set_short_epr_param(unGoHome);	break;
		case MENU_PRESSURE_CALIB_EX0:	__set_short_ex0_pr_calib(unGoHome);	break;
		case MENU_PRESSURE_CALIB_EX1:	__set_short_ex1_pr_calib(unGoHome);	break;
		
		//case MENU_SET_ETMEP_ZERO_LINE:	__set_short_etemp_param(unGoHome);	break;
		case MENU_SET_TMEP_EX0:			__set_short_ex0_etemp_calib(unGoHome);	break;
		case MENU_SET_TMEP_EX1:			__set_short_ex1_etemp_calib(unGoHome);	break;
		
		case MENU_SET_ILOOP_SCALE:		__set_short_ilp_scale(unGoHome);break;
		
		case MENU_SET_BAR_LEVEL_SCALE:	break;
		case MENU_SET_WORK_MODE:        break;		
		case MENU_SET_ILOOP_ADJUST:		__set_short_ilp_adjust_value(unGoHome);break;
		//
		case MENU_CALIB_DPR_2ND:		__set_short_calib_dpr_2nd(unGoHome);break;
		case MENU_CALIB_PR_2ND:			__set_short_calib_pr_2nd(unGoHome);break;
		case MENU_CALIB_EPR0_2ND:		__set_short_calib_epr0_2nd(unGoHome);break;
		case MENU_CALIB_EPR1_2ND:		__set_short_calib_epr1_2nd(unGoHome);break;

		default:break;
	}
}

void no_operation_save_exit(void)
{
	switch(menu){

		// case MENU_HOME:							break;

		// case MENU_PASSWORD:						break;		
		// case MENU_SET_DENSITY:				break;		
		// case MENU_SET_POSE_SIZE:				break;
		// case MENU_SET_BASE_ZERO:				break;
		

		//
		case MENU_DIFF_CALIB:
		case MENU_PRESSURE_CALIB:
		
		// case MENU_POLY_COEFFIC:				break;
		
		// case MENU_SET_WARN_TYPE:        		break;
		// case MENU_SET_WARN_VALUE:				break;
		

        case MENU_PRESSURE_CALIB_EX0:   
        case MENU_PRESSURE_CALIB_EX1:   
		

		 case MENU_SET_TMEP_EX0:				
		 case MENU_SET_TMEP_EX1:				
		// case MENU_SET_ILOOP_SCALE:	break;
									
		// case MENU_SET_BAR_LEVEL_SCALE:		break;
        // case MENU_SET_WORK_MODE:          break;
		//改版后增加
		// case MENU_SET_EX_PR_TEMP_SHOW:	break;
		// case MENU_PSW_SET_BL_ON_TM:		break;
		
		// case MENU_SET_WAKEUP_PERIOD:	break;
		// case MENU_SET_RF_SEND_PERIOD:	break;
		
		// case MENU_SET_ILOOP_ADJUST:			break;
		// case MENU_POLY_COEFFIC_MOD:		break;
		//二次标定
		 case MENU_CALIB_DPR_2ND:
		 case MENU_CALIB_PR_2ND:
		 case MENU_CALIB_EPR0_2ND:
		 case MENU_CALIB_EPR1_2ND:			return;

		
		default:key_process_set_long();
		break;
	}	
}
void key_process(void)
{
	uint16_t tm=0;
	uint8_t key;
	
	//if(keyEventCount)keyEventCount--;
	//if(keyEventCount==0)event &= ~flg_KEY_DOWN;
    event &= ~flg_KEY_DOWN;
    key=get_key_value();
    if(keyValue==KEY_VALUE_NONE && key== KEY_VALUE_NONE)return;
    do{
		if(!(LCDCONbits.LCDEN)){
			lcdOnTime=(stSysData.lcdOnTime)*60;
			lcd_on();
			break;
		}
		//玛德，这里可能有问题！可以把这个判断放在key_waite_release函数中，结构更简单！！！
		if(!((keyValue == KEY_VALUE_UP || keyValue==KEY_VALUE_DOWN) && \
		(menu==MENU_SET_BASE_ZERO || menu==MENU_SET_ILOOP_ADJUST) )){
			tm=key_waite_release(LONG_PRESS_TIME,&key);
		}
		if(tm>=LONG_PRESS_TIME){
			//长按
			if(key==KEY_VALUE_SET){
				key_process_set_long();
			}else if(key == (KEY_VALUE_SET+KEY_VALUE_UP)){
				key_process_set_up_long();
			}else if(key == KEY_VALUE_DOWN + KEY_VALUE_SET){
			   // blackEn= (!blackEn);
				if(lcdBlackNightOn){
					back_night_off();
					blShowTime=0;
				}
				else{ 
					back_night_on();
					blShowTime=stSysData.blOnTm;
					if(blShowTime<20)blShowTime=20;
				}				
			}
		}else{
			//短按
			if(keyValue == KEY_VALUE_DOWN){
				key_process_down();		
			}else if(keyValue == KEY_VALUE_UP){
				key_process_up();		
			}else if(keyValue == KEY_VALUE_SET){
				key_process_set();		
			}	
		}
		//点亮闪烁的数位，禁止闪烁
		lcd_twinkle_lock(TWINKLE_LOCK_TIME_s);
		//sys_ticker_stop();
		ui_disp_menu();
		//sys_ticker_start();
	}while(0);
	key_waite_release(LONG_PRESS_TIME,&key);
    keyValue=KEY_VALUE_NONE;
}

//file end
