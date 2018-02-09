#include "drivers.h"
#include "../soc/delay.h"
#include "../global/globle.h"
#include "../configs/configs.h"
iicDeviceObj_t at24c02Obj0;
iicDeviceObj_t at24c02Obj1;
iicDeviceObj_t at24c02Obj2;
iicDeviceObj_t at24c02Obj3;

void at24c02_vdd_on(void)
{
    
	run_status_init();
    run_status_on();
    delay_ms(10);
}
void at24c02_vdd_off(void)
{
#if EEPROM_PER_VIA_IO    
    delay_ms(10);
    run_status_off();
#else
    __nop();
#endif
}
void at24c02_set_slave_addr(st_iicDeviceObj* obj,uint8_t slv)
{
    if(!((void*)obj))return;
    obj->slaveAddr=slv;
}

void at24c02_init(st_iicDeviceObj* obj, uint8_t slv)
{
#if EEPROM_PER_VIA_IO
    obj->deviceVddOn=at24c02_vdd_on;
    obj->deviceVddOff=at24c02_vdd_off;
#else
    obj->deviceVddOn=kz_vadd_on;
    obj->deviceVddOff=at24c02_vdd_off;
#endif
    obj->slaveAddr=slv;
	obj->iic_start=iic_start;
	obj->iic_stop=iic_stop;
	obj->iic_send_byte=iic_send_byte;
	obj->iic_waite_ack=iic_waite_ack;
	obj->iic_received_byte_if_ack=iic_received_byte_if_ack;    
}
void at24c02_init_all_chip(void)
{
    at24c02_init(&at24c02Obj0,0xa8);//
    at24c02_init(&at24c02Obj1,0xaa);//
	at24c02_init(&at24c02Obj2,0xac);
	at24c02_init(&at24c02Obj3,0xae);
}
uint8_t at24c02_read_byte(st_iicDeviceObj* obj,uint8_t addr)
{
	uint8_t ret;
	//device must enable 
	obj->iic_start();
	obj->iic_send_byte(obj->slaveAddr);
	obj->iic_send_byte(addr);
	//
	obj->iic_start();
	obj->iic_send_byte(obj->slaveAddr+1);
	ret=obj->iic_received_byte_if_ack(IIC_NACK);
	obj->iic_stop();
    return ret;
}
void at24c02_read_n_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t* buf,uint16_t len)
{
	//device must enable 
	uint16_t i;
    obj->deviceVddOn();
	obj->iic_start();
	obj->iic_send_byte(obj->slaveAddr);
	obj->iic_send_byte(addr);
	//
	obj->iic_start();
	obj->iic_send_byte(obj->slaveAddr+1);
	for(i=0;i<len-1;i++){
		*buf++=obj->iic_received_byte_if_ack(IIC_ACK);
	}
	*buf=obj->iic_received_byte_if_ack(IIC_NACK);
	obj->iic_stop();	
    
    obj->deviceVddOff();
}
void at24c02_write_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t x)
{
	obj->iic_start();
	obj->iic_send_byte(obj->slaveAddr);
	obj->iic_send_byte(addr);
	
	obj->iic_send_byte(x);
	obj->iic_stop();	
}
/*
void at24c02_write_n_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t* buf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++){
		obj->iic_start();
		obj->iic_send_byte(obj->slaveAddr);
		obj->iic_send_byte(addr++);
		
		obj->iic_send_byte(*buf++);
		obj->iic_stop();
        delay_ms(1);
		//delay_us(20);
	}
}

*/
extern uint8_t globleBuffer[];
void at24c02_write_n_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t* buf,uint16_t len)
{
	uint16_t i;
    
	uint8_t tmpBuf[256];
	at24c02_read_n_byte(obj,addr,tmpBuf,len);
	obj->deviceVddOn();
	for(i=0;i<len;i++){
		if(tmpBuf[i]==buf[i])continue;
		
		obj->iic_start();
		obj->iic_send_byte(obj->slaveAddr);
		obj->iic_send_byte(addr+i);
		obj->iic_send_byte(buf[i]);
		obj->iic_stop();
        delay_ms(1);
	}
    
    obj->deviceVddOff();
}



//file end

