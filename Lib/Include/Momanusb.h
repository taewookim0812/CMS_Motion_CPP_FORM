/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*----------------------------------------------------------------------------
*//**\file
* \brief    Definition of the Moman USB API
*/
//---------------------------------------------------------------------------

#ifndef MOMANUSBH
#define MOMANUSBH

#ifdef BUILD_MOMANUSB
#    define MOMANUSB_API __declspec(dllexport)
#else
#    define MOMANUSB_API __declspec(dllimport)
#endif
//---------------------------------------------------------------------------

/* Return values */
enum eMomanusb {
	eMomanusb_ok = 0,
	eMomanusb_error = -1,
	eMomanusb_error_accessdenied = -2,
	eMomanusb_error_init = -3
};
//---------------------------------------------------------------------------

/* Callback function pointers */
typedef void (*tdmmUsbDataCallback)(void);

/* API function pointers */
typedef void (__stdcall *tdmmUsbInitLib)(tdmmUsbDataCallback DataReceived);
typedef void (__stdcall *tdmmUsbDeinitLib)(void);
typedef int (__stdcall *tdmmUsbOpen)(int port, int channel);
typedef void (__stdcall *tdmmUsbClose)(void);
typedef void (__stdcall *tdmmUsbSendData)(char* data, int len);
typedef int (__stdcall *tdmmUsbReadData)(char* data);
typedef int (__stdcall *tdmmUsbGetBufCount)(int direction);
//---------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */
MOMANUSB_API void __stdcall mmUsbInitLib(tdmmUsbDataCallback DataReceived);
MOMANUSB_API void __stdcall mmUsbDeinitLib(void);
MOMANUSB_API int __stdcall mmUsbOpen(int port, int channel);
MOMANUSB_API void __stdcall mmUsbClose(void);
MOMANUSB_API int __stdcall mmUsbSendData(char* data, int len);
MOMANUSB_API int __stdcall mmUsbReadData(char* data);
MOMANUSB_API int __stdcall mmUsbGetBufCount(int direction);
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* MOMANCOM */
//---------------------------------------------------------------------------

