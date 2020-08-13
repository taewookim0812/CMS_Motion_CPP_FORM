/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*----------------------------------------------------------------------------
*//**\file
* \brief    Definition of the Moman protocol API
*/
//---------------------------------------------------------------------------

#ifndef MOMANPROTH
#define MOMANPROTH

#ifdef BUILD_MOMANPROT
#    define MOMANPROT_API __declspec(dllexport)
#else
#    define MOMANPROT_API __declspec(dllimport)
#endif
//---------------------------------------------------------------------------


/* API function pointers */
typedef eMomanprot (__stdcall *tdmmProtInitInterface)(char* InterfaceDll,
	tdmmProtDataCallback DataReceived, tdmmProtTraceValuesCallback TraceValuesReceived);
typedef void (__stdcall *tdmmProtCloseInterface)(void);
typedef void (__stdcall *tdmmProtSetDataCallback)(tdmmProtDataCallback DataReceived);
typedef void (__stdcall *tdmmProtSetTraceValuesCallback)(
	tdmmProtTraceValuesCallback TraceValuesReceived);
typedef eMomanprot (__stdcall *tdmmProtOpenCom)(int port, int channel, int baud);
typedef void (__stdcall *tdmmProtCloseCom)(void);
typedef int (__stdcall *tdmmProtLoadCommandSet)(int cmdType);
typedef void (__stdcall *tdmmProtSetupMessageFilter)(int nodeNr, int activated,
	int cobId[], int cobIdCount);
typedef int (__stdcall *tdmmProtScanNode)(int nodeNr, const char** deviceName,
	int& deviceMode);
typedef eCheckCommand (__stdcall *tdmmProtCheckMotionCommand)(char *cmd);
typedef eCheckCommand (__stdcall *tdmmProtCheckCommand)(int index, int subIndex,
	int dataLen, int data);
typedef bool (__stdcall *tdmmProtSendMotionCommand)(char *cmd, int nodeNr);
typedef bool (__stdcall *tdmmProtSendCommand)(int nodeNr, int index, int subIndex,
	int dataLen, int data);
typedef bool (__stdcall *tdmmProtSendBuffer)(int nodeNr, int index, int subIndex,
	int dataLen, char* dataBuffer);
typedef bool (__stdcall *tdmmProtSendTelegram)(int id, char* data, int len);
typedef void (__stdcall *tdmmProtGetSendTelegram)(const char** sendTelegram,
																  const char** cmdString);
typedef eMomanprot (__stdcall *tdmmProtWaitAnswer)(int timeOut, int answ,
	const char** answData);
typedef eMomanprot (__stdcall *tdmmProtReadAnswer)(const char** answData,
	int& nodeNr, const char** cmdString, const char** receiveTelegram);
typedef bool (__stdcall *tdmmProtGetCommunicationHistory)(const char** timestamp,
	eHistoryState& state, const char** data, const char** telegram, eHistoryError& error);
typedef eMomanprot (__stdcall *tdmmProtSetupTrace)(STraceSetup& TraceSetup,
	STraceTrigger& TraceTrigger);
typedef eTraceRequest (__stdcall *tdmmProtRequestTrace)(int mode);
typedef int (__stdcall *tdmmProtConnect)(int& baudrate, bool tryBaudrates);
typedef int (__stdcall *tdmmProtFindConnection)(int scanMin, int scanMax,
	int& baudrate);
typedef eMomanprot (__stdcall *tdmmProtNetworkService)(int mode, int vendorId,
	int productCode, int revisionNumber, int serialNumber);
typedef bool (__stdcall *tdmmProtChangeBaudrate)(int baudrate, int activate);
typedef bool (__stdcall *tdmmProtChangeNodeNr)(int nodeNr);
typedef bool (__stdcall *tdmmProtGetCommunicationSettings)(int& nodeNr,
	int& baudrate);
typedef int (__stdcall *tdmmProtUnconfiguredSlavesCount)(void);
typedef const unsigned int* (_stdcall *tdmmProtSupportedBaudratesList)(int& count);
typedef eMomanprot (_stdcall *tdmmProtGetObj)(int nodeNr, int index, int subIndex,
	int& value);
typedef eMomanprot (_stdcall *tdmmProtGetInt64Obj)(int nodeNr, int index, int subIndex,
	__int64& value);
typedef eMomanprot (__stdcall *tdmmProtGetStrObj)(int nodeNr, int index, int subIndex,
	const char** value);
typedef eMomanprot (__stdcall *tdmmProtSetObj)(int nodeNr, int index, int subIndex,
	int value, int len, unsigned int& abortCode);
typedef eMomanprot (__stdcall *tdmmProtSetStrObj)(int nodeNr, int index, int subIndex,
	const char* value, unsigned int& abortCode);
typedef void (__stdcall *tdmmProtSetObjTimeout)(int timeout);
typedef const char* (__stdcall *tdmmProtGetAbortMessage)(unsigned int abortCode);
typedef const char* (__stdcall *tdmmProtGetErrorMessage)(unsigned int errorCode);
typedef eDecoded (__stdcall *tdmmProtDecodeCmdStr)(const char* cmdStr,
	int& nodeNr, int& index, int& subIndex, const char** valueStr);
typedef eDecoded (__stdcall *tdmmProtDecodeAnswStr)(const char* answStr, __int64& value);
//---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */
MOMANPROT_API eMomanprot __stdcall mmProtInitInterface(char* InterfaceDll,
	tdmmProtDataCallback DataReceived, tdmmProtTraceValuesCallback TraceValuesReceived);
MOMANPROT_API void __stdcall mmProtCloseInterface(void);
MOMANPROT_API void __stdcall mmProtSetDataCallback(tdmmProtDataCallback DataReceived);
MOMANPROT_API void __stdcall mmProtSetTraceValuesCallback(
	tdmmProtTraceValuesCallback TraceValuesReceived);
MOMANPROT_API eMomanprot __stdcall mmProtOpenCom(int port, int channel, int baud);
MOMANPROT_API void __stdcall mmProtCloseCom(void);
MOMANPROT_API int __stdcall mmProtLoadCommandSet(int cmdType);
MOMANPROT_API void __stdcall mmProtSetupMessageFilter(int nodeNr, int activated,
	int cobId[], int cobIdCount);
MOMANPROT_API int __stdcall mmProtScanNode(int nodeNr, const char** deviceName,
	int& deviceMode);
MOMANPROT_API eCheckCommand __stdcall mmProtCheckMotionCommand(char *cmd);
MOMANPROT_API eCheckCommand __stdcall mmProtCheckCommand(int index, int subIndex,
	int dataLen, int data);
MOMANPROT_API bool __stdcall mmProtSendMotionCommand(char *cmd, int nodeNr=-1);
MOMANPROT_API bool __stdcall mmProtSendCommand(int nodeNr, int index, int subIndex,
	int dataLen, int data);
MOMANPROT_API bool __stdcall mmProtSendBuffer(int nodeNr, int index, int subIndex,
	int dataLen, char* dataBuffer);
MOMANPROT_API bool __stdcall mmProtSendTelegram(int id, char* data, int len);
MOMANPROT_API void __stdcall mmProtGetSendTelegram(const char** sendTelegram,
																	const char** cmdString);
MOMANPROT_API eMomanprot __stdcall mmProtWaitAnswer(int timeOut, int answ,
	const char** answData);
MOMANPROT_API eMomanprot __stdcall mmProtReadAnswer(const char** answData,
	int& nodeNr, const char** cmdString, const char** receiveTelegram);
MOMANPROT_API bool __stdcall mmProtGetCommunicationHistory(const char** timestamp,
	eHistoryState& state, const char** data, const char** telegram, eHistoryError& error);
MOMANPROT_API eMomanprot __stdcall mmProtSetupTrace(STraceSetup& TraceSetup,
	STraceTrigger& TraceTrigger);
MOMANPROT_API eTraceRequest __stdcall mmProtRequestTrace(int mode=0);
MOMANPROT_API int __stdcall mmProtConnect(int& baudrate, bool tryBaudrates);
MOMANPROT_API int __stdcall mmProtFindConnection(int scanMin, int scanMax,
	int& baudrate);
MOMANPROT_API eMomanprot __stdcall mmProtNetworkService(int mode, int vendorId,
	int productCode, int revisionNumber, int serialNumber);
MOMANPROT_API bool __stdcall mmProtChangeBaudrate(int baudrate, int activate);
MOMANPROT_API bool __stdcall mmProtChangeNodeNr(int nodeNr);
MOMANPROT_API bool __stdcall mmProtGetCommunicationSettings(int& nodeNr,
	int& baudrate);
MOMANPROT_API int __stdcall mmProtUnconfiguredSlavesCount(void);
MOMANPROT_API const unsigned int* _stdcall mmProtSupportedBaudratesList(int& count);
MOMANPROT_API eMomanprot __stdcall mmProtGetObj(int nodeNr, int index, int subIndex,
	int& value);
MOMANPROT_API eMomanprot __stdcall mmProtGetInt64Obj(int nodeNr, int index, int subIndex,
	__int64& value);
MOMANPROT_API eMomanprot __stdcall mmProtGetStrObj(int nodeNr, int index, int subIndex,
	const char** value);
MOMANPROT_API eMomanprot __stdcall mmProtSetObj(int nodeNr, int index, int subIndex,
	int value, int len, unsigned int& abortCode);
MOMANPROT_API eMomanprot __stdcall mmProtSetStrObj(int nodeNr, int index, int subIndex,
	const char* value, unsigned int& abortCode);
MOMANPROT_API void __stdcall mmProtSetObjTimeout(int timeout);
MOMANPROT_API const char* __stdcall mmProtGetAbortMessage(unsigned int abortCode);
MOMANPROT_API const char* __stdcall mmProtGetErrorMessage(unsigned int errorCode);
MOMANPROT_API eDecoded __stdcall mmProtDecodeCmdStr(const char* cmdStr,
	int& nodeNr, int& index, int& subIndex, const char** valueStr);
MOMANPROT_API eDecoded __stdcall mmProtDecodeAnswStr(const char* answStr, __int64& value);
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* MOMANPROTH */
//---------------------------------------------------------------------------

