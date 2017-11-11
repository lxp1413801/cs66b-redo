#include "drivers.h"
#include "../soc/delay.h"
#include "ads1148.h"
ads1148Obj_t ads1148Chip0,ads1148Chip1;


uint8_t ads1148_send_cmd(ads1148Obj_t* obj,uint8_t cmd)
{
    uint8_t ret;
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
    ret=obj->ads1148_write_read_via_spi(cmd);
	delay_us(10);
	obj->pins_cs_set_hight();
    return ret;
}

uint16_t ads1148_read_data(ads1148Obj_t* obj)
{
	uint16_t t16=0;
	uint8_t t8=0;
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
	obj->ads1148_write_read_via_spi(ADS1148_CMD_RDATA);
    delay_us(5);
	t8=obj->ads1148_write_read_via_spi(ADS1148_CMD_NOP);
	t16=t8;
	t16<<=8;
    delay_us(5);
	t8=obj->ads1148_write_read_via_spi(ADS1148_CMD_NOP);
	t16 |= t8;
    delay_us(10);
	obj->pins_cs_set_hight();
	return t16;
}

void ads1148_write_register(ads1148Obj_t* obj,uint8_t offsetaddr,uint8_t *buf,uint8_t num)
{
	uint8_t i;
	uint8_t cmd;
	if(num<1)return;
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
	cmd=ADS1148_CMD_WREG;
	cmd |= (offsetaddr & 0x0f);
	obj->ads1148_write_read_via_spi(cmd);
	obj->ads1148_write_read_via_spi(num-1);
	for(i=0;i<num;i++){
		obj->ads1148_write_read_via_spi(*buf);
		buf++;
	}
    delay_us(10);
	obj->pins_cs_set_hight();
}

void ads1148_read_register(ads1148Obj_t* obj,uint8_t offsetaddr,uint8_t *buf,uint8_t num)
{
	uint8_t t8;
	uint8_t i;
	uint8_t cmd;
	if(num<1)return;
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
	cmd=ADS1148_CMD_RREG;
	cmd |= (offsetaddr & 0x0f);
	t8=obj->ads1148_write_read_via_spi(cmd);
	t8=obj->ads1148_write_read_via_spi(num-1);
	for(i=0;i<num;i++){
		*buf=obj->ads1148_write_read_via_spi(ADS1148_CMD_NOP);
		buf++;
	}
	//obj->pins_sck_set_hight();
	delay_us(10);
	obj->pins_cs_set_hight();
}
//api
void ads1148_slef_calibration(ads1148Obj_t* obj)
{
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
	obj->ads1148_write_read_via_spi(ADS1148_CMD_SELFOCAL);
	delay_ms(30);//bug
	obj->pins_cs_set_hight();
}

void ads1148_set_channle_normal(ads1148Obj_t* obj,uint8_t chp,uint8_t chn)
{
	st_ads1148RegMUX0 mux0Temp;

	//mux0Temp.mux0=obj->ads1148Regs.regs.regMUX0.mux0;
	ads1148_read_register(obj,ADS1148_REG_ADDR_MUX0,(uint8_t*)&mux0Temp,1);
    mux0Temp.bits.mux_sp=chp;
    mux0Temp.bits.mux_sn=chn;
    obj->ads1148Regs.regs.regMUX0.mux0=mux0Temp.mux0;
    ads1148_write_register(obj,ADS1148_REG_ADDR_MUX0,(uint8_t*)&mux0Temp,1);

}
void ads1148_set_bcs(ads1148Obj_t* obj,uint8_t bcs)
{
	st_ads1148RegMUX0 mux0Temp;
	//mux0Temp.mux0=obj->ads1148Regs.regs.regMUX0.mux0;
	ads1148_read_register(obj,ADS1148_REG_ADDR_MUX0,(uint8_t*)&mux0Temp,1);
    mux0Temp.bits.bcs=bcs;

    obj->ads1148Regs.regs.regMUX0.mux0=mux0Temp.mux0;
    ads1148_write_register(obj,ADS1148_REG_ADDR_MUX0,(uint8_t*)&mux0Temp,1);
}

void ads1148_set_vbias(ads1148Obj_t* obj,uint8_t vbias)
{
    uint8_t t8;
    t8=vbias;
    ads1148_write_register(obj,ADS1148_REG_ADDR_VBIAS,(uint8_t*)&t8,1);
	
}

void ads1148_set_vref(ads1148Obj_t* obj,uint8_t vref)
{
	ads1148RegMUX1_t mux1Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_MUX1,(uint8_t*)&mux1Temp,1);
	if(vref>ADS1148_REFSELT_INREF_CON_REF0)vref=ADS1148_REFSELT_INREF_CON_REF0;
    if(vref<=ADS1148_REFSELT_REF1){
        mux1Temp.bits.vrefcon=ADS1148_VREFCON_INREF_OFF;
    }else{
        mux1Temp.bits.vrefcon=ADS1148_VREFCON_INREF_ON;
    }
	mux1Temp.bits.refselt=vref;
    ads1148_write_register(obj,ADS1148_REG_ADDR_MUX1,(uint8_t*)&mux1Temp,1);
}

void ads1148_set_muxcal(ads1148Obj_t* obj,uint8_t muxcal)
{
	ads1148RegMUX1_t mux1Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_MUX1,(uint8_t*)&mux1Temp,1);
	if(muxcal>ADS1148_MUXCAL_DVDD_DVSS_DIV_4)muxcal=ADS1148_MUXCAL_DVDD_DVSS_DIV_4;
	mux1Temp.bits.muxcal=muxcal;
    ads1148_write_register(obj,ADS1148_REG_ADDR_MUX1,(uint8_t*)&mux1Temp,1);
}

void ads1148_set_data_rate(ads1148Obj_t* obj,uint8_t dr)
{
    ads1148RegSYS0_t sys0Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_SYS0,(uint8_t*)&sys0Temp,1);
	sys0Temp.bits.dr=dr;
    ads1148_write_register(obj,ADS1148_REG_ADDR_SYS0,(uint8_t*)&sys0Temp,1);
}

void ads1148_set_ani_pga(ads1148Obj_t* obj,uint8_t pga)
{
    ads1148RegSYS0_t sys0Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_SYS0,(uint8_t*)&sys0Temp,1);
	sys0Temp.bits.pga=pga;
    ads1148_write_register(obj,ADS1148_REG_ADDR_SYS0,(uint8_t*)&sys0Temp,1);
}

void ads1148_set_imag_idac(ads1148Obj_t* obj,uint8_t imag)
{
    ads1148RegIDAC0_t idac0Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_IDAC0,(uint8_t*)&idac0Temp,1);
	idac0Temp.bits.imag=imag;
    ads1148_write_register(obj,ADS1148_REG_ADDR_IDAC0,(uint8_t*)&idac0Temp,1);
}

void ads1148_set_drdy_mode(ads1148Obj_t* obj,uint8_t mode)
{
    ads1148RegIDAC0_t idac0Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_IDAC0,(uint8_t*)&idac0Temp,1);
	idac0Temp.bits.drdyMode=mode;
    ads1148_write_register(obj,ADS1148_REG_ADDR_IDAC0,(uint8_t*)&idac0Temp,1);
}

void ads1148_set_idac1_pins(ads1148Obj_t* obj,uint8_t i1dir)
{
    ads1148RegIDAC1_t idac1Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
	idac1Temp.bits.i1dir=i1dir;
    ads1148_write_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
}

void ads1148_set_idac2_pins(ads1148Obj_t* obj,uint8_t i2dir)
{
    ads1148RegIDAC1_t idac1Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
	idac1Temp.bits.i2dir=i2dir;
    ads1148_write_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
}

void ads1148_set_idac12_pins(ads1148Obj_t* obj,uint8_t i1dir,uint8_t i2dir)
{
    ads1148RegIDAC1_t idac1Temp;
	ads1148_read_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
	idac1Temp.bits.i2dir=i2dir;
    idac1Temp.bits.i1dir=i1dir;
    ads1148_write_register(obj,ADS1148_REG_ADDR_IDAC1,(uint8_t*)&idac1Temp,1);
}

void ads1148_get_all_register(ads1148Obj_t* obj)
{
	ads1148_read_register(obj,ADS1148_REG_ADDR_MUX0,obj->ads1148Regs.buf,14);
}
//
void ads1148_init_obj_0(void)
{
	ads1148Chip0.chipNm=0;
    ads1148Chip0.pins_sck_set_hight=ads1148_hal_sck_set_hight;
    ads1148Chip0.pins_sck_set_low=ads1148_hal_sck_set_low;
    
    ads1148Chip0.pins_dout_set_hight=ads1148_hal_dout_set_hight;
    ads1148Chip0.pins_dout_set_low=ads1148_hal_dout_set_low;
    
    ads1148Chip0.pins_din_get=ads1148_hal_din_get;
    
    ads1148Chip0.pins_cs_set_hight=ads1148_hal_cs_0_set_hight;
    ads1148Chip0.pins_cs_set_low=ads1148_hal_cs_0_set_low;
    
    ads1148Chip0.pins_start_set_hight=ads1148_hal_start_0_set_hight;
    ads1148Chip0.pins_start_set_low=ads1148_hal_start_0_set_low;
    
    ads1148Chip0.pins_drdy_get=ads1148_hal_drdy_0_get;
    
    ads1148Chip0.pins_init=ads1148_hal_port_init_chip0;
    ads1148Chip0.ads1148_write_read_via_spi=ads1148_hal_write_read_byte;
 
}
void ads1148_init_obj_1(void)
{
	ads1148Chip1.chipNm=0;
    ads1148Chip1.pins_sck_set_hight=ads1148_hal_sck_set_hight;
    ads1148Chip1.pins_sck_set_low=ads1148_hal_sck_set_low;
    
    ads1148Chip1.pins_dout_set_hight=ads1148_hal_dout_set_hight;
    ads1148Chip1.pins_dout_set_low=ads1148_hal_dout_set_low;
    
    ads1148Chip1.pins_din_get=ads1148_hal_din_get;
    
    ads1148Chip1.pins_cs_set_hight=ads1148_hal_cs_1_set_hight;
    ads1148Chip1.pins_cs_set_low=ads1148_hal_cs_1_set_low;
    
    ads1148Chip1.pins_start_set_hight=ads1148_hal_start_1_set_hight;
    ads1148Chip1.pins_start_set_low=ads1148_hal_start_1_set_low;
    
    ads1148Chip1.pins_drdy_get=ads1148_hal_drdy_1_get;
    
    ads1148Chip1.pins_init=ads1148_hal_port_init_chip1;
    ads1148Chip1.ads1148_write_read_via_spi=ads1148_hal_write_read_byte;
}
void ads1148_set_sync(ads1148Obj_t* obj)
{
    uint8_t ret;
	#if ADS1148_SCK_IDLE_STATUE==0
    obj->pins_sck_set_low();
	#else
	obj->pins_sck_set_hight();
	#endif
	obj->pins_cs_set_low();
    ret=obj->ads1148_write_read_via_spi(ADS1148_CMD_RESET);
    delay_ms(1);
    ret=obj->ads1148_write_read_via_spi(ADS1148_CMD_SYNC);
    delay_ms(1);
    ret=obj->ads1148_write_read_via_spi(ADS1148_CMD_SYNC);
	delay_ms(1);
	obj->pins_cs_set_hight();
}
const uint8_t ads1148DefaultBuf[]={1,0,0,0,0,0,0,0,0,0x40,0x90,0xff};
void ads1148_init_all(void)
{
	ads1148_init_obj_0();
	ads1148_init_obj_1();
	ads1148Chip0.pins_init();
	ads1148_send_cmd(&ads1148Chip0,ADS1148_CMD_RESET);
    delay_ms(10);
    //ads1148_set_sync(&ads1148Chip0);
	//delay_ms(1);
    //ads1148_write_register(&ads1148Chip0,ADS1148_REG_ADDR_MUX0,(uint8_t*)ads1148DefaultBuf,sizeof(ads1148DefaultBuf));
    //delay_ms(1);
	ads1148_get_all_register(&ads1148Chip0);
    
    ads1148Chip1.pins_init();
	ads1148_send_cmd(&ads1148Chip1,ADS1148_CMD_RESET);
	delay_ms(10);
    //ads1148_set_sync(&ads1148Chip1);
	//delay_ms(1);  
	ads1148_get_all_register(&ads1148Chip1);
    asm("NOP");
}
void ads1148_start_convert(ads1148Obj_t* obj)
{
	obj->pins_start_set_hight();
}
void ads1148_stop_convert(ads1148Obj_t* obj)
{
	obj->pins_start_set_low();
}
void ads1148_waite_convert(ads1148Obj_t* obj)
{
    while(!(obj->pins_drdy_get())){
    asm("nop");
    }
    while(obj->pins_drdy_get())
    {
        asm("nop");
    };
}
void ads1148_test(void)
{
    uint16_t t16;
	ads1148_set_bcs(&ads1148Chip0,ADS1148_BCS_10uA0);
	ads1148_set_vref(&ads1148Chip0,ADS1148_REFSELT_INREF);
	ads1148_set_muxcal(&ads1148Chip0,ADS1148_MUXCAL_AVDD_AVSS_DIV_4);
	ads1148_set_ani_pga(&ads1148Chip0,ADS1148_PGA_1);
    delay_ms(10);
    ads1148_get_all_register(&ads1148Chip0);
    delay_ms(10);
	ads1148_start_convert(&ads1148Chip0);
    delay_us(5);
    while(1){
        ads1148_waite_convert(&ads1148Chip0);
        delay_us(5);
        t16=ads1148_read_data(&ads1148Chip0);
		asm("nop");
		asm("nop");
    }
	
	
}