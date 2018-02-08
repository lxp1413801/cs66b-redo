#ifndef __ex_eeprom_h__
#define __ex_eeprom_h__

#ifdef __cplusplus
extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	
	extern iicDeviceObj_t at24c02Obj0;
	extern iicDeviceObj_t at24c02Obj1;
	extern iicDeviceObj_t at24c02Obj2;
	extern iicDeviceObj_t at24c02Obj3;	
    extern void at24c02_vdd_on(void);
    extern void at24c02_vdd_off(void);
	extern void at24c02_init(st_iicDeviceObj* obj, uint8_t slv);
	extern void at24c02_init_all_chip(void);
    extern uint8_t at24c02_read_byte(st_iicDeviceObj* obj,uint8_t addr);
	extern void at24c02_read_n_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t* buf,uint16_t len);
	extern void at24c02_write_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t x);
	extern void at24c02_write_n_byte(st_iicDeviceObj* obj,uint8_t addr,uint8_t* buf,uint16_t len);
	

#ifdef __cplusplus
}
#endif

#endif
//file end
