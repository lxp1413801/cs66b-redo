#include "../includes/includes.h"

const st_sysDataDef defultSystemData={
	1234,//uint32_t 	id;
	0,//em_posture	pos;							//??????
	95,//uint8_t		maxValueForlevelBar;			//?????????????,
												//(95%??100%)
	1000,//uint16_t	density;						//??
	
	15000,//int32_t		h;								//?
	3000,//uint32_t	d;								//??
	
	0,//int32_t		V1;								//??????
	0,//int32_t		V2;								//??????
	
	-200,//int32_t		baseZero;						//????
	//

	{{0,0},{10000,10000}},//st_2ndCalibDef	_2ndPrDiffCalib[2];			//???????
	{{0,0},{10000,10000}},//st_2ndCalibDef	_2ndPrCalib[2];				//???????
	
	{0},//st_warnDef		diffPressureWarnSet[4];		//??????
	{0},//st_warnDef		pressureWarnSet[2];			//??????

	
	{400,300,200,100},//uint16_t		ployCoeffic[4];					//v0'=a0.v0+a1.v1+ ...+an.vn

	{{0,0},{10000,10000}},//st_exClibDef	TmepCalib[2];				//?????
	
	{{0,0},{10000,10000}},//st_exClibDef	exPr0Calib[2];				//??????????
	{{0,0},{10000,10000}},//st_exClibDef	exPr1Calib[2];
	{{0,0},{10000,10000}},//st_exClibDef	exTempCalib[2];				//??????
	
	{1000,2000},//st_ilpScaleDef	exdiffPrilpScale0;			//????4-20????
	{1000,2000},//st_ilpScaleDef	exPrilpScale0;				//????4-20????
	{1000,2000},//st_ilpScaleDef	exPrIpScale0;
	{1000,2000},//st_ilpScaleDef	exPrIpScale1;		
	//st_ilpScaleDef	
	{950},//uint16_t	barScale;
	//
	0,//uint16_t	crc;
};
