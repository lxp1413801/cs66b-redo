#include "drivers.h"
#include "../soc/delay.h"
st_iicDeviceObj at24c02Ch0,at24c02Ch1;

void at24c02_set_slave_addr(st_iicDeviceObj* pAt24c02,uint8_t slv)
{
    if(!((void*)pAt24c02))return;
    pAt24c02->slaveAddr=slv;
}

void at24c02_init(st_iicDeviceObj* pAt24c02, uint8_t slv)
{
    pAt24c02->slaveAddr=slv;
	pAt24c02->iic_start=iic_start;
	pAt24c02->iic_stop=iic_stop;
	pAt24c02->iic_send_byte=iic_send_byte;
	//pAt24c02->iic_read_byte=iic_read_byte;
	pAt24c02->iic_waite_ack=iic_waite_ack;
    //pAt24c02->iic_received_byte=iic_received_byte;
	pAt24c02->iic_received_byte_if_ack=iic_received_byte_if_ack;
	//pAt24c02->iic_write_byte=iic_write_byte;
	//pAt24c02->iic_write_n_byte=iic_write_n_byte;    
}
void at24c02_init_all_chip(void)
{
    at24c02_init(&at24c02Ch0,0xaa);//压力
    at24c02_init(&at24c02Ch1,0xac);//差压
}
uint8_t at24c02_read_byte(st_iicDeviceObj* pAt24c02,uint8_t addr)
{
	uint8_t ret;
	//device must enable 
	pAt24c02->iic_start();
	pAt24c02->iic_send_byte(pAt24c02->slaveAddr);
	pAt24c02->iic_send_byte(addr);
	//
	pAt24c02->iic_start();
	pAt24c02->iic_send_byte(pAt24c02->slaveAddr+1);
	ret=pAt24c02->iic_received_byte_if_ack(IIC_NACK);
	pAt24c02->iic_stop();
    return ret;
}
void at24c02_read_n_byte(st_iicDeviceObj* pAt24c02,uint8_t addr,uint8_t* buf,uint16_t len)
{
	//device must enable 
	uint16_t i;
	pAt24c02->iic_start();
	pAt24c02->iic_send_byte(pAt24c02->slaveAddr);
	pAt24c02->iic_send_byte(addr);
	//
	pAt24c02->iic_start();
	pAt24c02->iic_send_byte(pAt24c02->slaveAddr+1);
	for(i=0;i<len-1;i++){
		*buf++=pAt24c02->iic_received_byte_if_ack(IIC_ACK);
	}
	*buf=pAt24c02->iic_received_byte_if_ack(IIC_NACK);
	pAt24c02->iic_stop();	
}
void at24c02_write_byte(st_iicDeviceObj* pAt24c02,uint8_t addr,uint8_t x)
{
	pAt24c02->iic_start();
	pAt24c02->iic_send_byte(pAt24c02->slaveAddr);
	pAt24c02->iic_send_byte(addr);
	
	pAt24c02->iic_send_byte(x);
	pAt24c02->iic_stop();	
}
/*
void at24c02_write_n_byte(st_iicDeviceObj* pAt24c02,uint8_t addr,uint8_t* buf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++){
		pAt24c02->iic_start();
		pAt24c02->iic_send_byte(pAt24c02->slaveAddr);
		pAt24c02->iic_send_byte(addr++);
		
		pAt24c02->iic_send_byte(*buf++);
		pAt24c02->iic_stop();
        delay_ms(1);
		//delay_us(20);
	}
}

*/
extern uint8_t globleBuffer[];
void at24c02_write_n_byte(st_iicDeviceObj* pAt24c02,uint8_t addr,uint8_t* buf,uint16_t len)
{
	uint16_t i;
	uint8_t tmpBuf[256];
	at24c02_read_n_byte(pAt24c02,addr,tmpBuf,len);
	
	for(i=0;i<len;i++){
		if(tmpBuf[i]==buf[i])continue;
		
		pAt24c02->iic_start();
		pAt24c02->iic_send_byte(pAt24c02->slaveAddr);
		pAt24c02->iic_send_byte(addr+i);
		pAt24c02->iic_send_byte(buf[i]);
		pAt24c02->iic_stop();
        delay_ms(1);
	}
}



//file end

