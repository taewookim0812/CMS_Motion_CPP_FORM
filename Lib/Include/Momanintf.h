/*---------------------------------------------------------------------------
* 							Dr. Fritz Faulhaber GmbH & Co.KG
*----------------------------------------------------------------------------
*//**\file
* \brief    Definition of the Moman Interface API
*/
//---------------------------------------------------------------------------

#ifndef MOMANINTFH
#define MOMANINTFH

#ifdef BUILD_MOMANINTF
#    define MOMANINTF_API __declspec(dllexport)
#else
#    define MOMANINTF_API __declspec(dllimport)
#endif
//---------------------------------------------------------------------------

/* Return values */
enum eMomanintf {
	eMomanintf_not_avail = 0,
	eMomanintf_avail = 1,
	eMomanintf_avail_inuse = 2
};
//---------------------------------------------------------------------------

/* API function pointers */
typedef int (__stdcall *tdmmIntfEnumPorts)(char** port, char** chan, char** deviceInfoList);
typedef eMomanintf (__stdcall *tdmmIntfIsPortAvailable)(int port, int chan);
//---------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */
MOMANINTF_API int __stdcall mmIntfEnumPorts(char** port, char** chan, char** deviceInfoList);
MOMANINTF_API eMomanintf __stdcall mmIntfIsPortAvailable(int port, int chan);
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* MOMANINTF */
//---------------------------------------------------------------------------

