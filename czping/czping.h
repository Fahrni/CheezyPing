#include "PlatDef.h"
#include "WinPlatDef.h"

#include "stdio.h"
#include <WinINet.h>

#include "HttpIf.h"
#include "HttpWin.h"

enum czpErrorCodes
	{
	SUCCESS		=	0,
	FAILURE		=	~0,
	E_BadParam	=	2,
	E_OutOfMem	=	3
	};	//	czpErrorCodes

//	The one and only site I know of that takes a ping?
//
#define SITE_WeblogsDotCom	_T("http://rpc.weblogs.com/RPC2\0")

#ifndef EXTERNC
	#define EXTERNC extern "C"
#endif

//#ifdef CZPING_EXPORTS
	#define CZDLLEXPORT		__declspec(dllexport)
//#else
//	#define CZDLLEXPORT		__declspec(dllimport)
//#endif	//	CZPING_EXPORTS

#define CZPAPI(type)	CZDLLEXPORT type APIENTRY

CZPAPI(Long) WeblogsDotComPing(
	IN		String	SiteToPing,
	IN		Long	LenSiteToPing,
	IN		String	SiteUpdateName,
	IN		Long	LenSiteUpdateName,
	IN		String	SiteUpdateURL,
	IN		Long	LenSiteUpdateURL,
	IN OUT	String	ErrorString,
	IN OUT	Long*	ErrorStringSize);
