#include "drivers.h"
#include "lcd_code_table.h"
#include "lcd_code_table_ex.h"
#include "lcd.h"

extern volatile bool blackEn;
//uint8_t* pLcdReg=(uint8_t*)(&LCDDATA0); 
uint16_t pLCD[LCD_PIXEL_REGISTER_SIZE];

const uint8_t  LCDDigitalIndexTable[]="0123456789abcdefghijklmnopqrstuvwxyz.-: GHC*";
const uint8_t LCDDigitalTable[]=
{
    LCD_CODE_0,LCD_CODE_1,LCD_CODE_2,LCD_CODE_3,
    LCD_CODE_4,LCD_CODE_5,LCD_CODE_6,LCD_CODE_7,
    LCD_CODE_8,LCD_CODE_9,LCD_CODE_A,LCD_CODE_B,
    LCD_CODE_C,LCD_CODE_D,LCD_CODE_E,LCD_CODE_F,
    LCD_CODE_G,LCD_CODE_H,LCD_CODE_I,LCD_CODE_J,
    LCD_CODE_K,LCD_CODE_L,LCD_CODE_M,LCD_CODE_N,
    LCD_CODE_O,LCD_CODE_P,LCD_CODE_Q,LCD_CODE_R,
    LCD_CODE_S,LCD_CODE_T,LCD_CODE_U,LCD_CODE_V,
    LCD_CODE_W,LCD_CODE_X,LCD_CODE_Y,LCD_CODE_Z,
    LCD_CODE_DOT,LCD_CODE__,LCD_CODE_DDOT,0x00,
	LCD_CODE_G_U,LCD_CODE_H_U,LCD_CODE_C,LCD_CODE_STAR,
};
const uint8_t LCDDigitalTableIndexEx[]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
const uint16_t LCDDigitalTableEx[]=
{
    LCD_CODE_0_EX,LCD_CODE_1_EX,LCD_CODE_2_EX,LCD_CODE_3_EX,
    LCD_CODE_4_EX,LCD_CODE_5_EX,LCD_CODE_6_EX,LCD_CODE_7_EX,
    LCD_CODE_8_EX,LCD_CODE_9_EX,LCD_CODE_a_EX,LCD_CODE_b_EX,
    LCD_CODE_c_EX,LCD_CODE_d_EX,LCD_CODE_e_EX,LCD_CODE_f_EX,
    LCD_CODE_g_EX,LCD_CODE_h_EX,LCD_CODE_i_EX,LCD_CODE_j_EX,
    LCD_CODE_k_EX,LCD_CODE_l_EX,LCD_CODE_m_EX,LCD_CODE_n_EX,
    LCD_CODE_o_EX,LCD_CODE_p_EX,LCD_CODE_q_EX,LCD_CODE_r_EX,
    LCD_CODE_s_EX,LCD_CODE_t_EX,LCD_CODE_u_EX,LCD_CODE_v_EX,
    LCD_CODE_w_EX,LCD_CODE_x_EX,LCD_CODE_y_EX,LCD_CODE_z_EX,
	LCD_CODE_A_EX,LCD_CODE_B_EX,
    LCD_CODE_C_EX,LCD_CODE_D_EX,LCD_CODE_E_EX,LCD_CODE_F_EX,
    LCD_CODE_G_EX,LCD_CODE_H_EX,LCD_CODE_I_EX,LCD_CODE_J_EX,
    LCD_CODE_K_EX,LCD_CODE_L_EX,LCD_CODE_M_EX,LCD_CODE_N_EX,
    LCD_CODE_O_EX,LCD_CODE_P_EX,LCD_CODE_Q_EX,LCD_CODE_R_EX,
    LCD_CODE_S_EX,LCD_CODE_T_EX,LCD_CODE_U_EX,LCD_CODE_V_EX,
    LCD_CODE_W_EX,LCD_CODE_X_EX,LCD_CODE_Y_EX,LCD_CODE_Z_EX,	
    0,
};
#define lcd_set_com_seg(c,s,show) do{ \
	if(show){pLCD[(c<<2)+(s>>4)] |= (1<<(s&0x0f));} \
    else{pLCD[(c<<2)+(s>>4)] &= ~(1<<(s&0x0f));} \
}while(0); 
/*
void lcd_set_com_seg(uint8_t com,uint8_t seg,uint16_t show)
{
	uint16_t offset;
	uint16_t	bits;
	if(com>7)return;
	if(seg>63)return;
	offset=com*4 + seg/16;
	bits=seg%16;
	if(show){
		pLCD[offset] |= (1<<bits);
	}else{
		pLCD[offset] &= ~(1<<bits);
	}
}
*/
void lcd_disp_level_bar(uint8_t bar,uint8_t show)
{
	//0-49 swap 
	uint8_t __bar;
	if(bar>49)return;
	__bar=49-bar;
	switch(__bar){
		case 0:		lcd_set_com_seg(7,63,show);	break;
		case 1:		lcd_set_com_seg(6,63,show);	break;
		case 2:		lcd_set_com_seg(5,63,show);	break;
		case 3:		lcd_set_com_seg(0,63,show);	break;
		
		case 4:		lcd_set_com_seg(1,63,show);	break;
		case 5:		lcd_set_com_seg(2,63,show);	break;
		case 6:		lcd_set_com_seg(3,63,show);	break;
		case 7:		lcd_set_com_seg(4,63,show);	break;
		
		case 8:		lcd_set_com_seg(4,62,show);	break;
		case 9:		lcd_set_com_seg(3,62,show);	break;		
		case 10:	lcd_set_com_seg(2,62,show);	break;
		case 11:	lcd_set_com_seg(1,62,show);	break;
		
		case 12:	lcd_set_com_seg(0,62,show);	break;
		case 13:	lcd_set_com_seg(5,62,show);	break;
		case 14:	lcd_set_com_seg(6,62,show);	break;
		case 15:	lcd_set_com_seg(7,62,show);	break;
		
		case 16:	lcd_set_com_seg(7,61,show);	break;
		case 17:	lcd_set_com_seg(6,61,show);	break;
		case 18:	lcd_set_com_seg(5,61,show);	break;
		case 19:	lcd_set_com_seg(0,61,show);	break;
		
		case 20:	lcd_set_com_seg(1,61,show);	break;
		case 21:	lcd_set_com_seg(2,61,show);	break;
		case 22:	lcd_set_com_seg(3,61,show);	break;
		case 23:	lcd_set_com_seg(4,61,show);	break;
		
		case 24:	lcd_set_com_seg(4,60,show);	break;
		case 25:	lcd_set_com_seg(3,60,show);	break;
		case 26:	lcd_set_com_seg(2,60,show);	break;
		case 27:	lcd_set_com_seg(1,60,show);	break;
		
		case 28:	lcd_set_com_seg(0,60,show);	break;
		case 29:	lcd_set_com_seg(5,60,show);	break;		
		case 30:	lcd_set_com_seg(6,60,show);	break;
		case 31:	lcd_set_com_seg(7,60,show);	break;
		
		case 32:	lcd_set_com_seg(7,59,show);	break;
		case 33:	lcd_set_com_seg(6,59,show);	break;
		case 34:	lcd_set_com_seg(5,59,show);	break;
		case 35:	lcd_set_com_seg(0,59,show);	break;
		
		case 36:	lcd_set_com_seg(1,59,show);	break;
		case 37:	lcd_set_com_seg(2,59,show);	break;
		case 38:	lcd_set_com_seg(3,59,show);	break;
		case 39:	lcd_set_com_seg(4,59,show);	break;
		
		case 40:	lcd_set_com_seg(4,58,show);	break;
		case 41:	lcd_set_com_seg(3,58,show);	break;
		case 42:	lcd_set_com_seg(2,58,show);	break;
		case 43:	lcd_set_com_seg(1,58,show);	break;
		
		case 44:	lcd_set_com_seg(0,58,show);	break;
		case 45:	lcd_set_com_seg(5,58,show);	break;
		case 46:	lcd_set_com_seg(6,58,show);	break;
		case 47:	lcd_set_com_seg(7,58,show);	break;
		
		case 48:	lcd_set_com_seg(7,46,show);	break;
		case 49:	lcd_set_com_seg(6,46,show);	break;		
	}
}
//@bierf scale:0~99
void lcd_disp_level(uint8_t level)
{
	uint8_t i;
	if(level>=100)level=100;
	level/=2;
	for(i=0;i<level;i++){
		lcd_disp_level_bar(i,1);
	}
	for(;i<50;i++){
		lcd_disp_level_bar(i,0);
	}
}
void lcd_disp_level_off(void)
{
	uint8_t i;
	for(i=0;i<50;i++){
		lcd_disp_level_bar(i,0);
	}	
}


void lcd_disp_battary_bar(uint8_t bar,uint8_t show)
{
	if(bar>=4)bar=4;
	switch(bar){
		case 0:	lcd_set_com_seg(3,50,show);	break;
		case 1:	lcd_set_com_seg(4,46,show);	break;
		case 2:	lcd_set_com_seg(3,46,show);	break;
		case 3:	lcd_set_com_seg(4,50,show);	break;
	}
}
void lcd_disp_battary(uint8_t level)
{
	uint8_t i;
	//if(level>=100)level=100;
	//level/=25;
	if(level>3)level=3;
	//if(level<1)level=1;
	for(i=0;i<=level;i++){
		lcd_disp_battary_bar(i,1);
	}
	for(;i<4;i++){
		lcd_disp_battary_bar(i,0);
	}
}
void lcd_disp_battary_off(void)
{
	uint8_t i;
	for(i=0;i<4;i++){
		lcd_disp_battary_bar(i,0);
	}
}

void lcd_disp_rf_bar(uint8_t bar,uint8_t show)
{
	if(bar>=4)bar=4;
	switch(bar){
		case 0:	lcd_set_com_seg(5,46,show);	break;
		case 1:	lcd_set_com_seg(0,46,show);	break;
		case 2:	lcd_set_com_seg(1,46,show);	break;
		case 3:	lcd_set_com_seg(0,47,show);	break;
	}	
}
void lcd_disp_rf(uint8_t rssi)
{
	uint8_t i;
	if(rssi>=100)rssi=100;
	rssi/=25;
	if(rssi<1)rssi=1;
	for(i=0;i<rssi;i++){
		lcd_disp_rf_bar(i,1);
	}
	for(;i<4;i++){
		lcd_disp_rf_bar(i,0);
	}
}
void lcd_disp_rf_off(void)
{
	uint8_t i;
	for(i=0;i<4;i++){
		lcd_disp_rf_bar(i,0);
	}
}

void lcd_disp_light_bar(uint8_t bar,uint8_t show)
{
	if(bar>=1)bar=1;
	switch(bar){
		case 0:	lcd_set_com_seg(2,46,show);	break;
		case 1:	lcd_set_com_seg(2,50,show);	break;
	}	
}
void lcd_disp_light(uint8_t light)
{
	//if(light>=100)light=100;
	//light/=50;
	if(light>2)light=2;
	//if(light<1)light=1;
	if(2==light){
		lcd_disp_light_bar(0,1);
		lcd_disp_light_bar(1,1);
	}else if(1==light){
		lcd_disp_light_bar(0,1);
	}else{
        
    }
}
void lcd_disp_light_off(void)
{
	lcd_disp_light_bar(0,0);
	lcd_disp_light_bar(1,0);
}

//show dig.
void lcd_disp_chr_loc_0(uint8_t code)
{
	lcd_set_com_seg(7,41,code&LCD_DSEG_A);
	lcd_set_com_seg(6,41,code&LCD_DSEG_B);
    lcd_set_com_seg(5,41,code&LCD_DSEG_C);
    lcd_set_com_seg(0,41,code&LCD_DSEG_D);
    
    lcd_set_com_seg(7,47,code&LCD_DSEG_F);
    lcd_set_com_seg(6,47,code&LCD_DSEG_G);
    lcd_set_com_seg(5,47,code&LCD_DSEG_E);
    //lcd_disp_com_seg(3,00,code&LCD_DSEG_DP);
}
void lcd_disp_dp_loc_0(bool dp)
{
	if(dp){
		lcd_set_com_seg(0,40,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(0,40,0);
    }
}

void lcd_disp_chr_loc_1(uint8_t code)
{
	lcd_set_com_seg(7,12,code&LCD_DSEG_A);
	lcd_set_com_seg(6,12,code&LCD_DSEG_B);
    lcd_set_com_seg(5,12,code&LCD_DSEG_C);
    lcd_set_com_seg(0,12,code&LCD_DSEG_D);
    
    lcd_set_com_seg(7,40,code&LCD_DSEG_F);
    lcd_set_com_seg(6,40,code&LCD_DSEG_G);
    lcd_set_com_seg(5,40,code&LCD_DSEG_E);
}
void lcd_disp_dp_loc_1(bool dp)
{
	if(dp){
		lcd_set_com_seg(0,11,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(0,11,0);
    }
}

void lcd_disp_chr_loc_2(uint8_t code)
{
	lcd_set_com_seg(7,10,code&LCD_DSEG_A);
	lcd_set_com_seg(6,10,code&LCD_DSEG_B);
    lcd_set_com_seg(5,10,code&LCD_DSEG_C);
    lcd_set_com_seg(0,10,code&LCD_DSEG_D);
    
    lcd_set_com_seg(7,11,code&LCD_DSEG_F);
    lcd_set_com_seg(6,11,code&LCD_DSEG_G);
    lcd_set_com_seg(5,11,code&LCD_DSEG_E);
}
void lcd_disp_dp_loc_2(bool dp)
{
	if(dp){
		lcd_set_com_seg(0,39,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(0,39,0);
    }
}

void lcd_disp_chr_loc_3(uint8_t code)
{
	lcd_set_com_seg(7,38,code&LCD_DSEG_A);
	lcd_set_com_seg(6,38,code&LCD_DSEG_B);
    lcd_set_com_seg(5,38,code&LCD_DSEG_C);
    lcd_set_com_seg(0,38,code&LCD_DSEG_D);
    
    lcd_set_com_seg(7,39,code&LCD_DSEG_F);
    lcd_set_com_seg(6,39,code&LCD_DSEG_G);
    lcd_set_com_seg(5,39,code&LCD_DSEG_E);
}

void lcd_disp_chr_loc_4(uint8_t code)
{
	lcd_set_com_seg(1,41,code&LCD_DSEG_A);
	lcd_set_com_seg(2,41,code&LCD_DSEG_B);
    lcd_set_com_seg(3,41,code&LCD_DSEG_C);
    lcd_set_com_seg(4,41,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,47,code&LCD_DSEG_F);
    lcd_set_com_seg(2,47,code&LCD_DSEG_G);
    lcd_set_com_seg(3,47,code&LCD_DSEG_E);
}
void lcd_disp_dp_loc_4(bool dp)
{
	if(dp){
		lcd_set_com_seg(4,40,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(4,40,0);
    }
}

void lcd_disp_chr_loc_5(uint8_t code)
{
	lcd_set_com_seg(1,12,code&LCD_DSEG_A);
	lcd_set_com_seg(2,12,code&LCD_DSEG_B);
    lcd_set_com_seg(3,12,code&LCD_DSEG_C);
    lcd_set_com_seg(4,12,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,40,code&LCD_DSEG_F);
    lcd_set_com_seg(2,40,code&LCD_DSEG_G);
    lcd_set_com_seg(3,40,code&LCD_DSEG_E);
}
void lcd_disp_dp_loc_5(bool dp)
{
	if(dp){
		lcd_set_com_seg(4,11,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(4,11,0);
    }
}

void lcd_disp_chr_loc_6(uint8_t code)
{
	lcd_set_com_seg(1,10,code&LCD_DSEG_A);
	lcd_set_com_seg(2,10,code&LCD_DSEG_B);
    lcd_set_com_seg(3,10,code&LCD_DSEG_C);
    lcd_set_com_seg(4,10,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,11,code&LCD_DSEG_F);
    lcd_set_com_seg(2,11,code&LCD_DSEG_G);
    lcd_set_com_seg(3,11,code&LCD_DSEG_E);
}
void lcd_disp_dp_loc_6(bool dp)
{
	if(dp){
		lcd_set_com_seg(4,39,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(4,39,0);
    }
}

void lcd_disp_chr_loc_7(uint8_t code)
{
	lcd_set_com_seg(1,38,code&LCD_DSEG_A);
	lcd_set_com_seg(2,38,code&LCD_DSEG_B);
    lcd_set_com_seg(3,38,code&LCD_DSEG_C);
    lcd_set_com_seg(4,38,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,39,code&LCD_DSEG_F);
    lcd_set_com_seg(2,39,code&LCD_DSEG_G);
    lcd_set_com_seg(3,39,code&LCD_DSEG_E);	
}

/*
void lcd_disp_dp_loc(bool dp,uint8_t loc)
{
	switch(loc){
		case 0:	lcd_disp_dp_loc_0(dp);break;
		case 1:	lcd_disp_dp_loc_1(dp);break;
		case 2:	lcd_disp_dp_loc_2(dp);break;
		case 4:	lcd_disp_dp_loc_4(dp);break;
		case 5:	lcd_disp_dp_loc_5(dp);break;
		case 6:	lcd_disp_dp_loc_6(dp);break;
	}		
}
*/
//show unit
void lcd_disp_logo(bool show)
{

}

void lcd_disp_unit_t(bool show)
{
	lcd_set_com_seg(1,34,0);
	lcd_set_com_seg(1,35,0);
	if(show){
		lcd_set_com_seg(1,49,1);
    }else{
		lcd_set_com_seg(1,49,0);
    }
}

void lcd_disp_unit_1st_m(bool show)
{
	//t2=3;t3=m
	lcd_set_com_seg(1,49,0);
	lcd_set_com_seg(1,35,0);
	if(show){
		lcd_set_com_seg(1,34,1);
	}else{
		lcd_set_com_seg(1,34,0);
	}
}

void lcd_disp_unit_1st_m3(bool show)
{
	//t2=3;t3=m
	lcd_set_com_seg(1,49,0);
	if(show){
		lcd_set_com_seg(1,34,1);
		lcd_set_com_seg(1,35,1);
	}else{
		lcd_set_com_seg(1,34,0);
		lcd_set_com_seg(1,35,0);
	}
}

void lcd_disp_unit_temperature(bool show)
{
	//lcd_set_com_seg(2,49,0);
	//lcd_set_com_seg(2,35,0);
	//lcd_set_com_seg(3,35,0);
	if(show){
		lcd_set_com_seg(4,35,1);
	}else{
		lcd_set_com_seg(4,35,0);
	}
}

void lcd_disp_unit_2nd_m(bool show)
{
	//t4=3;t5=m
	lcd_set_com_seg(2,49,0);
	lcd_set_com_seg(3,35,0);
	lcd_set_com_seg(4,35,0);
	if(show){
		lcd_set_com_seg(2,34,1);
    }else{
		lcd_set_com_seg(2,34,0);
    }
}

void lcd_disp_unit_2nd_m3(bool show)
{
	//t4=3;t5=m
	lcd_set_com_seg(2,49,0);
	lcd_set_com_seg(4,35,0);

	
	if(show){
		lcd_set_com_seg(2,34,1);
		lcd_set_com_seg(3,35,1);
	}else{
		lcd_set_com_seg(2,34,0);
		lcd_set_com_seg(3,35,0);
	}
}

void lcd_disp_unit_mpa(bool show)
{
	//mpa=t6
	lcd_set_com_seg(2,34,0);
	lcd_set_com_seg(3,35,0);
	lcd_set_com_seg(4,35,0);
	if(show){
		lcd_set_com_seg(2,49,1);
	}else{
		lcd_set_com_seg(2,49,0);
	}
}
//enn unit
//add
void lcd_disp_chr_loc_0_ex(uint16_t code)
{
	lcd_set_com_seg(7,49,code&SEG_A_EX);	
	lcd_set_com_seg(7,35,code&SEG_B_EX);	
	lcd_set_com_seg(5,35,code&SEG_C_EX);	
	lcd_set_com_seg(0,35,code&SEG_D_EX);	
	lcd_set_com_seg(0,49,code&SEG_E_EX);	
	lcd_set_com_seg(6,49,code&SEG_F_EX);	
	lcd_set_com_seg(5,49,code&SEG_G_EX);	
	lcd_set_com_seg(6,35,code&SEG_H_EX);
	lcd_set_com_seg(6,34,code&SEG_I_EX);	
	lcd_set_com_seg(7,34,code&SEG_J_EX);	
	lcd_set_com_seg(5,34,code&SEG_K_EX);	
	lcd_set_com_seg(0,34,code&SEG_L_EX);	
}
void lcd_disp_chr_loc_1_ex(uint16_t code)
{
	lcd_set_com_seg(7,4,code&SEG_A_EX);	
	lcd_set_com_seg(7,18,code&SEG_B_EX);	
	lcd_set_com_seg(5,18,code&SEG_C_EX);	
	lcd_set_com_seg(0,18,code&SEG_D_EX);	
	lcd_set_com_seg(0,4,code&SEG_E_EX);	
	lcd_set_com_seg(6,4,code&SEG_F_EX);	
	lcd_set_com_seg(5,4,code&SEG_G_EX);	
	lcd_set_com_seg(6,18,code&SEG_H_EX);
	lcd_set_com_seg(6,55,code&SEG_I_EX);	
	lcd_set_com_seg(7,55,code&SEG_J_EX);	
	lcd_set_com_seg(5,55,code&SEG_K_EX);	
	lcd_set_com_seg(0,55,code&SEG_L_EX);	
}
void lcd_disp_chr_loc_2_ex(uint16_t code)
{
	lcd_set_com_seg(7,19,code&SEG_A_EX);	
	lcd_set_com_seg(7,9,code&SEG_B_EX);	
	lcd_set_com_seg(5,9,code&SEG_C_EX);	
	lcd_set_com_seg(0,9,code&SEG_D_EX);	
	lcd_set_com_seg(0,19,code&SEG_E_EX);	
	lcd_set_com_seg(6,19,code&SEG_F_EX);	
	lcd_set_com_seg(5,19,code&SEG_G_EX);	
	lcd_set_com_seg(6,9,code&SEG_H_EX);
	lcd_set_com_seg(6,8,code&SEG_I_EX);	
	lcd_set_com_seg(7,8,code&SEG_J_EX);	
	lcd_set_com_seg(5,8,code&SEG_K_EX);	
	lcd_set_com_seg(0,8,code&SEG_L_EX);	
}
void lcd_disp_chr_loc_0_sm(uint8_t code)
{
	lcd_set_com_seg(1,55,code&LCD_DSEG_A);
	lcd_set_com_seg(2,55,code&LCD_DSEG_B);
    lcd_set_com_seg(3,55,code&LCD_DSEG_C);
    lcd_set_com_seg(4,55,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,4,code&LCD_DSEG_F);
    lcd_set_com_seg(2,4,code&LCD_DSEG_G);
    lcd_set_com_seg(3,4,code&LCD_DSEG_E);
    //lcd_disp_com_seg(3,00,code&LCD_DSEG_DP);
}
void lcd_disp_chr_loc_1_sm(uint8_t code)
{
	lcd_set_com_seg(1,19,code&LCD_DSEG_A);
	lcd_set_com_seg(2,19,code&LCD_DSEG_B);
    lcd_set_com_seg(3,19,code&LCD_DSEG_C);
    lcd_set_com_seg(4,19,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,18,code&LCD_DSEG_F);
    lcd_set_com_seg(2,18,code&LCD_DSEG_G);
    lcd_set_com_seg(3,18,code&LCD_DSEG_E);
    //lcd_disp_com_seg(3,00,code&LCD_DSEG_DP);
}
void lcd_disp_chr_loc_2_sm(uint8_t code)
{
	lcd_set_com_seg(1,9,code&LCD_DSEG_A);
	lcd_set_com_seg(2,9,code&LCD_DSEG_B);
    lcd_set_com_seg(3,9,code&LCD_DSEG_C);
    lcd_set_com_seg(4,9,code&LCD_DSEG_D);
    
    lcd_set_com_seg(1,8,code&LCD_DSEG_F);
    lcd_set_com_seg(2,8,code&LCD_DSEG_G);
    lcd_set_com_seg(3,8,code&LCD_DSEG_E);
    //lcd_disp_com_seg(3,00,code&LCD_DSEG_DP);
}
void lcd_disp_dp_loc_0_sm(bool dp)
{
	if(dp){
		lcd_set_com_seg(4,18,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(4,18,0);
    }
}
void lcd_disp_dp_loc_1_sm(bool dp)
{
	if(dp){
		lcd_set_com_seg(4,4,LCD_DSEG_DP);
    }else {
		lcd_set_com_seg(4,4,0);
    }
}
void lcd_disp_dp_loc_sign_sm(bool sig)
{
	if(sig){
		lcd_set_com_seg(2,35,1);
    }else {
		lcd_set_com_seg(2,35,0);
    }
}
void lcd_disp_dp_loc_sm_temperature(bool show)
{
	if(show){
		lcd_set_com_seg(4,8,1);
    }else {
		lcd_set_com_seg(4,8,0);
    }
}
void lcd_show_dp_sm(uint8_t loc,bool show)
{
	switch(loc){
		case 0:lcd_disp_dp_loc_0_sm(show);break;
		case 1:lcd_disp_dp_loc_1_sm(show);break;
		//case 7:
		default:break;
	}		
}
void lcd_clear_all_dp_sm(void)
{
	 lcd_disp_dp_loc_0_sm(false);
	 lcd_disp_dp_loc_1_sm(false);
}
//api
uint8_t lcd_disp_get_code(uint8_t chr)
{
	uint8_t i;
	uint8_t ret=0;
	for(i=0;i<sizeof(LCDDigitalIndexTable);i++){
		if(chr==LCDDigitalIndexTable[i])break;
	}
	if(i<sizeof(LCDDigitalIndexTable)){
		ret= LCDDigitalTable[i];
	}
	return ret;
}

uint16_t lcd_disp_get_code_ex(uint8_t chr)
{
	uint8_t i;
	uint16_t ret;
	for(i=0;i<sizeof(LCDDigitalTableIndexEx);i++){
		if(chr==LCDDigitalTableIndexEx[i])break;
	}
	if(i<sizeof(LCDDigitalTableIndexEx)){
		ret= LCDDigitalTableEx[i];
	}
	return ret;
}
void lcd_clear_all_dp(void)
{
	lcd_disp_dp_loc_0(false);
	lcd_disp_dp_loc_1(false);
	lcd_disp_dp_loc_2(false);
	lcd_disp_dp_loc_4(false);
	lcd_disp_dp_loc_5(false);
	lcd_disp_dp_loc_6(false);
}

void lcd_show_dp(uint8_t loc,bool show)
{
	switch(loc){
		case 0:lcd_disp_dp_loc_0(show);break;
		case 1:lcd_disp_dp_loc_1(show);break;
		case 2:lcd_disp_dp_loc_2(show);break;
		//case 3:
		case 4:lcd_disp_dp_loc_4(show);break;
		case 5:lcd_disp_dp_loc_5(show);break;
		case 6:lcd_disp_dp_loc_6(show);break;
		//case 7:
		default:break;
	}		
}

void lcd_show_chr(uint8_t loc,uint8_t chr)
{
    uint8_t code;
    
    code=lcd_disp_get_code(chr);
    //return;
	switch(loc){
		case 0:lcd_disp_chr_loc_0(code);break;
		case 1:lcd_disp_chr_loc_1(code);break;
		case 2:lcd_disp_chr_loc_2(code);break;
		case 3:lcd_disp_chr_loc_3(code);break;
		case 4:lcd_disp_chr_loc_4(code);break;
		case 5:lcd_disp_chr_loc_5(code);break;
		case 6:lcd_disp_chr_loc_6(code);break;
		case 7:lcd_disp_chr_loc_7(code);break;
		default:break;
	}		
}

void lcd_show_chr_sm(uint8_t loc,uint8_t chr)
{
    uint8_t code=lcd_disp_get_code(chr);
	switch(loc){
		case 0:lcd_disp_chr_loc_0_sm(code);break;
		case 1:lcd_disp_chr_loc_1_sm(code);break;
		case 2:lcd_disp_chr_loc_2_sm(code);break;
		default:break;
	}		
}
void lcd_show_chr_ex(uint8_t loc,uint8_t chr)
{
    uint16_t code=lcd_disp_get_code_ex(chr);
	switch(loc){
		case 0:lcd_disp_chr_loc_0_ex(code);break;
		case 1:lcd_disp_chr_loc_1_ex(code);break;
		case 2:lcd_disp_chr_loc_2_ex(code);break;
		default:break;
	}		
}
void lcd_show_string_sm(uint8_t* str)
{
	uint8_t t8=0;
	while(*str!='\0' && t8<3){
		lcd_show_chr_sm(t8,*str);
		str++;
		t8++;
	}
}
void lcd_show_string_ex(uint8_t* str)
{
	uint8_t t8=0;
	while(*str!='\0' && t8<3){
		lcd_show_chr_ex(t8,*str);
		str++;
		t8++;
	}
}
//line col.
void lcd_show_chr_lc(uint8_t line,uint8_t col,uint8_t chr)
{
	uint8_t loc;
	if(line>1)return;
	if(col>3)return;
	loc=(line<<1)+col;
	lcd_show_chr(loc,chr);
}

void lcd_show_string_l0(uint8_t* str)
{
	uint8_t t8=0;
	while(*str!='\0' && t8<4){
		lcd_show_chr(t8,*str);
		str++;
		t8++;
	}
}

void lcd_show_string_l1(uint8_t* str)
{
	uint8_t t8=0;
	while(*str!='\0' && t8<4){
		lcd_show_chr(t8+4,*str);
		str++;
		t8++;
	}
}

void lcd_show_string(uint8_t* str)
{
	uint8_t t8=0;

	while(*str!='\0' && t8<8){
		lcd_show_chr(t8,*str);
		str++;
		t8++;
	}
}



void lcd_disp_refresh(void)
{
	//m_mem_cpy_len(pLcdReg,pLCD,LCD_PIXEL_REGISTER_SIZE);
	
	// while(!(LCDPSbits.WA)){
         //LCDCONbits.WERR=0;
    //};
    //if(LCDCONbits.WERR)LCDCONbits.WERR=0;
    if(!(LCDPSbits.WA))return;
	LCDDATA0=pLCD[0];
	LCDDATA1=pLCD[1];
	LCDDATA2=pLCD[2];
	LCDDATA3=pLCD[3];
	LCDDATA4=pLCD[4];
	LCDDATA5=pLCD[5];
	LCDDATA6=pLCD[6];
	LCDDATA7=pLCD[7];
	LCDDATA8=pLCD[8];
	LCDDATA9=pLCD[9];
	
	LCDDATA10=pLCD[10];
	LCDDATA11=pLCD[11];
	LCDDATA12=pLCD[12];
	LCDDATA13=pLCD[13];
	LCDDATA14=pLCD[14];
	LCDDATA15=pLCD[15];
	LCDDATA16=pLCD[16];
	LCDDATA17=pLCD[17];
	LCDDATA18=pLCD[18];
	LCDDATA19=pLCD[19];
	
	LCDDATA20=pLCD[20];	
	LCDDATA21=pLCD[21];
	LCDDATA22=pLCD[22];
	LCDDATA23=pLCD[23];
	
	LCDDATA24=pLCD[24];	
	LCDDATA25=pLCD[25];
	LCDDATA26=pLCD[26];
	LCDDATA27=pLCD[27];	
	
	LCDDATA28=pLCD[28];	
	LCDDATA29=pLCD[29];
	LCDDATA30=pLCD[30];
	LCDDATA31=pLCD[31];		
	//if(LCDCONbits.WERR)LCDCONbits.WERR=0;
	LCDCONbits.WERR=0;
}

void lcd_disp_all(uint16_t x)
{
    uint8_t i;
    for(i=0;i<LCD_PIXEL_REGISTER_SIZE;i++)
    {
        pLCD[i]=x;
    }
	//lcd_disp_refresh();
}

void lcd_config(void)
{
    LCDCONbits.CS=3;
    LCDCONbits.LCDSIDL=0;
    LCDCONbits.SLPEN=0;
    LCDCONbits.WERR=0;
    LCDCONbits.LMUX=7;
    
    LCDREGbits.CPEN=0;
    LCDREGbits.BIAS=7;
    LCDREGbits.CKSEL=0;
    LCDREGbits.MODE13=1;
    
    LCDPSbits.BIASMD=0;
    LCDPSbits.LP=3;
	//LCDPSbits.WFT=1;
    
    LCDREFbits.LCDIRE=1;
    LCDREFbits.LCDCST=5;
    LCDREFbits.VLCD1PE=0;
    LCDREFbits.VLCD2PE=0;
    LCDREFbits.VLCD3PE=0;
    
    LCDREFbits.LRLAP=3;
    LCDREFbits.LRLBP=1;
    LCDREFbits.LRLAT=7;
    
    

	// TRISDbits.TRISD0=0;//debug
	LCDSE0 = 0b0001111100010000;
	LCDSE1 = 0b0000000000001100;
	LCDSE2 = 0b1100001111001100;
	LCDSE3 = 0b1111110010000110; // Disable Seg30, Seg28 and Seg27
	//LCDSE4 = 0b11111110; // Disable unused segments
	//LCDSE5 = 0b11001111; // Disable unused segments

	//clear all pixel data
    lcd_disp_all(0xffff);
    lcd_disp_refresh();
	//lcd_clear_all();
	//config reference voltage

	//lcd_on();
}


void lcd_init(void)
{
	lcd_config();
	//lcd_bl_init();
	lcd_on();
    kz_vadd_on();
    //back_night_on();
    asm("nop");
    asm("nop");

}
//file end
