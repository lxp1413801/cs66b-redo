#ifndef __lcd_code_table_ex_h__
#define __lcd_code_table_ex_h__

#ifdef __cplusplus
extern "C"{
#endif
	#define LCD_DSEG_A_EX 	(0x01ul<<0)
	#define LCD_DSEG_B_EX 	(0x01ul<<1)
	#define LCD_DSEG_C_EX 	(0x01ul<<2)
	#define LCD_DSEG_D_EX 	(0x01ul<<3)	
	//
	#define LCD_DSEG_E_EX 	(0x01ul<<4)
	#define LCD_DSEG_F_EX 	(0x01ul<<5)
	#define LCD_DSEG_G_EX 	(0x01ul<<6)
	#define LCD_DSEG_H_EX 	(0x01ul<<7)
	
	#define LCD_DSEG_I_EX 	(0x01ul<<8)
	#define LCD_DSEG_J_EX 	(0x01ul<<9)
	#define LCD_DSEG_K_EX 	(0x01ul<<10)
	#define LCD_DSEG_L_EX 	(0x01ul<<11)	
	#define LCD_DSEG_DP_EX 	(0x01ul<<12)
	//#define LCD_DSEG_DP 0x80
	//
	#define SEG_A_EX	LCD_DSEG_A_EX
	#define SEG_B_EX	LCD_DSEG_B_EX
	#define SEG_C_EX	LCD_DSEG_C_EX
	#define SEG_D_EX	LCD_DSEG_D_EX	
	#define SEG_E_EX	LCD_DSEG_E_EX
	#define SEG_F_EX	LCD_DSEG_F_EX
	#define SEG_G_EX	LCD_DSEG_G_EX
	#define SEG_H_EX	LCD_DSEG_H_EX	
	#define SEG_I_EX	LCD_DSEG_I_EX
	#define SEG_J_EX	LCD_DSEG_J_EX
	#define SEG_K_EX	LCD_DSEG_K_EX
	#define SEG_L_EX	LCD_DSEG_L_EX	
	
	#define LCD_CODE_0_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX + SEG_F_EX)
	#define LCD_CODE_1_EX (SEG_B_EX + SEG_C_EX)
	#define LCD_CODE_2_EX (SEG_A_EX + SEG_B_EX + SEG_G_EX + SEG_H_EX + SEG_E_EX + SEG_D_EX)      
	#define LCD_CODE_3_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_G_EX + SEG_H_EX  )  
	#define LCD_CODE_4_EX (SEG_B_EX + SEG_C_EX + SEG_F_EX + SEG_G_EX + SEG_H_EX )
	#define LCD_CODE_5_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_H_EX + SEG_C_EX + SEG_D_EX )
	#define LCD_CODE_6_EX (SEG_A_EX + SEG_F_EX + SEG_E_EX + SEG_D_EX + SEG_C_EX + SEG_H_EX + SEG_G_EX )
	#define LCD_CODE_7_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX )  
	#define LCD_CODE_8_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX + SEG_F_EX + SEG_G_EX + SEG_H_EX)
	#define LCD_CODE_9_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_F_EX + SEG_G_EX + SEG_H_EX)

	#define LCD_CODE_A_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_E_EX + SEG_F_EX + SEG_G_EX + SEG_H_EX)
	#define LCD_CODE_B_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_J_EX + SEG_H_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX)
	#define LCD_CODE_C_EX (SEG_A_EX + SEG_F_EX + SEG_E_EX + SEG_D_EX )
	#define LCD_CODE_D_EX (0)
	#define LCD_CODE_E_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_E_EX + SEG_D_EX )
	#define LCD_CODE_F_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_E_EX )
	#define LCD_CODE_G_EX (SEG_A_EX + SEG_F_EX + SEG_E_EX + SEG_D_EX + SEG_C_EX + SEG_H_EX)
	#define LCD_CODE_H_EX (SEG_F_EX + SEG_E_EX + SEG_C_EX + SEG_B_EX + SEG_G_EX + SEG_H_EX )
	#define LCD_CODE_I_EX LCD_CODE_1
	#define LCD_CODE_J_EX (SEG_B_EX + SEG_C_EX + SEG_D_EX)
	#define LCD_CODE_K_EX (SEG_F_EX + SEG_E_EX + SEG_G_EX + SEG_J_EX + SEG_K_EX)
	#define LCD_CODE_L_EX (SEG_F_EX + SEG_E_EX + SEG_D_EX)
	#define LCD_CODE_M_EX (SEG_F_EX + SEG_E_EX + SEG_C_EX + SEG_B_EX + SEG_I_EX +  SEG_J_EX)
	#define LCD_CODE_N_EX (SEG_E_EX + SEG_F_EX + SEG_I_EX + SEG_K_EX + SEG_C_EX +  SEG_B_EX )
	
	//#define LCD_CODE_O LCD_CODE_0
    #define LCD_CODE_O_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX +  SEG_F_EX )
	#define LCD_CODE_P_EX (SEG_A_EX + SEG_B_EX + SEG_E_EX +  SEG_F_EX+ SEG_G_EX +  SEG_H_EX)
	#define LCD_CODE_Q_EX (SEG_A_EX + SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX + SEG_F_EX + SEG_K_EX)

	//#define LCD_CODE_R (LCD_DSEG_A +LCD_DSEG_F +LCD_DSEG_E)
    #define LCD_CODE_R_EX (SEG_A_EX + SEG_F_EX + SEG_E_EX + SEG_G_EX + SEG_J_EX + SEG_K_EX)
	#define LCD_CODE_S_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_K_EX + SEG_D_EX )
	#define LCD_CODE_T_EX (0)
	
	#define LCD_CODE_U_EX (SEG_F_EX + SEG_E_EX + SEG_D_EX + SEG_C_EX + SEG_B_EX)
	#define LCD_CODE_V_EX (SEG_F_EX + SEG_E_EX + SEG_L_EX + SEG_J_EX)
	#define LCD_CODE_W_EX (SEG_F_EX + SEG_E_EX + SEG_L_EX + SEG_K_EX + SEG_C_EX + SEG_B_EX)

	#define LCD_CODE_X_EX (SEG_I_EX + SEG_J_EX + SEG_L_EX + SEG_K_EX)
	#define LCD_CODE_Y_EX (SEG_I_EX + SEG_H_EX + SEG_B_EX+ SEG_C_EX + SEG_D_EX)
	#define LCD_CODE_Z_EX (SEG_A_EX + SEG_J_EX + SEG_L_EX + SEG_D_EX)
	
	#define LCD_CODE_a_EX (SEG_G_EX + SEG_E_EX + SEG_D_EX + SEG_K_EX)
	#define LCD_CODE_b_EX (SEG_F_EX + SEG_E_EX + SEG_G_EX + SEG_K_EX + SEG_D_EX)
	#define LCD_CODE_c_EX (SEG_G_EX + SEG_H_EX + SEG_E_EX + SEG_D_EX )
	#define LCD_CODE_d_EX (SEG_B_EX + SEG_C_EX + SEG_D_EX + SEG_L_EX + SEG_H_EX)
	#define LCD_CODE_e_EX (SEG_G_EX + SEG_H_EX + SEG_B_EX + SEG_A_EX + SEG_F_EX + SEG_E_EX + SEG_D_EX)
	#define LCD_CODE_f_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX + SEG_E_EX )
	#define LCD_CODE_g_EX (SEG_A_EX + SEG_B_EX + SEG_I_EX + SEG_H_EX + SEG_C_EX +  SEG_D_EX)
	#define LCD_CODE_h_EX (SEG_F_EX + SEG_E_EX + SEG_G_EX + SEG_H_EX + SEG_C_EX )
	#define LCD_CODE_i_EX LCD_CODE_1
	#define LCD_CODE_j_EX (SEG_B_EX + SEG_C_EX + SEG_D_EX)
	#define LCD_CODE_k_EX (SEG_F_EX + SEG_E_EX + SEG_G_EX + SEG_J_EX + SEG_K_EX)
	#define LCD_CODE_l_EX (SEG_F_EX + SEG_E_EX)
	#define LCD_CODE_m_EX (SEG_F_EX + SEG_E_EX + SEG_C_EX + SEG_B_EX + SEG_I_EX +  SEG_J_EX)
	#define LCD_CODE_n_EX (SEG_E_EX + SEG_F_EX + SEG_A_EX + SEG_B_EX + SEG_C_EX )
	
	//#define LCD_CODE_O LCD_CODE_0
    #define LCD_CODE_o_EX (SEG_G_EX + SEG_H_EX + SEG_C_EX + SEG_D_EX + SEG_E_EX)
	#define LCD_CODE_p_EX (SEG_A_EX + SEG_J_EX + SEG_G_EX + SEG_F_EX + SEG_E_EX )
	#define LCD_CODE_q_EX (SEG_A_EX + SEG_I_EX + SEG_B_EX + SEG_H_EX + SEG_C_EX)

	//#define LCD_CODE_R (LCD_DSEG_A +LCD_DSEG_F +LCD_DSEG_E)
    //#define LCD_CODE_r_EX (SEG_A_EX + SEG_F_EX + SEG_E_EX)
	#define LCD_CODE_r_EX (SEG_G_EX + SEG_L_EX + SEG_H_EX)
	#define LCD_CODE_s_EX (SEG_A_EX + SEG_F_EX + SEG_G_EX+ SEG_K_EX + SEG_D_EX )
	#define LCD_CODE_t_EX (SEG_G_EX + SEG_H_EX + SEG_J_EX + SEG_L_EX + SEG_D_EX)
	
	#define LCD_CODE_u_EX (SEG_F_EX + SEG_E_EX + SEG_D_EX + SEG_C_EX + SEG_B_EX)
	#define LCD_CODE_v_EX (SEG_F_EX + SEG_E_EX + SEG_L_EX + SEG_J_EX)
	#define LCD_CODE_w_EX (SEG_F_EX + SEG_E_EX + SEG_L_EX + SEG_K_EX + SEG_C_EX + SEG_B_EX)

	#define LCD_CODE_x_EX (SEG_I_EX + SEG_K_EX + SEG_J_EX + SEG_L_EX)
	#define LCD_CODE_y_EX (SEG_I_EX + SEG_J_EX + SEG_L_EX)
	#define LCD_CODE_z_EX (SEG_G_EX + SEG_L_EX + SEG_D_EX)	
	
	

	extern const uint16_t LCDDigitalTableEx[];


#ifdef __cplusplus
}
#endif


#endif