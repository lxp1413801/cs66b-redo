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

uint8_t globleBuffer[globle_BUFFER_SIZE];
st_sysDataDef stSysData={0};

uint32_t data_sys_cal_v1(st_sysDataDef* stp)
{
    float r,h,f;
    r=(float)(stp->d);
    h=(float)(stp->h);
    r=r/1000/2;
    h=h/1000;
    f=h*(r*r)*3.1416f;
    f*=1000;
    return (uint32_t)f;
}

uint32_t data_sys_cal_v2(st_sysDataDef* stp)
{
    float d,f;
    d=(float)(stp->d);
    d=d/1000;
    f=0.2618f*d*d*d;
    f*=1000;
    return (uint32_t)f;
}

uint8_t data_sys_init(void)
{
	uint8_t ret;
    uint16_t t16;
    t16=sizeof(st_sysDataDef);
	uint8_t* buf=(uint8_t*)(&stSysData);
    st_sysDataDef* stp=(st_sysDataDef*)buf; 
	//if(sizeof(globleBuffer1)<t16)return 0;
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
	ret=crc_verify(buf,sizeof(st_sysDataDef));
	if(!ret){
		m_mem_cpy_len(buf,(uint8_t*)(&defultSystemData),sizeof(st_sysDataDef));
        stp->V1=data_sys_cal_v1(stp);
        stp->V2=data_sys_cal_v2(stp);
		crc_append(buf,sizeof(st_sysDataDef)-2);
		m_flash_write(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
		m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
		ret=crc_verify(buf,sizeof(st_sysDataDef));		
	}
	return ret;
}

uint8_t data_sys_save(uint16_t offset,uint8_t* mbuf,uint16_t len)
{
	uint8_t ret;
	uint8_t* buf=(uint8_t*)(&stSysData);
	if(offset+len>sizeof(st_sysDataDef)-2)return 0;
	//if(sizeof(globleBuffer0)<sizeof(st_sysDataDef))return 0;
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
	m_mem_cpy_len(buf+offset,mbuf,len);
	crc_append(buf,sizeof(st_sysDataDef)-2);
	m_flash_write(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(st_sysDataDef));
	ret=crc_verify(buf,sizeof(st_sysDataDef));	
	return ret;
}

