#include "stdafx.h"
#include "Czpcom.h"
#include "CZPUtl.h"

#include "czping.h"		//	Definition of our exported point.

STDMETHODIMP Utilities::Ping(
	IN BSTR		SiteToPing, 
	IN BSTR		SiteUpdateName, 
	IN BSTR		SiteUpdateURL, 
	IN BSTR*	ResultString)
	{
	HRESULT hr(E_INVALIDARG);

	USES_CONVERSION;

	if (NULL != SiteToPing &&
		NULL != SiteUpdateName &&
		NULL != SiteUpdateURL)
		{
		hr = E_OUTOFMEMORY;

		//	Uses alloca, off of the stack no need to free/delete
		//
		LPTSTR Site		= OLE2A(SiteToPing);
		LPTSTR Update	= OLE2A(SiteUpdateName);
		LPTSTR URL		= OLE2A(SiteUpdateURL);

		//	We can still get back a NULL pointer.
		//
		if (NULL != Site &&
			NULL != Update &&
			NULL != URL)
			{
			hr		= E_FAIL;

			Char	ResultBuffer[MONSTER_BUFFER];
			Long	ResultBufferLen(MONSTER_BUFFER);
			
			::ZeroMemory(ResultBuffer, ResultBufferLen);

			//	Finally get around to pinging the site.
			//
			if (SUCCESS == WeblogsDotComPing(Site, StrLen(Site), 
											 Update, StrLen(Update), 
											 URL, StrLen(URL), 
											 ResultBuffer, &ResultBufferLen) &&
				NULL != ResultBuffer[0])
				{
				//	Fill out the result buffer with our return value.
				//
				*ResultString = ::SysAllocString(T2OLE(ResultBuffer));
				hr = NOERROR;	
				}
			}
		}	//	NULL Checks.

	return hr;
	}	//	Ping
