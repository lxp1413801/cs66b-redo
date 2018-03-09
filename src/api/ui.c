#include "../includes/includes.h"
#include <stdbool.h>
#define __STR_cs66 (uint8_t*)("cs66")
#define fi_twinkle() (RCFGCALbits.HALFSEC)
//#define fi_twinkle() 1
#define LCD_LINE_0		0
#define LCD_LINE_1		1
//uint8_t tmpBuffer[16];
//extern st_RtcDef glRtc;

//#define ui_delay_ms(ms) ticker_ms_delay(ms)
uint8_t lcdTwinkle=0;
extern bool paramChangedFlag;

void __x_arrange_str(uint8_t *str,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++){
		if(str[i]=='\0')str[i]=' ';
	}
	str[i]='\0';
}

/*
	下面两个函数非常恶心，液晶面板上面4个有效数字，3个小数点。
	显示的数据范围为0.000~9999.000。
	如果为负数
	显示范围为-0.00~999,00
	规定，int32类型固定为三个小数位，
	通过下面的函数调整小数点的位置。
*/
/*
int32_t __int32_2_mflot32(int32_t x)
{
	st_float32 mf={0};
	uint32_t t32;
	t32=x;
	if(x<0){
		t32 = ((~x) +1);
		mf.stru.sign=1;
	}
	if(mf.stru.sign){
		while(t32>999){
			mf.stru.exponent++;
			t32/=10;
			if( mf.stru.exponent>=2)break;			
		}
		if(t32>999)t32=999;
		mf.stru.significand=t32;		
	}else{
		while(t32>9999){
			mf.stru.exponent++;
			t32/=10;
			if( mf.stru.exponent>=3)break;
		}
		if(t32>9999)t32=9999;
		mf.stru.significand=t32;
	}
	return mf.t32;
}
*/
//显示两个小数点的装换
int32_t __int32_2_mflot32_02(int32_t x)
{
	uint32_t tt=0;
	uint32_t t32;
	st_float32 mf={0};
	t32=x;
	if(x<0){
		t32 = ((~x) +1);
		mf.stru.sign=1;
	}
	while(t32>999){
		mf.stru.exponent++;
		tt=t32%10;
		t32/=10;
		
		if( mf.stru.exponent>=2)break;
	}
	if(tt>=5)t32++;
	if(t32>999)t32=999;
	mf.stru.significand=t32;
	return mf.t32;
}

void ui_disp_xfloat_pt_02(st_float32_m* xpf)
{
    uint8_t buf[5];
    uint8_t t8;
	uint16_t x;

	x=xpf->stru.significand;
	m_int16_2_str_3(buf,x);
	buf[3]='\0';
	lcd_show_string_sm(buf);
	t8=(uint8_t)(xpf->stru.exponent);
	lcd_show_dp_sm(t8,true);
	if(xpf->stru.sign){
		lcd_disp_dp_loc_sign_sm(true);
	}
	//lcd_disp_refresh();    
}

int32_t __int32_2_mflot32(int32_t x)
{
	uint32_t tt=0;
	st_float32 mf={0};
	uint32_t t32;
	t32=x;
	if(x<0){
		t32 = ((~x) +1);
		mf.stru.sign=1;
	}
	while(t32>9999){
		mf.stru.exponent++;
		tt=t32%10;
		t32/=10;
		if( mf.stru.exponent>=3)break;
	}
	if(tt>=5)t32++;
	if(t32>9999)t32=9999;
	mf.stru.significand=t32;
	return mf.t32;
}


int32_t	__mflot32_2_int32(int32_t x)
{
    uint8_t i;
	st_float32 mf={0};
    int32_t ret;
	mf.t32=x;
    ret=mf.stru.significand;
    for(i=0;i<mf.stru.exponent;i++){
        ret*=10;
    }
    if(mf.stru.sign)ret=((~ret)+1);
	return ret;
}
/*
int32_t __int32_2_parAdj_format(int32_t x)
{
	st_float32 mf={0};
	mf.t32=__int32_2_mflot32(x);
	st_paramAdjFormat tpf={0};
	tpf.stru.exponent=mf.stru.exponent;
	tpf.stru.sign=mf.stru.sign;
	uint16_t t16=mf.stru.significand;
	tpf.stru.c0=(uint8_t)(t16 %10);
	t16/=10;
	tpf.stru.c1=(uint8_t)(t16 %10);
	t16/=10;
	tpf.stru.c2=(uint8_t)(t16 %10);
	t16/=10;   
	tpf.stru.c3=(uint8_t)(t16 %10);
	return tpf.t32;
}

int32_t __parAdj_format_2_int32(int32_t x)
{
	st_paramAdjFormat tpf={0};
	tpf.t32=x;
	st_float32 mf={0};
    mf.stru.exponent=tpf.stru.exponent;
    mf.stru.sign=tpf.stru.sign;
    uint16_t t16;
    t16=tpf.stru.c3;
    t16*=10;
    t16+=tpf.stru.c2;
    t16*=10;
    t16+=tpf.stru.c1;
    t16*=10;
    t16+=tpf.stru.c0;
    mf.stru.significand=t16;
    return __mflot32_2_int32(mf.t32);
}
*/

void ui_disp_all_on(void)
{
	lcd_disp_all(0xffff);
	lcd_disp_refresh();
}

void ui_disp_all_off(void)
{
	lcd_disp_all(0x00);
	lcd_disp_refresh();
}

/*
void ui_disp_clear_buffer(void)
{
	lcd_disp_all(0x00);
}
*/

void ui_disp_start_cs600(uint8_t dly)
{
	uint8_t t8;
	uint8_t buf[6]="-00-";
	lcd_disp_clear_buffer();
	lcd_show_string_l0(__STR_cs66);
	lcd_disp_logo(true);
	t8=dly;
	if(t8<1)t8=1;
	while(t8){
		m_int8_2_hex(buf+1,t8-1);
		buf[4]='\0';
		lcd_show_string_l1(buf);
        //lcd_disp_level(60);
		lcd_disp_refresh();
		ticker_ms_delay(1000);
		t8--;
	}
}

void ui_disp_rtc_mm_ss(void)
{/*
    uint8_t buf[10];
    uint8_t t8;
    if(RTCCFGbits.HALFSEC){
        lcd_show_dp(1,false);
    }else{
        rtc_get();
        t8=glRtc.hour;
        m_int8_2_hex(buf,t8);
        t8=glRtc.minute;
        m_int8_2_hex(buf+2,t8);
        //buf[4]='\0';
        t8=glRtc.month;
        m_int8_2_hex(buf+4,t8);
        t8=glRtc.date;
        m_int8_2_hex(buf+6,t8);
        buf[8]='\0';
        //lcd_show_string_l0(buf); 
        lcd_show_string(buf); 
        lcd_show_dp(1,true);
        lcd_show_dp(5,true);
    }
   
    lcd_disp_level(60);
    lcd_disp_refresh();
    */
}
void ui_disp_clear_num_dp(void)
{
	lcd_show_string((uint8_t*)"        ");
	lcd_show_dp(0,false);
    lcd_show_dp(1,false);
    lcd_show_dp(2,false);
    lcd_show_dp(4,false);
    lcd_show_dp(5,false);
    lcd_show_dp(6,false);
}

void ui_disp_adj_xfloat_pt(uint8_t* str,st_float32_m* xpf,uint8_t loc)
{
	
    uint8_t buf[10];
    
	uint16_t x;
	uint8_t t8;
	//add 
	// uint32_t t32;
	// t32=xpf->t32;
	// t32=__mflot32_2_int32(t32);
	// t32=__int32_2_mflot32(t32);
	// xpf->t32=t32;
	//add end
	x=xpf->stru.significand;
	m_mem_cpy(buf,str);
	if(xpf->stru.sign==0){
		if(x>9999)x=9999;
		m_int16_2_str_4(buf+4,x);    
        __x_arrange_str(buf,8);
        t8=xpf->stru.exponent;
        lcd_show_dp(4+t8,true);
		if(loc<4){
            loc=3-loc;
			if(!fi_twinkle() && !fi_lcd_twinkle_lock())buf[4+loc]=' ';
		}else if(loc==4){
            if(!fi_twinkle() && !fi_lcd_twinkle_lock())lcd_show_dp(4+t8,false);
		}else{
			if(!fi_twinkle() && !fi_lcd_twinkle_lock()){
				m_mem_cpy(buf+4,(uint8_t*)("    "));
				lcd_show_dp(4+t8,false);
			}			
		}            
    }else{
		if(loc==0)return;
		if(x>9999)x=9999;
		//x-=(x%10);
		m_int16_2_str_4(buf+5,x);
		buf[4]='-';
		__x_arrange_str(buf,8);
        t8=xpf->stru.exponent;
		lcd_show_dp(4+1+t8,true);
		if(loc<4){
            loc=3-loc+1;
			if(!fi_twinkle() && !fi_lcd_twinkle_lock())buf[4+loc]=' ';
		}else if(loc==4){
			if(!fi_twinkle() && !fi_lcd_twinkle_lock())lcd_show_dp(4+1+t8,false);				
		}else{
			if(!fi_twinkle() && !fi_lcd_twinkle_lock()){
				m_mem_cpy(buf+4,(uint8_t*)("    "));
				lcd_show_dp(4+1+t8,false);
			}
		}
	}
	lcd_show_string(buf); 
	lcd_disp_refresh(); 	
	/*
	if(xpf->stru.sign){
		x/=10;
        if(x>999)x=999;
		m_int16_2_str_4(buf+4,x);
		buf[4]='-';
		if(loc>2)loc=2;
		loc++;
    }else{
		if(x>9999)x=9999;
		m_int16_2_str_4(buf+4,x);
		if(loc>3)loc=3;
	}
	
	__x_arrange_str(buf,8);
	t8=xpf->stru.exponent+xpf->stru.sign;
	if(t8<3)lcd_show_dp(4+t8,true);
	loc=3-loc;
	if(!fi_lcd_twinkle_lock()){
		if(loc<4){
			if(!fi_twinkle())buf[4+loc]=' ';
		}else{
			if(t8<3)lcd_show_dp(4+t8,false);
		}
	}
	
	lcd_show_string(buf); 
	lcd_disp_refresh();  
	*/	
}
//无小数点，符号数，无闪烁
void ui_disp_adj_xfixed(uint8_t* str,int16_t x)
{
    uint8_t buf[10];
	ui_disp_clear_num_dp();
	m_mem_cpy(buf,str);
	if(x>=0){
		if(x>9999)x=9999;

		m_int16_2_str_4(buf+4,x);
	}else{
		x=0-x;
		if(x>999)x=999;
		m_int16_2_str_4(buf+4,x);
		buf[4]='-';
	}
	__x_arrange_str(buf,8);

	lcd_show_string(buf); 
	lcd_disp_refresh();
}
//有小数点，不闪烁
void ui_disp_adj_xfixed_static(uint8_t* str,uint16_t x,uint8_t dp)
{
    uint8_t buf[10];
	ui_disp_clear_num_dp();
	if(x>9999)x=9999;
	m_mem_cpy(buf,str);
	m_int16_2_str_4(buf+4,x);
	
	__x_arrange_str(buf,8);

	if(dp<=2)lcd_show_dp(4+dp,true);
	
	lcd_show_string(buf); 
	lcd_disp_refresh();
}
//无小数点，闪烁
void ui_disp_adj_xfixed_pt(uint8_t* str,uint16_t x,uint8_t loc)
{
    uint8_t buf[10];
	ui_disp_clear_num_dp();
	if(x>9999)x=9999;
	m_mem_cpy(buf,str);
	m_int16_2_str_4(buf+4,x);
	__x_arrange_str(buf,8);
	if(loc>3)loc=3;
	loc=3-loc;
	if(!fi_lcd_twinkle_lock()){
		if(!fi_twinkle())buf[4+loc]=' ';
	}
	lcd_show_string(buf); 
	lcd_disp_refresh();
}
//无小数点，闪烁
void ui_disp_adj_xfixed_pt_t8(uint8_t* str,uint8_t x,uint8_t loc)
{
    uint8_t buf[10];
	ui_disp_clear_num_dp();
	//if(x>9999)x=9999;
	m_mem_cpy(buf,str);
	//m_int16_2_str_4(buf+4,x);
	buf[4]=' ';
	buf[5]='0'+(x / 100);
	x%=100;
	buf[6]='0'+(x / 10);
	x%=10;
	buf[7]='0'+(x / 1);
	buf[8]='\0';
	//__x_arrange_str(buf,8);
	
	if(loc>2)loc=2;
	loc=3-loc;
	if(!fi_lcd_twinkle_lock()){
		if(!fi_twinkle())buf[4+loc]=' ';
	}
	lcd_show_string(buf); 
	lcd_disp_refresh();
}
//有小数点，闪烁，
void ui_disp_adj_xfixed_pt_dp(uint8_t* str,uint16_t x,uint8_t loc,uint8_t dploc)
{
    uint8_t buf[10];
	ui_disp_clear_num_dp();
	if(x>9999)x=9999;
	m_mem_cpy(buf,str);
	m_int16_2_str_4(buf+4,x);
	__x_arrange_str(buf,8);
	if(loc>3)loc=3;
	loc=3-loc;
	if(!fi_lcd_twinkle_lock()){
		if(!fi_twinkle())buf[4+loc]=' ';
	}
	lcd_show_dp(4+dploc,true);
	lcd_show_string(buf); 
	lcd_disp_refresh();
}



void ui_disp_xfloat_pt_twinkle(st_float32_m* xpf,uint8_t line,uint8_t loc)
{
    uint8_t buf[10];
    uint8_t t8;
	uint16_t x;
	if(line>1)return; 
	x=xpf->stru.significand;
	if(xpf->stru.sign){
		x/=10;
        if(x>999)x=999;
        m_int16_2_str_4(buf,x);
        buf[0]='-';
    }else{
        if(x>9999)x=9999;
        m_int16_2_str_4(buf,x);
    }
	//if(loc>3)loc=3;
	if(loc<=3){
		loc=3-loc;
		if(!fi_twinkle() && !fi_lcd_twinkle_lock())buf[loc]=' ';
	}

    buf[5]='\0';
	if(line==0){
		lcd_show_string_l0(buf);
	}else{
		lcd_show_string_l1(buf);
	}
    t8=xpf->stru.exponent+xpf->stru.sign;
    if(t8<3)lcd_show_dp(t8+4*line,true);
	if(loc==4){
		if(!fi_twinkle() && !fi_lcd_twinkle_lock())lcd_show_dp(t8+4*line,false);
	}
	//lcd_disp_refresh();    
}

void ui_disp_xfloat_pt_ex(st_float32_m* xpf,uint8_t line)
{
    uint8_t buf[10];
    uint8_t t8;
	uint8_t exs=0x00;
	uint16_t x;
	if(line>1)return; 
	x=xpf->stru.significand;
	if(xpf->stru.sign){
		if(x>999){
			x/=10;
			exs=1;
		}
        if(x>999)x=999;
        m_int16_2_str_4(buf,x);
        buf[0]='-';
    }else{
        if(x>9999)x=9999;
        m_int16_2_str_4(buf,x);
    }
    buf[5]='\0';
	if(line==0){
		lcd_show_string_l0(buf);
	}else{
		lcd_show_string_l1(buf);
	}
    //t8=xpf->stru.exponent+xpf->stru.sign;
	t8=xpf->stru.exponent+exs;
    if(t8<3)lcd_show_dp(t8+4*line,true);
	//lcd_disp_refresh();    
}


void ui_disp_xfloat_pt(st_float32_m* xpf,uint8_t line)
{
    uint8_t buf[10];
    uint8_t t8,exs=0x00;
	uint16_t x;
	if(line>1)return; 
	x=xpf->stru.significand;
	if(xpf->stru.sign){
		if(x>999){
			exs=1;
			x/=10;
		}
		
        if(x>999)x=999;
        m_int16_2_str_4(buf,x);
        buf[0]='-';
    }else{
        if(x>9999)x=9999;
        m_int16_2_str_4(buf,x);
    }
    buf[5]='\0';
	if(line==0){
		lcd_show_string_l0(buf);
	}else{
		lcd_show_string_l1(buf);
	}
    //t8=xpf->stru.exponent+xpf->stru.sign;
    t8=xpf->stru.exponent+exs;
    if(t8<3)lcd_show_dp(t8+4*line,true);
	//lcd_disp_refresh();    
}
/*
void ui_disp_adj_xfixed_pt_dp_ex(int16_t adcv,uint16_t x,uint8_t loc,uint8_t dploc)
{
    uint8_t buf[10];
	st_float32_m fx;
	
	fx.t32=__int32_2_mflot32((int32_t)adcv); 
	ui_disp_xfloat_pt(&fx);
    
	ui_disp_clear_num_dp();
	m_int16_2_str_4(buf,x);
	__x_arrange_str(buf,4);
	if(loc>3)loc=3;
	loc=3-loc;
	if(!fi_lcd_twinkle_lock()){
		if(!fi_twinkle())buf[4+loc]=' ';
	}
	lcd_show_dp(4+dploc,true);
	lcd_show_string_l1(buf);
	lcd_disp_refresh();
}
*/
void ui_disp_menu_psw_adj(void)
{
	lcd_clear_all();
	lcd_disp_logo(true);
	ui_disp_adj_xfixed_pt((uint8_t*)" psd",passWord,adjLocation);
}
/*
// 第一个界面第一行显示高度,第二行压力MPA;
void ui_disp_menu_home_00(void)
{
	//差压
	uint8_t t8;
	st_float32 mf;
	ui_disp_clear_num_dp();
	mf.t32=__int32_2_mflot32(rtHight);
	ui_disp_xfloat_pt(&mf,LCD_LINE_0);
	lcd_disp_unit_1st_m(true);
	
	mf.t32=__int32_2_mflot32(rtPressure);//rtPressure
	ui_disp_xfloat_pt(&mf,LCD_LINE_1);
	lcd_disp_unit_mpa(true);
	//t8=cal_diff_hight_level();
    t8=rtLevel;
	lcd_disp_level(t8);

	lcd_disp_refresh(); 
}

// 第二个界面第一行显示体积,第二行压力MPA;
void ui_disp_menu_home_01(void)
{
	//差压
	uint8_t t8;
	st_float32 mf;
	ui_disp_clear_num_dp();
	mf.t32=__int32_2_mflot32(rtVolume);
	ui_disp_xfloat_pt(&mf,LCD_LINE_0);
	lcd_disp_unit_1st_m3(true);
	
	mf.t32=__int32_2_mflot32(rtPressure);
	ui_disp_xfloat_pt(&mf,LCD_LINE_1);
	lcd_disp_unit_mpa(true);
	//t8=cal_diff_hight_level();
    t8=rtLevel;
	lcd_disp_level(t8);

	lcd_disp_refresh(); 
}

// 第三个界面第一行显示重量吨,第二行压力MPA;
void ui_disp_menu_home_02(void)
{
	//差压
	uint8_t t8;
	st_float32 mf;
	ui_disp_clear_num_dp();
	mf.t32=__int32_2_mflot32(rtWeight);
	ui_disp_xfloat_pt(&mf,LCD_LINE_0);
	//lcd_disp_unit_1st_m3(true);
	lcd_disp_unit_t(true);
	
	mf.t32=__int32_2_mflot32(rtPressure);
	ui_disp_xfloat_pt(&mf,LCD_LINE_1);
	lcd_disp_unit_mpa(true);
	//t8=cal_diff_hight_level();
    t8=rtLevel;
	lcd_disp_level(t8);

	lcd_disp_refresh(); 

}
*/
void ui_disp_menu_home_test(void)
{
    /*
	uint8_t t8;
	lcd_clear_all();
	t8=subMenu & 0x0f;
	switch(t8)
	{
		case 0:lcd_disp_all(0xff);break;
		case 1:lcd_disp_battary(100);break;
		case 2:lcd_disp_battary(75);break;
		case 3:lcd_disp_battary(50);break;
		case 4:lcd_disp_battary(25);break;
		case 5:lcd_disp_rf(100);break;
		case 6:lcd_disp_rf(75);break;
		case 7:lcd_disp_rf(50);break;
		case 8:lcd_disp_rf(25);break;
		case 9:lcd_disp_light(100);break;
		case 10:lcd_disp_light(50);break;
		default:break;
	}
    lcd_disp_refresh(); 
    */
    lcd_show_string((uint8_t*)"cs66-06-");
    lcd_disp_refresh();    
}
void ui_disp_home_sm_tmp_in(int32_t x)
{
	//int8_t x;
	uint8_t buf[4];
	if(hardStatus.bits.bInTempSensor==1){
		x=x/100;
		if(x>99)x=99;
		if(x<-99)x=-99;
		if(x<0){
			lcd_disp_dp_loc_sign_sm(true);
			x=0-x;
		}
		buf[0]=(x/10)+'0';
		buf[1]=(x%10)+'0';
		buf[2]='*';
		buf[3]=0;
		lcd_show_string_sm(buf);
	}else{
		lcd_show_string_sm((uint8_t*)"nc*");
	}
	lcd_disp_dp_loc_sm_temperature(true);
}
/*
void ui_disp_home_sm_tmp_ex(int32_t x)
{
	st_float32 tempft;
	tempft.t32=__int32_2_mflot32_02(x);
	ui_disp_xfloat_pt_02(&tempft);
	lcd_disp_unit_temperature(true);
}
*/

void ui_disp_home_sm_ex(uint8_t* str,int32_t x, uint8_t err)
{
	st_float32 tempft;

	lcd_show_string_ex(str);
	if(err==0){
		tempft.t32=__int32_2_mflot32_02(x);
		ui_disp_xfloat_pt_02(&tempft);
	}else{
		lcd_show_string_sm((uint8_t*)" nc");
	}		
}

void ui_disp_ext_loop(void)
{
    uint8_t t8;
	uint8_t err=0;
    int32_t x;
	uint32_t t32=globleHalfSec;
	t32>>=3;
	t32%=5;
	if(hardStatus.bits.bAdcChip1==0){
		// lcd_show_string_ex((uint8_t*)"Adc");
		// lcd_show_string_sm((uint8_t*)" nc");
		// return;
		t32=4;
	}
	do{
		if(t32==0){
			if(hardStatus.bits.bEx0TempSensor==0)t32=1;
		}
		if(t32==1){
			if(hardStatus.bits.bEx1TempSensor==0)t32=2;
		}
		if(t32==2){
			if(hardStatus.bits.bEx0PrEeprom==0)t32=3;
		}
		if(t32==3){
			/*
			if(hardStatus.bits.bEx0TempSensor==0 && hardStatus.bits.bEx1TempSensor==0
			&& hardStatus.bits.bEx0PrEeprom==0 && hardStatus.bits.bEx1PrEeprom==0){
				t32=4;break;
			}else if(hardStatus.bits.bEx1PrEeprom){
				//continue;
				break;
			}else{
				t32=0;
				continue;
			}
			*/
			if(hardStatus.bits.bEx1PrEeprom==0)t32=4;
		}
		break;
	}while(1);
	switch(t32){
		case 0:
			lcd_disp_unit_temperature(true);
            x=rtTemperatureEx0/10;
            if((rtTemperatureEx0%10)>=5)x++;
			err=0;
			if(hardStatus.bits.bEx0TempSensor==0){
				err=1;
			}
			ui_disp_home_sm_ex((uint8_t*)"ww1",x,err);break;
		case 1:
			lcd_disp_unit_temperature(true);
            x=rtTemperatureEx1/10;
            if((rtTemperatureEx1%10)>=5)x++;
			err=0;
			if(hardStatus.bits.bEx1TempSensor==0){
				err=1;
			}			
			ui_disp_home_sm_ex((uint8_t*)"ww2",x,err);break;
		case 2:
            x=rtEx0Pressure/10;
            if((rtEx0Pressure%10)>=5)x++;
			err=0;
			if(hardStatus.bits.bEx0PrEeprom==0){
				err=1;
			}				
            ui_disp_home_sm_ex((uint8_t*)"wy1",x,err);
            break;
		case 3:
            x=rtEx1Pressure/10;
            if((rtEx1Pressure%10)>=5)x++;
			err=0;
			if(hardStatus.bits.bEx1PrEeprom==0){
				err=1;
			}				
            ui_disp_home_sm_ex((uint8_t*)"wy2",x,err);break;
		case 4:
			t8=(uint16_t)stSysData.matterIndex;
			lcd_show_string_ex((uint8_t*)(stSysData.matterTab[t8].name));
			//ui_disp_home_sm_tmp_ex(rtTemperatureIn);
			ui_disp_home_sm_tmp_in(rtTemperatureIn);
			break;
		default:
			break;
	}
}

void ui_disp_menu_home(void)
{
	uint8_t t8;
	int32_t t32;
    st_float32 mf;
	lcd_clear_all();
	t8=subMenu & 0xf0;
	t8>>=4;
	
	if(hardStatus.bits.bDprSensor==0 && t8<3){
		lcd_show_string_l0((uint8_t*)" err");
	}else{
		if(t8==0){
			t32=rtHight;
			if(t32<0l)t32=0l;
			mf.t32=__int32_2_mflot32(t32);
			lcd_disp_unit_1st_m(true);		
		}else if(t8==1){
			
			mf.t32=__int32_2_mflot32(rtVolume);
			lcd_disp_unit_1st_m3(true);		
		}else if(t8==2){
			
			mf.t32=__int32_2_mflot32(rtWeight);
			lcd_disp_unit_t(true);		
		}else if(t8==3){
			#if DEBUG_EX_TEMP_EN
			mf.t32=__int32_2_mflot32(rtTempRes0);
			#endif
		}
		ui_disp_xfloat_pt(&mf,LCD_LINE_0);
		//
	}
	t8=subMenu & 0x0f;
	if((hardStatus.bits.bPrSensor==0 || hardStatus.bits.bInTempSensor==0) && t8<3){
    //if((hardStatus.bits.bPrSensor==0 ) && t8<3){
		lcd_show_string_l1((uint8_t*)" err");
	}else{	
		if(t8==0){
			mf.t32=__int32_2_mflot32(rtPressure);
			lcd_disp_unit_mpa(true);		
		}else if(t8==1){
			t32=rtHight;
			if(t32<0l)t32=0l;		
			mf.t32=__int32_2_mflot32(t32);
			lcd_disp_unit_2nd_m(true);			
		}else if(t8==2){
			mf.t32=__int32_2_mflot32(rtVolume);
			lcd_disp_unit_2nd_m3(true);			
		}else if(t8==3){
			#if DEBUG_EX_TEMP_EN
			mf.t32=__int32_2_mflot32(rtTempRes1);
			#endif
		}
		ui_disp_xfloat_pt(&mf,LCD_LINE_1);
	}
    t8=rtLevel;

	if(hardStatus.bits.bDprSensor==1){
		lcd_disp_level(t8);
	}
	lcd_disp_battary(batLevel);
	lcd_disp_light(solorLevel);

	ui_disp_ext_loop();
	lcd_disp_refresh(); 	
}

/*
void ui_disp_menu_home(void)
{
    //lcd_clear_all();
    lcd_disp_all(0);
    //pLCD[0]=0xffff;pLCD[1]=0xffff;pLCD[2]=0xffff;pLCD[3]=0xffff;
    uint8_t str[]="cs66-06-";
    lcd_show_string(str);
	lcd_disp_refresh(); 		
}
*/
void ui_disp_menu_density_sel_matter(void)
{
    uint16_t t16;
	uint8_t str[5]={"  p1"};
    lcd_clear_all();
	if(adjValue>5)adjValue=5;
	str[3]='1'+(uint8_t)adjValue;
	
	t16=stSysData.matterTab[adjValue].density;
	//ui_disp_adj_xfixed_static(str,t16,adjLocation);	
	ui_disp_adj_xfixed_static(str,t16,0);
    lcd_show_string_ex((uint8_t*)(stSysData.matterTab[adjValue].name));
	lcd_disp_refresh(); 
}

void ui_disp_menu_density_sel_custom(void)
{
	uint8_t str[5]={"  p1"};
    lcd_clear_all();
	//if(adjValue>5)adjValue=5;
	str[3]='1'+(uint8_t)tmpAdjValue;
	ui_disp_adj_xfixed_pt_dp(str,adjValue,adjLocation,0);
	lcd_show_string_ex((uint8_t*)(stSysData.matterTab[tmpAdjValue].name));
	lcd_disp_refresh(); 
}

void ui_disp_menu_density_adj(void)
{
	/*
	lcd_clear_all();
	lcd_disp_logo(true);
	ui_disp_adj_xfloat_pt((uint8_t*)"   p",&m_floatAdj,adjLocation);
	*/
	switch(subMenu){
		case sub_MENU_SET_SEL_MATTER:ui_disp_menu_density_sel_matter();break;
		case sub_MENU_SET_DENSITY_CUSTOM:ui_disp_menu_density_sel_custom();break;
	}
}

void ui_disp_menu_pos_adj(void)
{
	uint8_t buf[6];
	lcd_clear_all();
	lcd_disp_logo(true);
	m_mem_cpy(buf,(uint8_t*)"  fs");
	lcd_show_string_l0(buf);
	uint8_t* p=(uint8_t*)(&adjValue);
	m_mem_cpy(buf,(uint8_t*)"    ");
	if(*p==HOTIZONTAL){
		buf[3]='l';
	}else{
		buf[3]='h';
	}
	lcd_show_string_l1(buf);
	lcd_disp_refresh(); 
}

void ui_disp_menu_h_adj(void)
{
	lcd_clear_all();
	lcd_disp_logo(true);
	//sysDataDef_t* fps=(sysDataDef_t*)SYSTEM_DATA_ADDR;
	//sysDataDef_t* fps= &stSysData;
	if(stSysData.pos==HOTIZONTAL){
        ui_disp_adj_xfloat_pt((uint8_t*)"   l",&m_floatAdj,adjLocation);	
    }else{
        ui_disp_adj_xfloat_pt((uint8_t*)"   h",&m_floatAdj,adjLocation);	
    }
}

void ui_disp_menu_d_adj(void)
{
	lcd_clear_all();
	lcd_disp_logo(true);
	ui_disp_adj_xfloat_pt((uint8_t*)"   d",&m_floatAdj,adjLocation);		
}
void ui_disp_menu_pose_size(void)
{
    switch(subMenu){
        case sub_MENU_SET_POSE: ui_disp_menu_pos_adj(); break;
        case sub_MENU_SET_L:    ui_disp_menu_h_adj();   break;
        case sub_MENU_SET_D:    ui_disp_menu_d_adj();   break;
        default:break;
    }
}

void ui_disp_menu_bzero_adj(void)
{
    int16_t t16;
	//int16_t* p16;
	int32_t t32;
	st_float32 mf;
	lcd_clear_all();
	lcd_disp_logo(true);
	//ui_disp_adj_xfloat_pt((uint8_t*)"  Hb",&m_floatAdj,adjLocation);
	//ui_disp_adj_xfloat_pt()
	//(uint16_t*)(&adjValue)
	t16=*(int16_t*)(&adjValue);
    //t16=
	t32=(stSysData.baseZero);
	if(t32>32767)t32=32767;
	if(t32<-32768)t32=-32768;
	t32=(int32_t)(t16)-t32;
	t32=rtHight-t32;
    //if(t32<-999)t32=-999;
	 mf.t32=__int32_2_mflot32(t32);
	
	lcd_show_string_l0((uint8_t*)"  Hb");
	ui_disp_xfloat_pt_ex(&mf,LCD_LINE_1);
    
	lcd_disp_refresh(); 
}

void ui_disp_menu_calib_adj_x(uint8_t chr,__xDataStruct_t* xdat)
{
    st_float32 ft;
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	buf[0]=chr;
	buf[1]='1'+calibRow;
	/*
	if(calibRow==0)buf[1]='d';
	else if(calibRow==1)buf[1]='C';
	else if(calibRow==2)buf[1]='G';
	*/
	t8=calibCol;
	buf[2]='0'+t8%10;

	buf[3]='\0';
	buf[4]='\0';
	lcd_show_string_ex(buf);
	if(calibCol){
        ft.t32=__int32_2_mflot32((int32_t)(xdat->sigAdcValue));
        ui_disp_xfloat_pt(&ft,0);
		ui_disp_xfloat_pt_twinkle(&m_floatAdj,1,adjLocation);
	}else{
		buf[3]=' ';
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;;
		buf[8]='\0';
		lcd_show_string(buf);	
	}
    lcd_disp_refresh(); 
}
/*
void ui_disp_menu_calib_diff_adj(void)
{
    st_float32 ft;
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	buf[0]='C';
	if(calibRow==0)buf[1]='d';
	else if(calibRow==1)buf[1]='C';
	else if(calibRow==2)buf[1]='G';
	
	t8=calibCol;
	buf[2]='0'+t8%10;
	//t8/=10;
	//buf[2]='0'+t8%10;
	buf[3]='\0';
	buf[4]='\0';
	lcd_show_string_ex(buf);
	if(calibCol){
		//buf[3]=' ';
		//ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
        ft.t32=__int32_2_mflot32((int32_t)(x_prDiffData.sigAdcValue));
        ui_disp_xfloat_pt(&ft,0);
        //ui_disp_xfloat_pt(&m_floatAdj,1);
		ui_disp_xfloat_pt_twinkle(&m_floatAdj,1,adjLocation);
	}else{
		buf[3]=' ';
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;;
		buf[8]='\0';
		lcd_show_string(buf);
		//lcd_disp_refresh(); 		
	}
    lcd_disp_refresh(); 
	
}


void ui_disp_menu_calib_pr_adj(void)
{
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	buf[0]='y';
	if(calibRow==0)buf[1]='d';
	else if(calibRow==1)buf[1]='c';
	else if(calibRow==2)buf[1]='G';
	
	t8=calibCol;
	buf[3]='0'+t8%10;
	t8/=10;
	buf[2]='0'+t8%10;
	buf[4]='\0';	
	if(calibCol){
		ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
	}else{
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;;
		buf[8]='\0';
		lcd_show_string(buf);
		lcd_disp_refresh(); 		
	}
}
//ui_disp_menu_calib_ex0_pr_adj
void ui_disp_menu_calib_ex0_pr_adj(void)
{
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	buf[0]='1';
	if(calibRow==0)buf[1]='d';
	else if(calibRow==1)buf[1]='c';
	else if(calibRow==2)buf[1]='G';
	
	t8=calibCol;
	buf[3]='0'+t8%10;
	t8/=10;
	buf[2]='0'+t8%10;
	buf[4]='\0';	
	if(calibCol){
		ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
	}else{
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;;
		buf[8]='\0';
		lcd_show_string(buf);
		lcd_disp_refresh(); 		
	}
}

//ui_disp_menu_calib_ex0_pr_adj
void ui_disp_menu_calib_ex1_pr_adj(void)
{
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	buf[0]='2';
	if(calibRow==0)buf[1]='d';
	else if(calibRow==1)buf[1]='c';
	else if(calibRow==2)buf[1]='G';
	
	t8=calibCol;
	buf[3]='0'+t8%10;
	t8/=10;
	buf[2]='0'+t8%10;
	buf[4]='\0';	
	if(calibCol){
		ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
	}else{
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;;
		buf[8]='\0';
		lcd_show_string(buf);
		lcd_disp_refresh(); 		
	}
}
*/
/*
void ui_disp_menu_calib_pr_adj(void)
{
	uint8_t t8;
	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);	
	buf[0]=' ';
	// if(calibRow==0)buf[1]='l';
	// else if(calibRow==1)buf[1]='c';
	// else if(calibRow==2)buf[1]='h';
	buf[1]='p';
	t8=calibCol;
	buf[3]='0'+t8%10;
	t8/=10;
	buf[2]='0'+t8%10;
	buf[4]='\0';	
	if(calibCol){
		ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
	}else{
		m_mem_cpy(buf+4,(uint8_t*)"    ");
		t8=*((uint8_t*)(&adjValue));
		buf[7]='0'+ t8;
		buf[8]='\0';
		lcd_show_string(buf);
		lcd_disp_refresh(); 		
	}	
}
*/

void ui_disp_menu_poly_c_adj(void)
{
	uint8_t buf[6];
	uint8_t t8;
	
	lcd_clear_all();
	lcd_disp_logo(true);
	
	t8=subMenu;
	if(t8>3)return;
	m_mem_cpy(buf,(uint8_t*)"    ");
	
	buf[3]='a'+t8;
	ui_disp_adj_xfixed_pt_dp(buf,adjValue,adjLocation,0);
}

void ui_disp_menu_warn_t_adj(void)
{
	uint8_t buf[6];
	uint8_t t8;		
	lcd_clear_all();
	lcd_disp_logo(true);
	t8=subMenu;
	if(t8>3)return;
	//这个地方的显示字符需要确认用atx还是alx
	m_mem_cpy(buf,(uint8_t*)" al0");
	buf[3]='1'+t8;
	
	lcd_show_string_l0(buf);
	uint8_t* p=(uint8_t*)(&adjValue);
	m_mem_cpy(buf,(uint8_t*)"    ");
	if(*p==HIGHT_HI){
		m_mem_cpy(buf,(uint8_t*)" h-u");
	}else if(*p==HIGHT_LO){
		m_mem_cpy(buf,(uint8_t*)" h-d");
	}else if(*p==PRESSURE_HI){
		m_mem_cpy(buf,(uint8_t*)" p-u");
	}else{
		m_mem_cpy(buf,(uint8_t*)" p-d");
	}
	lcd_show_string_l1(buf);
	lcd_disp_refresh(); 
	
}

void ui_disp_menu_warn_v_adj(void)
{
	uint8_t buf[6];
	uint8_t t8,type;
	//int32_t t32	;
	lcd_clear_all();
	lcd_disp_logo(true);
	t8=subMenu;
	if(t8>7)return;
	//sysDataDef_t* fps= &stSysData;
	t8=subMenu>>1;
	type=stSysData.dprWarnSet[t8].type;
	m_mem_cpy(buf,(uint8_t*)" al1");
	buf[3]='1'+t8;
	if(subMenu & 0x01){
		//m_mem_cpy(buf,(uint8_t*)" ah0");
		buf[2]='H';
	}
	
	if(type == HIGHT_HI || type== HIGHT_LO){
		lcd_disp_unit_2nd_m(true);
	}else{
		lcd_disp_unit_mpa(true);
	}
	ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);
}


void ui_disp_menu_calib_ex0_temp_adj(void)
{
	int32_t t32;
	st_float32 ft;
	uint8_t buf[10];
	lcd_clear_all();
	buf[0]='E';
	buf[1]='t';
	buf[2]='1';
	buf[3]='\0';	
	lcd_show_string_ex(buf);

	t32=stSysData.tempCalibEx0[subMenu].resValue;
	ft.t32=__int32_2_mflot32(t32);
	ui_disp_xfloat_pt(&ft,0);
   
    if(paramChangedFlag){
        t32=(uint32_t)(rtAdcValueTemperatureEx0A-rtAdcValueTemperatureEx0B-rtAdcValueTemperatureEx0B);
    }else{
        t32=stSysData.tempCalibEx0[subMenu].adcValue;
    }
    ft.t32=__int32_2_mflot32(t32);
    ui_disp_xfloat_pt(&ft,1);
    lcd_disp_refresh(); 	
}

void ui_disp_menu_calib_ex1_temp_adj(void)
{
	int32_t t32;
	st_float32 ft;
	uint8_t buf[10];
	lcd_clear_all();
	buf[0]='E';
	buf[1]='t';
	buf[2]='2';
	buf[3]='\0';	
	lcd_show_string_ex(buf);

	t32=stSysData.tempCalibEx1[subMenu].resValue;
	ft.t32=__int32_2_mflot32(t32);
	ui_disp_xfloat_pt(&ft,0);
   
    if(paramChangedFlag){
        t32=(uint32_t)(rtAdcValueTemperatureEx1A-rtAdcValueTemperatureEx1B-rtAdcValueTemperatureEx1B);
    }else{
        t32=stSysData.tempCalibEx1[subMenu].adcValue;
    }
    ft.t32=__int32_2_mflot32(t32);
    ui_disp_xfloat_pt(&ft,1);
    lcd_disp_refresh(); 	
}

void ui_disp_menu_epr_ilp_scale_adj(void)
{
    uint8_t buf[6];
	lcd_clear_all();
	lcd_disp_logo(true);	
	switch(subMenu){
		case sub_MENU_SET_ILP_CH0_Lo:m_mem_cpy(buf,(uint8_t*)" cyl");break;
		case sub_MENU_SET_ILP_CH0_Hi:m_mem_cpy(buf,(uint8_t*)" cyH");break;
		case sub_MENU_SET_ILP_CH1_Lo:m_mem_cpy(buf,(uint8_t*)" yll");break;
		case sub_MENU_SET_ILP_CH1_Hi:m_mem_cpy(buf,(uint8_t*)" ylH");break;
        default:return;
	}
	ui_disp_adj_xfloat_pt(buf,&m_floatAdj,adjLocation);	
}

void ui_disp_menu_ilp_adj(void)
{
	int16_t t16;
	lcd_clear_all();
	//lcd_disp_logo(true);
	t16=*((int16_t*)(&adjValue));
	switch(subMenu){
		case sub_MENU_SET_ILP_ADJUST_CH0_Lo:ui_disp_adj_xfixed((uint8_t*)"cy04",t16);break;
		case sub_MENU_SET_ILP_ADJUST_CH0_Hi:ui_disp_adj_xfixed((uint8_t*)"cy20",t16);break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Lo:ui_disp_adj_xfixed((uint8_t*)"yl04",t16);break;
		case sub_MENU_SET_ILP_ADJUST_CH1_Hi:ui_disp_adj_xfixed((uint8_t*)"yl20",t16);break;
        default:break;
	}	
}
/*
void ui_disp_menu_bar_full_adj(void)
{
	lcd_clear_all();
	//lcd_disp_logo(true);	
	ui_disp_adj_xfixed_pt_dp((uint8_t*)" scl",(int16_t)adjValue,adjLocation,0);
}
*/
void ui_disp_menu_bar_full_adj(void)
{
	lcd_clear_all();
	//lcd_disp_logo(true);	
	ui_disp_adj_xfixed_static((uint8_t*)" scl",(int16_t)adjValue,0);
}
//ui_disp_adj_xfixed_static
void ui_disp_menu_work_mode_adj(void)
{
    uint8_t* p;
    uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
    p=(uint8_t*)(&adjValue);
    
    if(*p==WORK_MODE){
        m_mem_cpy(buf,(uint8_t*)" sta nor");
    }else{
        m_mem_cpy(buf,(uint8_t*)" sta tst");
    }
    lcd_show_string(buf);
    lcd_disp_refresh(); 
}

void ui_disp_menu_ext_show_mode(void)
{
    uint8_t* p;
    uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
    p=(uint8_t*)(&adjValue);
    
    if(*p==0){
        m_mem_cpy(buf,(uint8_t*)" epd  no");
    }else{
        m_mem_cpy(buf,(uint8_t*)" epd yes");
    }
    lcd_show_string(buf);
    lcd_disp_refresh(); 	
}


void ui_disp_menu_wake_up_period(void)
{
	int16_t t16;
	lcd_clear_all();
	t16=(int16_t)adjValue;
	if(t16==WAKE_UP_SAMPLE_FORBID){
		lcd_show_string((uint8_t*)(" slp off"));
		lcd_disp_refresh(); 
	}else{
		ui_disp_adj_xfixed_static((uint8_t*)(" slp"),t16,3);
	}
}

void ui_disp_menu_rf_send_period(void)
{
	lcd_clear_all();
	ui_disp_adj_xfixed_static((uint8_t*)(" rfp"),(int16_t)adjValue,3);
}



void ui_disp_menu_poly_coefic_adj_mod(void)
{

    uint8_t buf[10];
	lcd_clear_all();
	//lcd_disp_logo(true);
	if(adjValue==0){
		m_mem_cpy(buf,(uint8_t*)"   n   1");
	}else if(adjValue==1){
		m_mem_cpy(buf,(uint8_t*)"   n   4");
	}else{
		m_mem_cpy(buf,(uint8_t*)"   n   6");
	}

    lcd_show_string(buf);
    lcd_disp_refresh(); 	
}
/*
		case MENU_CALIB_DPR_2ND:		__set_short_calib_dpr_2nd(goHOME);break;
		case MENU_CALIB_PR_2ND:			__set_short_calib_pr_2nd(goHOME);break;
		case MENU_CALIB_EPR0_2ND:		__set_short_calib_epr0_2nd(goHOME);break;
		case MENU_CALIB_EPR1_2ND:		__set_short_calib_epr1_2nd(goHOME);break;
*/
/*
void ui_disp_menu_calib_x_2nd(void)
{
    st_float32 ft;

	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	switch(menu){
		
		case MENU_CALIB_DPR_2ND:
			m_mem_cpy(buf,(uint8_t*)"CY1");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtDiffPrOriginal);
			break;
		case MENU_CALIB_PR_2ND:
			m_mem_cpy(buf,(uint8_t*)"YL1");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtPrOriginal);
			break;
		case MENU_CALIB_EPR0_2ND:
			m_mem_cpy(buf,(uint8_t*)"W11");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtEx0PrOriginal);
			break;	
		case MENU_CALIB_EPR1_2ND:
			m_mem_cpy(buf,(uint8_t*)"W21");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtEx1PrOriginal);
			break;			
		
		
	}
	ui_disp_xfloat_pt(&ft,0);
	ui_disp_xfloat_pt_twinkle(&m_floatAdj,1,adjLocation);		
    lcd_disp_refresh(); 
}
*/
void ui_disp_menu_calib_dpr_2nd(void)
{
    st_float32 ft;

	uint8_t buf[10];
	lcd_clear_all();
	
	m_mem_cpy(buf,(uint8_t*)"CY1");
	buf[2]=subMenu+'1';
	lcd_show_string_ex(buf);
	//ft.t32=__int32_2_mflot32(rtDiffPrOriginal);	
	ft.t32=__int32_2_mflot32(rtHight);
	ui_disp_xfloat_pt(&ft,0);
	ui_disp_xfloat_pt_twinkle(&m_floatAdj,1,adjLocation);		
    lcd_disp_refresh(); 	
}
void ui_disp_menu_calib_x_2nd(void)
{
    st_float32 ft,fr;

	uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
	switch(menu){
		

		case MENU_CALIB_PR_2ND:
			m_mem_cpy(buf,(uint8_t*)"YL1");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtPrOriginal);
			fr.t32=__int32_2_mflot32(rtPressure);
			break;
		case MENU_CALIB_EPR0_2ND:
			m_mem_cpy(buf,(uint8_t*)"WY1");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtEx0PrOriginal);
			fr.t32=__int32_2_mflot32(rtEx0Pressure);
			break;	
		case MENU_CALIB_EPR1_2ND:
			m_mem_cpy(buf,(uint8_t*)"WY2");
			//buf[2]=subMenu+'1';
			lcd_show_string_ex(buf);
			ft.t32=__int32_2_mflot32(rtEx1PrOriginal);
			fr.t32=__int32_2_mflot32(rtEx1Pressure);
			break;			
		
		
	}
	ui_disp_xfloat_pt(&ft,0);
	if(paramChangedFlag){
		if(!fi_twinkle() && !fi_lcd_twinkle_lock()){
			m_mem_cpy(buf,(uint8_t*)"    ");
			lcd_show_string_l1(buf);
		}
		else{
			ui_disp_xfloat_pt(&fr,1);
		}
	}else{
		ui_disp_xfloat_pt(&fr,1);
	}
	//ui_disp_xfloat_pt_twinkle(&m_floatAdj,1,adjLocation);		
    lcd_disp_refresh(); 
}

void ui_disp_menu_bl_on_tm(void)
{
	uint8_t t8;
    uint8_t* p;
    uint8_t buf[10];
	lcd_clear_all();
	lcd_disp_logo(true);
    p=(uint8_t*)(&adjValue);
    t8=*p;
	m_mem_cpy(buf,(uint8_t*)"  bl    ");
	if(t8>99)t8=99;
	buf[6]=t8/10+'0';
	buf[7]=t8%10+'0';
	buf[8]='\0';
    lcd_show_string(buf);
    lcd_disp_refresh(); 	
}
void ui_disp_menu_lcd_on_tm(void)
{
	lcd_clear_all();
	ui_disp_adj_xfixed_pt_t8((uint8_t*)" lcd",(int8_t)adjValue,adjLocation);
}
void ui_disp_menu_modbus_id(void)
{
	lcd_clear_all();
	ui_disp_adj_xfixed_pt_t8((uint8_t*)"  id",(int8_t)adjValue,adjLocation);
}

void ui_disp_menu_ver(void)
{
	lcd_clear_all();
	//ui_disp_adj_xfixed_pt_t8((uint8_t*)"  id",(int8_t)adjValue,adjLocation);
	lcd_show_string((uint8_t*)SOFTWARE_VER);
	lcd_disp_refresh(); 
}
void ui_disp_menu(void)
{

	switch(menu){
		#if LCD_TEST_EX_EN==1
		case MENU_HOME:					ui_disp_menu_home_test();		break;
		#else 
		case MENU_HOME:					ui_disp_menu_home();			break;
		#endif
		case MENU_PASSWORD:				ui_disp_menu_psw_adj();			break;		
		case MENU_SET_DENSITY:			ui_disp_menu_density_adj();		break;		
		case MENU_SET_POSE_SIZE:		ui_disp_menu_pose_size();		break;
		case MENU_SET_BASE_ZERO:		ui_disp_menu_bzero_adj();		break;
		
		//case MENU_DIFF_CALIB:			ui_disp_menu_calib_diff_adj();	break;
		//case MENU_PRESSURE_CALIB:		ui_disp_menu_calib_pr_adj();	break;
		//
		case MENU_DIFF_CALIB:ui_disp_menu_calib_adj_x('c',&x_prDiffData);break;
		case MENU_PRESSURE_CALIB:ui_disp_menu_calib_adj_x('y',&x_prData);break;
		
		case MENU_POLY_COEFFIC:			ui_disp_menu_poly_c_adj();		break;
		
		case MENU_SET_WARN_TYPE:        ui_disp_menu_warn_t_adj();		break;
		case MENU_SET_WARN_VALUE:		ui_disp_menu_warn_v_adj();		break;
		
		//case MENU_SET_EPR_ZERO_LINE:ui_disp_menu_epr_calib_adj();		break;
        case MENU_PRESSURE_CALIB_EX0:   ui_disp_menu_calib_adj_x('1',&x_ex0prData);break;
        case MENU_PRESSURE_CALIB_EX1:   ui_disp_menu_calib_adj_x('2',&x_ex1prData);break;
		// case MENU_SET_ETMEP_ZERO_LINE:
									// ui_disp_menu_etemp_calib_adj();		break;
		case MENU_SET_TMEP_EX0:			ui_disp_menu_calib_ex0_temp_adj();	break;
		case MENU_SET_TMEP_EX1:			ui_disp_menu_calib_ex1_temp_adj();	break;
		case MENU_SET_ILOOP_SCALE:	
									ui_disp_menu_epr_ilp_scale_adj();	break;
		case MENU_SET_BAR_LEVEL_SCALE:	ui_disp_menu_bar_full_adj();	break;
        case MENU_SET_WORK_MODE:        ui_disp_menu_work_mode_adj();   break;
		//改版后增加
		case MENU_SET_EX_PR_TEMP_SHOW:	ui_disp_menu_ext_show_mode();break;
		
		//
		case MENU_SET_WAKEUP_PERIOD:	ui_disp_menu_wake_up_period();break;
		case MENU_SET_RF_SEND_PERIOD:	ui_disp_menu_rf_send_period();break;
		//
		case MENU_SET_ILOOP_ADJUST:		ui_disp_menu_ilp_adj();		break;
		case MENU_POLY_COEFFIC_MOD:		ui_disp_menu_poly_coefic_adj_mod();break;
		//二次标定
		case MENU_CALIB_DPR_2ND:ui_disp_menu_calib_dpr_2nd();break;	
		case MENU_CALIB_PR_2ND:
		case MENU_CALIB_EPR0_2ND:
		case MENU_CALIB_EPR1_2ND:		ui_disp_menu_calib_x_2nd();break;	

		case MENU_SET_BL_ON_TM:		ui_disp_menu_bl_on_tm();break;
		case MENU_SET_LCD_ON_TM:	ui_disp_menu_lcd_on_tm();break;
		case MENU_SET_MODBUS_ID:	ui_disp_menu_modbus_id();break;
		case MENU_SHOW_VER:			ui_disp_menu_ver();break;
		default:break;
	}	
}
//file end
