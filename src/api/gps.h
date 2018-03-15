#ifndef __gps_h__
#define __gps_h__

#ifdef __cplusplus
extern "C"{
#endif

	#include "../../mcc_generated_files/mcc.h"
    #include <stdint.h>
	#include <stdbool.h>
	
	typedef enum{
		GPS_IDLE=0,
		GPS_RUN,
	}gpsStatus_t;
	extern gpsStatus_t gpsStatus;
	extern bool getedGpsGprmc;
	extern bool getedGpsGpgga;
	
	#define fi_gps_inf_whole() (gpsGprmc & gpsGpgga)
	//$GPRMC,013732.000,A,3150.7238,N,11711.7278,E,0.00,0.00,220413,,,A*68<CR><LF>
	extern int32_t Latitude;
	extern int32_t Longitude;
	//
	

#ifdef __cplusplus
}
#endif

#endif
//file end
