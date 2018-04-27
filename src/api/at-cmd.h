//file:at-cmd.h
#ifndef __at_cmd_h__
#define __at_cmd_h__
#ifdef __cplusplus
	extern "C"{
#endif

	#include <stdint.h>
	#include <stdbool.h>
	
	typedef struct __st_st_ATcmdDef{
		const uint8_t* cmdStr;
		//const uint8_t* promptStr;
		//const uint8_t* prompErrStr;
		//const uint8_t* respStr;
		const uint8_t* okMatchStr;
		const uint8_t* errMatchStr;
		//const uint8_t* respStrEx;
		//const em_nbiotErrorCode errcode;
		//const uint8_t respExTimes;
		//const bool retAssert;
	}st_ATcmdDef;
	
	extern const st_ATcmdDef AT_CMD_AT;
	extern const st_ATcmdDef AT_CMD_ATI;
	extern const st_ATcmdDef AT_CMD_QSECSWT;
	extern const st_ATcmdDef AT_CMD_QSECSWT_S;
	
	extern const st_ATcmdDef AT_CMD_CFUN_0;
	extern const st_ATcmdDef AT_CMD_CFUN_R;
	extern const st_ATcmdDef AT_CMD_CFUN;
	extern const st_ATcmdDef AT_CMD_CMEE;
	extern const st_ATcmdDef AT_CMD_NRB;
	extern const st_ATcmdDef AT_CMD_CMI;
	extern const st_ATcmdDef AT_CMD_CGSN;
	extern const st_ATcmdDef AT_CMD_NBAND_R;
	extern const st_ATcmdDef AT_CMD_CGDCONT;
	extern const st_ATcmdDef AT_CMD_CGDCONT_R;
	extern const st_ATcmdDef AT_CMD_CGDCONT_COAP;
	extern const st_ATcmdDef AT_CMD_CGATT_R;
	extern const st_ATcmdDef AT_CMD_CGATT_R_COAP;
	extern const st_ATcmdDef AT_CMD_CGATT;
	extern const st_ATcmdDef AT_CMD_CSQ;
	extern const st_ATcmdDef AT_CMD_CEREG_R;
	extern const st_ATcmdDef AT_CMD_NSOCR;
	extern const st_ATcmdDef AT_CMD_NCDP;
	extern const st_ATcmdDef AT_CMD_NCDP_R;
	extern const st_ATcmdDef AT_CMD_NSOCR_R;
	extern const st_ATcmdDef AT_CMD_NSOCL;
	extern const st_ATcmdDef AT_CMD_NSOCT;
	extern const st_ATcmdDef AT_CMD_NSORF;
	
	extern const st_ATcmdDef AT_CMD_CGMR;
	extern const st_ATcmdDef AT_CMD_NCCID;
	
	extern const st_ATcmdDef AT_CMD_CEREG_Rn;
	extern const st_ATcmdDef AT_CMD_CEREG;
	
	extern const st_ATcmdDef AT_CMD_NQMGR;
	extern const st_ATcmdDef AT_CMD_NMGR;
	
	extern const st_ATcmdDef AT_CMD_CGPADDR;
	
	//extern const st_ATcmdDef AT_CMD_CMEE;
	extern const st_ATcmdDef AT_CMD_NUESTATS;

#ifdef __cplusplus
	}
#endif
#endif
//file end

