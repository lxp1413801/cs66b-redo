//file name:key_menu.h
#ifndef __key_menu_h__
#define __key_menu_h__

#ifdef __cplusplus
extern "C"{
#endif
	#include <stdint.h>
	#include <stdbool.h>
	
	#define PSW_SET_DENSITY						36	
	#define PSW_SET_POSE_SIZE					66
	
	#define PSW_SET_BASE_ZERO					56
	//calibration
	#define PSW_CALIB_DIFF_PRESSURE				168
	#define PSW_CALIB_PRESSURE					169
	//Polynomial coefficients(滤波多项式系数)
	#define PSW_SET_POLY_COEFFIC				133
	#define PSW_SET_WARN_TYPE					6
	#define PSW_SET_WARN_VALUE					16
	//外压零点和线性
	#define PSW_SET_EPR_ZERO_LINE               138
	//外部温度修正
	#define PSW_SET_ETMEP_ZERO_LINE				136	
	//差压二次修正
	//压力二次修正
	//外部差压输出范围
	#define PSW_SET_EPR_ILOOP_SCALE				139

	//高度条满刻度对应的值95%还是100%
	#define PSW_SET_BAR_LEVEL_SCALE				188
	#define PSW_SET_WORK_MODE					18
	
	//==============================================================
	//定义菜单,主界面
	#define MENU_HOME							0x00
	#define sub_MENU_HOME_00					0x00
	#define sub_MENU_HOME_01					0x01
	#define sub_MENU_HOME_02					0x02
	//密码验证界面
	#define MENU_PASSWORD						0x10
	#define	sub_MENU_PASSWORD					0x00
	
	//设置密度	psd=36
	#define MENU_SET_DENSITY					0x20
	#define	sub_MENU_SET_DENSITY				0x00
	#define sub_MENU_SET_SEL_MATTER				0x00
	#define sub_MENU_SET_DENSITY_CUSTOM			0x01
	//设置尺寸 psd=66
	#define MENU_SET_POSE_SIZE					0x30
	#define sub_MENU_SET_POSE					0x00
	#define sub_MENU_SET_L						0x01
	#define sub_MENU_SET_D						0x02
	//设置基础零位	psd=56	
	#define MENU_SET_BASE_ZERO					0x40
	//差压标定,psd=168
	#define MENU_DIFF_CALIB						0x50
	//压力标定,psd=169
	#define MENU_PRESSURE_CALIB					0x60
	//滤波多项式系数psd=133
	#define MENU_POLY_COEFFIC					0x70
	#define sub_MENU_POLY_COEFFIC_a				0x00
	#define sub_MENU_POLY_COEFFIC_b				0x01
	#define sub_MENU_POLY_COEFFIC_c				0x02
	#define sub_MENU_POLY_COEFFIC_d				0x03
	//报警方式,psd=6								
	#define MENU_SET_WARN_TYPE					0x80
	#define sub_MENU_SET_WARN_TYPE_0			0x00
	#define sub_MENU_SET_WARN_TYPE_1			0x01
	#define sub_MENU_SET_WARN_TYPE_2			0x02
	#define sub_MENU_SET_WARN_TYPE_3			0x03
	//报警值和回差,psd=16
	#define MENU_SET_WARN_VALUE					0x90
	#define sub_MENU_SET_WARN_VALUE_0			0x00
	#define sub_MENU_SET_WARN_VALUE_1			0x01
	#define sub_MENU_SET_WARN_VALUE_2			0x02
	#define sub_MENU_SET_WARN_VALUE_3			0x03
	#define sub_MENU_SET_WARN_VALUE_4			0x04
	#define sub_MENU_SET_WARN_VALUE_5			0x05
	#define sub_MENU_SET_WARN_VALUE_6			0x06
	#define sub_MENU_SET_WARN_VALUE_7			0x07
	//外部压力零点和线性,psd=138
	#define MENU_SET_EPR_ZERO_LINE              0xa0
	//#define MENU_SET_EX_D_PR_ZERO				0xa0
	#define sub_MENU_SET_EPR_CH0_P0				0x00
	#define sub_MENU_SET_EPR_CH0_P1				0x01
	#define sub_MENU_SET_EPR_CH1_P0				0x02
	#define sub_MENU_SET_EPR_CH1_P1				0x03
	//外部温度修正PSW_SET_ETMEP_ZERO_LINE	=136
	#define MENU_SET_ETMEP_ZERO_LINE			0xa1
	#define sub_MENU_SET_P0						0x00
	#define sub_MENU_SET_P1						0x01
	//外部压输出范围,psd=139
	#define MENU_SET_EPR_ILOOP_SCALE			0xb0
	//#define MENU_SET_EX_D_PR_ILOOP_L			0xb0
	#define sub_MENU_SET_EXPR_ILP_CH0_Lo		0x00
	#define sub_MENU_SET_EXPR_ILP_CH0_Hi		0x01
	#define sub_MENU_SET_EXPR_ILP_CH1_Lo		0x02
	#define sub_MENU_SET_EXPR_ILP_CH1_Hi		0x03
	
	//高度条满刻度对应的值95%还是100%,psd=188	
	#define MENU_SET_BAR_LEVEL_SCALE			0xc0
	#define sub_MENU_SET_BAR_LEVEL_SCALE		0x00
	//显示方式,显示即时值还是平均值
	#define MENU_SET_WORK_MODE					0xf0
	#define sub_MENU_SET_WORK_MODE				0x00
	
	typedef union{
		uint8_t t8;
		struct{
			uint8_t upLineMenu:4;
			uint8_t downLineMenu:4;
		}stru;
	}st_homeSubMenu;

	//variable
	extern volatile uint8_t menu;
    extern volatile uint8_t subMenu;
	//extern volatile uint8_t keyValue;
	extern volatile uint16_t passWord;
	extern volatile uint8_t adjLocation;
    extern volatile int32_t adjValue;
	extern  st_float32_m m_floatAdj;
	//
	extern volatile uint8_t  calibRow;
	extern volatile uint8_t  calibCol;	
	//function
	extern void key_process(void);
	//9086504300
	//3045006890
#ifdef __cplusplus
}
#endif
#endif
//file  end
