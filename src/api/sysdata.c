#include "../includes/includes.h"
#include "float.h"

sysDataDef_t stSysData;
uint8_t globleBuffer[globle_BUFFER_SIZE]={0};



xCalibTab_t calibTab0={0};
xCalibTab_t calibTab1={0};
xCalibTab_t calibTab2={0};
xCalibTab_t calibTab3={0};

calibDataObj_t diffPrCalibDataObj;
calibDataObj_t prPrCalibDataObj;

__xDataStruct_t	x_prDiffData;
__xDataStruct_t	x_prData;

volatile int16_t	adc_diffPr;
volatile int16_t	adc_bridgeTemp;	
volatile int16_t 	adc_inPt100;
volatile int16_t	adc_pressure;
volatile int16_t	adc_exPt100;
volatile int16_t	adc_iPrEx[2];
volatile int16_t	adc_iPrEx0;
volatile int16_t	adc_iPrEx1;
volatile int16_t	adc_ibat;
volatile int16_t	adc_iRef;

volatile int32_t    rtDiffPrBuf[4];
volatile int32_t	rtDiffPressure;
volatile int32_t	rtHight;
volatile int32_t	rtWeight;
volatile int32_t	rtVolume;

volatile uint8_t    rtLevel;
volatile int32_t    rtTemperatureIn=0;
volatile int32_t    rtPressure=0;
volatile int32_t    rtTemperatureEx=0;

volatile int32_t	rtExPressure[2];
//

volatile st_deviceOpMode dwm=TEST_MODE;

// %水平圆筒的局部容积系数,其中x=H/D
// %Vp=k*Va
// %k= k=(1/pi)*acos(1-2*x)-(1/pi)*(1-2*x)*((1-(1-2*x)^2))^0.5;
// matlab产生系数表代码示例如下：
/*
clear  all
i=0;
for x=0:0.01:1.0;
    k=(1/pi)*acos(1-2*x)-(1/pi)*(1-2*x)*((1-(1-2*x)^2))^0.5;
    fprintf('%1.4f,',k)
    i=i+1;
    if i== 8 
        fprintf('\r\n');
        i=0;
    end
end
*/
const float hKcy[]={
	0.0000,0.0017,0.0048,0.0087,0.0134,0.0187,0.0245,0.0308,0.0375,0.0446,
	0.0520,0.0598,0.0680,0.0764,0.0851,0.0941,0.1033,0.1127,0.1224,0.1323,
	0.1424,0.1527,0.1631,0.1738,0.1845,0.1955,0.2066,0.2178,0.2292,0.2407,
	0.2523,0.2640,0.2759,0.2878,0.2998,0.3119,0.3241,0.3364,0.3487,0.3611,
	0.3735,0.3860,0.3986,0.4112,0.4238,0.4364,0.4491,0.4618,0.4745,0.4873,
	0.5000,0.5127,0.5255,0.5382,0.5509,0.5636,0.5762,0.5888,0.6014,0.6140,
	0.6265,0.6389,0.6513,0.6636,0.6759,0.6881,0.7002,0.7122,0.7241,0.7360,
	0.7477,0.7593,0.7708,0.7822,0.7934,0.8045,0.8155,0.8262,0.8369,0.8473,
	0.8576,0.8677,0.8776,0.8873,0.8967,0.9059,0.9149,0.9236,0.9320,0.9402,
	0.9480,0.9554,0.9625,0.9692,0.9755,0.9813,0.9866,0.9913,0.9952,0.9983,
	1.0000,  
};

// 计算水平圆筒的椭圆封头局部容积,球形容器以及立式圆筒的椭圆封头同样适用本表
// 详见《石油化工设备设计便查手册.pdf》P379
// 当h=D时，最大容积为Vmax=pi/12*D^3=0.2618*D^3;
// 计算系数，输入x=h/D;k=V/Vmax;K=2*x^2*(3/2-x)
// matlab产生系数表代码示例如下：
/*
clear  all
i=0;
for x=0:0.01:1.0;
    k=2*x^2*(3/2-x);
    fprintf('%1.4f,',k)
    i=i+1;
    if i== 10 
        fprintf('\r\n');
        i=0;
    end
end  
*/
const float hKel[]={
	0.0000,0.0003,0.0012,0.0026,0.0047,0.0073,0.0104,0.0140,0.0182,0.0228,
	0.0280,0.0336,0.0397,0.0463,0.0533,0.0607,0.0686,0.0769,0.0855,0.0946,
	0.1040,0.1138,0.1239,0.1344,0.1452,0.1563,0.1676,0.1793,0.1913,0.2035,
	0.2160,0.2287,0.2417,0.2548,0.2682,0.2818,0.2955,0.3094,0.3235,0.3377,
	0.3520,0.3665,0.3810,0.3957,0.4104,0.4253,0.4401,0.4551,0.4700,0.4850,
	0.5000,0.5150,0.5300,0.5449,0.5599,0.5748,0.5896,0.6043,0.6190,0.6335,
	0.6480,0.6623,0.6765,0.6906,0.7045,0.7183,0.7318,0.7452,0.7583,0.7713,
	0.7840,0.7965,0.8087,0.8207,0.8324,0.8438,0.8548,0.8656,0.8761,0.8862,
	0.8960,0.9054,0.9145,0.9231,0.9314,0.9392,0.9467,0.9537,0.9603,0.9664,
	0.9720,0.9772,0.9818,0.9860,0.9896,0.9928,0.9953,0.9974,0.9988,0.9997,
	1.0000,  
};


const sysDataDef_t defultSystemData={

		1234,//uint32_t 	id;
		0,//em_posture	pos;							//立式或者卧式
		95,//uint8_t		maxValueForlevelBar;			//状态条显示满时对应的高度值,
													//(95%或者100%)
		0,//uint16_t	density;						//密度
		{{"LO2",1140},{"LN2",810},{"LAR",1402},{"CO2",1020},{"LNG",460},{"CON",1000}},
		15000,//int32_t		h;								//高
		3000,//uint32_t	d;								//直径
		
		0,//int32_t		V1;								//圆筒部分体积
		0,//int32_t		V2;								//封头椭球体积
		
		-200,//int32_t		baseZero;						//基础零位
		//

		{{0,0},{10000,10000}},//st_2ndCalibDef	_2ndPrDiffCalib[2];			//二次修正，差压
		{{0,0},{10000,10000}},//st_2ndCalibDef	_2ndPrCalib[2];				//二次修正，压力
		
		{{0},{0},{0},{0}},//st_warnDef		diffPressureWarnSet[4];		//差压报警设置
		{{0},{0}},//st_warnDef		pressureWarnSet[2];			//压力报警设置

		
		{400,300,200,100},//uint16_t		ployCoeffic[4];					//v0'=a0.v0+a1.v1+ ...+an.vn

		{{0,0},{10000,10000}},//st_exClibDef	TmepCalib[2];				//温度标定，
		
		{{0,0},{10000,10000}},//st_exClibDef	exPr0Calib[2];				//外部压力传传感器标定
		{{0,0},{10000,10000}},//st_exClibDef	exPr1Calib[2];
		{{0,0},{10000,10000}},//st_exClibDef	exTempCalib[2];				//外部温度标定
		
		{1000,2000},//st_ilpScaleDef	exdiffPrilpScale0;			//外部压力4-20毫安范围
		{1000,2000},//st_ilpScaleDef	exPrilpScale0;				//外部压力4-20毫安范围
		{1000,2000},//st_ilpScaleDef	exPrIpScale0;
		{1000,2000},//st_ilpScaleDef	exPrIpScale1;		
		//st_ilpScaleDef	
		950,//uint16_t	barScale;
		//
		0,//uint16_t	crc;
};
uint16_t data_sys_get_density(void)
{
    uint16_t t16,density;
    t16=stSysData.matterIndex;
    density=stSysData.matterTab[t16].density;
    return density;
}
uint32_t data_sys_cal_v1(sysDataDef_t* stp)
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

uint32_t data_sys_cal_v2(sysDataDef_t* stp)
{
    float r,f;
    //int32_t t32;
    //t32=stp->d;
    r=(float)(stp->d);
    r=r/1000/2;
    f=r*r*r*0.2618;
    f*=1000;
    return (uint32_t)f;
}

uint8_t data_sys_init(void)
{
	uint8_t ret;
    uint16_t t16;
    t16=sizeof(sysDataDef_t);
	uint8_t* buf=(uint8_t*)(&stSysData);
    sysDataDef_t* stp=(sysDataDef_t*)buf; 
	//if(sizeof(globleBuffer1)<t16)return 0;
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
	ret=crc_verify(buf,sizeof(sysDataDef_t));
	if(!ret){
		m_mem_cpy_len(buf,(uint8_t*)(&defultSystemData),sizeof(sysDataDef_t));
        stp->V1=data_sys_cal_v1(stp);
        stp->V2=data_sys_cal_v2(stp);
		crc_append(buf,sizeof(sysDataDef_t)-2);
		m_flash_write(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
		m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
		ret=crc_verify(buf,sizeof(sysDataDef_t));		
	}
	return ret;
}

uint8_t data_sys_save(uint16_t offset,uint8_t* mbuf,uint16_t len)
{
	uint8_t ret;
	uint8_t* buf=(uint8_t*)(&stSysData);
	if(offset+len>sizeof(sysDataDef_t)-2)return 0;
	//if(sizeof(globleBuffer0)<sizeof(sysDataDef_t))return 0;
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
	m_mem_cpy_len(buf+offset,mbuf,len);
	crc_append(buf,sizeof(sysDataDef_t)-2);
	m_flash_write(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
	m_flash_read(SYSTEM_DATA_ADDR,buf,sizeof(sysDataDef_t));
	ret=crc_verify(buf,sizeof(sysDataDef_t));	
	return ret;
}

//保存标定点数据到数据表
void calib_data_put_piont_tab(xCalibTab_t* ptab,xCalibPoint_t* pp,uint8_t row,uint8_t col)
{
	uint8_t t8;
	xCalibPoint_t* stp;
	t8=ptab->rowCount;
	if(row>t8-1)return;
	if(col>CALIB_P_POINT_NUM-1)return;
	stp=&(ptab->calibRow[row].calibPoint[col]);
	stp->value=pp->value;
	stp->sigAdcValue=pp->sigAdcValue;
	stp->tAdcValue=pp->tAdcValue;

}

void calib_data_set_default(xCalibTab_t *ctab,uint8_t rowCount)
{
    uint8_t i,j;
	if(!(rowCount >=1 && rowCount <=3))rowCount=1;
	m_mem_set((uint8_t*)ctab,0,sizeof(xCalibTab_t));
	ctab->rowCount=rowCount;

    for(i=0;i<rowCount;i++){
        ctab->calibRow[i].pCount=CALIB_P_POINT_NUM;
        for(j=0;j<CALIB_P_POINT_NUM;j++){
            ctab->calibRow[i].calibPoint[j].sigAdcValue=j*3000+i*500;
            ctab->calibRow[i].calibPoint[j].value=j*3000;
            ctab->calibRow[i].calibPoint[j].tAdcValue=i*1000;
        }
    }
    //crc_append((uint8_t*)(&diff_prCalibTabDef),sizeof(diff_prCalibTabDef)-2);
}
/*

uint8_t  calib_data_init_diff_pr(void)
{
	uint8_t ret=0;
	uint16_t t16;
	uint8_t* buf=(uint8_t*)(&calibTab0);
	iicDeviceObj_t* eprObj;
	eprObj= &at24c02Obj0;
	at24c02_init(eprObj,0xa8);
	t16=sizeof(calibTab0);
	at24c02_read_n_byte(eprObj,0,buf,t16);
	ret=crc_verify(buf,t16);
	if(!ret){
		//calib_data_set_default_diff_pr();
		calib_data_set_default(&calibTab1,3);
		crc_append(buf,t16-2);
		at24c02_write_n_byte(eprObj,0,buf,t16);
		at24c02_read_n_byte(eprObj,0,buf,t16);
		ret=crc_verify(buf,t16);		
        if(!ret){
            //calib_data_set_default_diff_pr();
			calib_data_set_default(&calibTab1,3);
            crc_append(buf,t16-2);
           }
	}
	return ret;
}
//压力标定数据初始化
uint8_t  calib_data_init_pr(void)
{
	uint8_t ret=0;
	uint16_t t16;
	uint8_t* buf=(uint8_t*)(&calibTab1);
	iicDeviceObj_t* eprObj; 
	//p_prEepromObj=&at24c02Ch0;
    eprObj=&at24c02Obj1;
	at24c02_init(eprObj,0xaa);
	t16=sizeof(xCalibTab_t);
	at24c02_read_n_byte(eprObj,0,buf,t16);
	ret=crc_verify(buf,t16);
	if(!ret){
		//calib_data_set_default_pr();
		calib_data_set_default(&calibTab1,1);
		crc_append(buf,t16-2);
		at24c02_write_n_byte(eprObj,0,buf,t16);
		at24c02_read_n_byte(eprObj,0,buf,t16);
		ret=crc_verify(buf,t16);
        if(!ret){
            //calib_data_set_default_pr();
			calib_data_set_default(&calibTab1,1);
            crc_append(buf,t16-2);
			//todo
        }
	}
	return ret;	
}
*/
//一阶插值p-vin 压力--电压
//输入xin:	[pvalue(未知),pAdcvalue(已知),tAdcValue(实际温度)];
//返回xin:	[pvalue(已知),pAdcvalue(已知),tAdcValue(实际温度)];并且返回的pvalue无实际意义;
//返回xout:	[pvalue(已知),pAdcvalue(已知),tAdcValue(图表中选定的温度)];
//无温度补偿的情况，直接用xin返回计算结果;
//signal adc value to phy.value,e.t. pressure;
uint8_t m_interp1_cal_p_s(xCalibRow_t* tabrow,__xDataStruct_t* xin,__xDataStruct_t* xout)
{
	uint8_t i;
	//int32_t x,y,phv;
	int16_t t16;
    float x,y,phv,f;
    if(tabrow->pCount<2)return 0;
    
	t16=(float)(xin->sigAdcValue);
	for(i=0;i< (tabrow->pCount) - 1 ;i++){
		//waht !!!!
		if(tabrow->calibPoint[i].sigAdcValue < tabrow->calibPoint[i+1].sigAdcValue){
			if(t16 <= tabrow->calibPoint[i+1].sigAdcValue)break;
		}else{
			if(t16 >= tabrow->calibPoint[i].sigAdcValue)break;
		}
	}
	if(i==(tabrow->pCount) - 1)i=(tabrow->pCount) - 2;
    
    y = (float)(tabrow->calibPoint[i+1].value - tabrow->calibPoint[i].value);
    x = (float)(tabrow->calibPoint[i+1].sigAdcValue - tabrow->calibPoint[i].sigAdcValue);
	phv=tabrow->calibPoint[i].value;
    if(x != 0){
        phv = phv + y*((float)(t16 -  tabrow->calibPoint[i].sigAdcValue))/x;
    }
	xin->value=(int32_t)phv;
	if(xout){
		xout->value =   (int32_t)phv;
		xout->sigAdcValue = xin->sigAdcValue;
		
		t16=xin->sigAdcValue;
		y=(float)(tabrow->calibPoint[i+1].tAdcValue-tabrow->calibPoint[i].tAdcValue);
		x=(float)(tabrow->calibPoint[i+1].sigAdcValue-tabrow->calibPoint[i].sigAdcValue);
		
		phv=tabrow->calibPoint[i].tAdcValue;
        if(x!=0){
			phv=phv+(float)(t16-tabrow->calibPoint[i].sigAdcValue)*y/x;

        }
		xout->tAdcValue = (int16_t)phv;
	}
    return i;
}

//tmpx
uint8_t m_interp1_cal_p_t(__xDataStruct_t* ptmpx,__xDataStruct_t* xin,uint8_t tmpxLen)
{
	uint8_t i;
	int16_t t16;
	float x,y,phv;
	t16=xin->tAdcValue;
	if(tmpxLen<2){
		//xin->value=
		return 0;
	}
    for(i=0;i<tmpxLen-1;i++){
        if(ptmpx[i].tAdcValue < ptmpx[i+1].tAdcValue){
            if(t16 <= ptmpx[i+1].tAdcValue)break;
        }else{
            if(t16  >= ptmpx[i].tAdcValue)break;
        }
    }
    
    if(i==tmpxLen-1)i=tmpxLen-2;
    
	phv=(float)(ptmpx[i].value);
	
    y=(float)(ptmpx[i+1].value-ptmpx[i].value);
    x=(float)(ptmpx[i+1].tAdcValue-ptmpx[i].tAdcValue);
    if(x!=0){
        phv = phv + ((float)(t16 - ptmpx[i].tAdcValue))*y/x;
    }
	xin->value=(int32_t)phv;
    return i;
}

float m_interp1_float_fast(float* tab,float in,int16_t len)
{

	uint16_t i;
	float f,x,y;	
	f=in*100;
	if(f>100)f=100;
	i=(uint16_t)f;
	x=tab[i];
	y=tab[i+1]-x;
	f=y*(f-(float)i);
	f=f+x;
	return f;
}

uint8_t  calib_data_obj_init(calibDataObj_t* obj,uint8_t rowCount)
{
	uint8_t ret=0;
	uint16_t t16;
	uint8_t* buf=(uint8_t*)(obj->calibTab);
    t16=sizeof(xCalibTab_t);
    at24c02_read_n_byte(obj->eep24c02,0,buf,t16);
	ret=crc_verify(buf,t16);
	if(!ret){
		calib_data_set_default(obj->calibTab,rowCount);
		crc_append(buf,t16-2);
		at24c02_write_n_byte(obj->eep24c02,0,buf,t16);
		at24c02_read_n_byte(obj->eep24c02,0,buf,t16);
		ret=crc_verify(buf,t16);		
        if(!ret){
			calib_data_set_default(obj->calibTab,rowCount);
            crc_append(buf,t16-2);
           }
	}
	return ret;    
}
//api
//api
void data_init_all(void)
{
	data_sys_init();
	//初始化eeprom对象
	at24c02_init_all_chip();
	//初始化标定数据对象
	diffPrCalibDataObj.calibTab=&calibTab0;
    diffPrCalibDataObj.eep24c02=&at24c02Obj0;
	
    prPrCalibDataObj.calibTab=&calibTab1;
    prPrCalibDataObj.eep24c02=&at24c02Obj1;

    calib_data_obj_init(&diffPrCalibDataObj,3);
    calib_data_obj_init(&prPrCalibDataObj,1);
    __nop();
    __nop();
}

//高度折算容积，水平放置
int32_t cal_diff_hight_to_vol_h(int32_t h)
{
	float v1,v2;
	float f1,f2;
    f1=(float)h;
    if(f1<0.0)f1=0.0;
	f2=(float)(stSysData.d);
	f1=f1/f2;//h/D
    if(f1>1.0)f1=1.0;
    
    f2=f1;
	f1=m_interp1_float_fast((float*)hKcy,f1,sizeof(hKcy)/sizeof(hKcy[0]));
	v1=(float)(stSysData.V1);
    v1=v1*f1;
    
    f1=f2;
    f1=m_interp1_float_fast((float*)hKel,f1,sizeof(hKel)/sizeof(hKel[0]));
	v2=(float)(stSysData.V2);
    v2=v2*f1;
    
    v1=v1+v2;
	return (int32_t)v1;
}

//计算高度百分比,刻度条
uint8_t cal_diff_hight_level(void)
{
    float f1,f2;
	f1=(float)stSysData.d;
	f2=(float)stSysData.h;
	if(stSysData.pos==HOTIZONTAL){
	}else{
		f1=f1+f2/2;
	}
	/*
	if(stSysData.pos==HOTIZONTAL){
        f1=(float)stSysData.d;
    }else{
        f1=(float)stSysData.h;
        f1=(f1+stSysData.d)+(f1+stSysData.d);
    }
	*/
	f2=(float)(stSysData.maxValueForlevelBar)/100.0;
	f1=f1*f2;
	
    //f1=f1*(stSysData.maxValueForlevelBar)/100;
    if(f1==0)f1=1;
    f2=(float)rtHight;
    if(f2<0.0)f2=0.0;
    f1=f2/f1;
    f1*=100;
    if(f1>100)f1=100;
	rtLevel=(uint8_t)f1;
    return rtLevel;
}

//高度折算容积，竖直放置
int32_t cal_diff_hight_to_vol_v(int32_t h)
{
	float v1,v2;
	float f1,D,H;
	v1=(float)(stSysData.V1);
	v2=(float)(stSysData.V2);
	
    f1=(float)h;
	D=(float)(stSysData.d);
	H=(float)(stSysData.h);
    if(f1<D/4){
        f1=2*f1/D;
        f1=m_interp1_float_fast((float*)hKel,f1,sizeof(hKel)/sizeof(hKel[0]));
		v2=v2*f1;
        return (int32_t)v2;
    }else if(f1<D/4+H){
        f1=f1-D/4;
        v1=v1*(f1/H);
        v2=v2/2;
        return (int32_t)(v1+v2);
    }else{
        if(f1>H+D/2)f1=H+D/2;
        f1=H+D/2-f1;
		f1=0.5-f1;
		if(f1<=0.0)f1=0.0;
		f1=2*f1/D;
        f1=m_interp1_float_fast((float*)hKel,f1,sizeof(hKel)/sizeof(hKel[0]));
        v2=v2*(0.5+f1);
        return (int32_t)(v1+v2); 
    }
}

//压力转高度
//折算为，高度，P=ρgh<-->h=p/ρg;单位为P(KPa),ρ(N/m3),(g=9.8)
int32_t cal_diff_p_to_h(int32_t p)
{
    uint16_t density;
	float f1,f2;
	//t32=xin->pValue;
	f1=(float)(p);
    density=data_sys_get_density();
	f2=(float)(density);
    f1=f1/(f2*9.8f);
    f1*=1000;
	rtHight=(int32_t)f1;	
	return rtHight;
}

int32_t cal_diff_vol_to_t(int32_t v)
{
    uint16_t density;
	float f1,f2;
	f1=(float)(v);
    density=data_sys_get_density();
	f2=(float)(density);
	f1=f1*f2/1000;
	rtWeight=(int32_t)f1;
	return rtWeight;
}

//计算差压
//计算结果直接用xin返回
__xDataStruct_t tmpx[3];
uint8_t cal_diff_press()
{
	__xDataStruct_t* xin= &x_prDiffData;
	m_mem_set((uint8_t*)tmpx,0,sizeof(tmpx));
	uint8_t i=0,j=0;
	xCalibRow_t* tabrow;
    j=0;
    for(i=0;i<calibTab0.rowCount;i++){
        tabrow = &(calibTab0.calibRow[i]);
		if(tabrow->pCount<2)continue;
        m_interp1_cal_p_s(tabrow,xin,&tmpx[j++]);
    }
	//温补
    m_interp1_cal_p_t(&tmpx[0],xin,j);

	rtDiffPressure=xin->value;
	cal_diff_p_to_h(rtDiffPressure);
    rtLevel=cal_diff_hight_level();
    if(stSysData.pos==HOTIZONTAL){
        rtVolume=cal_diff_hight_to_vol_h(rtHight);
    }else{
		rtVolume=cal_diff_hight_to_vol_v(rtHight);
	}

	cal_diff_vol_to_t(rtVolume);
	return i;
}

int32_t calculate_and_compensate(xCalibTab_t* cTab,__xDataStruct_t* xin)
{
	uint8_t i=0,j=0;
	xCalibRow_t* tabrow;
	m_mem_set((uint8_t*)tmpx,0,sizeof(tmpx));
    for(i=0;i<cTab->rowCount;i++){
        tabrow = &(cTab->calibRow[i]);
		if(tabrow->pCount<2)continue;
        m_interp1_cal_p_s(tabrow,xin,&tmpx[j++]);
    }	
	//温补
	m_interp1_cal_p_t(&tmpx[0],xin,j);
	return xin->value;
}

uint8_t cal_press(void)
{
	uint8_t ret;
	__xDataStruct_t  xin={0};
	xin.value=0;
    xin.sigAdcValue=adc_pressure;
    xin.tAdcValue=0;
	xCalibRow_t* tabrow;
	tabrow= &calibTab1.calibRow[0];
	ret=m_interp1_cal_p_s(tabrow,&xin,NULL);
	rtPressure=xin.value;
	return ret;
}

// -----------------------------------------------------
// 计算温度
// a=3.90802e-3;b=-5.8e-7;c=-4.2735e-12;
// b/a=-1.484e-4;默认3个小数位
// t=ax-b+c*t^2;//c=1.484e-4
// t0=ax-b;
// t1=t0+c*t0^2;
// -----------------------------------------------------
#define __kT (1.484e-4f)
void cal_pt100_temperature_in(void)
{
	/*
    float f1,f2;
    f1=(float)(adc_inPt100);

    f2=(float)(fpSysData->TempZero);
    f1=f1-f2;    
	
    f2=(float)(fpSysData->TempLine);
    f2/=1000;
    f1=f1*f2;

    f1/=1000;
    f2=__kT;
    f2=f2*f1*f1;
    f1=f1+f2;
    
    f1=f1*1000;
    rtTemperatureIn= (int32_t)f1;
	*/
	rtTemperatureIn= 0;
}

/*
int32_t __cal_x_inter1_2(st_exCalibDef* pl,int32_t adc)
{
    float y,x;
    //sysDataDef_t* stp=&stSysData;
    y=(float)(pl->exTempCalib[1].value-pl->exTempCalib[0].value);
    x=(float)(pl->exTempCalib[1].adcValue-pl->exTempCalib[0].adcValue);
    if(x!=0){
        y=y/x;
        x=(float)adc-(float)stp->exTempCalib[0].adcValue;
        y=y*x;
        y=y+(float)(stp->exTempCalib[0].value);
    }else{
        y=(float)(stp->exTempCalib[0].value);
    }
    if(y>300000)y=300000;
	rtTemperatureEx= (int32_t)y;
}
*/

void cal_pt100_temperature_ex(void)
{
    float y,x;
    sysDataDef_t* stp=&stSysData;
    y=(float)(stp->exTempCalib[1].value-stp->exTempCalib[0].value);
    x=(float)(stp->exTempCalib[1].adcValue-stp->exTempCalib[0].adcValue);
    if(x!=0){
        y=y/x;
        x=(float)adc_exPt100-(float)stp->exTempCalib[0].adcValue;
        y=y*x;
        y=y+(float)(stp->exTempCalib[0].value);
    }else{
        y=(float)(stp->exTempCalib[0].value);
    }
    if(y>300000)y=300000;
	rtTemperatureEx= (int32_t)y;
}

void cal_additional_pressute(uint8_t index)
{
	/*
    if(index>1)return;
	float f1,f2;
	f1=(float)adc_iPrEx[index];
    f2=(float)(fpSysData->ex_pressZero[index]);
    f1=f1-f2;   
    
    f2=(float)(fpSysData->ex_pressLine[index]);
    f2/=1000;
    
    f1=f1*f2;
    rtExPressure[index]=(int32_t)f1;
	*/
	rtExPressure[index]=0;
}


void cal_battery_voltage(void)
{
	
}

uint32_t cal_pt100_temperature(int16_t x,uint32_t l,uint32_t b)
{
	int32_t t32,ret;
	t32=(int32_t)l*x-b;
	//三个小数位
	if(t32>200000)t32=200000;
	if(t32<-200000)t32=-200000;
	ret=t32;
	t32/=10;
	t32=t32*t32/10000;
	t32*=1484;
	t32/=10000;
	ret=ret+t32;
	return ret;
}


//file end
