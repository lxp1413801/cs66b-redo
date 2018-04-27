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
    extern uint16_t nbRecLen;
    #define NB_REC_BUFFER_LEN UART_2_REC_BUF_LEN
    extern uint8_t nbRecBuf[NB_REC_BUFFER_LEN];
    
#ifdef __cplusplus
}
#endif

#endif
//file end
