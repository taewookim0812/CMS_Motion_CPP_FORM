/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*							Modified by Dr. Taewoo Kim
*----------------------------------------------------------------------------
*//**\file
* \brief   	Implementation of class CMomanLibSample as wrapper for
*				MomanLib API functions used in the C++ demo examples
*/
//---------------------------------------------------------------------------

#include "MomanLibSample.h"
//---------------------------------------------------------------------------

//Used Dlls from communication API:
const char* cProtDll = "..\\Lib\\Bin\\Protocol\\USB\\CO_USB.dll";
const char* cIntfDll = "..\\Lib\\Bin\\Interface\\USB\\MC3USB.dll";
//---------------------------------------------------------------------------

//***************
//*** Public: ***
//***************
CMomanLibSample::CMomanLibSample(void)
{
	m_hProtocolDll = NULL;
	m_isComOpen = false;
	m_Statusword = 0;
	m_abortMessage = "";
}
//---------------------------------------------------------------------------

CMomanLibSample::~CMomanLibSample(void)
{
	if (m_hProtocolDll) {
		if (m_isComOpen) {
			mmProtCloseCom();
			mmProtCloseInterface();
		}
		FreeLibrary(m_hProtocolDll);
	}
}
//---------------------------------------------------------------------------

/**
* Load and initialize the communication Library
*
* \param[in]		SignalDataReceived	callback function to signal received data
* \return			true = initialization succesfull
*						false = error loading the library
*/
bool CMomanLibSample::Init(tdmmProtDataCallback SignalDataReceived)
{
	m_isComOpen = false;
	m_hProtocolDll = LoadLibraryA(cProtDll);
	if (m_hProtocolDll == NULL) {
		return false;
	}

	//Needed functions of the communication library:
	bool ok = true;
	mmProtInitInterface = (tdmmProtInitInterface)GetProcAddress(m_hProtocolDll, "mmProtInitInterface");
	ok &= mmProtInitInterface != NULL;
	mmProtCloseInterface = (tdmmProtCloseInterface)GetProcAddress(m_hProtocolDll, "mmProtCloseInterface");
	ok &= mmProtCloseInterface != NULL;
	mmProtOpenCom = (tdmmProtOpenCom)GetProcAddress(m_hProtocolDll, "mmProtOpenCom");
	ok &= mmProtOpenCom != NULL;
	mmProtCloseCom = (tdmmProtCloseCom)GetProcAddress(m_hProtocolDll, "mmProtCloseCom");
	ok &= mmProtCloseCom != NULL;
	mmProtSendCommand = (tdmmProtSendCommand)GetProcAddress(m_hProtocolDll, "mmProtSendCommand");
	ok &= mmProtSendCommand != NULL;
	mmProtReadAnswer = (tdmmProtReadAnswer)GetProcAddress(m_hProtocolDll, "mmProtReadAnswer");
	ok &= mmProtReadAnswer != NULL;
	mmProtDecodeAnswStr = (tdmmProtDecodeAnswStr)GetProcAddress(m_hProtocolDll, "mmProtDecodeAnswStr");
	ok &= mmProtDecodeAnswStr != NULL;
	mmProtGetStrObj = (tdmmProtGetStrObj)GetProcAddress(m_hProtocolDll, "mmProtGetStrObj");
	ok &= mmProtGetStrObj != NULL;
	mmProtSetObj = (tdmmProtSetObj)GetProcAddress(m_hProtocolDll, "mmProtSetObj");
	ok &= mmProtSetObj != NULL;
	mmProtGetAbortMessage = (tdmmProtGetAbortMessage)GetProcAddress(m_hProtocolDll, "mmProtGetAbortMessage");
	ok &= mmProtGetAbortMessage != NULL;
	if (!ok) {
		return false;
	}

	if (mmProtInitInterface((char*)cIntfDll, SignalDataReceived, 0) != eMomanprot_ok) {
		return false;
	}
	if (mmProtOpenCom(1, 0, 0) != eMomanprot_ok) {
		return false;
	}
	m_isComOpen = true;

	return true;

}
//---------------------------------------------------------------------------

/**
* Read data of a string object in the object dictionary
*
* \param[in]		nodeNr		node number
* \param[in]		index			object index
* \param[in]		subIndex		object subindex
* \param[out]		value			object data
* \return			true = object successfully read
*						false = error reading object value
*/
bool CMomanLibSample::GetStrObj(int nodeNr, int index, int subIndex, std::string& value)
{
	const char* answData = NULL;
	eMomanprot ret = mmProtGetStrObj(nodeNr, index, subIndex, &answData);
	if (ret == eMomanprot_ok) {
		value = answData;
		return true;
	}
	else {
		return false;
	}
}

bool CMomanLibSample::GetObj(int nodeNr, int index, int subIndex, int& value)
{
	int recvData;
	eMomanprot ret = mmProtGetObj(nodeNr, index, subIndex, recvData);
	if (ret == eMomanprot_ok)
	{
		value = recvData;
		return true;
	}
	else
	{
		value = -1;
		return false;
	}
}

bool CMomanLibSample::GetInt64Obj(int nodeNr, int index, int subIndex, __int64& value)
{
	__int64 recvData;
	eMomanprot ret = mmProtGetInt64Obj(nodeNr, index, subIndex, recvData);
	if (ret == eMomanprot_ok)
	{
		value = recvData;
		return true;
	}
	else
	{
		value = -1;
		return false;
	}
}
//---------------------------------------------------------------------------

/**
* Send a Motion Manager command
*
* \param[in]		nodeNr		node number
* \param[in]		cmd			Motion Manager command
* \return			true = command successfully sent
*						false = error sending command
*/
bool CMomanLibSample::SendCommand(int nodeNr, eMomancmd cmd)
{
	return mmProtSendCommand(nodeNr, 0x0000, cmd, 0, 0);
}
//---------------------------------------------------------------------------

/**
* Read asynchronous received data
*
* \param[out]		data		received data
* \param[out]		cmd		command assigned to the data
* \return			true = data received
*						false = no data received
*/
bool CMomanLibSample::ReadReceivedData(std::string& data, std::string& cmd)
{
	const char *answData = NULL;
	const char *cmdString = NULL;
	const char* receiveTelegram = NULL;
	int nodeNr;
	eMomanprot ret = mmProtReadAnswer(&answData, nodeNr, &cmdString, &receiveTelegram);
	if (ret != eMomanprot_noData) {
		data = answData;
		cmd = cmdString;
		__int64 value;
		if (mmProtDecodeAnswStr(answData, value) == eDecoded_Statusword) {
			m_Statusword = (int)value;
		}
		return true;
	}
	else {
   	return false;
	}
}
//---------------------------------------------------------------------------

/**
* Write data to an object in the object dictionary
*
* \param[in]		nodeNr		node number
* \param[in]		index			object index
* \param[in]		subIndex		object subindex
* \param[in]		value			object data
* \param[in]		len			len of object data
* \return			true = object successfully written
*						false = error writing object value
*								  (an abort message is written to a member variable)
*/
bool CMomanLibSample::SetObj(int nodeNr, int index, int subIndex, int value, int len)
{
	unsigned int abortCode;
	eMomanprot ret = mmProtSetObj(nodeNr, index, subIndex, value, len, abortCode);
	if (ret == eMomanprot_ok) {
		return true;
	}
	else {
		m_abortMessage = mmProtGetAbortMessage(abortCode);
		return false;
	}
}
//---------------------------------------------------------------------------

/**
* Read last value of the statusword
*
* \return			value of statusword set in ReadReceivedData()
*/
int CMomanLibSample::GetStatusword(void)
{
	return m_Statusword;
}
//---------------------------------------------------------------------------

/**
* Read last abort message
*
* \return			abort message set in SetObj()
*/
std::string CMomanLibSample::GetAbortMessage(void)
{
	return m_abortMessage;
}
//---------------------------------------------------------------------------
