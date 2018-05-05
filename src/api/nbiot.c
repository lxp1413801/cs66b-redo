#include "../includes/includes.h"
#define nb_uart_send_str uart2_send_str

const st_ATcmdDef* pAtCmd=(st_ATcmdDef*)(NULL);
uint32_t recTimerSec=0x00;
atCmdProcessSm_t atCmdSm=AT_CMD_PROCESS_NOTHING;

uint16_t nbBufLen;
uint8_t nbBuf[NB_BUFFER_LEN];

uint8_t CIMI[16];
uint8_t	CGSN[16];
uint8_t	ICCID[21];

int8_t rssi=0; 
nbPsmStateMachine_t nbPsmStateMachine=NB_PSM_SM_NOTHING;

void nb_process_disable_sleep_in_lwp(void)
{
     noEventTimeOut=NO_EVENT_TIME_MAX;
}
void nb_at_cmd_recbuf_init(void)
{
    m_mem_set(uart2ReceivedBuf,'\0',sizeof(uart2ReceivedBuf));
    uart2ReceivedCount=0;
}

uint16_t nb_at_cmd_waite_resp(uint8_t* rec,uint32_t tm,uint16_t receiveLen)
{
    uint32_t endTm=globleHalfSec + tm/500;
    uint16_t t16;
    while(1){
        delay_ms(100);
        if(globleHalfSec>=endTm){t16=0x00;break;}
        if(event & flg_NB_GPS_RECEIVED){
            event &= ~flg_NB_GPS_RECEIVED;
            t16=uart2ReceivedCount;
            m_mem_cpy_len(rec,uart2ReceivedBuf,t16);
            break;
        }
    }
    return t16;
}

uint16_t nb_at_cmd_ex(const st_ATcmdDef* cmd,uint8_t* recbuf,uint16_t reclen)
{
	uint16_t sta=0;
	uint16_t len=0;
	uint16_t tryTm=0x00;
	if(!cmd)return 0;
	if(!recbuf)return 0;
    nb_at_cmd_recbuf_init();
	m_mem_set(recbuf,'\0',reclen);
	nb_uart_send_str((uint8_t*)(cmd->cmdStr));
	
	for(tryTm=0;tryTm<6;tryTm++){
		nb_process_enable_sleep_in_lwp();
		len=0;
		len=nb_at_cmd_waite_resp(recbuf,1000,reclen);
		if(len<=2)continue;
		else
			break;
	}
    sta=m_str_match(recbuf,(uint8_t*)(cmd->okMatchStr));
	//return len;
    return sta>0?len:0;
}

uint16_t nb_power_on_process_waite_ok(void)
{

	uint32_t tmSta=0,tm=0;
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	
	m_mem_set(nbBuf,0,sizeof(nbBuf));
	
	tmSta=globleHalfSec;
	do{
		nb_process_enable_sleep_in_lwp();

		//if(pwrStatus==POWER_STATUS_DOWN)return 0;		
        delay_ms(500);
		nb_at_cmd_waite_resp(recbuf,1000,reclen);
		tm=globleHalfSec-tmSta;
		if(m_str_match(recbuf,(uint8_t*)"\r\nOK\r\n"))break;
		//tryTm++;
		
		if(tm>20)break;
	}while(1);
	if(tm<20){
		return 1;
	}else{
		return 0;
	}
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
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	return nb_at_cmd_ex(&AT_CMD_NRB,recbuf,reclen);
}

uint16_t nb_coap_ncbp(void)
{
	st_ATcmdDef atcmdTemp={0};
	
	uint16_t ret;
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	uint16_t tyrtm=4;
	m_mem_cpy_len((uint8_t*)&atcmdTemp,(uint8_t*)&AT_CMD_NCDP,sizeof(st_ATcmdDef));
	//atcmdTemp.cmdStr=(uint8_t*)"AT+NCDP=117.60.157.137\r\n"//sysData.venderUdpSetting;
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
		//nbiotDescInf.nbStatus=NB_CONNECTED;
	}else{
		//nbiotDescInf.nbStatus=NB_ERROR;
	}
	return tyrtm;
}	

int8_t nb_get_csq(void)
{
	uint8_t* p8;
	int16_t t16;
	int8_t ret;
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);	
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

uint16_t nb_module_cfun_off(void)
{
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	return nb_at_cmd_ex(&AT_CMD_CFUN_0,recbuf,reclen);
}

uint16_t nb_coap_enter_psm(void)
{
	if(nbPsmStateMachine!=NB_PSM_SM_NRZ)nbPsmStateMachine=NB_PSM_SM_PSM;
	delay_ms(500);
	return 1;
}

uint16_t nb_coap_psm_send_ready(void)
{
	uint32_t tm;
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	uint16_t tryTm,ret;	
	tryTm=0;

	nb_process_enable_sleep_in_lwp();
	if(nbPsmStateMachine== NB_PSM_SM_NRZ){
		
	}else if(nbPsmStateMachine==NB_PSM_SM_PSM){
		nbPsmStateMachine=NB_PSM_SM_NCDPR;
	}else{nbPsmStateMachine=NB_PSM_SM_AT;}
	__nop();
	tm=globleHalfSec;
	while(tryTm<=20){
		//tryTm++;
		if((globleHalfSec-tm)>240){
			nbPsmStateMachine=NB_PSM_SM_NO_NET;break;
		}
#if 0
		if(pwrStatus<POWER_STATUS_LOW){
			nbPsmStateMachine= NB_PSM_SM_NRZ;break;
		}
#endif
		switch(nbPsmStateMachine){
		case NB_PSM_SM_NRZ:
			ret=nb_module_nbr();
			//osDelay(1000);
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
			tm=globleHalfSec;
			while(1){
				ret=nb_at_cmd_ex(&AT_CMD_CGATT_R,recbuf,reclen);
				if(ret){nbPsmStateMachine=NB_PSM_SM_CIMI;break;}
				else{
					delay_ms(2000);
					if(globleHalfSec-tm>=200){
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

uint16_t nb_send_packet_load(uint8_t* sbuf,uint16_t slen)
{
	return 1;
}

uint8_t* nb_send_load_atcmd_coap(uint8_t* buf,uint16_t len)
{
	uint16_t t16,ret;
	//uint8_t tmpBuf[256];
	
	uint8_t* d=globleBuffer;
	
	m_mem_set(globleBuffer,'\0',sizeof(globleBuffer));
	ret=m_str_cpy(d,(uint8_t*)"AT+NMGS=");
	
	t16=ret-1;
	d+=(ret-1);

	ret=int16_2_d(d,len+1);
	t16+=ret;
	d+=ret;
	*d++=',';
	t16+=1;
	
	//*d++='0';
	//*d++='0';
	//t16+=2;
	
	ret=m_str_b2h(d,buf,len);
	d+=ret;
	t16+=ret;
	
	*d++='\r';
	*d++='\n';
	*d++='\0';
	
	t16+=3;
	
	//m_mem_cpy_len(buf,tmpBuf,t16);
	return d;

}

uint16_t nb_send_coap(uint8_t* str)
{

	uint8_t* recbuf=nbRecBuf;
	uint16_t reclen=sizeof(nbRecBuf);	
	nb_process_disable_sleep_in_lwp();	
	uint16_t tryTm,ret,sendTime;
	sendTime=0x00;
	do{
		ret=0;

		nb_uart_send_str(str);
		#if NBIOT_ROUTINES_DISP_EN
		nb_routines_information_disp((uint8_t*)("send-"));
		#endif	
		
		for(tryTm=0;tryTm<5;tryTm++){
			len=0;ret=0;
			//if(pwrStatus==POWER_STATUS_DOWN)break;		
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
		//if(pwrStatus==POWER_STATUS_DOWN)break;	
		nb_process_disable_sleep_in_lwp();
		//osDelay(10000);
        delay_ms(500);
		
	}while(sendTime++<3);
	if(ret==0 && sendTime>3){
		//nbFirstCattch=true;
	}
	nb_process_disable_sleep_in_lwp();
	//nb_udp_close_socket();
	return ret;
}	

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

uint16_t np_received_extract_coap(uint8_t* str,uint8_t* bin,uint16_t len)
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

uint16_t nb_received_coap(void)
{
	uint32_t tm;
	uint16_t t16;
	//uint16_t loc;
	uint16_t tryTm=0x00;
	uint16_t ret;
	
	uint8_t* recbuf=nbBuf;
	uint16_t reclen=sizeof(nbBuf);
	nb_at_cmd_recbuf_init();
	tm=globleHalfSec;
	do{
		ret=0;
		if((globleHalfSec-tm)>80)break;
		
		delay_ms(500);
		tryTm++;
		//if(tryTm>30)break;
		ret=nb_at_cmd_ex(&AT_CMD_NQMGR,recbuf,reclen);
		if(!ret)continue;
		m_str_match_ex(recbuf,(uint8_t*)("BUFFERED="),&t16);
		//if(t16)
		ret=my_scanf_int16(recbuf+9+t16,',',NULL);
		if(ret==0)continue;
		delay_ms(500);
		
		m_mem_set(recbuf,0,reclen);
		ret=nb_at_cmd_ex(&AT_CMD_NMGR,recbuf,reclen);
		//np_udp_received_extract_coap();
		__nop();
		
		if(!ret)continue;
		__nop();
		break;
	}while(1);
	return ret;
}

uint16_t nb_received_process(uint8_t* rbuf,uint16_t rlen)
{
	return 1;
}

void nb_uart_enable(void)
{
	set_port_mode_out(GPS_EN_PORT,GPS_EN_PINS);
	set_port_value_hight(GPS_EN_PORT,GPS_EN_PINS);		
}

void nb_uart_disable(void)
{
	set_port_mode_in(GPS_EN_PORT,GPS_EN_PINS);		
}

void nb_process(void)
{
	uint16_t t16;
	uint16_t nbGLBufLen=sizeof(globleBuffer);
	uint8_t* nbGLBuf=globleBuffer;
	//uint8_t* recbuf=nbRecBuf;
	//uint16_t reclen=sizeof(nbRecBuf);
	uint8_t* sendStr; 
	uint8_t tryTm=0x00;
	
	nb_uart_enable();
	delay_ms(1000);
	nb_process_disable_sleep_in_lwp();
    do{
        nb_coap_psm_send_ready();
		if(nbPsmStateMachine!=NB_PSM_SM_SEND){
			nbPsmStateMachine=NB_PSM_SM_NRZ;
			//continue;
			break;
		}
		t16=nb_send_packet_load(nbGLBuf,nbGLBufLen);
		sendStr=nb_send_load_atcmd_coap(nbGLBuf,t16);
		nb_send_coap(sendStr,t16);
		delay_ms(500);
		t16=nb_received_coap();
		t16=np_received_extract_coap(nbBuf,nbGLBuf,t16);
		t16=nb_received_process(nbGLBuf,t16);
		if(t16>0){
			tryTm++;
		}else{
			break;
		}
		if(tryTm<5)continue;
		break;
    }while(1);
	
	nb_coap_enter_psm();
	nb_uart_disable();
	
}

//file end
