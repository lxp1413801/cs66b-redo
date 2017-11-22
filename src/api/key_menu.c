#include "../includes/includes.h"


#define goHOME  true
#define unGoHome    false

#define LONG_PRESS_TIME		2000

volatile uint16_t passWord=0x00;
volatile uint8_t menu=MENU_HOME;
volatile uint8_t subMenu=0;
//volatile uint8_t keyValue=KEY_VALUE_NONE;
volatile uint8_t adjLocation=0;
volatile int32_t adjValue=0x00;
//add lxp
st_float32_m m_floatAdj={0};
volatile uint8_t* pAdjValue;
//
volatile uint8_t  calibRow=0x00;
volatile uint8_t  calibCol=0x00;
volatile bool blackEn=false;
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
}



//set long time press process
void __enter_menu_password(void)
{	
	menu=MENU_PASSWORD;
	subMenu=0x00;
	
	passWord=0x00;
	adjLocation=0x00;
}

void __enter_menu_set_density(void)
{
	int32_t t32;
	menu=MENU_SET_DENSITY;
	subMenu=sub_MENU_SET_DENSITY;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	t32=fps->density;
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
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
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	if(m_floatAdj.stru.sign){
        adjLocation=1;
    }else{
        adjLocation=0;
    }
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
	adjLocation=0;
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
}

void __enter_menu_warn_type(uint8_t __subMenu)
{
	menu=MENU_SET_WARN_TYPE;
	subMenu=__subMenu;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	sysDataDef_t* fps= &stSysData;
	adjValue=0x00ul;
	*((uint8_t*)(&adjValue))=(uint8_t)(fps->diffPressureWarnSet[subMenu].type);
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
		t32=fps->diffPressureWarnSet[t8].warnValueHi;
	}else{
		t32=fps->diffPressureWarnSet[t8].warnValueLo;
	}
	
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
	adjLocation=0;
}

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
void __enter_menu_etemp_calib(uint8_t __subMenu)
{
	int32_t t32;
	menu=MENU_SET_ETMEP_ZERO_LINE;
	subMenu=__subMenu;
	sysDataDef_t* fps= &stSysData;
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
void __enter_menu_epr_ilp_scale(uint8_t __subMenu)
{
	menu=MENU_SET_EPR_ILOOP_SCALE;
	subMenu=__subMenu;
    int32_t t32=0;
	//if(subMenu>sub_MENU_SET_EX_DPR_ILP_Hi1)subMenu=sub_MENU_SET_EX_DPR_ILP_Hi1;
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
    sysDataDef_t* fps= &stSysData;
	switch(subMenu)
	{
		case sub_MENU_SET_EXPR_ILP_CH0_Lo:t32=fps->exPrIpScaleCh0.ilpLow;break;
		case sub_MENU_SET_EXPR_ILP_CH0_Hi:t32=fps->exPrIpScaleCh0.ilpHi;break;
		case sub_MENU_SET_EXPR_ILP_CH1_Lo:t32=fps->exPrIpScaleCh1.ilpLow;break;
		case sub_MENU_SET_EXPR_ILP_CH1_Hi:t32=fps->exPrIpScaleCh1.ilpHi;break;
		default:return;
	}
    
	t32=__int32_2_mflot32(t32);
	m_floatAdj.t32=t32;
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

void __exit_menu_to_home_unsave(void)
{
	menu=MENU_HOME;
	subMenu=0x00;

	adjValue=0;
	m_floatAdj.t32=0;
	adjLocation=0x00;
	
	calibRow=0;
	calibCol=0;
	passWord=0x00;
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

void __down_dpr_calib(void)
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
    if(t8>3)t8=0;
    //t8<<=4;
    subMenu &= 0xf0;
    subMenu |= t8;	
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
		case MENU_SET_DENSITY:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_SET_POSE_SIZE:__down_pose_size();break;
		case MENU_SET_BASE_ZERO:key_shift_loc((uint8_t*)(&adjLocation),0,5);break;
		case MENU_DIFF_CALIB:__down_dpr_calib();break;
		case MENU_PRESSURE_CALIB:__down_pr_calib();break;
		case MENU_POLY_COEFFIC:key_shift_loc((uint8_t*)(&adjLocation),0,2);break;
		case MENU_SET_WARN_TYPE:break;
		case MENU_SET_WARN_VALUE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_SET_EPR_ZERO_LINE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		//case MENU_SET_ETMEP_ZERO_LINE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_SET_EPR_ILOOP_SCALE:key_shift_loc((uint8_t*)(&adjLocation),0,4);break;
		case MENU_SET_BAR_LEVEL_SCALE:key_shift_loc((uint8_t*)(&adjLocation),0,2);break;
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
    if(t8>4)t8=0;
    t8<<=4;
    subMenu &= 0x0f;
    subMenu |= t8;
    
	//if(subMenu>sub_MENU_HOME_02)subMenu=sub_MENU_HOME_00;
}

void __up_psw_adj(void)
{
	key_adj_value_fixed((uint16_t*)(&passWord),adjLocation);
}

void __up_density_adj(void)
{
	key_adj_value_float(&m_floatAdj,adjLocation);
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
	key_adj_value_float(&m_floatAdj,adjLocation);
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
	}
}

void __up_pr_calib_adj(void)
{
	uint8_t t8;
	if(calibCol==0){
		t8=*(uint8_t*)(&adjValue);
		t8++;
		if(t8>=6)t8=2;
		*(uint8_t*)(&adjValue)=t8;
	}else{	
		key_adj_value_float(&m_floatAdj,adjLocation);
	}
}

void __up_poly_coefic_adj(void)
{
	key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
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

void __up_etemp_calib_adj(void)
{
	key_adj_value_float(&m_floatAdj,adjLocation);
}

void __up_epr_ilp_scale_adj(void)
{
	//key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
	key_adj_value_float(&m_floatAdj,adjLocation);
}

//-----------------------------------------------------
void __up_adj_bar_level_scale(void)
{
	key_adj_value_fixed((uint16_t*)(&adjValue),adjLocation);
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
		case MENU_SET_EPR_ZERO_LINE:	__up_epr_calib_adj();			break;
		//case MENU_SET_ETMEP_ZERO_LINE:	__up_etemp_calib_adj();			break;
		case MENU_SET_EPR_ILOOP_SCALE:	__up_epr_ilp_scale_adj();		break;
		
		case MENU_SET_BAR_LEVEL_SCALE:	__up_adj_bar_level_scale();	break;
		case MENU_SET_WORK_MODE:        __up_adj_work_mode();		break;
		//case 
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
		case PSW_SET_EPR_ZERO_LINE:		__enter_menu_epr_calib(0);			break;
		case PSW_SET_ETMEP_ZERO_LINE:	__enter_menu_etemp_calib(0);		break;
		case PSW_SET_EPR_ILOOP_SCALE:	__enter_menu_epr_ilp_scale(0);			break;
		case PSW_SET_BAR_LEVEL_SCALE:	__enter_menu_bar_scale();				break;
		case PSW_SET_WORK_MODE:			__enter_menu_work_mode();				break;
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

//============================================================================
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
	if(gohome){__exit_menu_to_home_unsave(); return;}
    __sys_data_save_write_flash();
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
        if(pra!=t32){
            calibTab0.calibRow[calibRow].calibPoint[calibCol-1].value=(uint16_t)t32;
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
        if(pra!=t32){
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].value=t32;
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].sigAdcValue=adc_pressure;
            calibTab1.calibRow[calibRow].calibPoint[calibCol-1].tAdcValue=0;
            saveFlg=true;
        }
    }
	
	if(saveFlg){
		t16=sizeof(calibTab1);
		crc_append((uint8_t*)&calibTab1,t16-2);
		at24c02_write_n_byte(&at24c02Obj1,0,(uint8_t*)&calibTab1,t16);        
    }
	if(gohome){__exit_menu_to_home_unsave(); return;}
	calibCol++;
	if(calibCol>calibTab1.calibRow[calibRow].pCount){
        calibCol=0;
        //calibRow++;
        //if(calibRow>2)calibRow=0;
    }
    __enter_menu_calib_press(0,calibCol);
	
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
	stp->diffPressureWarnSet[subMenu].type=*p;
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
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
	t32=__mflot32_2_int32(m_floatAdj.t32);	
	/*
	if(subMenu<sub_MENU_SET_WARN_VALUE_4){
		stp->diffPressureWarnSet[subMenu].warnValueLo=t32;
	}else{
        stp->diffPressureWarnSet[subMenu-sub_MENU_SET_WARN_VALUE_4].warnValueHi=t32;
    }
	*/
	t8=subMenu>>1;
	if(subMenu & 0x01){
		stp->diffPressureWarnSet[t8].warnValueHi=t32;
	}else{
		stp->diffPressureWarnSet[t8].warnValueLo=t32;
	}
	//
	__sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_WARN_VALUE_7)subMenu=sub_MENU_SET_WARN_VALUE_0;
    __enter_menu_warn_value(subMenu);     
}

void __set_short_epr_param(bool gohome)
{
	uint8_t* p;
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
void __set_short_etemp_param(bool gohome)
{
	uint8_t* p;
	int32_t t32;
	sysDataDef_t* stp=&stSysData;
    /*
    t32=__mflot32_2_int32(m_floatAdj.t32);	
	if(stp->exTempCalib[subMenu].value!=t32){
		stp->exTempCalib[subMenu].value=t32;
		stp->exTempCalib[subMenu].adcValue=adc_exPt100;
		__sys_data_save_write_flash();
	}
	*/
    t32=__mflot32_2_int32(m_floatAdj.t32);	
    stp->exTempCalib[subMenu].value=t32;
    stp->exTempCalib[subMenu].adcValue=adc_exPt100;
    __sys_data_save_write_flash();    
	if(gohome){__exit_menu_to_home_unsave(); return;}
	subMenu++;
	if(subMenu>1)subMenu=0;
	__enter_menu_etemp_calib(subMenu); 
}
void __set_short_epr_ilp_scale(bool gohome)
{
	uint8_t* p;
	int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
    t32=__mflot32_2_int32(m_floatAdj.t32);
	switch(subMenu){
		case sub_MENU_SET_EXPR_ILP_CH0_Lo:stp->exPrIpScaleCh0.ilpLow=t32;break;
		case sub_MENU_SET_EXPR_ILP_CH0_Hi:stp->exPrIpScaleCh0.ilpHi=t32;break;
		case sub_MENU_SET_EXPR_ILP_CH1_Lo:stp->exPrIpScaleCh1.ilpLow=t32;break;
		case sub_MENU_SET_EXPR_ILP_CH1_Hi:stp->exPrIpScaleCh1.ilpHi=t32;break;
		default:break;
	}
	__sys_data_save_write_flash();
    
    if(gohome){__exit_menu_to_home_unsave(); return;}
    
    subMenu++;
    if(subMenu>sub_MENU_SET_EXPR_ILP_CH1_Hi)subMenu=sub_MENU_SET_EXPR_ILP_CH0_Lo;
    __enter_menu_epr_ilp_scale(subMenu); 	
}

void __set_long_density(void)
{
	int32_t t32;
    t32=__mflot32_2_int32(m_floatAdj.t32);	
	stSysData.density=t32;    
    __sys_data_save_write_flash();
    __exit_menu_to_home_unsave();
}

void __set_long_base_zero(void)
{
	uint8_t* p;
	int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
    t32=__mflot32_2_int32(m_floatAdj.t32);	
	stp->baseZero=t32;
    
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave();
}
void __set_long_bar_level_scale(void)
{
	uint16_t* p;
	int32_t t32;
	// sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	// m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
	sysDataDef_t* stp=&stSysData;
    p=(uint16_t*)(&adjValue);	
	stp->barScale=*p;
    
    __sys_data_save_write_flash();
    
    __exit_menu_to_home_unsave();    
}

void __set_long_work_mode(void)
{
	uint8_t* p;
	int32_t t32;
	//sysDataDef_t* stp=(sysDataDef_t*)globleBuffer1; 
	//m_flash_read(SYSTEM_DATA_ADDR,globleBuffer1,sizeof(sysDataDef_t));	
    p=(uint8_t*)(&adjValue);	
	//stp->barScale=*p;
    dwm=*p;
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
		case MENU_SET_EPR_ZERO_LINE:	__set_short_epr_param(goHOME);      break;
		case MENU_SET_ETMEP_ZERO_LINE:	__set_short_etemp_param(goHOME);	break;
		case MENU_SET_EPR_ILOOP_SCALE:	__set_short_epr_ilp_scale(goHOME);  break;    
        
		case MENU_SET_BAR_LEVEL_SCALE:	__set_long_bar_level_scale();       break;
		case MENU_SET_WORK_MODE:        __set_long_work_mode();             break;		
		default:break;
	}
}

//============================================================================
void key_process_set(void)
{
	switch(menu){
		case MENU_HOME:             	__enter_menu_password();	break;
		case MENU_PASSWORD:				break;
		case MENU_SET_DENSITY:			break;
		case MENU_SET_POSE_SIZE:		__set_short_pose_size(unGoHome);	break;
		case MENU_SET_BASE_ZERO:		break;
		case MENU_DIFF_CALIB:			__set_short_diff_calib(unGoHome);	break;
		case MENU_PRESSURE_CALIB:		__set_short_pr_calib(unGoHome);		break;
		
		case MENU_POLY_COEFFIC:			__set_short_poly_coefic(unGoHome);	break;
		case MENU_SET_WARN_TYPE:		__set_short_warn_type(unGoHome);	break;
		
		case MENU_SET_WARN_VALUE:		__set_short_warn_value(unGoHome);	break;
		case MENU_SET_EPR_ZERO_LINE:	__set_short_epr_param(unGoHome);	break;
		case MENU_SET_ETMEP_ZERO_LINE:	__set_short_etemp_param(unGoHome);	break;
		case MENU_SET_EPR_ILOOP_SCALE:	__set_short_epr_ilp_scale(unGoHome);break;
		
		case MENU_SET_BAR_LEVEL_SCALE:	break;
		case MENU_SET_WORK_MODE:        break;		
		default:break;
	}
}


void key_process(void)
{
	uint16_t tm;
	uint8_t key;
	
	if(keyEventCount)keyEventCount--;
	if(keyEventCount==0)event &= ~flg_KEY_DOWN;
    key=get_key_value();
    if(keyValue==KEY_VALUE_NONE && key== KEY_VALUE_NONE)return;
	//玛德，这里可能有问题！
	tm=key_waite_release(LONG_PRESS_TIME,&key);
	if(tm>=LONG_PRESS_TIME){
		//长按
		if(key==KEY_VALUE_SET){
			key_process_set_long();
		}else if(key == (KEY_VALUE_SET+KEY_VALUE_UP)){
			key_process_set_up_long();
		}else if(key == KEY_VALUE_DOWN + KEY_VALUE_UP){
           // blackEn= (!blackEn);
            if(blackEn)lcd_bl_off();
            else 
                lcd_bl_on();
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
	key_waite_release(LONG_PRESS_TIME,&key);
    keyValue=KEY_VALUE_NONE;
}

//file end
