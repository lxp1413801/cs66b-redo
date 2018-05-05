#include "../includes/includes.h"


//#define my_uart1_send_poll(buf,len) uart1_send_len(buf,len)
void my_uart1_send_poll(uint8_t* buf,uint16_t len)
{
    rs_485_set_tx();
    delay_ms(2);
    uart1_send_len(buf,len);
    delay_ms(10);
    rs_485_set_rx();
}
//#define __mbStatusStartAddr__ 0xe000
/*
void modbus_response_write_flash_sys(uint8_t* buf){
	uint16_t startAddr=0;
	uint8_t len=0;
	st_modbusComReqStructDef* pmdbs=(st_modbusComReqStructDef*)buf;
	startAddr=pmdbs->addr_hi;
	startAddr<<=8;
	startAddr |= pmdbs->addr_lo;
	len=pmdbs->len_hi;
	len<<=8;
	len = pmdbs->len_lo;
	if(startAddr< main_FLOW_CALIBRATION_TABLE_ADDR || startAddr+len > END_FLASH || \
	len >16){
		modbus_response_illgeal_function(buf,ILLEGAL_DATA_ADDRESS);
		return;
	}
	m_mem_cpy_len(comBuffer,buf+5,len);
	flashOpStr.flashAddr=startAddr;
	flashOpStr.op=emFLASH_WRITE_main_SYSTEM_DATA;		
	flashOpStr.len=len;
	m_mem_cpy_len(comBuffer,buf+5,len);
	data_api_flash_process();
	modbus_response_illgeal_function(buf,0);
	
}
*/
void modbus_response_illgeal_function(uint8_t* buf,uint8_t errcode)
{
	st_modbusErrRespStructDef* pmdbs=(st_modbusErrRespStructDef*)buf;
	if(pmdbs->addr==0x00)return;
	pmdbs->addr=stSysData.ModbusId;
	if(errcode){
		pmdbs->func+=0x80;
	}
	pmdbs->errcord=errcode;
	crc_append(buf,3);
	my_uart1_send_poll(buf,5);		
}
/*
void modbus_response_write_clib_data(uint8_t* buf){	
	uint16_t startAddr=0;
	uint16_t t16;
	st_modbusWriteSingleClib* pmdbs=(st_modbusWriteSingleClib*)buf;
	if(pmdbs->addr!=stSysData.ModbusId)return;
	startAddr=pmdbs->addr_hi;
	startAddr<<=8;
	startAddr |= pmdbs->addr_lo;
	//if(pmdbs->addr!=0)return;
	if(startAddr>FLOW_CALIBRATION_POINT_NUM){
		modbus_response_illgeal_function(buf,ILLEGAL_DATA_ADDRESS);
		return;		
	}
	t16=pmdbs->data_hi;
	t16<<=8;
	t16|=pmdbs->data_lo;
	*((uint16_t*)(flashOpStr.buf))=t16;
	flashOpStr.op=emFLASH_WRITE_main_CALIB_DATA;   
    if(buf[1]==FUNC_WRITE_FLASH_CLIBDATA_COVER && startAddr>=1){
        data_api_calibration_table_data_save((uint8_t)startAddr,false);
    }else{
        data_api_calibration_table_data_save((uint8_t)startAddr,true);
    }
	//modbus_response_illgeal_function(buf,0);	
    if(pmdbs->addr==0)return;
    buf[0]=mainSystemData.shortID;
    crc_append(buf,6);
    my_uart1_send_poll(buf,8);      
}
*/
/*
void modbus_response_read_clib_data(uint8_t* buf)
{
    uint16_t i;
	uint16_t startAddr=0;
	uint16_t len=0;
	st_modbusComReqStructDef* pmdbs=(st_modbusComReqStructDef*)buf;
	if(pmdbs->addr!=stSysData.ModbusId)return;
	startAddr=pmdbs->addr_hi;
	startAddr<<=8;
	startAddr |= pmdbs->addr_lo;
	len=pmdbs->len_hi;
	len<<=8;
	len = pmdbs->len_lo;
    if((len+startAddr)>FLOW_CALIBRATION_POINT_NUM+1 || (len>16)){
		modbus_response_illgeal_function(buf,ILLEGAL_DATA_ADDRESS);
		return;
	} 
    data_api_read_eeprom(buf+3,addr_CALIB_DATA_ADDR_EEPROM+startAddr*4,len*4);
	buf[0] = mainSystemData.shortID;
	buf[1] = 3;
	buf[2] = (uint8_t)(len*4);
	len=buf[2]+3;
    crc_append(buf,len);
    len += 2;
    my_uart1_send_poll(buf,len);
}
*/


uint16_t getRegisterVal(uint16_t addr,uint16_t *tempData)
{
    int32_t t32;
	uint16_t result = 0; 
	//uint16_t tempAddr; 
    int16_t t16;
    //int16_t t8;
	//uint32_t TEMP;
	
	//tempAddr = addr & 0xff;
	switch(addr)
	{
		//????
		case 0x4001:
			*tempData = 0x5555; 
			break; 
		case 0x4002:
            t32=rtHight;
            *tempData = (uint16_t)((t32>>16) & 0x0000ffff); 
			break; 
		//????
		case 0x4003: 
            t32=rtHight;
            *tempData = (uint16_t)((t32) & 0x0000ffff); 
			break; 
		case 0x4004:
			t32=rtPressure;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
			break; 
		case 0x4005:
			t32=rtPressure;
			*tempData = (uint16_t)((t32) & 0x0000ffff); 
			break;
		case 0x4006: 
			t32=rtTemperatureIn;
            t32/=100;
            if(t32>127)t32=127;
            if(t32<-128)t32=-128;
            t16=(int16_t)t32;
			*tempData = t16;
			break;	
		case 0x4007: 
			t32=rtEx0Pressure;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
			break;	
		case 0x4008: 
			t32=rtEx0Pressure;
			*tempData = (uint16_t)((t32) & 0x0000ffff); 
			break;
        case 0x4009:
			t32=rtEx1Pressure;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
			break;   
        case 0x400a:
			t32=rtEx1Pressure;
			*tempData = (uint16_t)((t32) & 0x0000ffff); 
            break;   
        case 0x400b:
			t32=rtTemperatureEx0;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
			break;   
        case 0x400c:
			t32=rtTemperatureEx0;
			*tempData = (uint16_t)((t32) & 0x0000ffff); 
            break;
		case 0x400d:
			t32=rtTemperatureEx1;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
			break;   	
		case 0x400e:
			t32=rtTemperatureEx1;
			*tempData = (uint16_t)((t32) & 0x0000ffff); 
            break;	
		case 0x400f:
			t16=rtValueBat;
			*tempData = (uint16_t)t16; 
            break;
		case 0x4010:
			t16=deviceEvent.t16;
			*tempData = (uint16_t)t16; 
            break;		
		case 0x4011:
			t32=hardStatus.t32;
			*tempData = (uint16_t)((t32>>16) & 0x0000ffff);
            break;	
		case 0x4012:
			t32=hardStatus.t32;
			*tempData = (uint16_t)(t32 & 0x0000ffff);
            break;	            
		default: 
			*tempData = 0x55aa;
			break;	
	}
	return result;
}
/*
void modbus_response_write_single_register(uint8_t* rbuf)
{
    uint16_t startAddr=0;
	uint8_t len=0;
	st_modbusComReqStructDef* pmdbs=(st_modbusComReqStructDef*)rbuf;
    if(pmdbs->addr!=mainSystemData.shortID)return;
	startAddr=pmdbs->addr_hi;
	startAddr<<=8;
	startAddr |= pmdbs->addr_lo;
    //tmpAddr=startAddr;
	//len = pmdbs->len_lo;   
    //len<<=1;
    switch( startAddr & 0xff){
		case 0x02:
			if((rbuf[5]&0x04)==0){
				deviceStatus.bits.doorOpen=0;
			}
			break;

        default:
            modbus_response_illgeal_function(rbuf,ILLEGAL_DATA_ADDRESS);
            return;
	}
    if(pmdbs->addr==0)return;
    rbuf[0]=mainSystemData.shortID;
    crc_append(rbuf,6);
    my_uart1_send_poll(rbuf,8);      
}
*/
void modbus_response_command(uint8_t* rbuf){
    uint8_t i;
	uint16_t startAddr=0;
    uint16_t tempData,tmpAddr;
	uint8_t len=0;
	st_modbusComReqStructDef* pmdbs=(st_modbusComReqStructDef*)rbuf;
    if(pmdbs->addr!=stSysData.ModbusId)return;
	startAddr=pmdbs->addr_hi;
	startAddr<<=8;
	startAddr |= pmdbs->addr_lo;
    tmpAddr=startAddr;
	len = pmdbs->len_lo;   
    len<<=1;
    if(len>32)len=32;
    for(i=0;i<len;i=i+2,tmpAddr++){
		getRegisterVal(tmpAddr,&tempData);				
		rbuf[i+3] = tempData >> 8;				   		
		rbuf[i+4] = tempData & 0xff;			
        
    }
	rbuf[0] = stSysData.ModbusId;
	rbuf[1] = 3;
	rbuf[2] = len;
	len += 3;
    crc_append(rbuf,len);
    len += 2;
    my_uart1_send_poll(rbuf,len);       
    
}
void modbus_response_process(uint8_t* rbuf,uint16_t rlen){
	//uint8_t resp=0;
	st_modbusComReqStructDef* pmdbs=(st_modbusComReqStructDef*)rbuf;
	//if(!(pmdbs->addr ==0xff  || pmdbs->addr==mainSystemData.shortID || pmdbs->addr!=0x00))return;
    if(rlen<4)return;
    if(!( pmdbs->addr==stSysData.ModbusId && pmdbs->addr!=0x00))return;
	if(!(crc_verify(rbuf,rlen)))return ;
	//function expand expand
	switch(pmdbs->func){
        case FUNC_READ_HOLDING_REGISTERS:
            modbus_response_command(rbuf);
            break;
        /*case FUNC_WRITE_SINGLE_REGISTER:
             modbus_response_write_single_register(rbuf);
             break;
        
		case FUNC_WRITE_FLASH_SYSDATA:
			modbus_response_write_flash_sys(rbuf);
			break;	
			
		case FUNC_READ_FLASH_CLIBDATA:
			modbus_response_read_clib_data(rbuf);   
			break;				
        case    FUNC_WRITE_FLASH_CLIBDATA:
        case  FUNC_WRITE_FLASH_CLIBDATA_COVER:
			modbus_response_write_clib_data(rbuf);
			break;
		
		case FUNC_READ_FLASH_SYSDATA:
			break;
		case FUNC_READ_STATUS_REGISTER:
			modbus_response_read_status_register(rbuf);  
			break;
		case FUNC_WRITE_STATUS_REGISTER:
			modbus_response_write_status_register(rbuf);  
			break;    
             */       
		default:
			modbus_response_illgeal_function(rbuf,ILLEGAL_FUNCTION);break;		
	}	
}