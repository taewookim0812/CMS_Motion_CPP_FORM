/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*							Modified by Dr. Taewoo Kim
*----------------------------------------------------------------------------
*//**\file
* \brief   Definition of class CMomanLibSample as wrapper for
*				MomanLib API functions used in the C++ demo examples
*/
//---------------------------------------------------------------------------

#ifndef MomanLibSampleH
#define MomanLibSampleH
//---------------------------------------------------------------------------
#include "..\CMS_Motion_CPP_FORM\pch.h"
#include <string>
//#include <windows.h>

#include "Momancmd.h"
#include "Momanprot.h"
//---------------------------------------------------------------------------


class CMomanLibSample
{
private:
	tdmmProtInitInterface mmProtInitInterface;
	tdmmProtCloseInterface mmProtCloseInterface;
	tdmmProtOpenCom mmProtOpenCom;
	tdmmProtCloseCom mmProtCloseCom;
	tdmmProtSendCommand mmProtSendCommand;
	tdmmProtReadAnswer mmProtReadAnswer;
	tdmmProtDecodeAnswStr mmProtDecodeAnswStr;
	tdmmProtGetStrObj mmProtGetStrObj;
	tdmmProtGetObj mmProtGetObj;
	tdmmProtGetInt64Obj mmProtGetInt64Obj;
	tdmmProtSetObj mmProtSetObj;
	tdmmProtGetAbortMessage mmProtGetAbortMessage;

	HINSTANCE m_hProtocolDll;
	bool m_isComOpen;
	int m_Statusword;
	std::string m_abortMessage;

public:
	CMomanLibSample();
	~CMomanLibSample();

	bool Init(tdmmProtDataCallback SignalDataReceived);
	bool GetStrObj(int nodeNr, int index, int subIndex, std::string& value);
	bool GetObj(int nodeNr, int index, int subIndex, int& value);
	bool GetInt64Obj(int nodeNr, int index, int subIndex, __int64& value);
	bool SendCommand(int nodeNr, eMomancmd cmd);
	bool ReadReceivedData(std::string& data, std::string& cmd);
	bool SetObj(int nodeNr, int index, int subIndex, int value, int len);
	int GetStatusword(void);
	std::string  GetAbortMessage(void);

};
//---------------------------------------------------------------------------
#endif
