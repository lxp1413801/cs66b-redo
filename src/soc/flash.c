#include "flash.h"
#include "../global/globle.h"
uint16_t flashOffsetAddr;
uint8_t flashByteTemp;
uint16_t sh_SR;
extern void flash_unlock_pm(void);
void m_flash_unlock_write(void)
{
    SET_AND_SAVE_CPU_IPL(sh_SR, 7);
    flash_unlock_pm();
    RESTORE_CPU_IPL(sh_SR);    
}
void m_flash_read(uint32_t addr,uint8_t* d,uint16_t len)
{
    //uint8_t t8;
	uint16_t i;
    //uint16_t offsetAddr;
    TBLPAG=(uint8_t)((addr>>16)&0x7f);
    flashOffsetAddr=(uint16_t)(addr & 0xffff);
    asm("mov _flashOffsetAddr,w4");
    for(i=0;i<len;){
        asm("TBLRDL.B [W4],W3");
        asm("mov w3,_flashByteTemp");
        if(i<len)d[i]=flashByteTemp;        
        i++;
		
		asm("inc w4,w4");
        asm("TBLRDL.B [W4],W3");
        asm("mov w3,_flashByteTemp");
        if(i<len)d[i]=flashByteTemp; 	
		i++;

		asm("dec w4,w4");
        asm("TBLRDH.B [W4],W3");
        asm("mov w3,_flashByteTemp");
        if(i<len)d[i]=flashByteTemp; 	
		i++;
		
		asm("inc2 w4,w4");
    }
}

void m_flash_erase(uint32_t addr,uint16_t len)
{
    TBLPAG=(uint8_t)((addr>>16)&0x7f);
    flashOffsetAddr=(uint16_t)(addr & 0xffff);
	asm("mov _flashOffsetAddr,w4");
	asm("TBLWTL W4, [W4]");
	NVMCON = 0x4042; // Initialize NVMCON
    m_flash_unlock_write();
	__nop();
	__nop();
}

void m_flash_write(uint32_t addr,uint8_t* d,uint16_t len)
{
	uint16_t i=0;
	
    TBLPAG=(uint8_t)((addr>>16)&0x7f);
    flashOffsetAddr=(uint16_t)(addr & 0xffff);
	
	asm("mov _flashOffsetAddr,w4");
	
	for(i=0;i<len;){
        
		flashByteTemp=0xff;
		if(i<len)flashByteTemp=d[i];
		asm("mov _flashByteTemp,w3");
		asm("TBLWTL.B w3, [W4]");
		i++;
		
		asm("inc w4,w4");
		flashByteTemp=0xff;
		if(i<len)flashByteTemp=d[i];
		asm("mov _flashByteTemp,w3");		
		asm("TBLWTL.B w3, [W4]");
		i++;
		
		asm("dec w4,w4");
		flashByteTemp=0xff;
		if(i<len)flashByteTemp=d[i];
		asm("mov _flashByteTemp,w3");		
		asm("TBLWTH.B w3, [W4]");		
		i++;
		
		asm("inc2 w4,w4");
		
		NVMCON = 0x4003;
        m_flash_unlock_write();
	}
	__nop();
	__nop();
}