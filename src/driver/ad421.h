//file name:ad421.h
#ifndef __ad421_h__
#define __ad421_h__

#ifdef __cplusplus
extern "C"{
#endif

	#define AD421_DATA_1_PIN	PIN15
	#define AD421_DATA_1_PORT	portg
	
	#define AD421_CLOCK_1_PIN	PIN5
	#define AD421_CLOCK_1_PORT	porte
	
	#define AD421_LATCH_1_PIN	PIN6
	#define AD421_LATCH_1_PORT	porte
	
	#define AD421_DATA_2_PIN	PIN7
	#define AD421_DATA_2_PORT	porte
	
	#define AD421_CLOCK_2_PIN	PIN1
	#define AD421_CLOCK_2_PORT	portc
	
	#define AD421_LATCH_2_PIN	PIN2
	#define AD421_LATCH_2_PORT	portc
	
	
	typedef struct{
		void (*pins_init)(void);
		void (*pins_deinit)(void);
		void (*set_idac_value)(uint16_t x);
	}stAd421Obj,ad421Obj_t;
	
	extern  ad421Obj_t ad421ObjChip0;
	extern  ad421Obj_t ad421ObjChip1;
	
	extern void ad421_all_obj_init(void);
	extern void ad421_test(void);
    
    extern void ad421_chip0_set_idac_value(uint16_t x);
    extern void ad421_chip1_set_idac_value(uint16_t x);
	
#ifdef __cplusplus
}
#endif

#endif
