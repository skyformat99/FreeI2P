// FreeI2P++.Windows.DLL.cpp : Defines the exported functions for the DLL application.
//

#if _Library

#include "stdafx.h"
#include "FreeI2P++.Windows.DLL.h"


// This is an example of an exported variable
FREEI2PWINDOWSDLL_API int nFreeI2PWindowsDLL=0;

// This is an example of an exported function.
FREEI2PWINDOWSDLL_API int fnFreeI2PWindowsDLL(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see FreeI2P++.Windows.DLL.h for the class definition
CFreeI2PWindowsDLL::CFreeI2PWindowsDLL()
{
    return;
}


#endif  //< _Library