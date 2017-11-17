#include "drivers.h"
#include "../soc/delay.h"
#include "../global/globle.h"
#define __nop_delay() do{ \
__nop();__nop();__nop();__nop();__nop(); \
__nop();__nop();__nop();__nop();__nop(); \
}while(0);


void iic_start(void)
{
	iic_scl_mode_out();
	iic_sda_mode_out();
    
	iic_sda_hight();
	iic_scl_hight();
	delay_us(10);
	iic_sda_low();
	delay_us(10);
	iic_scl_low();
	delay_us(10);
}

void iic_stop(void)
{
	iic_scl_mode_out();
	iic_sda_mode_out();
	iic_sda_low();
	delay_us(10);
	iic_scl_hight();
	delay_us(10);
	iic_sda_hight();
	delay_us(10);
}

void iic_send_ack(int8_t ack)
{
	iic_scl_mode_out();
	iic_sda_mode_out();
	iic_scl_low();
	__nop_delay();
	if(ack){
		iic_sda_hight();
	}else{
		iic_sda_low();
	}
	__nop_delay();
	iic_scl_hight();
	__nop_delay();
	iic_scl_low();
	__nop_delay();
}

uint8_t iic_waite_ack(void)
{
	uint8_t timeout=200;
	iic_scl_mode_out();
	iic_sda_mode_in();
    iic_scl_low();
    __nop_delay();
	iic_scl_hight();
    __nop_delay();
	while(timeout--){
		if(!iic_sda_get())break;
	}
	if(!timeout){
		iic_stop();
		return 0;
	}
	iic_scl_low();
    __nop_delay();
	return 1;	
}

uint8_t iic_send_byte(uint8_t x)
{
	uint8_t i;
    iic_scl_mode_out();
	iic_sda_mode_out();
	iic_scl_low();
	__nop_delay();
	for(i=0;i<8;i++){       
		if(x&0x80){
			iic_sda_hight();
        }
		else{
			iic_sda_low();
        }
		__nop_delay();
		iic_scl_hight();
		//__nop_delay();
        __nop_delay();
		iic_scl_low();
        //__nop_delay();
        __nop_delay();
		x<<=1;
	}
	return iic_waite_ack();
}

uint8_t iic_received_byte(void)
{
	uint8_t i;
	uint8_t ret=0;
	iic_scl_mode_out();
	iic_sda_mode_in();//iic_sda_mode_in();
	for(i=0;i<8;i++){
        ret<<=1;
		iic_scl_low();
        __nop_delay();
		iic_scl_hight();
        __nop_delay();
		if(iic_sda_get()){
			ret|=1;
		}
	}
	iic_scl_low();
    __nop_delay();
	return ret;
}
uint8_t iic_received_byte_if_ack(uint8_t ack)
{
	uint8_t ret=0;
	ret=iic_received_byte();
	iic_send_ack(ack);
	return ret;
}
/*
uint8_t iic_read_byte(uint8_t slaveAddr,uint8_t addr)
{
	uint8_t ret;
	//device must enable 
	iic_start();
	iic_send_byte(slaveAddr);
	iic_send_byte(addr);
	//
	iic_start();
	iic_send_byte(slaveAddr+1);
	ret=iic_received_byte_if_ack(IIC_NACK);
	iic_stop();
    return ret;
}

void iic_write_byte(uint8_t slaveAddr,uint8_t addr,uint8_t x)
{
	iic_start();
	iic_send_byte(slaveAddr);
	iic_send_byte(addr);
	
	iic_send_byte(x);
	iic_stop();	
}

void iic_write_n_byte(uint8_t slaveAddr,uint8_t addr,uint8_t* buf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++){
		iic_start();
		iic_send_byte(slaveAddr);
		iic_send_byte(addr++);
		
		iic_send_byte(*buf++);
		iic_stop();			
	}
}
*/