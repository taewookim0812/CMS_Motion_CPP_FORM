/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*----------------------------------------------------------------------------
*//**\file
* \brief    Definition of Moman protocol API commands and values
*
*  Note:
*	Motion Manager standard commands "eMomancmd" are to be transfered in
*	parameter 'subIndex' of the API function mmProtSendCommand() with parameter
*	index = 0x0000. Set parameter dataLen = 0 for request commands and
*	dataLen > 0 to set a value in parameter data.
*	The answer of request commands can be read out with a subsequent
*	call to the API function mmProtWaitAnswer().
*/
//---------------------------------------------------------------------------

#ifndef MOMANCMDH
#define MOMANCMDH

/* Callback function pointers */
typedef void (*tdmmProtDataCallback)(void);
typedef void (*tdmmProtTraceValuesCallback)(int nodeNr, unsigned int value[], int timecode);
//---------------------------------------------------------------------------

/* Return values */
enum eMomanprot {
	eMomanprot_ok_bootup = 2,
	eMomanprot_ok_async = 1,
	eMomanprot_ok = 0,
	eMomanprot_error = -1,
	eMomanprot_error_timeout = -2,
	eMomanprot_error_cmd = -3,
	eMomanprot_error_emcy = -4,
	eMomanprot_error_param = -5,
	eMomanprot_error_accessdenied = -6,
	eMomanprot_error_init = -7,
	eMomanprot_noData = -8
};
//---------------------------------------------------------------------------

/*! Standard commands for mmProtSendCommand(), parameter subIndex (index = 0x0000) */
enum eMomancmd {
	//General:
	eMomancmd_kn = 1,
	eMomancmd_rm = 2,
	eMomancmd_serNr = 3,
	eMomancmd_save = 4,
	eMomancmd_restore = 5,
	eMomancmd_ver = 6,
	eMomancmd_motname = 7,
	//NMT:
	eMomancmd_start = 10,
	eMomancmd_stop = 11,
	eMomancmd_preop = 12,
	eMomancmd_reset = 13,
	eMomancmd_resetcom = 14,
	eMomancmd_startall = 15,
	//Device Control:
	eMomancmd_shutdown = 16,
	eMomancmd_switchon = 17,
	eMomancmd_disable = 18,
	eMomancmd_quickstop = 19,
	eMomancmd_DiOp = 20,
	eMomancmd_EnOp = 21,
	eMomancmd_faultreset = 22,
	eMomancmd_MA = 23,
	eMomancmd_MR = 24,
	eMomancmd_HS = 25,
	//Standard:
	eMomancmd_saveCom = 30,
	eMomancmd_saveApp = 31,
	eMomancmd_restCom = 32,
	eMomancmd_restApp = 33,
	//Special:
	eMomancmd_setCmdType = 250,
	eMomancmd_gprogseq = 251,
	eMomancmd_HistoryOff = 252,
	eMomancmd_XonXoff = 253,			/*!< data = 1: on, data = 0: off (MC2 RS232 only) */
	eMomancmd_SendBinMode = 254,		/*!< data_LB = mode1, data_HB = mode2 (MC2 RS232 only) */
	eMomancmd_SendBin = 255,			/*!< data_LB = value (only MC2 RS232) */
};
//---------------------------------------------------------------------------

/*! Answer modes for mmProtWaitAnswer(), parameter answ */
enum eWaitMode {
	eWaitMode_Int = 0,					/*< Int answer as string */
	eWaitMode_String = 1,				/*< String answer as string */
	eWaitMode_BinData = 2,           /*< Binary array > 4 byte */
	eWaitMode_noAsync_noAck = 10,		/*!< MC2 RS232 only */
	eWaitMode_noAck = 11,				/*!< MC2 RS232 only */
	eWaitMode_noAsync = 12,				/*!< MC2 RS232 only */
	eWaitMode_someAsync = 13,			/*!< MC2 RS232 only */
	eWaitMode_Bin = 14,					/*!< MC2 RS232 only */
	eWaitMode_Id = 255,					/*!< > 0xFF: Wait for answer with specified identifier */
};
//---------------------------------------------------------------------------

/*! Device modes for mmProtScanNode(), parameter devicemode */
enum eDeviceMode {
	eDeviceMode_Faulhaber = 0,			/*!< standard FAULHABER firmware */
	eDeviceMode_Bootloader = 1,		/*!< Bootloader active */
	eDeviceMode_Testprog = 2,			/*!< Testprogram */
	eDeviceMode_AnyDrive = 3,			/*!< not a FAULHABER drive */
	eDeviceMode_AnyDevice = 4,			/*!< not a drive */
};
//---------------------------------------------------------------------------

/*! Command types for mmProtLoadCommandSet(), parameter cmdType */
enum eCmdType {
	eCmdType_LoadedCommandSet = -1,
	eCmdType_Default = 0,
	eCmdType_MC3 = 1,
	eCmdType_CO = 2,
	eCmdType_CF = 3,
};
//---------------------------------------------------------------------------

/*! Return values for mmProtLoadCommandSet() */
enum eCommandSet {
	eCommandSet_invalidCmdType = -1,
	eCommandSet_Unknown = 0,
	eCommandSet_MC3RS = 1,			//halfCANopen
	eCommandSet_MC3USB = 2,			//halfCANopen
	eCommandSet_MC3CAN = 3,			//fullCANopen
	eCommandSet_MC2RS = 4,			//ASCII
	eCommandSet_MC2CAN = 5,			//fullCANopen
	eCommandSet_NET = 6,				//only SDO, EMCY
};
//---------------------------------------------------------------------------

/*! Return values for mmProtCheckMotionCommand() and mmProtCheckCommand() */
enum eCheckCommand {
	eCheckCommand_noAction = 0,
	eCheckCommand_State = 1,		/*!< Command could change NMT, Device state or Opmode */
	eCheckCommand_SwitchOn = 2, 	/*!< Command switches motor on */
	eCheckCommand_Save = 3,			/*!< Is a Save command */
	eCheckCommand_Restore = 4,		/*!< Is a Restore command */
	eCheckCommand_Reset = 5,		/*!< Is a Reset command */
};
//---------------------------------------------------------------------------

/*! Return values for mmProtDecodeCmdStr() and mmProtDecodeAnswStr() */
enum eDecoded {
	eDecoded_none = 0,    		/*!< none decoded */
	eDecoded_SOBJ = 1,			/*!< SOBJ command decoded */
	eDecoded_GOBJ = 2,			/*!< GOBJ command decoded*/
	eDecoded_Bootup = 3,
	eDecoded_NMT = 4,
	eDecoded_NMTRequest = 5,
	eDecoded_Heartbeat = 6,
	eDecoded_Statusword = 7,
	eDecoded_EMCY = 8,
};
//---------------------------------------------------------------------------

/*! Trace modes for STraceSetup::mode */
static const int cTraceMode_Logger = 0;
static const int cTraceMode_Recorder = 1;
//---------------------------------------------------------------------------
static const int cTrace_InvalidTimecode = -1;	/*!< No or invalid timecode in trace data */
//---------------------------------------------------------------------------

/*! TraceSetup structure for mmProtSetupTrace() */
typedef struct {
	bool run;				/*!< run or stop tracing */
	int nodeNr;				/*!< node number to be traced */
	int chan;				/*!< 0 = standard channel, 1 = logger uses CAN-PDOs */
	int mode;				/*!< 0 = logger (single requests), 1 = recorder (buffered) */
	int source[4];			/*!< trace parameter: OD Index/Subindex or number/address */
	int sourceLen[4];		/*!< data length in byte; 0 = source not used */
	int sourceType[4];	/*!< SrcType: 0 = OD, 1 = number/address; CAN logger: cobId of trace pdo */
	int buffer;				/*!< buffer size (number of samples to be recorded) */
	int sampletime;		/*!< sampletime in recorder mode */
} STraceSetup;
//---------------------------------------------------------------------------

/*! TraceTrigger structure for mmProtSetupTrace() */
typedef struct {
	int mode;				/*!< 0 = no trigger, 1 = singleshot, 2 = retriggered */
	int source;				/*!< trigger parameter: OD Index/Subindex or number/address */
	int sourceType;		/*!< TrigType: 0 = OD, 1 = number/address */
	int threshold;			/*!< trigger if source value > or < threshold value */
	int edge;				/*!< 0 = rising (>), 1 = falling (<) */
	int delay;				/*!< triggerdelay */
} STraceTrigger;
//---------------------------------------------------------------------------

/*! Return values for mmProtTraceRequest() */
enum eTraceRequest {
	eTraceRequest_inactive = 0,
	eTraceRequest_sent = 1,
	eTraceRequest_stateWaitResponse = 2,
	eTraceRequest_stateWaitForTrigger = 3,
	eTraceRequest_stateRecordingInProgress = 4,
	eTraceRequest_stateRecordingFinished = 5,
	eTraceRequest_errorReadBuffer = 6,
};
//---------------------------------------------------------------------------

/*! mode values for mmProtTraceRequest() */
enum eTraceRequestMode {
	eTraceRequestMode_standard = 0,
	eTraceRequestMode_checkState = 1,
	eTraceRequestMode_readRecordedData = 2,
};
//---------------------------------------------------------------------------

/*! State values for mmProtGetCommunicationHistory(), parameter state */
enum eHistoryState {
	eHistoryState_SendData = 0,
	eHistoryState_ReceiveWaitData = 1,
	eHistoryState_ReceiveData = 2,
	eHistoryState_Message = 3,
};
//---------------------------------------------------------------------------

/*! Error values for mmProtGetCommunicationHistory(), parameter error */
enum eHistoryError {
	eHistoryError_Ok = 0,
	eHistoryError_SendError = 1,
	eHistoryError_ReceiveError = 2,
	eHistoryError_ReceiveTimeout = 3,
	eHistoryError_ReceiveEmcy = 4,
	eHistoryError_UnexpectedData = 5
};
//---------------------------------------------------------------------------

/*! LSS-Mode */
enum eLSSMode {
	eLSSMode_normal = 0,				/*!< LSS switch normal mode */
	eLSSMode_configGlobal = 1,		/*!< LSS switch config mode global */
	eLSSMode_configSelective = 2,	/*!< LSS switch config mode selective */
	eLSSMode_IdentifySlave = 3,	/*!< LSS identify remote slave */
	eLSSMode_SelectNodeNr = 4		/*!< Select nodeNr */
};
//---------------------------------------------------------------------------

#endif /* MOMANCMDH */
//---------------------------------------------------------------------------

