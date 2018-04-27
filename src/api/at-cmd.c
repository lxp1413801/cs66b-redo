#include "../includes/includes.h"

const st_ATcmdDef AT_CMD_AT=
{
	"at\r\n",
	"\r\nOK\r\n",
	NULL,
};
const st_ATcmdDef AT_CMD_ATI=
{
	"ati\r\n",
	"\r\nOK\r\n",
	NULL,
};
//AT+QSECSWT?
const st_ATcmdDef AT_CMD_QSECSWT=
{
	"AT+QSECSWT?\r\n",
	"\r\nOK\r\n",
	NULL,
};
//AT+QSECSWT=2 
const st_ATcmdDef AT_CMD_QSECSWT_S=
{
	"AT+QSECSWT=0\r\n",
	"\r\nOK\r\n",
	NULL,
};
//+CFUN?
//"\r\n+CFUN:1\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_CFUN_0=
{
	"AT+CFUN=0\r\n",
	"OK",
	"ERROR",
};
const st_ATcmdDef AT_CMD_CFUN_R=
{
	"AT+CFUN?\r\n",
	"+CFUN:1",
	"+CFUN:0",
};

const st_ATcmdDef AT_CMD_CFUN=
{
	"AT+CFUN=1\r\n",
	"\r\nOK\r\n",
	NULL,
};
//AT+CMEE=1
const st_ATcmdDef AT_CMD_CMEE=
{
	"AT+CMEE=1\r\n",
	"OK",
	NULL,
};
const st_ATcmdDef AT_CMD_NRB=
{
	"AT+NRB\r\n",
	"REBOOTING\r\n",
	NULL,
};

//AT+CIMI
//"\r\n460111116906905\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_CMI=
{
	"AT+CIMI\r\n",
	"OK",
	"ERROR",
};

//AT+CGSN=1
//"\r\n???????????????\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_CGSN=
{
	"AT+CGSN=1\r\n",
	"OK",
	"ERROR",
};
//AT+NUESTATS
const st_ATcmdDef AT_CMD_NUESTATS=
{
	"AT+NUESTATS\r\n",
	"OK",
	"ERROR",
};
//AT+NBAND?
//"\r\n+NBAND:?\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_NBAND_R=
{
	"AT+NBAND?\r\n",
	"OK",
	"ERROR",
};

//AT+CGDCONT=1,"IP","ctnet"
const st_ATcmdDef AT_CMD_CGDCONT=
{
	"AT+CGDCONT=1,\"IP\",\"ctnet\"\r\n",
	"OK",
	"ERROR",
};
//AT+CGDCONT=1,"IP","ctnb"

const st_ATcmdDef AT_CMD_CGDCONT_COAP=
{
	"AT+CGDCONT=1,\"IP\",\"ctnb\"\r\n",
	"OK",
	"ERROR",
};
//AT+CGDCONT?
const st_ATcmdDef AT_CMD_CGDCONT_R=
{
	"AT+CGDCONT?\r\n",
	"1,\"IP\",\"ctnb\"",
	"ERROR",
};
//AT+CGATT=1
const st_ATcmdDef AT_CMD_CGATT=
{
	"AT+CGATT=1\r\n",	//cmdstr;
	"OK",
	"ERROR",
};

const st_ATcmdDef AT_CMD_CGATT_R=
{
	"AT+CGATT?\r\n",	//cmdstr;
	"\r\n+CGATT:1\r\n",
	NULL,
};
const st_ATcmdDef AT_CMD_CGATT_R_COAP=
{
	"at+cgatt=?\r\n",	//cmdstr;
	"\r\n+CGATT:(0,1)\r\n",
	NULL,
};
//AT+CSQ
//"\r\n+CSQ:??,??\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_CSQ=
{
	"AT+CSQ\r\n",
	"OK",
	"ERROR",
};

//AT+CEREG?
//	"\r\n+CEREG:?,?\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_CEREG_R=
{
	"AT+CEREG?\r\n",	//cmdstr;
	"+CEREG:0,1",
	NULL,
};

const st_ATcmdDef AT_CMD_CEREG_Rn=
{
	"AT+CEREG=?\r\n",	//cmdstr;
	"+CEREG:2",
	"ERROR",
};

const st_ATcmdDef AT_CMD_CEREG=
{
	"AT+CEREG=1\r\n",	//cmdstr;
	"OK",
	"ERROR",
};

//AT+NSOCR=DGRAM,17,XXXX,1
//211.149.185.137 :28881
//creates a socket 
//AT+NSOCR=DGRAM,17,XXXX,1
//AT+NSOCR=DGRAM,17,5683,1
//"\r\n+CEREG:?,?\r\n\r\nOK\r\n",	//resp00;
const st_ATcmdDef AT_CMD_NSOCR=
{
	"AT+NSOCR=DGRAM,17,9512,1\r\n",
	"OK",
	"ERROR",
};

const st_ATcmdDef AT_CMD_NCDP=
{
	"AT+NCDP=117.60.157.137\r\n",
	"OK",
	"ERROR",
};
const st_ATcmdDef AT_CMD_NCDP_R=
{
	"AT+NCDP?\r\n",
	"OK",
	"ERROR",
};
//AT+NSOCR
const st_ATcmdDef AT_CMD_NSOCR_R=
{
	"AT+NSOCR=?",
	"OK",
	"ERROR",
};
//close socket
const st_ATcmdDef AT_CMD_NSOCL=
{
	"AT+NSOCL=0\r\n",	//cmdstr;
	"OK",
	"ERROR",
};


const st_ATcmdDef AT_CMD_NSORF=
{
	
	"AT+NSORF=0,256\r\n",	//cmdstr;
	"OK",
	"ERROR",
};
//AT+CGMR
const st_ATcmdDef AT_CMD_CGMR=
{
	
	"AT+CGMR\r\n",	//cmdstr;
	"OK",
	"ERROR",

};

const st_ATcmdDef AT_CMD_NCCID=
{
	
	"AT+NCCID\r\n",	//cmdstr;

	"OK",
	"ERROR",

};

//AT+NQMGR
const st_ATcmdDef AT_CMD_NQMGR=
{
	"AT+NQMGR\r\n",	//cmdstr;
	"OK",
	"ERROR",
};
//AT+NMGR
const st_ATcmdDef AT_CMD_NMGR=
{
	"AT+NMGR\r\n",	//cmdstr;
	"OK",
	"ERROR",
};

//AT+CGPADDR
const st_ATcmdDef AT_CMD_CGPADDR=
{
	"AT+CGPADDR\r\n",	//cmdstr;
	"OK",
	"ERROR",
};



//file end
