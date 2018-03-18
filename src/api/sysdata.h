#ifndef __sysdata_h__
#define __sysdata_h__

#ifdef __cplusplus
extern "C"{
#endif

	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include <stdbool.h>
	
	#define get_offset_addr_of_str(TYPE, MEMBER) ((uint32_t) (&((TYPE *)0)->MEMBER))
	#define __STR_OFFSET get_offset_addr_of_str
	
    #define globle_BUFFER_SIZE  256
    //extern uint8_t globleBuffer0[globle_BUFFER_SIZE];
	extern uint8_t globleBuffer[globle_BUFFER_SIZE];
	/*
	typedef enum{
		NO_ERROR=0,
		
		DPR_EEPROM_ERROR,
        PR_EEPROM_ERROR, 
        EX_PR0_EEPROM_ERROR,        
        EX_PR1_EEPROM_ERROR, 
                
		DPR_SENSOR_ERROR,
		PR_SENSOR_ERROR,
		EX_PR0_SENSOR_ERROR,
		EX_PR1_SENSOR_ERROR,
			
		
		EX_TEMP0_SENSOR_ERROR,
		EX_TEMP1_SENSOR_ERROR,
		
		IN_TEMP1_SENSOR_ERROR,
		
		ADC_CHIP0_ERROR,
		ADC_CHIP1_ERROR,
	}emErrCode_t;
	extern emErrCode_t errCode;
	*/
	typedef union{
		uint32_t t32;
		struct{
			uint32_t bAdcChip0:1;
			
			uint32_t bDprEeprom:1;
			uint32_t bDprSensor:1;
			
			uint32_t bprEeprom:1;
			uint32_t bPrSensor:1;
			
			
			uint32_t bInTempSensor:1;
			
			uint32_t bAdcChip1:1;
			
			uint32_t bEx0PrEeprom:1;
			uint32_t bEx1PrEeprom:1;
			uint32_t bEx0PrSensor:1;
			uint32_t bEx1PrSensor:1;
			
			uint32_t bEx0TempSensor:1;
			uint32_t bEx1TempSensor:1;	

			uint32_t bBjBoard:1;	
			uint32_t bILoopBoard:1;	
			uint32_t bModbusBoard:1;
			uint32_t bNbiotBoard:1;
			uint32_t bNGpsBoard:1;
			
			uint32_t bSolorBoard:1;
			uint32_t bACPwrBoard:1;
			
			uint32_t bBatBorad:1;
			uint32_t bBatChargeBorad:1;
		}bits;
	}hardStatus_t;
	extern hardStatus_t hardStatus;
	
	typedef enum{
		HOTIZONTAL=0,				//horizontal,
		VERTICAL,					//Vertical,
	}em_posture,posture_t;

	typedef enum{
		TEST_MODE=0,
		WORK_MODE,
	}st_deviceOpMode;
	
	extern volatile st_deviceOpMode dwm;
	
	typedef enum{
		HIGHT_HI=0,					//高度报警
		HIGHT_LO,
		PRESSURE_HI,				//压力报警,
		PRESSURE_LO,
	}em_warnType,warnType_t;	
	
	typedef struct{
		int32_t 	warnValue;		//报警�?
		int32_t	warnValueOop;		//回差
		//bool upLimit;
		em_warnType	type;
		uint8_t reverse[3];
	}st_warnDef,warnDef_t;
	
	typedef struct{
		uint16_t t16;
		union{
			uint16_t :10;
            uint16_t powerStatus:2;
            uint16_t warnBit3:1;
            uint16_t warnBit2:1;
            uint16_t warnBit1:1;
            uint16_t warnBit0:1;
		}bits;
	}st_deviceEventDef,deviceEventDef_t;
	extern deviceEventDef_t deviceEvent;
	//外部差压温度标定�?
	typedef struct{
		int32_t	value;
		int16_t	sigAdcValue;
		int16_t tAdcValue;		
	}__xDataStruct_t;
	
	typedef struct{
		int16_t	value;
		uint16_t adcValue;
	}exClibDef_t;
	
	//差压，压力二次修�?
	typedef struct{
		int32_t oringinValue;
		int32_t realValue;
	}st_2ndCalibDef,__2ndCalibDef_t;
	
	typedef struct{
		int32_t ilpLow;
		int32_t ilpHi;
	}st_ilpScaleDef;
    
    typedef struct{
        int16_t valueLo;
        int16_t valueHi;
    }st_ilpAdjustValue,ilpAdjustValue_t;
    
    typedef struct{
		int32_t resValue;
        int32_t adcValue;
    }st_tmpCalib,tmpCalib_t;
    
	//定点数固定放�?000�?
	typedef struct{
		uint8_t name[6];
		uint16_t density;
		
	}matterDsc_t;
	
	typedef enum{
		LCD_BL_ON_10s=10,
		LCD_BL_ON_30s=30,
		LCD_BL_ON_60s=60
	}em_lcdBlOnTime;
	//add at 2018.03.05
	typedef struct{
		int32_t ex0PrWarnHight;
		int32_t ex0PrWarnLow;
		int32_t ex1PrWarnHight;
		int32_t ex1PrWarnLow;
		int32_t ex0TempWarnHight;
		int32_t ex0TempWarnLow;
		int32_t ex1TempWarnHight;
		int32_t ex1TempWarnLow;		
	}exWarnValue_t;
	
	typedef struct{
		uint32_t 		id;
		em_posture		pos;							//立式或者卧�?
		uint8_t			pdcEnterTm;						//maxValueForlevelBar;			//状态条显示满时对应的高度�?
														//(95%或�?00%)
		uint16_t		matterIndex;					//密度
		matterDsc_t 	matterTab[6];
		int32_t			h;								//�?
		uint32_t		d;								//直径
		
		int32_t			V1;								//圆筒部分体积
		int32_t			V2;								//封头椭球体积
		
		int32_t			baseZero;						//基础零位
		//

		st_2ndCalibDef	_2ndPrDiffCalib[2];			//二次修正，差�?
		st_2ndCalibDef	_2ndPrCalib[2];				//二次修正，压�?
		st_2ndCalibDef	_2ndPrEx0[2];
		st_2ndCalibDef	_2ndPrEx1[2];
		
		st_warnDef		dprWarnSet[4];		//差压报警设置
		//st_warnDef		pressureWarnSet[2];			//压力报警设置

		
		uint16_t		ployCoeffic[4];					//v0'=a0.v0+a1.v1+ ...+an.vn

		exClibDef_t		TmepCalib[2];				//温度标定�?
		
		exClibDef_t		exPr0Calib[2];				//外部压力传传感器标定
		exClibDef_t		exPr1Calib[2];
        
		//exClibDef_t	exTempCalib[2];			//外部温度标定
		tmpCalib_t		tempCalibEx0[2];
        tmpCalib_t		tempCalibEx1[2];
        
		//st_ilpScaleDef	diffPrilpScale0;			//压力4-20毫安范围
		//st_ilpScaleDef	PrilpScale0;				//压力4-20毫安范围
		st_ilpScaleDef	IpScaleCh0;
		st_ilpScaleDef	IpScaleCh1;
        
        ilpAdjustValue_t   ilpAdjustCh0;
        ilpAdjustValue_t   ilpAdjustCh1;
		//st_ilpScaleDef
        

		uint16_t		barScale;
		uint8_t			exPrTempShowEn;
		uint8_t			blOnTm;	
		uint16_t		sleepPeriod;				//休眠周期s
		uint16_t		rfSendPeriod;				//无线发送周期
		uint8_t			bpMenu;
		uint8_t			bpSubMenu;
		//add by 2018.02.08
		uint8_t			lcdOnTime;					//LCD点亮时间
		uint8_t			ModbusId;//					
		//add by 2018.03.15
		uint16_t		producteDate;//production date
		uint16_t		producteCode;
		//外部报警
		exWarnValue_t	exWarnValue;
		uint16_t		pdcWassword;
		
		uint16_t		crc;
	}sysDataDef_t;
	
	extern const sysDataDef_t defultSystemData;
	#define SYSTEM_DATA_ADDR	user_FLASH_ADDR_START
	extern sysDataDef_t stSysData;
	extern uint8_t data_sys_init(void); 
    extern uint8_t data_sys_save(uint16_t offset,uint8_t* mbuf,uint16_t len);
	
	//定义修正表格�?
	//这段算法好像很恶�?
	#define CALIB_P_POINT_NUM 3
	#define CALIB_ROW_NUM	6
	typedef struct{
		int32_t	value;
		int16_t	sigAdcValue;
		int16_t tAdcValue;		
	}xCalibPoint_t;

	typedef struct{
		uint8_t pCount;	//有效点个�?
		uint8_t reverse[3];
		xCalibPoint_t calibPoint[CALIB_P_POINT_NUM];
	}xCalibRow_t;
	
	typedef struct{
		int32_t pr;
		int32_t	diffPrZero;
	}staticPreErr_t;
	
	typedef struct{
		uint8_t rowCount;	//有效的行�?组数,
		uint8_t status;
        uint8_t reverse[2];
		xCalibRow_t calibRow[CALIB_ROW_NUM];
		staticPreErr_t staticPreAdj0;
		staticPreErr_t staticPreAdj1;
		uint16_t crc;		
	}xCalibTab_t;	
	
	//
	extern xCalibTab_t calibTab0;
	extern xCalibTab_t calibTab1;
	extern xCalibTab_t calibTab2;
	extern xCalibTab_t calibTab3;
	//extern xCalibTab_t ;
	//
    #include "../driver/drivers.h"
	typedef struct{
		xCalibTab_t* calibTab;
		iicDeviceObj_t* eep24c02;
	}calibDataObj_t;
	
	extern calibDataObj_t		diffPrCalibDataObj;
	extern calibDataObj_t		prPrCalibDataObj;
	extern calibDataObj_t		ex0PrCalibDataObj;
	extern calibDataObj_t		ex1PrCalibDataObj;	
	
	extern volatile int32_t		rtTemperatureInBuf[4];
    extern volatile int32_t    rtDiffPrBuf[4];
	extern volatile int16_t 	adc_inPt100;
	
	extern volatile int16_t		adc_pressure;
	extern volatile int16_t		adc_exPt100;

	extern volatile int16_t		adc_iPrEx0;
	extern volatile int16_t		adc_iPrEx1;

	extern volatile int16_t		adc_ibat;
	extern volatile int16_t		adc_iRef;

	//extern __xDataStruct_t	x_prDiffData;
	extern volatile int16_t		adc_diffPr;
	extern volatile int16_t		adc_bridgeTemp;	
    extern volatile int32_t		rtDiffPressure;
    extern volatile int32_t     rtDiffPrOriginal;
	extern volatile int32_t		rtVolume;
    extern volatile int32_t		rtHight;
	extern volatile int32_t		rtWeight;
	extern volatile uint8_t		rtLevel;
	extern volatile int32_t		rtPressure;
	extern volatile int32_t		rtPrOriginal;
    //extern volatile int32_t    rtTemperatureEx;
	extern volatile int32_t		rtTemperatureIn;
    
    extern volatile int32_t		rtTemperatureEx0;
    extern volatile int32_t		rtTemperatureEx1;	

	extern volatile int32_t		rtEx0Pressure;
	extern volatile int32_t		rtEx1Pressure;	
	extern volatile int32_t		rtEx0PrOriginal;
	extern volatile int32_t		rtEx1PrOriginal;		
	//
	extern __xDataStruct_t		x_prDiffData;
	extern __xDataStruct_t		x_prData;
	extern __xDataStruct_t		x_ex0prData;
	extern __xDataStruct_t		x_ex1prData;	
	//fk 
    extern uint32_t data_sys_cal_v1(sysDataDef_t* stp);
    extern uint32_t data_sys_cal_v2(sysDataDef_t* stp);
    

    
	extern void calib_data_put_piont_tab(xCalibTab_t* ptab,xCalibPoint_t* pp,uint8_t row,uint8_t col);
    //apl
	extern int32_t calculate_and_compensate(xCalibTab_t* cTab,__xDataStruct_t* xin);
    
	extern uint8_t cal_diff_press(void);
    extern int32_t cal_diff_p_to_h(int32_t p);
	
    extern int32_t cal_diff_vol_to_t(int32_t v);
    
    extern int32_t cal_diff_hight_to_vol_h(int32_t h);
    extern int32_t cal_diff_hight_to_vol_v(int32_t h);    
    
    extern uint8_t cal_diff_hight_level(void);
	extern  void cal_pt100_temperature_in(void);

	extern uint8_t cal_press(void);
	extern  void cal_pt100_temperature_ex(void);
	
	extern void cal_additional_pressute(uint8_t index);

	extern void data_init_all(void);
	
	extern float calc_res_2_temp(float rr);
	
	extern  int32_t  cal_smoothing_filter(int32_t* buf,int32_t in,uint8_t len);
	//add 
	extern uint8_t calc_warning_pr_dpr(void);
	extern uint16_t calc_dpr_iloop_out_put(void);
	extern uint16_t calc_pr_iloop_out_put(void);
	extern int32_t calc_dpr_iloop_out_put_ex(void);
	extern int32_t calc_pr_iloop_out_put_ex(void);
#ifdef __cplusplus
}
#endif

#endif
//file end
