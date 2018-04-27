#include "../includes/includes.h"
#define nb_uart_send_str uart2_send_str

const st_ATcmdDef* pAtCmd=(st_ATcmdDef*)(NULL);
uint32_t recTimerSec=0x00;
atCmdProcessSm_t atCmdSm=AT_CMD_PROCESS_NOTHING;

uint16_t nbRecLen;
uint8_t nbRecBuf[NB_REC_BUFFER_LEN];

uint8_t CIMI[16];
uint8_t	CGSN[16];
uint8_t	ICCID[21];

/*
uint16_t nb_at_cmd_ex(const st_ATcmdDef* cmd,uint8_t* recbuf,uint16_t reclen)
{
    //UART2_Initialize();
	switch(atCmdSm){
		case AT_CMD_PROCESS_NOTHING:break;
		case AT_CMD_PROCESS_READY_SEND:{
			nb_uart_send_str((uint8_t*)(cmd->cmdStr));
			recTimerSec=globleHalfSec;
			atCmdSm=AT_CMD_PROCESS_WAITE_RESP;
			break;
		}
		case AT_CMD_PROCESS_WAITE_RESP:break;
			if(recTimerSec-globleHalfSec>6){
				atCmdSm=AT_CMD_PROCESS_ERROR;
				break;
			}
			if(event & flg_NB_GPS_RECEIVED){
                atCmdSm=AT_CMD_PROCESS_REC_RESP;
				m_mem_cpy_len(nbRecBuf,uart2ReceivedBuf,uart2ReceivedCount);
				uart2ReceivedCount=0;
                break;
            }
		case AT_CMD_PROCESS_WAITE_RESP_TM_OUT:
			atCmdSm=AT_CMD_PROCESS_ERROR;break;
		case AT_CMD_PROCESS_REC_RESP:
            break;
	}
    return 1;
}
*/

uint16_t nb_at_cmd_ex(const st_ATcmdDef* cmd,uint8_t* recbuf,uint16_t reclen)
{
	uint16_t sta=0;
	uint16_t len=0;
	uint16_t tryTm=0x00;
	if(!cmd)return 0;
	if(!recbuf)return 0;

	m_mem_set(recbuf,'\0',reclen);
	nb_uart_send_str((uint8_t*)(cmd->cmdStr));

	for(tryTm=0;tryTm<6;tryTm++){
		len=0;
		len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
		if(len<=2)continue;
		else
			break;
	}
    sta=m_str_match(recbuf,(uint8_t*)(cmd->okMatchStr));
	return len;


}

#if 0
uint8_t CIMI[16];
uint8_t	CGSN[16];
uint8_t	ICCID[21];
volatile bool nbFirstCattch=true;	
void nb_process_disable_sleep_in_lwp(void)
{
	noEventTimeOut=NO_EVEN_MAX_TIME_OUT;
}
void nb_process_enable_sleep_in_lwp(void)
{
	noEventTimeOut=0;
}
void nb_module_pwr_pins_init(void)
{
	m_gpio_set_mode(NB_PWR_PORT,NB_PWR_PINS,GPIO_MODE_OUTPUT_PP);
}

void nb_module_pwr_pins_deinit(void)
{
	m_gpio_set_mode(NB_PWR_PORT,NB_PWR_PINS,GPIO_MODE_ANALOG);
}

void nb_module_pwr_on(void)
{
	//if(nbiotModuleStatus.pwrOn)return;
	//if(nbiotDescInf.nbStatus>=NB_POWER_ON)return;
	m_gpio_write(NB_PWR_PORT,NB_PWR_PINS,NB_PWR_PINS);
	//nbiotModuleStatus.pwrOn=true;
	nbiotDescInf.nbStatus=NB_POWER_ON;
}

void nb_module_pwr_off(void)
{
	m_gpio_write(NB_PWR_PORT,NB_PWR_PINS,0);
	//nbiotModuleStatus.pwrOn=false;
	nbiotDescInf.nbStatus=NB_POWER_OFF;
}
// rst
void nb_module_rst_pins_init(void)
{
	m_gpio_set_mode(NB_RST_PORT,NB_RST_PINS,GPIO_MODE_OUTPUT_PP);
}

void nb_module_rst_pins_deinit(void)
{
	m_gpio_set_mode(NB_RST_PORT,NB_RST_PINS,GPIO_MODE_ANALOG);
}

void nb_module_reset_enable(void)
{
	//nb_module_rst_pins_init();
	m_gpio_write(NB_RST_PORT,NB_RST_PINS,NB_RST_PINS);
	//nbiotDescInf.nbStatus=NB_POWER_ON;
}

void nb_module_reset_disable(void)
{
	//nb_module_pwr_pins_deinit();
	m_gpio_write(NB_RST_PORT,NB_RST_PINS,0);
}

void nb_module_hal_init(void)
{
	nb_module_pwr_pins_init();
	nb_module_pwr_on();

}

void nb_module_hal_deinit(void)
{

}
//apl
void nb_routines_information_disp(uint8_t* str)
{
	m_lcd_disp_str_refresh(str);
}

uint16_t nb_at_cmd_waite_resp(uint8_t* rec,uint32_t tm,uint16_t receiveLen)
{
	uint16_t t16;
	osEvent event;
	//m_mem_set(rec,'\0',receiveLen);
	nb_process_disable_sleep_in_lwp();
	event=osSignalWait(flg_NB_MODULE_ALL_BITS,tm);
	
	if(event.status==osEventSignal){
		if(event.value.signals & flg_NB_MODULE_UART_RECEIVED_LF){
			//return uartRceivedBufCountUser;
			if(uartRceivedBufCountUser && (void*)rec){
				t16=uartRceivedBufCountUser;
				if(t16>receiveLen){
					t16=receiveLen;
				}
				if((void*)(rec)!=NULL && (void*)(rec) != (void*)(uartReceivedBufUser)){
					m_mem_cpy_len(rec,uartReceivedBufUser,t16);
				}
				return t16;
			}
		}
		if(event.value.signals & flg_NB_MODULE_UART_RECEIVED_ERROR){
			t16=0x00;
			m_uart4_deinit();
			osDelay(200);
			m_uart4_init();
			__nop();
		}
		
	}
	return 0;
}

uint16_t nb_at_cmd_ex(const st_ATcmdDef* cmd,uint8_t* recbuf,uint16_t reclen)
{
	uint16_t sta=0;
	uint16_t len=0;
	uint16_t tryTm=0x00;
	if(!cmd)return 0;
	if(!recbuf)return 0;
	nb_process_disable_sleep_in_lwp();
	#ifdef STM32L152xB
	osDelay(1000);
	#else
	osDelay(100);
	#endif
	m_mem_set(recbuf,'\0',reclen);
	m_uart_send_str((uint8_t*)(cmd->cmdStr));
	#if NBIOT_ROUTINES_DISP_EN
	nb_routines_information_disp((uint8_t*)(cmd->promptStr));
	#endif
	for(tryTm=0;tryTm<6;tryTm++){
		len=0;
		if(pwrStatus==POWER_STATUS_DOWN)return 0;
		len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
		if(len<=2)continue;
		else
			break;
	}
	if(!(cmd->retAssert)){
		nbiotDescInf.errCode=NO_ERROR;
		return len;
	}
	
	recbuf[len]='\0';
	if(!(cmd->retAssert)){
		sta=len;
	}else if(cmd->respStr){
		sta=m_str_cmp_ex(recbuf,(uint8_t*)(cmd->respStr));	
	}else if(cmd->okMatchStr){
		sta=m_str_match(recbuf,(uint8_t*)(cmd->okMatchStr));
	}
	tryTm=cmd->respExTimes;
	if(tryTm>3)tryTm=3;
	while(tryTm){

		if(pwrStatus==POWER_STATUS_DOWN)return 0;	
		nb_at_cmd_waite_resp(recbuf,3000,reclen);
		tryTm--;
	}
	__nop();
	if(!sta){
		nbiotDescInf.errCode=cmd->errcode;
		#if NBIOT_ROUTINES_DISP_EN
		nb_routines_information_disp((uint8_t*)(cmd->prompErrStr));
		#endif
		return 0;
	}else{
		nbiotDescInf.errCode=NO_ERROR;
		#if NBIOT_ROUTINES_DISP_EN
		nb_routines_information_disp((uint8_t*)(cmd->promptStr));
		#endif		
		return len;
	}
}

//apl 
uint16_t nb_module_reset_soft(void)
{

	uint16_t tryTm=0x00;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	
	nb_module_rst_pins_init();
	nb_module_reset_enable();
	osDelay(100);
	
	nb_module_reset_disable();
	//nb_module_rst_pins_deinit();
	
	//m_uart4_init();
	do{
		if(pwrStatus==POWER_STATUS_DOWN)return 0;
		nb_at_cmd_waite_resp(recbuf,1000,reclen);

		if(m_str_match(recbuf,(uint8_t*)"\r\nOK\r\n"))break;
		tryTm++;
	}while(tryTm<20);
	
	__nop();
	return 1;
}

int8_t nb_get_csq(void)
{
	uint8_t* p8;
	int16_t t16;
	int8_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	ret=nb_at_cmd_ex(&AT_CMD_CSQ,recbuf,reclen);
	do{
		if(!ret)break;
		ret=m_str_match_ex(recbuf,(uint8_t*)"+CSQ:",(uint16_t*)&t16);
		if(!ret)break;
		p8=recbuf+t16+sizeof("+CSQ:")-1;
		t16=0;
		while(*p8!=','){
			t16*=10;
			t16+=(*p8-'0');
			p8++;
			if(t16>100)break;
		}
		ret=(int8_t)t16;
	}while(0);
	if(ret>=0 && ret<=31){
		ret=-113+(ret*2);
	}else{
		ret=-127;
	}
	return ret;
}

uint16_t nb_extract_cimi(uint8_t* recbuf,uint16_t reclen,uint8_t* cimi)
{
	__nop();
	if(reclen<19)return 0;
	m_mem_cpy_len(cimi,recbuf+2,15);
	cimi[15]='\0';
	return 1;
}

uint16_t nb_extract_cgsn(uint8_t* recbuf,uint16_t reclen,uint8_t* cgsn)
{
	__nop();
	if(reclen<30)return 0;
	m_mem_cpy_len(cgsn,recbuf+8,15);
	cgsn[15]='\0';
	return 1;
}

uint16_t nb_extract_nccid(uint8_t* recbuf,uint16_t reclen,uint8_t* nccid)
{
	__nop();
	if(reclen<36)return 0;
	m_mem_cpy_len(nccid,recbuf+9,20);
	nccid[20]='\0';
	return 1;
}
uint16_t nb_module_nbr(void)
{
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	return nb_at_cmd_ex(&AT_CMD_NRB,recbuf,reclen);
}
uint16_t nb_module_cfun_off(void)
{
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	return nb_at_cmd_ex(&AT_CMD_CFUN_0,recbuf,reclen);
}
#if config_NB_PLAT==UDP
uint16_t nb_attach_network(void)
{
	uint32_t tm;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tryTm,ret;
	//nb_module_pwr_on();
	//osDelay(1000);
	//if(nbiotDescInf.nbStatus>=NB_CGATTED)return 1;
	if(!(nb_at_cmd_ex(&AT_CMD_AT,recbuf,reclen)))return 0;

	
	nb_at_cmd_ex(&AT_CMD_CFUN,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_CFUN_R,recbuf,reclen);
	
	nb_at_cmd_ex(&AT_CMD_CMI,recbuf,reclen);
	nb_extract_cimi(recbuf,reclen,CIMI);
	
	nb_at_cmd_ex(&AT_CMD_NCCID,recbuf,reclen);
	nb_extract_nccid(recbuf,reclen,ICCID);
	
	nb_at_cmd_ex(&AT_CMD_CGSN,recbuf,reclen);
	nb_extract_cgsn(recbuf,reclen,CGSN);
	
	
	nb_at_cmd_ex(&AT_CMD_CSQ,recbuf,reclen);
	
	tryTm=0;
	while(tryTm<5){
		tryTm++;
		ret=nb_at_cmd_ex(&AT_CMD_CGDCONT,recbuf,reclen);
		if(ret)break;
		osDelay(1000);
	}
	if(tryTm>=5)return 0;
	//nb_at_cmd_ex(&AT_CMD_CGDCONT,recbuf,reclen);
	//osDelay(4000);
	 tryTm=0;
	while(tryTm<10){	
		tryTm++;
		ret=nb_at_cmd_ex(&AT_CMD_CGATT,recbuf,reclen);
		if(ret)break;
	};
	if(tryTm>=10)return 0;
	
	tryTm=0;
	tm=osKernelSysTick();
	while(tryTm<100){
		tryTm++;
		osDelay(1000);
		ret=nb_at_cmd_ex(&AT_CMD_CGATT_R,recbuf,reclen);
		if(osKernelSysTick()-tm>100*1000)break;
		if(ret)break;
	};
	if(tryTm>=100){
		nbiotDescInf.nbStatus=NB_ERROR;
		return 0;
	}
	nbiotDescInf.nbStatus=NB_CGATTED;
	rssi=nb_get_csq();
	return 1;

}
#else
/*
at
at+cfun=0
at+cfun=1
AT+CFUN?
AT+CGDCONT=1,"IP","ctnb"
AT+CGDCONT=1,"IP","HUAWEI.COM"
at+cgatt=1
at+cgatt=?
at+csq
AT+NCDP=180.101.147.115

AT+NCDP?
AT+CGPADDR
AT+NSMI=1
AT+NNMI=2
AT+NMGS=44,2A0341B2000020006C13B82200901C2208940A8F9DDE7D8800E358E650BA6CB443E57DEF622F2A452DEE8A97
AT+NMGS=45,002A0341B2000020006C13B82200901C2208940A8F9DDE7D8800E358E650BA6CB443E57DEF622F2A452DEE8A97
AT+NMGS=30, 303132333435363738393031323334353637383930313233343536373839
AT+NMGS=2, AA72
AT+NMGS=8, AA72AA72AA72AA72
AT+NQMGS
AT+NQMGR
AT+NMGR
AT+NQMGR
*/
extern uint16_t nb_coap_ncbp(void);
uint16_t nb_attach_network_coap(void)
{
	uint32_t tm;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tryTm,ret;
	
	if(!(nb_at_cmd_ex(&AT_CMD_AT,recbuf,reclen)))return 0;
	nb_at_cmd_ex(&AT_CMD_ATI,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_CMEE,recbuf,reclen);
	//nb_at_cmd_ex(&AT_CMD_CFUN_0,recbuf,reclen);
	
	nb_at_cmd_ex(&AT_CMD_CFUN,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_CFUN_R,recbuf,reclen);
	
	//nb_at_cmd_ex(&AT_CMD_CFUN,recbuf,reclen);
	//nb_at_cmd_ex(&AT_CMD_CFUN_R,recbuf,reclen);
	
	nb_at_cmd_ex(&AT_CMD_CMI,recbuf,reclen);
	nb_extract_cimi(recbuf,reclen,CIMI);
	
	nb_at_cmd_ex(&AT_CMD_NCCID,recbuf,reclen);
	nb_extract_nccid(recbuf,reclen,ICCID);
	
	nb_at_cmd_ex(&AT_CMD_CGSN,recbuf,reclen);
	nb_extract_cgsn(recbuf,reclen,CGSN);
	
	nb_at_cmd_ex(&AT_CMD_CSQ,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_CMEE,recbuf,reclen);
	
	nb_at_cmd_ex(&AT_CMD_CGMR,recbuf,reclen);
	
	
	tryTm=0;
	while(tryTm<5){
		if(pwrStatus==POWER_STATUS_DOWN)return 0;
		tryTm++;
		ret=nb_at_cmd_ex(&AT_CMD_CGDCONT_COAP,recbuf,reclen);
		if(ret)break;
		osDelay(1000);
	}
	if(tryTm>=5)return 0;
	
	do{
		
		ret=nb_at_cmd_ex(&AT_CMD_NCDP_R,recbuf,reclen);	
		__nop();
		if(m_str_match(recbuf,(uint8_t*)IOT_IP)){
			ret=1;break;
		}
		nb_at_cmd_ex(&AT_CMD_CFUN_0,recbuf,reclen);
		ret=nb_coap_ncbp();
		//ret=nb_at_cmd_ex(&AT_CMD_NRB,recbuf,reclen);	
		return 0;
	}while(0);
	
	

	 tryTm=0;
	while(tryTm<10){	
		if(pwrStatus==POWER_STATUS_DOWN)return 0;
		tryTm++;
		ret=nb_at_cmd_ex(&AT_CMD_CGATT,recbuf,reclen);
		if(ret)break;
	};
	if(tryTm>=10)return 0;
	
	tryTm=0;
	tm=osKernelSysTick();
	while(tryTm<100){
		if(pwrStatus==POWER_STATUS_DOWN)return 0;
		tryTm++;
		osDelay(1000);
		ret=nb_at_cmd_ex(&AT_CMD_CGATT_R,recbuf,reclen);
		if(osKernelSysTick()-tm>100*1000)break;
		if(ret)break;
	};
	if(tryTm>=100){
		nbiotDescInf.nbStatus=NB_ERROR;
		return 0;
	}
	nbiotDescInf.nbStatus=NB_CGATTED;
	rssi=nb_get_csq();
	nb_at_cmd_ex(&AT_CMD_NUESTATS,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_QSECSWT_S,recbuf,reclen);
	nb_at_cmd_ex(&AT_CMD_QSECSWT,recbuf,reclen);
	
	return 1;

}	
#endif

#if config_NB_PLAT==UDP
uint16_t nb_udp_cereg(void)
{
	uint16_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tyrtm=10;	
	while(tyrtm){
		ret=nb_at_cmd_ex(&AT_CMD_CEREG_R,recbuf,reclen);
		if(ret)break;
		nb_at_cmd_ex(&AT_CMD_CEREG,recbuf,reclen);
		__nop();
		osDelay(1000);
		tyrtm--;

	}
	return tyrtm;

}
#else
uint16_t nb_udp_cereg_coap(void)
{
	uint16_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tyrtm=10;	
	while(tyrtm){
		ret=nb_at_cmd_ex(&AT_CMD_CGPADDR,recbuf,reclen);
		if(ret)break;
		//nb_at_cmd_ex(&AT_CMD_CEREG,recbuf,reclen);
		//__nop();
		osDelay(1000);
		tyrtm--;

	}
	return tyrtm;

}	
#endif

uint16_t nb_get_cereg(void)
{
	uint16_t ret;
	#if config_NB_PLAT==UDP
	ret=nb_udp_cereg();
	#else
	ret=nb_udp_cereg_coap();
	#endif
	return ret;
}
#if config_NB_PLAT==UDP
uint16_t nb_udp_create_socket(void)
{
	uint16_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tyrtm=4;
	//if(nbiotDescInf.nbStatus>=NB_UPD_CONNECTED)return 1;
	while(tyrtm){
		tyrtm--;
		//nb_at_cmd_ex(&AT_CMD_NSOCL,recbuf,reclen);
		__nop();

		ret=nb_at_cmd_ex(&AT_CMD_NSOCR,recbuf,reclen);
		if(ret)break;
		nb_at_cmd_ex(&AT_CMD_NSOCL,recbuf,reclen);

	}
	if(tyrtm){
		nbiotDescInf.nbStatus=NB_CONNECTED;
	}else{
		nbiotDescInf.nbStatus=NB_ERROR;
	}
	return tyrtm;
}
#else
//const uint8_t testNcdp[]="AT+NCDP=117.60.157.137,5684\r\n";
uint16_t nb_coap_ncbp(void)
{
	st_ATcmdDef atcmdTemp={0};
	
	uint16_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tyrtm=4;
	m_mem_cpy_len((uint8_t*)&atcmdTemp,(uint8_t*)&AT_CMD_NCDP,sizeof(st_ATcmdDef));
	atcmdTemp.cmdStr=sysData.venderUdpSetting;
	//atcmdTemp.cmdStr=testNcdp;
	while(tyrtm){
		tyrtm--;
		__nop();
		//ret=nb_at_cmd_ex(&AT_CMD_NCDP,recbuf,reclen);
		ret=nb_at_cmd_ex(&atcmdTemp,recbuf,reclen);
		if(ret)break;
		//nb_at_cmd_ex(&AT_CMD_NSOCL,recbuf,reclen);
	}
	if(!tyrtm)return tyrtm;
	
	tyrtm=4;
	while(tyrtm){
		tyrtm--;
		__nop();
		ret=nb_at_cmd_ex(&AT_CMD_NCDP_R,recbuf,reclen);
		if(ret)break;
	}	
	if(tyrtm){
		nbiotDescInf.nbStatus=NB_CONNECTED;
	}else{
		nbiotDescInf.nbStatus=NB_ERROR;
	}
	return tyrtm;
}	
#endif
uint16_t nb_create_socket(void)
{
	#if config_NB_PLAT==UDP
	return  nb_udp_create_socket();
	#else
	//return nb_coap_ncbp();
	return 1;
	#endif
}

void nb_udp_close_socket(void)
{
	//uint16_t ret;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	nb_at_cmd_ex(&AT_CMD_NSOCL,recbuf,reclen);
	nbiotDescInf.nbStatus=NB_CGATTED;
}

uint16_t nb_udp_send_test(void)
{
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	uint16_t ret;
	ret=nb_at_cmd_ex(&AT_CMD_NSOCT,recbuf,reclen);
	return ret;
}


#if config_NB_PLAT==UDP
const uint8_t testUdpSetting[]="211.149.175.111,2200";
uint8_t* nb_udp_send_load(uint8_t* buf,uint16_t len,uint16_t ipidex)
{
	uint16_t t16,ret;
	uint8_t tmpBuf[256];
	uint8_t* d=tmpBuf;
	uint8_t* ipsettins=NULL;	
	
	ret=m_str_cpy(d,(uint8_t*)"AT+NSOST=0,");
	
	t16=ret-1;
	d+=(ret-1);
	if(sysData.DLCS<DLC_STATUS_B){
		ipsettins=(uint8_t*)testUdpSetting;
	}else{
		if(ipidex==0){
			ipsettins=sysData.venderUdpSetting;
		}else{
			ipsettins=sysData.userUdpSetting;
			//ipsettins=(uint8_t*)testUdpSetting;
		}
	}
	ret=m_str_cpy(d,ipsettins);
	d[ret-1]=',';

	t16+=(ret);
	d+=(ret);
	ret=int32_2_d(d,len);
	
	t16+=ret;
	d+=ret;
	*d++=',';
	t16+=1;
	
	ret=m_str_b2h(d,buf,len);
	d+=ret;
	t16+=ret;
	
	*d++='\r';
	*d++='\n';
	*d++='\0';
	
	t16+=3;
	
	m_mem_cpy_len(nbAplSendBuffer,tmpBuf,t16);
	return nbAplSendBuffer;

}
#else
//const uint8_t testUdpSetting[]="211.149.175.111,2200";
uint8_t* nb_udp_send_load_coap(uint8_t* buf,uint16_t len,uint16_t ipidex)
{
	uint16_t t16,ret;
	uint8_t tmpBuf[256];
	//tmpBuf[0]='0';
	//tmpBuf[1]='0';
	uint8_t* d=tmpBuf;
	//uint8_t* ipsettins=NULL;	
	
	ret=m_str_cpy(d,(uint8_t*)"AT+NMGS=");
	
	t16=ret-1;
	d+=(ret-1);

	ret=int32_2_d(d,len+1);
	t16+=ret;
	d+=ret;
	*d++=',';
	t16+=1;
	
	*d++='0';
	*d++='0';
	t16+=2;
	
	ret=m_str_b2h(d,buf,len);
	d+=ret;
	t16+=ret;
	
	*d++='\r';
	*d++='\n';
	*d++='\0';
	
	t16+=3;
	
	m_mem_cpy_len(nbAplSendBuffer,tmpBuf,t16);
	return nbAplSendBuffer;

}	
#endif
#if config_NB_PLAT==UDP
uint16_t nb_udp_send(uint8_t* buf,uint16_t len)
{
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	
	nb_process_disable_sleep_in_lwp();
	//nb_udp_create_socket();
	
	m_mem_set(nbAplReceivedBuffer,'\0',sizeof(nbAplReceivedBuffer));
	uint8_t tmpbuf[20]={0};
	
	uint16_t tryTm,ret;
	uint8_t* str;
	m_mem_cpy(tmpbuf,(uint8_t*)"\r\n0,");
	int32_2_d(tmpbuf+4,len);
	str=nb_udp_send_load(buf,len,0);
	m_uart_send_str(str);
	#if NBIOT_ROUTINES_DISP_EN
	nb_routines_information_disp((uint8_t*)("send-"));
	#endif	
	
	for(tryTm=0;tryTm<5;tryTm++){
		len=0;
		if(pwrStatus==POWER_STATUS_DOWN)break;
		
		len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
		__nop();
		if(len<=2)continue;
		else{
			//break;
			__nop();
			ret=m_str_cmp(recbuf,tmpbuf);
			if(ret)break;
		}
	}
	__nop();
	nb_process_disable_sleep_in_lwp();
	for(tryTm=0;tryTm<5;tryTm++){
		len=0;ret=0;
		if(pwrStatus==POWER_STATUS_DOWN)break;	
		len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
		__nop();
		if(len<=2)continue;
		else{
			ret=m_str_cmp(recbuf,(uint8_t*)"+NSONMI:0,");
			if(ret)break;
			break;
		}
	}	
	//nb_udp_close_socket();
	return ret;
}
#else
uint16_t nb_udp_send_coap(uint8_t* buf,uint16_t len)
{
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	
	nb_process_disable_sleep_in_lwp();
	//nb_udp_create_socket();
	
	m_mem_set(nbAplReceivedBuffer,'\0',sizeof(nbAplReceivedBuffer));
	//uint8_t tmpbuf[20]={0};
	
	uint16_t tryTm,ret,sendTime;
	uint8_t* str;
	//m_mem_cpy(tmpbuf,(uint8_t*)"\r\n0,");
	//int32_2_d(tmpbuf+4,len);
	str=nb_udp_send_load_coap(buf,len,0);
	sendTime=0x00;
	do{
		ret=0;
		if(pwrStatus==POWER_STATUS_DOWN)break;	
		m_uart_send_str(str);
		#if NBIOT_ROUTINES_DISP_EN
		nb_routines_information_disp((uint8_t*)("send-"));
		#endif	
		
		for(tryTm=0;tryTm<5;tryTm++){
			len=0;ret=0;
			if(pwrStatus==POWER_STATUS_DOWN)break;		
			len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
			__nop();
			if(len<=2)continue;
			else{
				//break;
				__nop();
				ret=m_str_match(recbuf,(uint8_t*)"OK\r\n");
				if(ret)break;
				if(m_str_match(recbuf,(uint8_t*)"ERROR:513\r\n")){
					ret=0;
					__nop();
					break;
				}
			}
		}
		__nop();
		if(ret>0)break;
		ret=0;
		if(pwrStatus==POWER_STATUS_DOWN)break;	
		nb_process_disable_sleep_in_lwp();
		osDelay(10000);
		
	}while(sendTime++<3);
	if(ret==0 && sendTime>3){
		nbFirstCattch=true;
	}
	nb_process_disable_sleep_in_lwp();
	//nb_udp_close_socket();
	return ret;
}	
#endif

#if config_NB_PLAT==UDP
uint16_t np_udp_received_extract(uint8_t* str,uint8_t* bin,uint16_t len)
{
	uint8_t t8=0;
	uint16_t i;
	uint16_t t16,ret;
	t16=0;
	//if()
	for(i=0;i<len;i++){
		if(str[i]==',')t8++;
		if(t8==3 && str[i]!=','){
			t16*=10;
			t16+=(str[i]-'0');
		}
		if(t8==4)break;
	}
	if(t8!=4)return 0;
	if(t16>len)return 0;
	t16<<=1;
	str=str+i+1;
	ret=m_str_h2b(bin,str,t16);
	return ret;
}

uint16_t nb_udp_received_test(void)
{
	uartRceivedBufCount=0;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	uint16_t ret;
	ret=nb_at_cmd_ex(&AT_CMD_NSORF,recbuf,reclen);
	return ret;
}

#else

uint16_t my_scanf_int16(uint8_t* str,uint8_t eof,uint16_t* loc)
{
	uint16_t t16,i=0;
	uint16_t ret=0x00;
	uint8_t chr;
	do{
		chr=*str;
		if(chr==eof)break;
		ret*=10;
		
		t16=0;
		_chr2hex(t16,chr);
		ret += t16;
		str++;
		i++;
		if(i>=4)break;
		//;
	}while(1);
	if(loc){
		*loc=i;
	}
	return ret;
}
uint16_t np_udp_received_extract_coap(uint8_t* str,uint8_t* bin,uint16_t len)
{
	//uint8_t t8=0;
	uint16_t i;
	uint16_t t16,ret,loc;
	t16=0;
	//if()
	m_str_match_ex(str,(uint8_t*)("\r\n"),&loc);
	t16=my_scanf_int16(str+2+loc,',',&i);
	t16<<=1;
	str=str+i+3;
	ret=m_str_h2b(bin,str,t16);
	return ret;
}
uint16_t nb_udp_received_coap(void)
{
	uint32_t tm;
	uint16_t t16;
	//uint16_t loc;
	uint16_t tryTm=0x00;
	uint16_t ret;
	uartRceivedBufCount=0;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);	
	tm=osKernelSysTick();
	do{
		ret=0;
		if((osKernelSysTick()-tm)>40*1000)break;
		
		osDelay(1000);
		tryTm++;
		//if(tryTm>30)break;
		ret=nb_at_cmd_ex(&AT_CMD_NQMGR,recbuf,reclen);
		if(!ret)continue;
		m_str_match_ex(recbuf,(uint8_t*)("BUFFERED="),&t16);
		//if(t16)
		ret=my_scanf_int16(recbuf+9+t16,',',NULL);
		if(ret==0)continue;
		osDelay(2000);
		m_mem_set(nbAplReceivedBuffer,0,sizeof(nbAplReceivedBuffer));
		ret=nb_at_cmd_ex(&AT_CMD_NMGR,recbuf,reclen);
		//np_udp_received_extract_coap();
		__nop();
		
		if(!ret)continue;
		__nop();
		break;
	}while(1);
	return ret;
}
#endif

uint16_t np_received_extract_process(uint8_t* str,uint8_t* bin,uint16_t len)
{
	uint16_t ret;
	#if config_NB_PLAT==UDP
		ret=np_udp_received_extract(str,bin,len);
	#else
		ret=np_udp_received_extract_coap(str,bin,len);
	#endif
	return ret;
}
/*
const  uint8_t TestBuff[]={
0x11,0x03,0xFD,0xEB,0x00,0x00,0x21,0x05,0x04,0x00,0xB8,0x22,0x43,0x00,0x00,0x07,0x35,0x2D,0x33};
*/
uint16_t nb_power_on_process_waite_ok(void)
{

	uint32_t tmSta=0,tm=0;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	
	m_mem_set(nbAplReceivedBuffer,0,sizeof(nbAplReceivedBuffer));
	
	tmSta=osKernelSysTick();
	do{
		nb_process_enable_sleep_in_lwp();

		if(pwrStatus==POWER_STATUS_DOWN)return 0;		
		nb_at_cmd_waite_resp(recbuf,1000,reclen);
		tm=osKernelSysTick()-tmSta;
		if(m_str_match(recbuf,(uint8_t*)"\r\nOK\r\n"))break;
		//tryTm++;
		
		if(tm>10000)break;
	}while(1);
	if(tm<10000){
		return 1;
	}else{
		nbiotDescInf.nbStatus=NB_ERROR;
		return 0;
	}
		
}
uint16_t nb_power_on_process(void)
{
	uint16_t ret=0;
	uint16_t tryTm=0;
	//if(nbiotDescInf.nbStatus>=NB_UPD_CONNECTED)return 1;
	menu=0x00;
	subMenu=subMENU_MAIN_HOME_NB_ATTACH;	
	ui_disp_menu(0);
	m_uart4_deinit();
	nb_module_rst_pins_init();
	nb_module_reset_disable();
	nb_module_pwr_pins_init();
	m_uart4_init();
	do{
		nb_process_enable_sleep_in_lwp();
		nb_module_pwr_on();
		if(nb_power_on_process_waite_ok())break;
		tryTm++;
		nb_module_pwr_off();
		osDelay(1000);
	}while(tryTm<3);	
	if(tryTm>=3)return 0;
	#if config_NB_PLAT==UDP
	ret=nb_attach_network();
	#else
	tryTm=2;
	while(tryTm){
		ret=nb_attach_network_coap();	
		if(ret)break;
		tryTm--;
		//ret=nb_at_cmd_ex(&AT_CMD_NRB,recbuf,reclen);	
		ret=nb_module_nbr();
		osDelay(1000);
 		nb_power_on_process_waite_ok();
		__nop();
	}
	#endif
	if(ret){
		nbiotDescInf.nbStatus=NB_CONNECTED;
		return ret;
	}else{
		nbiotDescInf.nbStatus=NB_ERROR;
		return 0;
	}
}



uint16_t nb_send_process(uint8_t* buf,uint16_t len)
{
	if(pwrStatus==POWER_STATUS_DOWN)return 0;
	menu=0x00;
	subMenu=subMENU_MAIN_HOME_NB_SEND;	
	ui_disp_menu(0);
	#if config_NB_PLAT==UDP
	nb_udp_send(buf,len);
	#else
	nb_udp_send_coap(buf,len);	
	#endif
	//subMenu=0;
	return 1;
}

uint16_t nb_received_process(void)
{
	uint16_t ret;
	menu=0x00;
	subMenu=subMENU_MAIN_HOME_NB_RECEIVED;	
	ui_disp_menu(0);
	#if config_NB_PLAT==UDP
	ret=nb_udp_received_test();
	#else
	ret=nb_udp_received_coap();	
	#endif
	return ret;
}

uint16_t nb_power_off_process(void)
{
	nb_process_disable_sleep_in_lwp();
	//menu=0x00;
	//subMenu=0;	
	ui_disp_menu(0);	
	m_uart4_deinit();	
	nb_module_pwr_pins_init();
	nb_module_pwr_off();
	osDelay(1000);
	return 1;
}

typedef enum{
	NB_SEND_POP,
	NB_SEND_ACK,
}nbSendType_t;

void delay_long_lwp_dis(uint16_t sec)
{
	//return ;
	#if config_NB_PLAT==UDP
	while(sec){
		nb_process_disable_sleep_in_lwp();
		sec--;
		osDelay(1000);
	}
	#else
	__nop();
	#endif
	
}

void delay_long_lwp_dis_ex(uint16_t sec)
{

	while(sec){
		nb_process_disable_sleep_in_lwp();
		sec--;
		osDelay(1000);
	}

}

#if config_NB_PSM_EN ==0 
void vTheadUdp(void * pvParameters)
{
	osEvent event;
	uint8_t buf[128];
	uint16_t ret,sendNum=0,subSendNum=0x00;
	uint16_t len;//,t16=10;
	(void)pvParameters;	
	//nbSendType_t sendType=NB_SEND_POP;
	em_15sOpRetCode bkupOpRetCode=__15S_OP_NOTHING;
	while(1){
		event=osSignalWait(flg_NB_MODULE_UDP_PROCESS_REQ,osWaitForever);
		if(event.value.signals & flg_NB_MODULE_UDP_PROCESS_REQ){
			if(pwrStatus<POWER_STATUS_LOW)continue;
			sendNum=0;

			do{
				nb_process_disable_sleep_in_lwp();
				ret=nb_power_on_process();
				if(!ret)break;
				nb_create_socket();
				protocolCmd=0xff;
				opRetCode=__15S_OP_NOTHING;
				sendNum=0;
				subSendNum=0;
				
				do{
					nb_process_disable_sleep_in_lwp();
					if(opRetCode ==__15S_OP_OK || opRetCode==__15S_OP_PAY_OK ){
						len=qc_comm_send_pop_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_RET_CLEAR);			
					}else if(opRetCode == __15S_OP_SEND_ACK || opRetCode ==__15S_OP_STEP_PRICE_ERR || \
						opRetCode == __15S_OP_PAY_OVER || opRetCode == __15S_OP_PAY_VERIFY 
						||opRetCode == __15S_OP_NOT_MINE || opRetCode==__15S_OP_KEY_UPDATE_ERR){
						//2018.03.28,??????????
						if(opRetCode == __15S_OP_PAY_VERIFY && sendNum<16)sendNum=16;						
						if(opRetCode == __15S_OP_SEND_ACK){opRetCode=bkupOpRetCode;}
						len=qc_comm_ins_reply_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_DATA);
						opRetCode=__15S_OP_NOTHING;
						
					}else{
						len=qc_comm_send_pop_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_DATA);	
					}

					if(subSendNum>=4){delay_long_lwp_dis(50);subSendNum=0x00;}
					if(nb_get_cereg()==0)break;

					nb_send_process(nbAplSendBuffer,len);
					sendNum++;
					subSendNum++;
					
					//if(opRetCode ==__15S_OP_OK || opRetCode==__15S_OP_PAY_OK ){
					if(opRetCode ==__15S_OP_OK || opRetCode==__15S_OP_PAY_OK ){					
						bkupOpRetCode=opRetCode;
						opRetCode=__15S_OP_SEND_ACK;
						continue;
					}
					
					ret=nb_received_process();
					if(!ret){break;}
					ret=np_received_extract_process(nbAplReceivedBuffer,buf,ret);
					
					if(ret>sizeof(buf))ret=sizeof(buf);
					m_mem_cpy_len(nbAplReceivedBuffer,buf,ret);
				
					ret=qc_comm_received_process(nbAplReceivedBuffer,ret);
				
					if(ret==0 || opRetCode == __15S_OP_NOTHING || opRetCode==__15S_OP_RTC_SYNC)break;
					if(sendNum>=21)break;
					if(pwrStatus==POWER_STATUS_DOWN)break;

				}while(1);
				//????
				opRetCode=__15S_OP_NOTHING;
				break;
			}while(1);
			__nop();
			//nb_udp_close_socket();
			nb_power_off_process();
			//nb_udp_close_socket();
			if(!(sysData.DLCS==DLC_STATUS_A && !fi_id_writed_in_dlcs_a())){
				menu=7;
				subMenu=0;
			}
		}
		data_api_day_change();
		//test 
		#if SEND_TIMES_TEST
		if(sysData.DLCS==DLC_STATUS_C){
			nb_process_disable_sleep_in_lwp();
			menu=0;
			subMenu=subMENU_MAIN_SEND_TIMES;
			osDelay(5000);
			even_send_msg_to_start_rf(false);
		}
		#endif
	}	
}
#else

nbPsmStateMachine_t nbPsmStateMachine=NB_PSM_SM_NRZ;
uint16_t nb_coap_enter_psm(void)
{
	//uint8_t* recbuf=nbAplReceivedBuffer;
	//uint16_t reclen=sizeof(nbAplReceivedBuffer);
	if(nbPsmStateMachine!=NB_PSM_SM_NRZ)nbPsmStateMachine=NB_PSM_SM_PSM;
	osDelay(1000);
	return 1;
}
uint16_t nb_coap_psm_send_ready(void)
{
	uint32_t tm;
	uint8_t* recbuf=nbAplReceivedBuffer;
	uint16_t reclen=sizeof(nbAplReceivedBuffer);
	uint16_t tryTm,ret;	
	tryTm=0;

	menu=0x00;
	subMenu=subMENU_MAIN_HOME_NB_ATTACH;	
	ui_disp_menu(0);	
	
	//nbPsmStateMachine=NB_PSM_SM_AT;
	m_uart4_deinit();
	osDelay(1000);
	m_uart4_init();
	if(nbPsmStateMachine== NB_PSM_SM_NRZ){
		
	}else if(nbPsmStateMachine==NB_PSM_SM_PSM){
		nbPsmStateMachine=NB_PSM_SM_NCDPR;
	}else{nbPsmStateMachine=NB_PSM_SM_AT;}
	__nop();
	tm=osKernelSysTick();
	while(tryTm<=20){
		//tryTm++;
		if((osKernelSysTick()-tm)>120000){
			nbPsmStateMachine=NB_PSM_SM_NO_NET;break;
		}
		if(pwrStatus<POWER_STATUS_LOW){
			nbPsmStateMachine= NB_PSM_SM_NRZ;break;
		}
		switch(nbPsmStateMachine){
		case NB_PSM_SM_NRZ:
			ret=nb_module_nbr();
			osDelay(1000);
			nb_power_on_process_waite_ok();
			__nop();
			nbPsmStateMachine=NB_PSM_SM_AT;
			break;
		case NB_PSM_SM_AT:
			nb_at_cmd_ex(&AT_CMD_AT,recbuf,reclen);
			ret=nb_at_cmd_ex(&AT_CMD_AT,recbuf,reclen);
			if(ret){nbPsmStateMachine=NB_PSM_SM_ATI;}
			else{tryTm++;nbPsmStateMachine=NB_PSM_SM_NRZ;}
			break;
		case NB_PSM_SM_ATI:
			nb_at_cmd_ex(&AT_CMD_ATI,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CMEE;
			break;
		case NB_PSM_SM_CMEE:
			nb_at_cmd_ex(&AT_CMD_CMEE,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CGMR;
			break;
		case NB_PSM_SM_CGMR:
			nb_at_cmd_ex(&AT_CMD_CGMR,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CFUNR;
			break;
		case NB_PSM_SM_CFUN:
			nb_at_cmd_ex(&AT_CMD_CFUN,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CFUNR;
			break;
		case NB_PSM_SM_CFUNR:
			ret=nb_at_cmd_ex(&AT_CMD_CFUN_R,recbuf,reclen);
			if(ret){nbPsmStateMachine=NB_PSM_SM_CGCCONT_R;}
			else{tryTm++;nbPsmStateMachine=NB_PSM_SM_CFUN;}
			break;
		case NB_PSM_SM_CGCCONT:
			ret=nb_at_cmd_ex(&AT_CMD_CGDCONT_COAP,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CGCCONT_R;
			//if(ret){nbPsmStateMachine=NB_PSM_SM_NCDPR;}
			//else{tryTm++;nbPsmStateMachine=NB_PSM_SM_CGCCONT;}
			break;
		case NB_PSM_SM_CGCCONT_R:
			ret=nb_at_cmd_ex(&AT_CMD_CGDCONT_R,recbuf,reclen);
			if(ret){nbPsmStateMachine=NB_PSM_SM_NCDPR;}
			else{tryTm++;nbPsmStateMachine=NB_PSM_SM_CGCCONT;}
			break;
		case NB_PSM_SM_NCDP:
			nb_at_cmd_ex(&AT_CMD_CFUN_0,recbuf,reclen);
			ret=nb_coap_ncbp();
			tryTm++;
			nbPsmStateMachine=NB_PSM_SM_NRZ;
			break;
		case NB_PSM_SM_NCDPR:
			ret=nb_at_cmd_ex(&AT_CMD_NCDP_R,recbuf,reclen);	
			if(!ret){nbPsmStateMachine=NB_PSM_SM_NCDP;break;}
			
			if(m_str_match(recbuf,(uint8_t*)IOT_IP)){
				nbPsmStateMachine=NB_PSM_SM_CGATTR_FAST;
			}else{
				nbPsmStateMachine=NB_PSM_SM_NCDP;
			}
			break;
		case NB_PSM_SM_CGATT:
			ret=nb_at_cmd_ex(&AT_CMD_CGATT,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_CGATTR_SLOW;
			break;
		case NB_PSM_SM_CGATTR_SLOW:
			tm=osKernelSysTick();
			while(1){
				ret=nb_at_cmd_ex(&AT_CMD_CGATT_R,recbuf,reclen);
				if(ret){nbPsmStateMachine=NB_PSM_SM_CIMI;break;}
				else{
					osDelay(2000);
					if(osKernelSysTick()-tm>=100*1000){
						nbPsmStateMachine=NB_PSM_SM_NO_NET;break;
					}
					continue;
				}
			}
			break;			
		case NB_PSM_SM_CGATTR_FAST:
			ret=nb_at_cmd_ex(&AT_CMD_CGATT_R,recbuf,reclen);
			if(ret){nbPsmStateMachine=NB_PSM_SM_CIMI;}
			else{nbPsmStateMachine=NB_PSM_SM_CGATT;}
			break;
		case NB_PSM_SM_CIMI:
			nb_at_cmd_ex(&AT_CMD_CMI,recbuf,reclen);
			nb_extract_cimi(recbuf,reclen,CIMI);
			nbPsmStateMachine=NB_PSM_SM_NCCID;
			break;
		case NB_PSM_SM_NCCID:
			nb_at_cmd_ex(&AT_CMD_NCCID,recbuf,reclen);
			nb_extract_nccid(recbuf,reclen,ICCID);	
			nbPsmStateMachine=NB_PSM_SM_CGSN;
			break;
		case NB_PSM_SM_CGSN:
			nb_at_cmd_ex(&AT_CMD_CGSN,recbuf,reclen);
			nb_extract_cgsn(recbuf,reclen,CGSN);
			nbPsmStateMachine=NB_PSM_SM_CSQ;
			break;
		case NB_PSM_SM_CSQ:
			nb_at_cmd_ex(&AT_CMD_CSQ,recbuf,reclen);
			rssi=nb_get_csq();
			nbPsmStateMachine=NB_PSM_SM_NUESTATS;
			break;
		case NB_PSM_SM_NUESTATS:
			nb_at_cmd_ex(&AT_CMD_NUESTATS,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_QSECSWT;
			break;
		case NB_PSM_SM_QSECSWT:
			nb_at_cmd_ex(&AT_CMD_QSECSWT_S,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_QSECSWT_R;
			break;
		case NB_PSM_SM_QSECSWT_R:
			nb_at_cmd_ex(&AT_CMD_QSECSWT,recbuf,reclen);
			nbPsmStateMachine=NB_PSM_SM_SEND;
			break;
		default:
			nbPsmStateMachine=NB_PSM_SM_NO_NET;
			break;
		}
		
		if(nbPsmStateMachine==NB_PSM_SM_SEND || nbPsmStateMachine==NB_PSM_SM_NO_NET)break;
	};
	if(nbPsmStateMachine!=NB_PSM_SM_SEND){
		nb_module_cfun_off();
	}
	return 1;
}
void vTheadUdpPsm(void * pvParameters)
{
	osEvent event;
	uint8_t buf[128];
	uint16_t ret,sendNum=0,subSendNum=0x00;
	uint16_t len;//,t16=10;
	uint16_t rtcSyncTm=0;
	bool exitEnable=false;
	(void)pvParameters;	

	em_15sOpRetCode bkupOpRetCode=__15S_OP_NOTHING;
	while(1){
		event=osSignalWait(flg_NB_MODULE_UDP_PROCESS_REQ,osWaitForever);
		if(event.value.signals & flg_NB_MODULE_UDP_PROCESS_REQ){
			if(pwrStatus<POWER_STATUS_LOW)continue;
			sendNum=0;
			rtcSyncTm=0;
			nb_coap_psm_send_ready();
			if(nbPsmStateMachine!=NB_PSM_SM_SEND){
				nbPsmStateMachine=NB_PSM_SM_NRZ;
				continue;
			}
			
			nb_create_socket();
			protocolCmd=0xff;
			opRetCode=__15S_OP_NOTHING;
			sendNum=0;
			subSendNum=0;
			
			do{
				nb_process_disable_sleep_in_lwp();
				if(opRetCode ==__15S_OP_OK || opRetCode==__15S_OP_PAY_OK ){
					len=qc_comm_send_pop_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_RET_CLEAR);
					nb_process_disable_sleep_in_lwp();
					osDelay(4000);
					//exitEnable=false;
				}else if(opRetCode == __15S_OP_SEND_ACK || opRetCode ==__15S_OP_STEP_PRICE_ERR || \
					opRetCode == __15S_OP_PAY_OVER || opRetCode == __15S_OP_PAY_VERIFY 
					||opRetCode == __15S_OP_NOT_MINE || opRetCode==__15S_OP_KEY_UPDATE_ERR){
					//2018.03.28,??????????
					if(opRetCode == __15S_OP_PAY_VERIFY && sendNum<16)sendNum=16;
					
					if(opRetCode == __15S_OP_SEND_ACK){opRetCode=bkupOpRetCode;}
					len=qc_comm_ins_reply_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_DATA);
					opRetCode=__15S_OP_NOTHING;
					nb_process_disable_sleep_in_lwp();
					osDelay(4000);
					//exitEnable=true;
				}else{
					
					len=qc_comm_send_pop_ready(nbAplSendBuffer,__15E_CB_CTRL_CODE_DATA);	
					m_mem_cpy_len(nbAplSendBuffer+len,ICCID,20);
					len+=20;					
					exitEnable=false;
				}

				if(subSendNum>=4){delay_long_lwp_dis(50);subSendNum=0x00;}
				if(nb_get_cereg()==0)break;
				//osDelay(4000);

				ret=nb_send_process(nbAplSendBuffer,len);
				if(!ret){nb_module_cfun_off();nbPsmStateMachine=NB_PSM_SM_NRZ;break;}
				sendNum++;
				subSendNum++;
				
				if(opRetCode ==__15S_OP_OK || opRetCode==__15S_OP_PAY_OK ){
					bkupOpRetCode=opRetCode;
					opRetCode=__15S_OP_SEND_ACK;
					continue;
				}
				
				ret=nb_received_process();			
				if(!ret){nbPsmStateMachine=NB_PSM_SM_NRZ;break;}
				//if(!ret){break;}
				ret=np_received_extract_process(nbAplReceivedBuffer,buf,ret);
				
				if(ret>sizeof(buf))ret=sizeof(buf);
				m_mem_cpy_len(nbAplReceivedBuffer,buf,ret);
			
				ret=qc_comm_received_process(nbAplReceivedBuffer,ret);
			
				if(ret==0 || opRetCode == __15S_OP_NOTHING || opRetCode==__15S_OP_RTC_SYNC)break;
				/*
				if(ret==0 || opRetCode == __15S_OP_NOTHING )break;
				if(opRetCode==__15S_OP_RTC_SYNC){
					rtcSyncTm++;
					if(rtcSyncTm>=2)break;
					opRetCode=__15S_OP_NOTHING;
					osDelay(4000);
				}
				*/
				//if(sendNum>=21 && exitEnable)break;
				if(sendNum>=21)break;
				if(pwrStatus==POWER_STATUS_DOWN)break;

			}while(1);
			opRetCode=__15S_OP_NOTHING;
			__nop();
			nb_coap_enter_psm();
			//nb_power_off_process();
			if(!(sysData.DLCS==DLC_STATUS_A && !fi_id_writed_in_dlcs_a())){
				menu=7;
				subMenu=0;
			}			
		}
		data_api_day_change();
	}	
}
#endif


void m_thread_create_nb_udp(void)
{
	#if config_NB_PSM_EN ==0 
	osThreadDef(TheadUdp, vTheadUdp, osPriorityNormal, 0, configMINIMAL_STACK_SIZE*4);
	idTheadUdpId=osThreadCreate(osThread(TheadUdp), NULL);	
	#else
	osThreadDef(TheadUdp, vTheadUdpPsm, osPriorityNormal, 0, configMINIMAL_STACK_SIZE*4);
	idTheadUdpId=osThreadCreate(osThread(TheadUdp), NULL);			
	#endif
}

#endif

//file end
