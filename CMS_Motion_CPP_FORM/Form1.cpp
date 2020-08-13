#include "pch.h"
#include "Form1.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CMS_MOTION_CPP_FORM::Form1);
}

namespace CMS_MOTION_CPP_FORM {
	/**
	* Read and display asynchronous received data from the communication library
	*/
	void Form1::AsyncDataReceived()
	{
		//Asynchronous data received
		std::string data, cmd;
		momanLibSample->ReadReceivedData(data, cmd);
		if (cmd != "") {
			String^ text = gcnew String(("Async Received: " + data + " (Cmd = " + cmd + ")").c_str());
			this->tbCommLog->AppendText(text + L"\r\n");
		}
		else {
			String^ text = gcnew String(("Async Received:: " + data).c_str());
			this->tbCommLog->AppendText(text + L"\r\n");
		}

		if ((momanLibSample->GetStatusword() & 0x00FF) == 0x0027) {	//"Operation Enabled"
			//btnRelPos->Enabled = true;
		}
		else {
			//btnRelPos->Enabled = false;
		}
	}

	void Form1::AsyncStageMonitor()
	{
		if (m_bMomanLibLoaded) {
			std::string value;
			momanLibSample->GetStrObj(cNodeNr, 0x6064, 0x00, value);
			//int value;
			//momanLibSample->GetObj(cNodeNr, 0x6064, 0x00, value);
			
			String^ currPos = gcnew String(value.c_str());
			this->tbAxis1CurrPosition->Text = currPos;
		}
	}
	//---------------------------------------------------------------------------

	/**
	* Callback function, called from the communication library
	* when receiving asynchronous data
	*/
	void __stdcall CBAsyncDataReceived()
	{
		SetEvent(hReceiveEvent);
	}
	//---------------------------------------------------------------------------

	/**
	* Working thread
	*/
	void EventReceiver()
	{
		while (!threadTerminated)
		{
			if (WaitForSingleObject(hReceiveEvent, INFINITE) == WAIT_OBJECT_0) {
				if (!threadTerminated) {
					Form1::_instance->Invoke(gcnew MethodInvoker(Form1::_instance, &Form1::AsyncDataReceived));
				}
			}
			Sleep(1);
		}
	}

	void MonitorWorker()
	{
		while (!monitorTerminated)
		{
			if (!monitorTerminated) {
				Form1::_instance->Invoke(gcnew MethodInvoker(Form1::_instance, &Form1::AsyncStageMonitor));
			}
			Sleep(1000);
		}
	}
}