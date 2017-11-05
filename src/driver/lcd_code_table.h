#ifndef __lcd_code_table_h__
#define __lcd_code_table_h__

#ifdef __cplusplus
extern "C"{
#endif
	#define LCD_DSEG_A 	0x01
	#define LCD_DSEG_B 	0x02
	#define LCD_DSEG_C 	0x04
	#define LCD_DSEG_D 	0x08	
	//
	#define LCD_DSEG_E 	0x10
	#define LCD_DSEG_F 	0x20
	#define LCD_DSEG_G 	0x40
	#define LCD_DSEG_DP 0x80
	//

	#define LCD_CODE_0 (LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_D + LCD_DSEG_C + LCD_DSEG_B + LCD_DSEG_A)
	#define LCD_CODE_1 (LCD_DSEG_B + LCD_DSEG_C)
	#define LCD_CODE_2 (LCD_DSEG_A + LCD_DSEG_B + LCD_DSEG_G + LCD_DSEG_E + LCD_DSEG_D)      
	#define LCD_CODE_3 (LCD_DSEG_A + LCD_DSEG_B + LCD_DSEG_G + LCD_DSEG_C + LCD_DSEG_D)  
	#define LCD_CODE_4 (LCD_DSEG_F + LCD_DSEG_G + LCD_DSEG_B + LCD_DSEG_C) 
	#define LCD_CODE_5 (LCD_DSEG_F + LCD_DSEG_G + LCD_DSEG_C + LCD_DSEG_D + LCD_DSEG_A)
	#define LCD_CODE_6 (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_D + LCD_DSEG_C + LCD_DSEG_G)
	#define LCD_CODE_7 (LCD_DSEG_A + LCD_DSEG_B + LCD_DSEG_C)  
	#define LCD_CODE_8 (LCD_DSEG_A + LCD_DSEG_B + LCD_DSEG_C + LCD_DSEG_D + LCD_DSEG_E + LCD_DSEG_F + LCD_DSEG_G)
	#define LCD_CODE_9 (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_G + LCD_DSEG_B + LCD_DSEG_C+ LCD_DSEG_D)

	#define LCD_CODE_A (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_B + LCD_DSEG_C + LCD_DSEG_G)
	#define LCD_CODE_B (LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_G + LCD_DSEG_C + LCD_DSEG_D)
	#define LCD_CODE_C (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_D)
	#define LCD_CODE_D (LCD_DSEG_B + LCD_DSEG_E + LCD_DSEG_G + LCD_DSEG_C + LCD_DSEG_D)
	#define LCD_CODE_E (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_D + LCD_DSEG_G)
	#define LCD_CODE_F (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_E + LCD_DSEG_G)
	#define LCD_CODE_G (LCD_DSEG_A + LCD_DSEG_F + LCD_DSEG_G + LCD_DSEG_B + LCD_DSEG_C+ LCD_DSEG_D)
	#define LCD_CODE_G_U (LCD_DSEG_A + LCD_DSEG_C + LCD_DSEG_D + LCD_DSEG_E + LCD_DSEG_F)
	
	#define LCD_CODE_H_U (LCD_DSEG_B + LCD_DSEG_C + LCD_DSEG_E + LCD_DSEG_F + LCD_DSEG_G)
	#define LCD_CODE_H (LCD_DSEG_C + LCD_DSEG_E + LCD_DSEG_F + LCD_DSEG_G)
	#define LCD_CODE_I LCD_CODE_1
	#define LCD_CODE_J (LCD_DSEG_B + LCD_DSEG_C + LCD_DSEG_D)
	#define LCD_CODE_K (LCD_DSEG_B+LCD_DSEG_D+LCD_DSEG_E+LCD_DSEG_F+LCD_DSEG_G)
	#define LCD_CODE_L (LCD_DSEG_F +LCD_DSEG_E +LCD_DSEG_D)
	#define LCD_CODE_M 0
	#define LCD_CODE_N (LCD_DSEG_F +LCD_DSEG_E +LCD_DSEG_A+LCD_DSEG_B+LCD_DSEG_C)
	
	//#define LCD_CODE_O LCD_CODE_0
    #define LCD_CODE_O (LCD_DSEG_C + LCD_DSEG_D + LCD_DSEG_E + LCD_DSEG_G)
	#define LCD_CODE_P (LCD_DSEG_A +LCD_DSEG_B +LCD_DSEG_E+LCD_DSEG_F+LCD_DSEG_G)
	#define LCD_CODE_Q (LCD_DSEG_A +LCD_DSEG_B +LCD_DSEG_C+LCD_DSEG_F+LCD_DSEG_G)

	//#define LCD_CODE_R (LCD_DSEG_A +LCD_DSEG_F +LCD_DSEG_E)
    #define LCD_CODE_R (LCD_DSEG_E + LCD_DSEG_G)
	#define LCD_CODE_S LCD_CODE_5
	#define LCD_CODE_T (LCD_DSEG_F +LCD_DSEG_E +LCD_DSEG_D+LCD_DSEG_G)
	
	#define LCD_CODE_U (LCD_DSEG_B +LCD_DSEG_C +LCD_DSEG_D+LCD_DSEG_E+LCD_DSEG_F)
	#define LCD_CODE_V 0
	#define LCD_CODE_W 0

	#define LCD_CODE_X 0
	#define LCD_CODE_Y (LCD_DSEG_B +LCD_DSEG_C +LCD_DSEG_D+LCD_DSEG_G+LCD_DSEG_F)
	#define LCD_CODE_Z LCD_CODE_2
	
	#define LCD_CODE_DP LCD_DSEG_DP
	#define LCD_CODE__ (LCD_DSEG_G)
	#define LCD_CODE_DOT	(LCD_DSEG_G)
	#define LCD_CODE_DDOT	(LCD_DSEG_G+LCD_DSEG_D)

	#define LCD_TABLE_LEN 40
	extern const uint8_t LCDDigitalTable[];


#ifdef __cplusplus
}
#endif


#endif