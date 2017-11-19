//file name :flash.h
#ifndef __flash_h__
#define __flash_h__
#ifdef __cplusplus
	extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	
	#define FLASH_SIZE_ADDR			0x15800
	#define FLASH_PAGE_SIZE			0x200*2
	#define FLASH_ROW_SIZE			64

	#define FLASH_FAGE_BYTIES		0x200*3
	#define FLASH_ROW_BYTIES		64*3
	#define user_FLASH_ADDR_START (FLASH_SIZE_ADDR-FLASH_PAGE_SIZE-FLASH_PAGE_SIZE)
	
	extern void m_flash_read(uint32_t addr,uint8_t* d,uint16_t len);
	extern void m_flash_erase(uint32_t addr,uint16_t len);
	extern void m_flash_write(uint32_t addr,uint8_t* d,uint16_t len);
	
#ifdef __cplusplus
	}
#endif

#endif
