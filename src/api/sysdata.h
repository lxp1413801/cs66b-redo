//file name :sys_data.h
#ifndef __sys_data_h__
#define __sys_data_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#define get_offset_addr_of_str(TYPE, MEMBER) ((uint32_t) (&((TYPE *)0)->MEMBER))
	#define __STR_OFFSET get_offset_addr_of_str
	
    #define globle_BUFFER_SIZE  256
    //extern uint8_t globleBuffer0[globle_BUFFER_SIZE];
	extern uint8_t globleBuffer[globle_BUFFER_SIZE];
	typedef enum{
		HOTIZONTAL=0,//horizontal,
		VERTICAL,//Vertical,
		
	}em_posture,posture_t;

	typedef enum{
		TEST_MODE=0,
		WORK_MODE,
	}st_deviceOpMode;
	
	extern volatile st_deviceOpMode dwm;
	
	typedef enum{
		HIGHT_HI=0,	//高度报警
		HIGHT_LO,
		PRESSURE_HI,	//压力报警,
		PRESSURE_LO,
	}em_warnType,warnType_t;	
	
	typedef struct{
		uint32_t 	warnValueLo;//报警值
		uint32_t	warnValueHi;//回差
		//bool upLimit;
		em_warnType	type;
		uint8_t reverse[3];
	}st_warnDef,warnDef_t;
	
	//外部差压温度标定点
	typedef struct{
		int32_t	value;
		uint16_t adcValue;
		uint16_t reverse;
	}st_exCalibDef,exClibDef_t,comTwoPointCalib_t;
	
	//差压，压力二次修正
	typedef struct{
		int32_t prOut;
		int32_t prIn;
	}st_2ndCalibDef;
	typedef struct{
		int32_t ilpLow;
		int32_t ilpHi;
	}st_ilpScaleDef;
	//定点数固定放大1000倍
	typedef struct{
		uint32_t 	id;
		em_posture	pos;							//立式或者卧式
		uint8_t		maxValueForlevelBar;			//状态条显示满时对应的高度值,
													//(95%或者100%)
		uint16_t	density;						//密度
		
		int32_t		h;								//高
		uint32_t	d;								//直径
		
		int32_t		V1;								//圆筒部分体积
		int32_t		V2;								//封头椭球体积
		
		int32_t		baseZero;						//基础零位
		//

		st_2ndCalibDef	_2ndPrDiffCalib[2];			//二次修正，差压
		st_2ndCalibDef	_2ndPrCalib[2];				//二次修正，压力
		
		st_warnDef		diffPressureWarnSet[4];		//差压报警设置
		st_warnDef		pressureWarnSet[2];			//压力报警设置

		
		uint16_t		ployCoeffic[4];					//v0'=a0.v0+a1.v1+ ...+an.vn

		comTwoPointCalib_t	TmepCalib[2];				//温度标定，
		
		st_exCalibDef	exPr0Calib[2];				//外部压力传传感器标定
		st_exCalibDef	exPr1Calib[2];
		st_exCalibDef	exTempCalib[2];				//外部温度标定
		
		st_ilpScaleDef	diffPrilpScale0;			//压力4-20毫安范围
		st_ilpScaleDef	PrilpScale0;				//压力4-20毫安范围
		st_ilpScaleDef	exPrIpScaleCh0;
		st_ilpScaleDef	exPrIpScaleCh1;
		//st_ilpScaleDef	
		uint16_t	barScale;
		//
		uint16_t	crc;
	}st_sysDataDef,sysDataDef_t;
	extern const st_sysDataDef defultSystemData;
    #ifndef SYSTEM_DATA_ADDR 

    #define SYSTEM_DATA_ADDR user_FLASH_ADDR_START
#endif

	extern st_sysDataDef stSysData;
	extern uint8_t data_sys_init(void); 
    extern uint8_t data_sys_save(uint16_t offset,uint8_t* mbuf,uint16_t len);
	

#ifdef __cplusplus
	}
#endif

#endif
//file end