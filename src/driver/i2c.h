#ifndef __iic_h__
#define __iic_h__

#ifdef __cplusplus
extern "C"{
#endif

	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	
	enum
	{
		IIC_NACK=1,
		IIC_ACK=0,
	};


	//rd0<>scl
	#define IIC_SCL_PIN		PIN0
	#define IIC_SCL_PORT	portd
	//rd11<>sda
	#define IIC_SDA_PIN		PIN11
	#define IIC_SDA_PORT 	portd

	#define iic_sda_mode_out() do{ \
		set_port_mode_dig(IIC_SDA_PORT,IIC_SDA_PIN); \
		set_port_mode_out(IIC_SDA_PORT,IIC_SDA_PIN); \
		}while(0);
		
	#define iic_sda_mode_in() do{ \
		set_port_mode_dig(IIC_SDA_PORT,IIC_SDA_PIN); \
		set_port_mode_in(IIC_SDA_PORT,IIC_SDA_PIN); \
		}while(0);
		
	#define	iic_sda_hight() set_port_value_hight(IIC_SDA_PORT,IIC_SDA_PIN);
	#define	iic_sda_low() 	set_port_value_low(IIC_SDA_PORT,IIC_SDA_PIN);
	#define iic_sda_get() 	get_port_value(IIC_SDA_PORT,IIC_SDA_PIN)

	#define iic_scl_mode_out() do{ \
		set_port_mode_dig(IIC_SCL_PORT,IIC_SCL_PIN); \
		set_port_mode_out(IIC_SCL_PORT,IIC_SCL_PIN); \
		}while(0);

	#define iic_scl_mode_in() do{ \
		set_port_mode_dig(IIC_SCL_PORT,IIC_SCL_PIN); \
		set_port_mode_in(IIC_SCL_PORT,IIC_SCL_PIN); \
		}while(0);		

	#define	iic_scl_hight() set_port_value_hight(IIC_SCL_PORT,IIC_SCL_PIN);
	#define	iic_scl_low() set_port_value_low(IIC_SCL_PORT,IIC_SCL_PIN);

	extern uint8_t iicSlaveAddr;
    extern void iic_pins_disable(void);
	extern void iic_start(void);
	extern void iic_stop(void);
	extern uint8_t iic_send_byte(uint8_t x);
	extern uint8_t iic_read_byte(uint8_t slaveAddr,uint8_t addr);
	extern uint8_t iic_waite_ack(void);
	extern uint8_t iic_received_byte(void);
	extern uint8_t iic_received_byte_if_ack(uint8_t ack);


	typedef struct{
		uint8_t slaveAddr;
        void (*deviceVddOn)(void);
		void (*iic_start)(void);
		void (*iic_stop)(void);
		uint8_t (*iic_send_byte)(uint8_t);
		uint8_t (*iic_waite_ack)(void);
		uint8_t (*iic_received_byte_if_ack)(uint8_t ack);
	}st_iicDeviceObj,iicDeviceObj_t;

#ifdef __cplusplus
}
#endif
#endif