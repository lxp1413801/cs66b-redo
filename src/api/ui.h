#ifndef __ui_h__
#define __ui_h__

#ifdef __cplusplus
extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include <stdbool.h>
	typedef union{
		uint32_t t32;
        struct{
            uint16_t 	significand;	//有效数字
            uint8_t 	exponent;		//小数位
            uint8_t 	sign;			//符号位
        }stru;
	}st_float32,m_float32_t,st_float32_m;
	/*
	typedef union{
		int32_t t32;
		struct{
			uint8_t	c0:4;			//数码管上面对应位置,000x	
			uint8_t	c1:4;			//数码管上面对应位置,00x0
			uint8_t	c2:4;			//数码管上面对应位置,0x00
			uint8_t	c3:4;			//数码管上面对应位置,x000
			uint8_t	exponent;		//小数位
			uint8_t	sign;			//符号位
		}stru;
	}st_paramAdjFormat,paramAdjFormat_t;
	*/
    extern uint8_t lcdTwinkle;
    #define TWINKLE_LOCK_TIME_s 1
    #define lcd_twinkle_lock(s) do{lcdTwinkle=s;}while(0);
	#define fi_lcd_twinkle_lock() (lcdTwinkle>0)
	extern int32_t __int32_2_mflot32(int32_t x);
	extern int32_t __mflot32_2_int32(int32_t x);
	
	// extern int32_t __int32_2_parAdj_format(int32_t x);
	// extern int32_t __parAdj_format_2_int32(int32_t x);
	extern void ui_disp_all_on(void);
    extern void ui_disp_all_off(void);
    extern void ui_disp_rtc_mm_ss(void);
	extern void ui_disp_start_cs600(uint8_t dly);
	
	extern void ui_disp_adj_xfloat_pt(uint8_t* str,st_float32_m* xpf,uint8_t loc);
	extern void ui_disp_adj_xfixed_pt(uint8_t* str,uint16_t x,uint8_t loc);
	
	extern inline void ui_disp_menu(void);
	
#ifdef __cplusplus
}
#endif

#endif
//file end
