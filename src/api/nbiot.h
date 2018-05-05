#ifndef __nbiot_h__
#define __nbiot_h__

#ifdef __cplusplus
extern "C"{
#endif
	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include <stdbool.h>

    typedef enum{
        AT_CMD_PROCESS_NOTHING=0,
        AT_CMD_PROCESS_READY_SEND,
		AT_CMD_PROCESS_WAITE_RESP,
		AT_CMD_PROCESS_WAITE_RESP_TM_OUT,
		AT_CMD_PROCESS_REC_RESP,
		AT_CMD_PROCESS_OK,
		AT_CMD_PROCESS_ERROR,
    }stAtCmdProcessSm,atCmdProcessSm_t;
	
    extern atCmdProcessSm_t atCmdSm;
    
 	typedef enum{
        NB_PSM_SM_NOTHING,
		NB_PSM_SM_NRZ,
		NB_PSM_SM_AT,
		NB_PSM_SM_ATI,
		NB_PSM_SM_CMEE,
		NB_PSM_SM_CGMR,
		NB_PSM_SM_CFUN,
		NB_PSM_SM_CFUNR,

		NB_PSM_SM_CGCCONT,
		NB_PSM_SM_CGCCONT_R,
		NB_PSM_SM_NCDP,
		NB_PSM_SM_NCDPR,
		NB_PSM_SM_CGATT,
		NB_PSM_SM_CGATTR,
		NB_PSM_SM_CGATTR_SLOW,
		NB_PSM_SM_CGATTR_FAST,
		
		NB_PSM_SM_CIMI,
		NB_PSM_SM_NCCID,
		NB_PSM_SM_CGSN,	
		NB_PSM_SM_CSQ,
		NB_PSM_SM_NUESTATS,
		NB_PSM_SM_QSECSWT,
		NB_PSM_SM_QSECSWT_R,
		
		NB_PSM_SM_SEND,
		NB_PSM_SM_RECEIVE,
		NB_PSM_SM_PSM,
		NB_PSM_SM_NO_NET,
                
             
	}em_nbPsmStateMachine,nbPsmStateMachine_t;
	extern nbPsmStateMachine_t nbPsmStateMachine;
    
    extern uint16_t nbBufLen;
    #define NB_BUFFER_LEN UART_2_REC_BUF_LEN
    extern uint8_t nbBuf[NB_BUFFER_LEN];
    
#ifdef __cplusplus
}
#endif

#endif
//file end
