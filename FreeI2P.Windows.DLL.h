// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FREEI2PWINDOWSDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FREEI2PWINDOWSDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#if _Library

#ifdef FREEI2PWINDOWSDLL_EXPORTS
#define FREEI2PWINDOWSDLL_API __declspec(dllexport)
#else
#define FREEI2PWINDOWSDLL_API __declspec(dllimport)
#endif

// This class is exported from the FreeI2P++.Windows.DLL.dll
class FREEI2PWINDOWSDLL_API CFreeI2PWindowsDLL {
public:
	CFreeI2PWindowsDLL(void);
	// TODO: add your methods here.
};

extern FREEI2PWINDOWSDLL_API int nFreeI2PWindowsDLL;

FREEI2PWINDOWSDLL_API int fnFreeI2PWindowsDLL(void);
#endif	//< _Library