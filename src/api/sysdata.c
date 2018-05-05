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
calibDataObj_t ex0PrCalibDataObj;
calibDataObj_t ex1PrCalibDataObj;

__xDataStruct_t	x_prDiffData;
__xDataStruct_t	x_prData;
__xDataStruct_t	x_ex0prData;
__xDataStruct_t	x_ex1prData;

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

volatile int32_t    rtTemperatureInBuf[4]={0,0,0,0};
volatile int32_t    rtDiffPrBuf[4]={0,0,0,0};
volatile int32_t	rtDiffPressure;

volatile int32_t    rtHightOriginal;
volatile int32_t	rtHight;
volatile int32_t	rtWeight;
volatile int32_t	rtVolume;

volatile uint8_t    rtLevel;
volatile int32_t    rtTemperatureIn=0;

volatile int32_t    rtPressure=0;

volatile int32_t    rtTemperatureEx0=0;
volatile int32_t    rtTemperatureEx1=0;

//volatile int32_t	rtExPressure[2];
volatile int32_t		rtEx0Pressure;
volatile int32_t		rtEx1Pressure;


volatile int32_t		rtDiffPrOriginal;
volatile int32_t		rtPrOriginal=0;
volatile int32_t		rtEx0PrOriginal;
volatile int32_t		rtEx1PrOriginal;	
//

volatile st_deviceOpMode dwm=TEST_MODE;
uint16_t modifyPolyCeofficTimer=0x00;

deviceEventDef_t deviceEvent={0};
hardStatus_t hardStatus={~0x00ul};
//emErrCode_t errCode=NO_ERROR;
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
/*
clear  all
A=3.9083e-3
B=-5.775e-7
C=4.183e-12
i=0;
for t=-200:1:200;
    if(t<0.0)
        r=100*(1+A*t+B*t^2+C*t^3*(t-100));
    else
         r=100*(1+A*t+B*t^2);
    end
    %k=2*x^2*(3/2-x);
    fprintf('%1.4f,',r)
    i=i+1;
    if i== 10 
        fprintf('\r\n');
        i=0;
    end
end  
*/
/*
const float pt100ResTempTable[]={
	20.5279,20.9235,21.3192,21.7151,22.1111,22.5072,22.9034,23.2998,23.6963,24.0929,
	24.4896,24.8864,25.2833,25.6804,26.0775,26.4748,26.8721,27.2696,27.6672,28.0648,
	28.4626,28.8604,29.2583,29.6564,30.0545,30.4527,30.8509,31.2493,31.6477,32.0462,
	32.4448,32.8435,33.2422,33.6410,34.0398,34.4388,34.8377,35.2368,35.6359,36.0351,
	36.4343,36.8335,37.2329,37.6322,38.0317,38.4311,38.8306,39.2302,39.6298,40.0294,
	40.4291,40.8288,41.2285,41.6283,42.0281,42.4279,42.8277,43.2276,43.6275,44.0274,
	44.4274,44.8273,45.2273,45.6273,46.0273,46.4273,46.8273,47.2274,47.6274,48.0274,
	48.4275,48.8275,49.2276,49.6276,50.0277,50.4277,50.8278,51.2278,51.6278,52.0278,
	52.4278,52.8278,53.2278,53.6277,54.0277,54.4276,54.8275,55.2274,55.6272,56.0270,
	56.4268,56.8266,57.2264,57.6261,58.0258,58.4254,58.8250,59.2246,59.6242,60.0237,
	60.4232,60.8226,61.2220,61.6213,62.0206,62.4199,62.8191,63.2183,63.6174,64.0164,
	64.4155,64.8144,65.2133,65.6122,66.0110,66.4097,66.8084,67.2070,67.6056,68.0041,
	68.4026,68.8009,69.1992,69.5975,69.9957,70.3938,70.7918,71.1898,71.5877,71.9856,
	72.3833,72.7810,73.1786,73.5762,73.9736,74.3710,74.7683,75.1655,75.5627,75.9598,
	76.3568,76.7537,77.1505,77.5472,77.9439,78.3404,78.7369,79.1333,79.5296,79.9258,
	80.3220,80.7180,81.1140,81.5098,81.9056,82.3012,82.6968,83.0923,83.4877,83.8830,
	84.2781,84.6732,85.0682,85.4631,85.8579,86.2526,86.6472,87.0417,87.4361,87.8304,
	88.2246,88.6187,89.0127,89.4065,89.8003,90.1940,90.5875,90.9810,91.3743,91.7676,
	92.1607,92.5537,92.9466,93.3394,93.7321,94.1247,94.5172,94.9096,95.3018,95.6939,
	96.0860,96.4779,96.8697,97.2614,97.6530,98.0444,98.4358,98.8270,99.2181,99.6091,
	100.0000,100.3908,100.7814,101.1720,101.5624,101.9527,102.3429,102.7330,103.1229,103.5128,
	103.9025,104.2921,104.6816,105.0710,105.4603,105.8495,106.2385,106.6274,107.0162,107.4049,
	107.7935,108.1820,108.5703,108.9585,109.3467,109.7347,110.1225,110.5103,110.8980,111.2855,
	111.6729,112.0602,112.4474,112.8345,113.2215,113.6083,113.9950,114.3817,114.7681,115.1545,
	115.5408,115.9270,116.3130,116.6989,117.0847,117.4704,117.8560,118.2414,118.6268,119.0120,
	119.3971,119.7821,120.1670,120.5518,120.9364,121.3210,121.7054,122.0897,122.4739,122.8579,
	123.2419,123.6257,124.0095,124.3931,124.7766,125.1600,125.5432,125.9264,126.3094,126.6923,
	127.0751,127.4578,127.8404,128.2228,128.6052,128.9874,129.3695,129.7515,130.1334,130.5152,
	130.8968,131.2783,131.6597,132.0411,132.4222,132.8033,133.1843,133.5651,133.9458,134.3264,
	134.7069,135.0873,135.4676,135.8477,136.2277,136.6077,136.9875,137.3671,137.7467,138.1262,
	138.5055,138.8847,139.2638,139.6428,140.0217,140.4005,140.7791,141.1576,141.5360,141.9143,
	142.2925,142.6706,143.0485,143.4264,143.8041,144.1817,144.5592,144.9366,145.3138,145.6910,
	146.0680,146.4449,146.8217,147.1984,147.5750,147.9514,148.3277,148.7040,149.0801,149.4561,
	149.8319,150.2077,150.5833,150.9589,151.3343,151.7096,152.0847,152.4598,152.8347,153.2096,
	153.5843,153.9589,154.3334,154.7078,155.0820,155.4562,155.8302,156.2041,156.5779,156.9516,
	157.3251,157.6986,158.0719,158.4451,158.8182,159.1912,159.5641,159.9368,160.3095,160.6820,
	161.0544,161.4267,161.7989,162.1709,162.5429,162.9147,163.2864,163.6580,164.0295,164.4009,
	164.7721,165.1433,165.5143,165.8852,166.2560,166.6267,166.9972,167.3677,167.7380,168.1082,
	168.4783,168.8483,169.2181,169.5879,169.9575,170.3271,170.6965,171.0658,171.4349,171.8040,
	172.1729,172.5418,172.9105,173.2791,173.6475,174.0159,174.3842,174.7523,175.1203,175.4882,
	175.8560,
    
};
*/
const float pt100ResTempTable[]={
1852,1895,1938,1982,2025,2068,2111,2154,2197,2240,
2283,2325,2368,2411,2454,2497,2539,2582,2624,2667,
2710,2752,2795,2837,2880,2922,2964,3007,3049,3091,
3134,3176,3218,3260,3302,3344,3386,3428,3470,3512,
3554,3596,3638,3680,3722,3764,3805,3847,3889,3931,
3972,4014,4056,4097,4139,4180,4222,4263,4305,4346,
4388,4429,4470,4512,4553,4594,4636,4677,4718,4759,
4800,4842,4883,4924,4965,5006,5047,5088,5129,5170,
5211,5252,5293,5334,5375,5415,5456,5497,5538,5579,
5619,5660,5701,5741,5782,5823,5863,5904,5944,5985,
6026,6066,6107,6147,6188,6228,6268,6309,6349,6390,
6430,6470,6511,6551,6591,6631,6672,6712,6752,6792,
6833,6873,6913,6953,6993,7033,7073,7113,7153,7193,
7233,7273,7313,7353,7393,7433,7473,7513,7553,7593,
7633,7673,7712,7752,7792,7832,7872,7911,7951,7991,
8031,8070,8110,8150,8189,8229,8269,8308,8348,8387,
8427,8467,8506,8546,8585,8625,8664,8704,8743,8783,
8822,8862,8901,8940,8980,9019,9059,9098,9137,9177,
9216,9255,9295,9334,9373,9412,9452,9491,9530,9569,
9609,9648,9687,9726,9765,9804,9844,9883,9922,9961,
10000,10039,10078,10117,10156,10195,10234,10273,10312,10351,
10390,10429,10468,10507,10546,10585,10624,10663,10702,10740,
10779,10818,10857,10896,10935,10973,11012,11051,11090,11129,
11167,11206,11245,11283,11322,11361,11400,11438,11477,11515,
11554,11593,11631,11670,11708,11747,11786,11824,11863,11901,
11940,11978,12017,12055,12094,12132,12171,12209,12247,12286,
12324,12363,12401,12439,12478,12516,12554,12593,12631,12669,
12708,12746,12784,12822,12861,12899,12937,12975,13013,13052,
13090,13128,13166,13204,13242,13280,13318,13357,13395,13433,
13471,13509,13547,13585,13623,13661,13699,13737,13775,13813,
13851,13888,13926,13964,14002,14040,14078,14116,14154,14191,
14229,14267,14305,14343,14380,14418,14456,14494,14531,14569,
14607,14644,14682,14720,14757,14795,14833,14870,14908,14946,
14983,15021,15058,15096,15133,15171,15208,15246,15283,15321,
15358,15396,15433,15471,15508,15546,15583,15620,15658,15695,
15733,15770,15807,15845,15882,15919,15956,15994,16031,16068,
16105,16143,16180,16217,16254,16291,16329,16366,16403,16440,
16477,16514,16551,16589,16626,16663,16700,16737,16774,16811,
16848,16885,16922,16959,16996,17033,17070,17107,17143,17180,
17217,17254,17291,17328,17365,17402,17438,17475,17512,17549,
17586,
};
const sysDataDef_t defultSystemData={

		1234,//uint32_t 	id;
		1,//em_posture	pos;							//立式或者卧式
		0,//uint8_t		maxValueForlevelBar;			//状态条显示满时对应的高度值,
													//(95%或者100%)
		5,//uint16_t	density;						//密度
		{{"LO2",1140},{"LN2",810},{"LAr",1402},{"CO2",1020},{"LNG",436},{"  P",1000}},
		3670,//int32_t		h;								//高
		1400,//uint32_t	d;								//直径
		
		0,//int32_t		V1;								//圆筒部分体积
		0,//int32_t		V2;								//封头椭球体积
		
		0,//int32_t		baseZero;						//基础零位
		//

		{{0,0},{50000,50000}},//st_2ndCalibDef	_2ndPrDiffCalib[2];			//二次修正，差压
		{{0,0},{50000,50000}},//st_2ndCalibDef	_2ndPrCalib[2];				//二次修正，压力
		{{0,0},{50000,50000}},
		{{0,0},{50000,50000}},
		{{6000,20,0,{0}},{1000,20,1,{0}},{800,5,2,{0}},{200,5,3,{0}}},//st_warnDef		diffPressureWarnSet[4];		//差压报警设置
		//{{0},{0}},//st_warnDef		pressureWarnSet[2];			//压力报警设置

		//{600,200,100,100},
		{1000,0,0,0},//uint16_t		ployCoeffic[4];					//v0'=a0.v0+a1.v1+ ...+an.vn

		{{0,0},{10000,10000}},//st_exClibDef	TmepCalib[2];				//温度标定，
		
		{{0,0},{10000,10000}},//st_exClibDef	exPr0Calib[2];				//外部压力传传感器标定
		{{0,0},{10000,10000}},//st_exClibDef	exPr1Calib[2];
		{{20000,1277},{120000,7664}},//st_exClibDef	exTempCalib[2];				//外部温度标定
		{{20000,1277},{120000,7664}},//st_exClibDef	exTempCalib[2];				//外部温度标定
        
		//{1000,2000},//st_ilpScaleDef	exdiffPrilpScale0;			//外部压力4-20毫安范围
		//{1000,2000},//st_ilpScaleDef	exPrilpScale0;				//外部压力4-20毫安范围
		{0,2000},//st_ilpScaleDef	exPrIpScale0;
		{0,2000},//st_ilpScaleDef	exPrIpScale1;		
		//st_ilpScaleDef
        {0,0},      //ilpAdjustValue_t   ilpAdjustCh0;
        {0,0},      //ilpAdjustValue_t   ilpAdjustCh1;
		1000,//uint16_t	barScale;
		0,//uint8_t 	exPrTempShowEn;
		10,//uint8_t		blOnTm;		        
		//
		10,//sleepPeriod
		RF_SEND_OFF,//rfSendPeriod
		0,//bpMenu;
		0,//bpSubMenu
		0,//lcdOnTime
		255,//ModbusId
		//
		__default_PD,//1803,//production date
		__default_PC,//0,//producteCode
		//
		{0},//pdcWassword
		(PSW_SET_PDC),//pdcWassword
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
	h=h-r;
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
    r=r/1000;
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
	menu=stSysData.bpMenu;
	subMenu=stSysData.bpSubMenu;
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
	if(!(rowCount >=1 && rowCount <=CALIB_ROW_NUM))rowCount=1;
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
    ctab->staticPreAdj0.pr=0;
    ctab->staticPreAdj0.diffPrZero=0;
    ctab->staticPreAdj1.pr=10000;
    ctab->staticPreAdj1.diffPrZero=0;
	ctab->status=0x01;
	ctab->reverse[0]=0x55;
    ctab->reverse[1]=0xAA;
    //ctab->reverse[2]=0xAA;
    //crc_append((uint8_t*)(&diff_prCalibTabDef),sizeof(diff_prCalibTabDef)-2);
}
int32_t  cal_smoothing_filter(int32_t* buf,int32_t in,uint8_t len)
{
	uint8_t i;
	int32_t ret=0;
	for(i=0;i<len-1;i++){
		buf[i]=buf[i+1];
		ret+=buf[i];
	}
	buf[i]=in;
	ret+=buf[i];
	return (ret/len);
	
}
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
    float x,y,phv;
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
    if(x >= 1.0f){
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
    if(x>=1.0f){
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
            obj->calibTab->status=0x00;
            crc_append(buf,t16-2);
           }
	}
    

	return ret;    
}

//api
//api
void data_init_all(void)
{
    uint8_t ret;
	data_sys_init();
	//初始化eeprom对象
	at24c02_init_all_chip();
	//初始化标定数据对象
	diffPrCalibDataObj.calibTab=&calibTab0;
    diffPrCalibDataObj.eep24c02=&at24c02Obj0;
	
    prPrCalibDataObj.calibTab=&calibTab1;
    prPrCalibDataObj.eep24c02=&at24c02Obj1;
	
	ex0PrCalibDataObj.calibTab=&calibTab2;
	ex0PrCalibDataObj.eep24c02=&at24c02Obj2;

	ex1PrCalibDataObj.calibTab=&calibTab3;
	ex1PrCalibDataObj.eep24c02=&at24c02Obj3;
	
    ret=calib_data_obj_init(&diffPrCalibDataObj,CALIB_ROW_NUM);
    if(ret){
        hardStatus.bits.bDprEeprom=1;
    }else{
        hardStatus.bits.bDprEeprom=0;
    }
    
    ret=calib_data_obj_init(&prPrCalibDataObj,1);
     if(ret){
        hardStatus.bits.bprEeprom=1;
    }else{
        hardStatus.bits.bprEeprom=0;
    }   
	
	ret=calib_data_obj_init(&ex0PrCalibDataObj,1);
     if(ret){
        hardStatus.bits.bEx0PrEeprom=1;
    }else{
        hardStatus.bits.bEx0PrEeprom=0;
    }
    
	ret=calib_data_obj_init(&ex1PrCalibDataObj,1);
     if(ret){
        hardStatus.bits.bEx1PrEeprom=1;
    }else{
        hardStatus.bits.bEx1PrEeprom=0;
    }	
    __nop();
    __nop();
}

//高度折算容积，水平放置
int32_t cal_diff_hight_to_vol_h(int32_t h)
{
    int32_t t32;
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
    t32=(int32_t)v1;
    if(t32<0)t32=0;
	return t32;
}

//计算高度百分比,刻度条
uint8_t cal_diff_hight_level(void)
{
    float f1,f2;
	f1=(float)stSysData.d;
	f2=(float)stSysData.h;
	if(stSysData.pos==HOTIZONTAL){
	}else{
		//f1=f1+f2/2;
        f1=f2;
	}
	/*
	if(stSysData.pos==HOTIZONTAL){
        f1=(float)stSysData.d;
    }else{
        f1=(float)stSysData.h;
        f1=(f1+stSysData.d)+(f1+stSysData.d);
    }
	*/
	f2=(float)(stSysData.barScale)/1000.0;
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
    int32_t t32;
	float v1,v2;
	float f1,D,H;
	v1=(float)(stSysData.V1);
	v2=(float)(stSysData.V2);
	__nop();
    f1=(float)h;
	D=(float)(stSysData.d);
	H=(float)(stSysData.h);
    H=H-(D/2);
    if(f1<D/4){
        f1=2*f1/D;
        f1=m_interp1_float_fast((float*)hKel,f1,sizeof(hKel)/sizeof(hKel[0]));
		v2=v2*f1;
        t32=(int32_t)v2;
        if(t32<0l)t32=0l;
        return t32;
    }else if(f1<D/4+H){
        f1=f1-D/4;
        v1=v1*(f1/H);
        v2=v2/2;
        t32=(int32_t)(v1+v2);
        if(t32<0l)t32=0l;
        return t32;
    }else{
        if(f1>H+D/2)f1=H+D/2;
		f1=(H+D/2)-f1;
		f1=2*f1/D;
        f1=m_interp1_float_fast((float*)hKel,f1,sizeof(hKel)/sizeof(hKel[0]));
		v2=v2*(1-f1);
        t32=(int32_t)(v1+v2);
        if(t32<0l)t32=0l;
        return t32;
        
    }
}

//压力转高度
//折算为，高度，P=ρgh<-->h=p/ρg;单位为P(KPa),ρ(N/m3),(g=9.8)
int32_t cal_diff_p_to_h(int32_t p)
{
    int32_t t32;
    uint16_t density;
	float f1,f2;
	//t32=xin->pValue;
	f1=(float)(p);
    density=data_sys_get_density();
	f2=(float)(density);
    f1=f1/(f2*9.80665f);
    f1*=1000;
    t32=(int32_t)f1;	
    //if(t32<0l)t32=0l;
	//rtHight=t32;
	/*
	if(stSysData.pos==HOTIZONTAL){
        if(t32>(int32_t)(stSysData.d))t32=(int32_t)(stSysData.d);
    }else{
        //if(t32>(int32_t)(stSysData.h + (stSysData.d * 2)))t32=(int32_t)(stSysData.h + (stSysData.d * 2));
		if(t32>(int32_t)(stSysData.h ))t32=(int32_t)(stSysData.h );
    }	
	*/
	return t32;
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
__xDataStruct_t tmpx[6];

int32_t calculate_and_compensate(xCalibTab_t* cTab,__xDataStruct_t* xin)
{
	uint8_t i=0,j=0;
	xCalibRow_t* tabrow;
	m_mem_set((uint8_t*)tmpx,0,sizeof(tmpx));
	for(i=0;i<CALIB_ROW_NUM;i++){
    //for(i=0;i<cTab->rowCount;i++){
        tabrow = &(cTab->calibRow[i]);
		if(tabrow->pCount<2)continue;
        m_interp1_cal_p_s(tabrow,xin,&tmpx[j++]);
    }	
	//温补
	m_interp1_cal_p_t(&tmpx[0],xin,j);
	return xin->value;
}

// -----------------------------------------------------
// 计算温度
// a=3.90802e-3;b=-5.8e-7;c=-4.2735e-12;
// b/a=-1.484e-4;默认3个小数位
// t=ax-b+c*t^2;//c=1.484e-4
// t0=ax-b;
// t1=t0+c*t0^2;
// -----------------------------------------------------

/*
float calc_res_2_temp(float r)
{
	float x;
	x=(r-100)/3.940e-1;
	//http://blog.csdn.net/xiaowei_cqu/article/details/8585703/
    x= x - ((-5.802e-5 * x * x ) + (3.940e-1 * x) + 100 - r)/(2* -5.802e-5 * x +  3.940e-1);
    __nop();
    x= x - ((-5.802e-5 * x * x ) + (3.940e-1 * x) + 100 - r)/(2* -5.802e-5 * x +  3.940e-1);
    __nop();
    x= x - ((-5.802e-5 * x * x ) + (3.940e-1 * x) + 100 - r)/(2* -5.802e-5 * x +  3.940e-1);
    __nop();    
    return x;
}
*/

float calc_res_2_temp(float rr)
{
	int32_t r=(int32_t)(rr*100);
	uint16_t i,j;
	float x;
	for(i=0;i<390;i+=10){
		if(r<pt100ResTempTable[i+10])break;
	}
	for(j=i;j<i+10;j++){
		if(r<pt100ResTempTable[j+1])break;
	}
	if(j==399)j=398;
	x=pt100ResTempTable[j+1]-pt100ResTempTable[j];
	x=1.0/x;
	x=x*(r-pt100ResTempTable[j]);
    x=x+(float)j;
    x=x-200.0;
	//x=x+(float)(j-200);
	return x;
}

void cal_battery_voltage(void)
{
	
}

uint8_t calc_warning_pr_dpr(void)
{
	uint16_t oldEvent;
	oldEvent=deviceEvent.t16;
	warnType_t type;
    uint8_t i;
    int32_t v,oop;
    for(i=0;i<4;i++){
        v=stSysData.dprWarnSet[i].warnValue;
        oop=stSysData.dprWarnSet[i].warnValueOop;
        if(v==oop)continue;
        type=stSysData.dprWarnSet[i].type;
        switch(type){
            case HIGHT_LO:
                if(rtHight<v)deviceEvent.t16 |= (0x01<<i);
                else if(rtHight>v+oop)
                    deviceEvent.t16 &= ~(0x01<<i);
                break;
			case HIGHT_HI:
				if(rtHight>v)deviceEvent.t16 |= (0x01<<i);
                else if(rtHight < v-oop)
                    deviceEvent.t16 &= ~(0x01<<i);
                break;
			case PRESSURE_HI:
				if(rtPressure>v)deviceEvent.t16 |= (0x01<<i);
                else if(rtPressure < v-oop)
                    deviceEvent.t16 &= ~(0x01<<i);
                break;
			case PRESSURE_LO:
				if(rtPressure<v)deviceEvent.t16 |= (0x01<<i);
				else if(rtPressure > v+oop)
					deviceEvent.t16 &= ~(0x01<<i);
				break;
			default:
				break;
        }
    }
	return (oldEvent != deviceEvent.t16);
}

uint16_t calc_dpr_iloop_out_put(void)
{
	float x,y;
    uint16_t t16;
    x=(float)(stSysData.IpScaleCh0.ilpHi-stSysData.IpScaleCh0.ilpLow);
    y=65535;
    y=y/x;
    x=(float)(rtHight-stSysData.IpScaleCh0.ilpLow);
    y=y*x;
    if(y<=0)y=0;
    if(y>=65535)y=65535;
    t16=(uint16_t)y;
    return t16;
}

int32_t calc_dpr_iloop_out_put_ex(void)
{
	int32_t lo,hi;
	float x,y;
    int32_t t32;

	lo=0x4000+(int32_t)stSysData.ilpAdjustCh0.valueLo;
    hi=0x14000+(int32_t)stSysData.ilpAdjustCh0.valueHi;
    
    x=(float)(stSysData.IpScaleCh0.ilpHi-stSysData.IpScaleCh0.ilpLow);
    y=(float)(hi-lo);
    
    y=y/x;
    x=(float)(rtHight-stSysData.IpScaleCh0.ilpLow);
    y=y*x;
    y=y+(float)lo;
    
    t32=(int32_t)y;
    if(t32<=lo)t32=lo;
    if(t32>=hi)t32=hi;

    return t32;
}

uint16_t calc_pr_iloop_out_put(void)
{
	float x,y;
    uint16_t t16;
    x=(float)(stSysData.IpScaleCh1.ilpHi-stSysData.IpScaleCh1.ilpLow);
    y=65535;
    y=y/x;
    x=(float)(rtPressure-stSysData.IpScaleCh1.ilpLow);
    y=y*x;
    if(y<=0)y=0;
    if(y>=65535)y=65535;
    t16=(uint16_t)y;
    return t16;
}

int32_t calc_pr_iloop_out_put_ex(void)
{
	int32_t lo,hi;
	float x,y;
    int32_t t32;

	lo=0x4000+(int32_t)stSysData.ilpAdjustCh1.valueLo;
    hi=0x14000+(int32_t)stSysData.ilpAdjustCh1.valueHi;
    
    x=(float)(stSysData.IpScaleCh1.ilpHi-stSysData.IpScaleCh1.ilpLow);
    y=(float)(hi-lo);
    
    y=y/x;
    x=(float)(rtPressure-stSysData.IpScaleCh1.ilpLow);
    y=y*x;
    y=y+(float)lo;
    
    t32=(int32_t)y;
    if(t32<=lo)t32=lo;
    if(t32>=hi)t32=hi;

    return t32;    
}
//file end
