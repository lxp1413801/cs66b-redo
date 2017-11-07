//file name :ads1148.h
#ifndef __ads1148_h__
#define __ads1148_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include "gpio_config.h"
	#include "gpio.h"
	//see datasheet page 37
	//WAKEUP Exit power down mode 0000 000x (00h, 01h)
	//SLEEP Enter power down mode 0000 001x (02h, 03h)
	//SYNC Synchronize ADC conversions 0000 010x (04h, 05h) 0000 010x (04,05h)
	//RESET Reset to default values 0000 011x (06h, 07h)
	//NOP No operation 1111 1111 (FFh)
	//RDATA Read data once 0001 001x (12h, 13h)
	//RDATAC Read data continuous mode 0001 010x (14h, 15h)
	//SDATAC Stop read data continuous mode 0001 011x (16h, 17h)
	//RREG Read from register rrrr  0010 rrrr (2xh) 0000 nnnn
	//WREG Write to register rrrr 0100 rrrr (4xh) 0000 nnnn
	//SYSOCAL System offset calibration 0110 0000 (60h)
	//SYSGCAL System gain calibration 0110 0001 (61h)
	//SELFOCAL Self offset calibration 0110 0010 (62h)
	//Restricted Restricted command. Never send to the device. 1111 0001 (F1h)
	
	#define ADS1148_CMD_WAKEUP 		0x00
	#define ADS1148_CMD_SLEEP		0x03
	#define ADS1148_CMD_SYNC		0x05
	#define ADS1148_CMD_RESET		0x07
	#define ADS1148_CMD_NOP			0xff
	#define ADS1148_CMD_RDATA		0x13
	#define ADS1148_CMD_RDATAC		0x15
	#define ADS1148_CMD_SDATAC		0x17
	#define ADS1148_CMD_RREG		0x20
	#define ADS1148_CMD_WREG		0x40
	#define ADS1148_CMD_SYSOCAL		0x60
	#define ADS1148_CMD_SYSGCAL		0x61
	#define ADS1148_CMD_SELFOCAL	0x62

	
	#define CHIP_ADS1146 1146
	#define CHIP_ADS1147 1147
	#define CHIP_ADS1148 1148
	
	#define CHIP_TYPE CHIP_ADS1148
	
	#if CHIP_TYPE==CHIP_ADS1146
	
	//define register
	#define ADS1146_REG_ADDR_BCS 		0x00
	#define ADS1146_REG_ADDR_VBIAS 		0x01
	#define ADS1146_REG_ADDR_MUX1 		0x02
	#define ADS1146_REG_ADDR_SYS0 		0x03
	#define ADS1146_REG_ADDR_OFC0		0x04
	#define ADS1146_REG_ADDR_OFC1		0x05
	#define ADS1146_REG_ADDR_OFC2		0x06
	#define ADS1146_REG_ADDR_FSC0		0x07
	#define ADS1146_REG_ADDR_FSC1		0x08
	#define ADS1146_REG_ADDR_FSC2		0x09
	#define ADS1146_REG_ADDR_ID			0x0a
	
	//define register format
	//BCS:BCS—Burn-out Current Source Register (offset = 00h) [reset = 01h]
	#define ADS1146_BCS_OFF 	0x00
	#define ADS1146_BCS_0uA5 	0x01
	#define ADS1146_BCS_2uA0 	0x02
	#define ADS1146_BCS_10uA0 	0x03
	typedef union{
		uint8_t bcs;
		struct{
			uint8_t:6;
			uint8_t:bcs;
		}bits;
	}st_ads1146RegBCS,ads1146RegBCS_t;
	//VBIAS—Bias Voltage Register (offset = 01h) [reset = 00h]
	#define ADS1146_VBIAS_ENABLE 	1
	#define ADS1146_VBIAS_DISABLE	0
	typedef union{
		uint8_t vbias;
		struct{
			uint8_t vbias_ainP:1;
			uint8_t vbias_ainN:1;
			uint8_t:6;
		}bits;
	}st_ads1146RegVBIAS,ads1146RegVBIAS_t;
	//MUX—Multiplexer Control Register (offset = 02h) [reset = x0h]
	#define ADS1146_MUX_CLKSTAT_INTERNAL 0
	#define ADS1146_MUX_CLKSTAT_EXTERNAL 1
	#define ADS1146_MUX_MUXCA_NORMAL 		0x00
	#define ADS1146_MUX_MUXCA_MID_AVDD 		0x01
	#define ADS1146_MUX_MUXCA_REF	 		0x02
	#define ADS1146_MUX_MUXCA_TEMP	 		0x03
	typedef union{
		uint8_t mux;
		struct{
			uint8_t muxca:3;
			uint8_t:4;
			uint8_t clkstat:1
		}bits;
	}st_ads1146RegMUX,ads1146RegMUX_t;
	//SYS0—System Control Register 0 (offset = 03h) [reset = 00h]
	#define ADS1146_SYS0_DR_5SPS	0x00
	#define ADS1146_SYS0_DR_10SPS	0x01
	#define ADS1146_SYS0_DR_20SPS	0x02
	#define ADS1146_SYS0_DR_40SPS	0x03
	#define ADS1146_SYS0_DR_80SPS	0x04
	#define ADS1146_SYS0_DR_160SPS	0x05
	#define ADS1146_SYS0_DR_320SPS	0x06
	#define ADS1146_SYS0_DR_640SPS	0x07
	#define ADS1146_SYS0_DR_1000SPS	0x08
	#define ADS1146_SYS0_DR_2000SPS	0x09
	
	#define ADS1146_PGA_1			0x00
	#define ADS1146_PGA_2			0x01
	#define ADS1146_PGA_4			0x02
	#define ADS1146_PGA_8			0x03
	#define ADS1146_PGA_16			0x04
	#define ADS1146_PGA_32			0x05
	#define ADS1146_PGA_64			0x06
	#define ADS1146_PGA_128			0x07
	typedef union{
		uint8_t sys0;
		struct{
			uint8_t dr:4;
			uint8_t pga:3;
			uint8_t:1;
		}bits;
	}st_ads1146RegSYS0,ads1146RegSYS0_t;
	// ID—ID Register (offset = 0Ah) [reset = x0h]
	#define ADS1146_DRDY_VIA_DRDY	0
	#define ADS1146_DRDY_VIA_DOUT	1
	typedef union{
		uint8_t id;
		struct{
			uint8_t:3;
			uint8_t drdyMode:1;
			uint8_t idBits:4;
		}bits;
	}st_ads1146RegID,ads1146RegID_t;
	#else
	
	#define ADS1148_REG_ADDR_MUX0 		0x00
	#define ADS1148_REG_ADDR_VBIAS 		0x01
	#define ADS1148_REG_ADDR_MUX1 		0x02
	#define ADS1148_REG_ADDR_SYS0 		0x03
	#define ADS1148_REG_ADDR_OFC0		0x04
	#define ADS1148_REG_ADDR_OFC1		0x05
	#define ADS1148_REG_ADDR_OFC2		0x06
	#define ADS1148_REG_ADDR_FSC0		0x07
	#define ADS1148_REG_ADDR_FSC1		0x08
	#define ADS1148_REG_ADDR_FSC2		0x09
	#define ADS1148_REG_ADDR_IDAC0		0x0a
	#define ADS1148_REG_ADDR_IDAC1		0x0b
	#define ADS1148_REG_ADDR_GPIOCFG	0x0c
	#define ADS1148_REG_ADDR_GPIODIR	0x0d
	#define ADS1148_REG_ADDR_GPIODAT	0x0e
	
	//MUX0—Multiplexer Control Register 0 (offset = 00h) [reset = 01h]
	#define ADS1148_BCS_OFF 	0x00
	#define ADS1148_BCS_0uA5 	0x01
	#define ADS1148_BCS_2uA0 	0x02
	#define ADS1148_BCS_10uA0 	0x03	
	
	#define ADS1148_MUX_SP_AIN0	0x00
	#define ADS1148_MUX_SP_AIN1	0x01
	#define ADS1148_MUX_SP_AIN2	0x02
	#define ADS1148_MUX_SP_AIN3	0x03
	#define ADS1148_MUX_SP_AIN4	0x04
	#define ADS1148_MUX_SP_AIN5	0x05
	#define ADS1148_MUX_SP_AIN6	0x06
	#define ADS1148_MUX_SP_AIN7	0x07

	#define ADS1148_MUX_SN_AIN0	0x00
	#define ADS1148_MUX_SN_AIN1	0x01
	#define ADS1148_MUX_SN_AIN2	0x02
	#define ADS1148_MUX_SN_AIN3	0x03
	#define ADS1148_MUX_SN_AIN4	0x04
	#define ADS1148_MUX_SN_AIN5	0x05
	#define ADS1148_MUX_SN_AIN6	0x06
	#define ADS1148_MUX_SN_AIN7	0x07
	
	typedef union{
		uint8_t mux0;
		struct{
			uint8_t mux_sn:3;
			uint8_t mux_sp:3;
			uint8_t bcs:2;
		}bits;
	}st_ads1148RegMUX0,ads1148RegMUX0_t;
	//VBIAS—Bias Voltage Register (offset = 01h) [reset = 00h]
	#define ADS1148_VBIAS_ENABLE 	1
	#define ADS1148_VBIAS_DISABLE	0
	typedef union{
		uint8_t vbias;
		struct{
			uint8_t vbias0:1;
			uint8_t vbias1:1;
			uint8_t vbias2:1;
			uint8_t vbias3:1;
			uint8_t vbias4:1;
			uint8_t vbias5:1;
			uint8_t vbias6:1;
			uint8_t vbias7:1;
		}bits;
	}st_ads1148RegVBIAS,ads1148RegVBIAS_t;	
	
	//MUX1—Multiplexer Control Register 1 (offset = 02h) [reset = x0h]
	#define ADS1148_MUX_CLKSTAT_INTERNAL 			0
	#define ADS1148_MUX_CLKSTAT_EXTERNAL 			1
	
	#define ADS1148_VREFCON_INREF_OFF				0
	#define ADS1148_VREFCON_INREF_ON				1
	#define ADS1148_VREFCON_INREF_ON_WHEN_START		2
	
	#define ADS1148_REFSELT_REF0					0
	#define ADS1148_REFSELT_REF1					1
	#define ADS1148_REFSELT_INREF					2
	#define ADS1148_REFSELT_INREF_CON_REF0			3
	
	#define ADS1148_MUXCAL_NORMAL 				0x00
	#define ADS1148_MUXCAL_OFFSET_CALIB 		0x01
	#define ADS1148_MUXCAL_GAIN_CALIB	 		0x02
	#define ADS1148_MUXCAL_TEMP	 				0x03
	#define ADS1148_MUXCAL_REF1_MONITOR			0x04
	#define ADS1148_MUXCAL_REF0_MONITOR			0x05
	#define ADS1148_MUXCAL_AVDD_AVSS_DIV_4		0x06
	#define ADS1148_MUXCAL_DVDD_DVSS_DIV_4		0x07
	typedef union{
		uint8_t mux1;
		struct{
			uint8_t muxcal:3;
			uint8_t refselt:2;
			uint8_t	vrefcon:2;
			uint8_t clkstat:1;
		}bits;
	}st_ads1148RegMUX1,ads1146RegMUX8_t;
	
	//SYS0—System Control Register 0 (offset = 03h) [reset = 00h]
	#define ADS1148_SYS0_DR_5SPS	0x00
	#define ADS1148_SYS0_DR_10SPS	0x01
	#define ADS1148_SYS0_DR_20SPS	0x02
	#define ADS1148_SYS0_DR_40SPS	0x03
	#define ADS1148_SYS0_DR_80SPS	0x04
	#define ADS1148_SYS0_DR_160SPS	0x05
	#define ADS1148_SYS0_DR_320SPS	0x06
	#define ADS1148_SYS0_DR_640SPS	0x07
	#define ADS1148_SYS0_DR_1000SPS	0x08
	#define ADS1148_SYS0_DR_2000SPS	0x09
	
	#define ADS1148_PGA_1			0x00
	#define ADS1148_PGA_2			0x01
	#define ADS1148_PGA_4			0x02
	#define ADS1148_PGA_8			0x03
	#define ADS1148_PGA_16			0x04
	#define ADS1148_PGA_32			0x05
	#define ADS1148_PGA_64			0x06
	#define ADS1148_PGA_128			0x07
	typedef union{
		uint8_t sys0;
		struct{
			uint8_t dr:4;
			uint8_t pga:3;
			uint8_t:1;
		}bits;
	}st_ads1148RegSYS0,ads1148RegSYS0_t;	
	//IDAC0—IDAC Control Register 0 (offset = 0Ah) [reset = x0h]
	#define ADS1148_DRDY_VIA_DRDY	0
	#define ADS1148_DRDY_VIA_DOUT	1
	
	#define ADS1148_IMAG_OFF		0
	#define ADS1148_IMAG_0uA		0
	#define ADS1148_IMAG_50uA		1
	#define ADS1148_IMAG_100uA		2
	#define ADS1148_IMAG_250uA		3
	#define ADS1148_IMAG_500uA		4
	#define ADS1148_IMAG_750uA		5
	#define ADS1148_IMAG_1000uA		6
	#define ADS1148_IMAG_1500uA		7
	typedef union{
		uint8_t idac0;
		struct{
			uint8_t	imag:3;
			uint8_t drdyMode:1;
			uint8_t id:4;
		}bits;
	}st_ads1148RegIDAC0,ads1148RegIDAC0_t;
	
	//IDAC1—IDAC Control Register 1 (offset = 0Bh) [reset = FFh]
	#define ADS1148_IDAC_OUT_PINS_AIN0	0
	#define ADS1148_IDAC_OUT_PINS_AIN1	1	
	#define ADS1148_IDAC_OUT_PINS_AIN2	2	
	#define ADS1148_IDAC_OUT_PINS_AIN3	3	
	#define ADS1148_IDAC_OUT_PINS_AIN4	4	
	#define ADS1148_IDAC_OUT_PINS_AIN5	5	
	#define ADS1148_IDAC_OUT_PINS_AIN6	6	
	#define ADS1148_IDAC_OUT_PINS_AIN7	7		
	#define ADS1148_IDAC_OUT_PINS_IEXC1	8
	#define ADS1148_IDAC_OUT_PINS_IEXC2	9
	#define ADS1148_IDAC_OUT_PINS_NC	0x0f
	typedef union{
		uint8_t idac1;
		struct{
			uint8_t i2dir:4;
			uint8_t i1dir:4;
		}bits;
	}st_ads1148RegIDAC1,ads1148RegIDAC1_t;
	#endif
	
	typedef struct{
		void (*pins_init)(void);
		void (*pins_deinit)(void);
		
		void (*pins_cs_set_low)(void);
		void (*pins_cs_set_hight)(void);
		
		//void (*pins_reset_set_hight)(void);
		//void (*pins_reset_set_low)(void);
		
		void (*pins_start_set_hight)(void);
		void (*pins_start_set_low)(void);
		
		void (*pins_drdy_mode_in)(void);
		uint16_t (*pins_drdy_get)(void);
		
		void (*pins_drdy_mode_out)(void);
		void (*pins_drdy_set_hight)(void);
		void (*pins_drdy_set_low)(void);
		
		uint8_t (*ads1148_write_read_via_spi)(uint8_t);	
        uint8_t chipNm;
	}st_ads1148Obj,ads1148Obj_t;
	
	extern ads1148Obj_t adsii48Chip0,adsii48Chip1;
	
#ifdef __cplusplus
	}
#endif

#endif
//file end
