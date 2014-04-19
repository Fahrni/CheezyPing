// czping.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain(
	IN HINSTANCE	hInstance, 
    IN DWORD		dwReason, 
	IN LPVOID		lpReserved)
	{
    if (dwReason == DLL_PROCESS_ATTACH)
		{
        ::DisableThreadLibraryCalls(hInstance);
		}

    return TRUE;    // ok
	}	//	DllMain
