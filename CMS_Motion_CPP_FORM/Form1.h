#pragma once
#include "..\Common\MomanLibSample.h"
#include "CMS_header.h"
#include <atlstr.h>

namespace CMS_MOTION_CPP_FORM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	HANDLE hReceiveEvent = NULL;
	bool threadTerminated = false;
	bool monitorTerminated = false;
	static void __stdcall CBAsyncDataReceived();
	static void EventReceiver();
	static void MonitorWorker();

	const int cNodeNr = 1;	//node number of the connected device
	
	/// <summary>
	/// Zusammenfassung f? Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			_instance = this;
			momanLibSample = new CMomanLibSample();
			if (momanLibSample->Init((tdmmProtDataCallback) & (CBAsyncDataReceived)) == true) {
				m_bMomanLibLoaded = true;
				btnAxis1GetStatus->Enabled = true;
				//toolStripStatusLabel1->Text = "FAULHABER communication API loaded";
				//btnGetStrObj->Enabled = true;
				btnShutdown->Enabled = true;
				btnSwitchOn->Enabled = true;
				btnEnOp->Enabled = true;
			}
			else {
				m_bMomanLibLoaded = false;
				MessageBox::Show("Interface can not be opened!");
			}
			hReceiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		}
	private: System::Windows::Forms::Button^ btnAxis1GetStatus;
	private: System::Windows::Forms::TextBox^ tbCommLog;
	private: System::Windows::Forms::Button^ btnShutdown;
	private: System::Windows::Forms::Button^ btnSwitchOn;
	private: System::Windows::Forms::Button^ btnEnOp;
	private: System::Windows::Forms::Button^ btnRelPos;
	private: System::Windows::Forms::TextBox^ tbAxis1CurrPosition;


	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ btnAxis1Stop;
	private: System::Windows::Forms::Button^ btnAxis1Homing;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ tbAxis1CurrVelocity;


	public:
		static Form1^ _instance;
		void AsyncDataReceived();
		void AsyncStageMonitor();

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components) {
				delete components;
			}
			delete this->momanLibSample;
			CloseHandle(hReceiveEvent);
		}


	private:
		CMomanLibSample* momanLibSample;
		bool m_bMomanLibLoaded;
		Thread^ ReceiveThread;
		Thread^ MonitorThread;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f? die Designerunterst?zung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge?dert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAxis1GetStatus = (gcnew System::Windows::Forms::Button());
			this->tbCommLog = (gcnew System::Windows::Forms::TextBox());
			this->btnShutdown = (gcnew System::Windows::Forms::Button());
			this->btnSwitchOn = (gcnew System::Windows::Forms::Button());
			this->btnEnOp = (gcnew System::Windows::Forms::Button());
			this->btnRelPos = (gcnew System::Windows::Forms::Button());
			this->tbAxis1CurrPosition = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btnAxis1Stop = (gcnew System::Windows::Forms::Button());
			this->btnAxis1Homing = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbAxis1CurrVelocity = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnAxis1GetStatus
			// 
			this->btnAxis1GetStatus->Location = System::Drawing::Point(6, 25);
			this->btnAxis1GetStatus->Name = L"btnAxis1GetStatus";
			this->btnAxis1GetStatus->Size = System::Drawing::Size(75, 23);
			this->btnAxis1GetStatus->TabIndex = 0;
			this->btnAxis1GetStatus->Text = L"Get Status";
			this->btnAxis1GetStatus->UseVisualStyleBackColor = true;
			this->btnAxis1GetStatus->Click += gcnew System::EventHandler(this, &Form1::btnAxis1GetStatus_Click);
			// 
			// tbCommLog
			// 
			this->tbCommLog->AcceptsReturn = true;
			this->tbCommLog->AcceptsTab = true;
			this->tbCommLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbCommLog->Location = System::Drawing::Point(9, 293);
			this->tbCommLog->Margin = System::Windows::Forms::Padding(0);
			this->tbCommLog->Multiline = true;
			this->tbCommLog->Name = L"tbCommLog";
			this->tbCommLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbCommLog->Size = System::Drawing::Size(796, 151);
			this->tbCommLog->TabIndex = 1;
			// 
			// btnShutdown
			// 
			this->btnShutdown->Location = System::Drawing::Point(87, 25);
			this->btnShutdown->Name = L"btnShutdown";
			this->btnShutdown->Size = System::Drawing::Size(75, 23);
			this->btnShutdown->TabIndex = 2;
			this->btnShutdown->Text = L"Shutdown";
			this->btnShutdown->UseVisualStyleBackColor = true;
			this->btnShutdown->Click += gcnew System::EventHandler(this, &Form1::btnShutdown_Click);
			// 
			// btnSwitchOn
			// 
			this->btnSwitchOn->Location = System::Drawing::Point(168, 25);
			this->btnSwitchOn->Name = L"btnSwitchOn";
			this->btnSwitchOn->Size = System::Drawing::Size(75, 23);
			this->btnSwitchOn->TabIndex = 3;
			this->btnSwitchOn->Text = L"Switch On";
			this->btnSwitchOn->UseVisualStyleBackColor = true;
			this->btnSwitchOn->Click += gcnew System::EventHandler(this, &Form1::btnSwitchOn_Click);
			// 
			// btnEnOp
			// 
			this->btnEnOp->Location = System::Drawing::Point(249, 25);
			this->btnEnOp->Name = L"btnEnOp";
			this->btnEnOp->Size = System::Drawing::Size(75, 23);
			this->btnEnOp->TabIndex = 3;
			this->btnEnOp->Text = L"EnOp";
			this->btnEnOp->UseVisualStyleBackColor = true;
			this->btnEnOp->Click += gcnew System::EventHandler(this, &Form1::btnEnOp_Click);
			// 
			// btnRelPos
			// 
			this->btnRelPos->Location = System::Drawing::Point(330, 25);
			this->btnRelPos->Name = L"btnRelPos";
			this->btnRelPos->Size = System::Drawing::Size(75, 23);
			this->btnRelPos->TabIndex = 4;
			this->btnRelPos->Text = L"Rel. Pos";
			this->btnRelPos->UseVisualStyleBackColor = true;
			this->btnRelPos->Click += gcnew System::EventHandler(this, &Form1::btnRelPos_Click);
			// 
			// tbAxis1CurrPosition
			// 
			this->tbAxis1CurrPosition->BackColor = System::Drawing::Color::Black;
			this->tbAxis1CurrPosition->ForeColor = System::Drawing::Color::Lime;
			this->tbAxis1CurrPosition->Location = System::Drawing::Point(168, 53);
			this->tbAxis1CurrPosition->Name = L"tbAxis1CurrPosition";
			this->tbAxis1CurrPosition->ReadOnly = true;
			this->tbAxis1CurrPosition->Size = System::Drawing::Size(100, 29);
			this->tbAxis1CurrPosition->TabIndex = 5;
			this->tbAxis1CurrPosition->Text = L"0";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->btnAxis1GetStatus);
			this->groupBox1->Controls->Add(this->btnShutdown);
			this->groupBox1->Controls->Add(this->btnSwitchOn);
			this->groupBox1->Controls->Add(this->btnRelPos);
			this->groupBox1->Controls->Add(this->btnEnOp);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(790, 72);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"BASIC TEST";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->btnAxis1Stop);
			this->groupBox2->Controls->Add(this->btnAxis1Homing);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->tbAxis1CurrVelocity);
			this->groupBox2->Controls->Add(this->tbAxis1CurrPosition);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"굴림", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->groupBox2->Location = System::Drawing::Point(12, 90);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(790, 127);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"AXIS1";
			// 
			// btnAxis1Stop
			// 
			this->btnAxis1Stop->Font = (gcnew System::Drawing::Font(L"휴먼둥근헤드라인", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->btnAxis1Stop->ForeColor = System::Drawing::Color::Red;
			this->btnAxis1Stop->Location = System::Drawing::Point(6, 63);
			this->btnAxis1Stop->Name = L"btnAxis1Stop";
			this->btnAxis1Stop->Size = System::Drawing::Size(75, 50);
			this->btnAxis1Stop->TabIndex = 7;
			this->btnAxis1Stop->Text = L"Stop";
			this->btnAxis1Stop->UseVisualStyleBackColor = true;
			// 
			// btnAxis1Homing
			// 
			this->btnAxis1Homing->Font = (gcnew System::Drawing::Font(L"굴림", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->btnAxis1Homing->Location = System::Drawing::Point(6, 27);
			this->btnAxis1Homing->Name = L"btnAxis1Homing";
			this->btnAxis1Homing->Size = System::Drawing::Size(75, 30);
			this->btnAxis1Homing->TabIndex = 7;
			this->btnAxis1Homing->Text = L"Homing";
			this->btnAxis1Homing->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"굴림", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label1->Location = System::Drawing::Point(165, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 16);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Position";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"굴림", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label2->Location = System::Drawing::Point(313, 34);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Velocity";
			// 
			// tbAxis1CurrVelocity
			// 
			this->tbAxis1CurrVelocity->BackColor = System::Drawing::Color::Black;
			this->tbAxis1CurrVelocity->ForeColor = System::Drawing::Color::Lime;
			this->tbAxis1CurrVelocity->Location = System::Drawing::Point(316, 53);
			this->tbAxis1CurrVelocity->Name = L"tbAxis1CurrVelocity";
			this->tbAxis1CurrVelocity->ReadOnly = true;
			this->tbAxis1CurrVelocity->Size = System::Drawing::Size(100, 29);
			this->tbAxis1CurrVelocity->TabIndex = 5;
			this->tbAxis1CurrVelocity->Text = L"0";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(814, 453);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tbCommLog);
			this->Name = L"Form1";
			this->Text = L"Curved Motion System";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnAxis1GetStatus_Click(System::Object^ sender, System::EventArgs^ e) {
		if (m_bMomanLibLoaded) {
			//Read device name
			std::string value;
			momanLibSample->GetStrObj(cNodeNr, 0x1008, 0x00, value);
			this->tbCommLog->AppendText(L"Sync Read 0x1008.00\r\n");
			String^ text = gcnew String(("Sync Received: " + value + "\r\n").c_str());
			this->tbCommLog->AppendText(text);

			// TODO
			/*
			wstring strUni = CA2W("멀티바이트를 유니코드로 변환"); 
			string strMulti = CW2A(L"유니코드를 멀티바이트로 변환"); 
			string strUTF8 = CW2A(L"유니코드를 UTF8로변환", CP_UTF8);
			*/

			//std::string curr;
			//momanLibSample->GetStrObj(cNodeNr, 0x6041, 0x00, curr);
			/*for (int i = 0; i < curr.length(); i++) {
				this->tbCommLog->AppendText(curr[i].ToString());
			}*/

			int curr;
			momanLibSample->GetObj(cNodeNr, 0x6064, 0x00, curr);

			//__int64 curr;
			//momanLibSample->GetInt64Obj(cNodeNr, 0x6064, 0x00, curr);
			String^ text2 = gcnew String(curr.ToString());
			this->tbCommLog->AppendText(text2);

			
		}
	}
	private: System::Void btnShutdown_Click(System::Object^ sender, System::EventArgs^ e) {
		if (m_bMomanLibLoaded) {
			if (momanLibSample->SendCommand(cNodeNr, eMomancmd_shutdown) == true) {
				this->tbCommLog->AppendText(L"Send SHUTDOWN\r\n");
			}
		}
	}

	private: System::Void btnSwitchOn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (m_bMomanLibLoaded) {
			if (momanLibSample->SendCommand(cNodeNr, eMomancmd_switchon) == true) {
				this->tbCommLog->AppendText(L"Send SWITCHON\r\n");
			}
		}
	}

	private: System::Void btnEnOp_Click(System::Object^ sender, System::EventArgs^ e) {
		if (m_bMomanLibLoaded) {
			if (momanLibSample->SendCommand(cNodeNr, eMomancmd_EnOp) == true) {
				this->tbCommLog->AppendText(L"Send ENOP\r\n");
			}
		}
	}
	
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		ReceiveThread = gcnew Thread(gcnew ThreadStart(&EventReceiver));
		ReceiveThread->Start();

		MonitorThread = gcnew Thread(gcnew ThreadStart(&MonitorWorker));
		MonitorThread->Start();
	}

	private: System::Void Form1_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		threadTerminated = true;
		SetEvent(hReceiveEvent);	//terminate WaitForSingleObject in EventReceiver()
		ReceiveThread->Join();

		monitorTerminated = true;
		// Event??
		MonitorThread->Join();
	}

	private: System::Void btnRelPos_Click(System::Object^ sender, System::EventArgs^ e) {
		bool err = true;

		this->tbCommLog->AppendText(L"Execute MOVE RELATIVE\r\n");
		//Modes of Operation = Profile Position Mode (1):
		if (momanLibSample->SetObj(cNodeNr, 0x6060, 0x00, 1, 1) == true) {
			//Target Position = 1000:
			if (momanLibSample->SetObj(cNodeNr, 0x607A, 0x00, 1000, 4) == true) {
				//Enable Operation:
				if (momanLibSample->SetObj(cNodeNr, 0x0000, eMomancmd_EnOp, 0, 0) == true) {
					//Move relative:
					if (momanLibSample->SetObj(cNodeNr, 0x6040, 0x00, 0x007F, 2) == true) {
						err = false;
					}
				}
			}
		}

		if (err) {
			std::string abortMessage = momanLibSample->GetAbortMessage();
			String^ text = gcnew String(("Error Received: " + abortMessage + "\r\n").c_str());
			if (abortMessage != "") {
				this->tbCommLog->AppendText(text);
			}
		}
	}

	private: System::Void MoveStage(String^ op_mode, int target_value)
	{
			   
	}
};
}
