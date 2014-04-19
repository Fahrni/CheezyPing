/*	HTTPWIN.CPP - One line description.
 *	Copyright (C) 2001 Rob Fahrni.  All rights reserved.
 *
 */
#include "PlatDef.h"		//	Cross platform types.
#include "WinPlatDef.h"		//	Our windows typedefs & #defines.

#include <WinINet.h>		//	Windows internet api's.
#include "HttpIf.h"			//	HTTP ABC interface.
#include "HttpWin.h"		//	HTTP for windows.
#include <stdio.h>

#define STR_CheezyPing	_T("Cheezy.Ping\0")

/**************************************************************************
 *+ CHttpWindows - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
CHttpWindows::CHttpWindows() :
	m_hInternet(NULL),
	m_hConnection(NULL),
	m_StatusCode(0L),
	m_Response(NULL)
	{
	//	nothing for now.
	//
	}	//	ctor

/**************************************************************************
 *+ ~CHttpWindows - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
CHttpWindows::~CHttpWindows()
	{
	//	Wack the Response string.
	//
	delete [] m_Response;
	m_Response = NULL;

	//	Make double sure we've closed and NULL'd the handles.
	//
	this->Close();
	}	//	dtor

/**************************************************************************
 *+ Open - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
HTTPRC CHttpWindows::Open(void)
	{
	HTTPRC rc(0L);

	if (m_hInternet == NULL)
		{
		m_hInternet = ::InternetOpen(STR_CheezyPing, 
									 INTERNET_OPEN_TYPE_PRECONFIG,
									 NULL, NULL, 0);
		}

	return rc;
	}	//	Open

/**************************************************************************
 *+ Close - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
void CHttpWindows::Close()
	{
	if (m_hInternet != NULL)
		{
		::InternetCloseHandle(m_hInternet);
		m_hInternet = NULL;
		}
	}	//	Close


/**************************************************************************
 *+ SendRequest - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
HTTPRC CHttpWindows::SendRequest(
	IN		ConstString	verb,
	IN		ConstString	fullUrl,
	IN		ConstString	request,
	IN		Int			requestLen, 
	IN		ConstString	version)
	{
	HTTPRC		rc(eHTTPNOERROR);
	
	HINTERNET	hRequest(this->createRequest(verb, fullUrl, version));
	if (hRequest != NULL)
		{
		String	requestData = new Char[requestLen+1];
		
		if (requestData != NULL)
			{
			Memset(requestData, 0, requestLen+1);
			StrNCpy(requestData, request, requestLen);

			//	Make the Http request. 
			//
			rc = (::HttpSendRequest(hRequest, NULL, 0L, (LPVOID)requestData, requestLen) == TRUE) 
				 ? eHTTPNOERROR : eHTTPCONNECTIONFAIL;
		
			//	If no error occured then query the server for the result text.
			//
			if (rc == eHTTPNOERROR)
				{
				//	We've succeeded on the request. This doesn't mean the server
				//	succeeded. It just means the request was received successfully.
				//
				//	Get the server response to a successful HttpSendRequest.
				//
				this->getServerReplyInfo(hRequest);
				}
			
			//	Cleanup the request data.
			//
			delete [] requestData;
			requestData = NULL;
			}

		//	Cleanup before we leave, this will close the request handle and the connection.
		//
		this->cleanupRequest(hRequest);
		}
	
	return rc;
	}	//	SendRequest

/**************************************************************************
 *+ PostRequest - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
HTTPRC CHttpWindows::PostRequest(
	IN		ConstString	fullUrl, 
	IN		ConstString	request, 
	IN		Int			requestLen, 
	IN		ConstString	version)
	{
	return this->SendRequest(STR_PostVerb, fullUrl, request, requestLen, version);
	}	//	PostRequest

/**************************************************************************
 *+ GetStatusCode - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
DWord CHttpWindows::GetStatusCode(void)
	{
	return m_StatusCode;
	}	//	GetStatusCode

/**************************************************************************
 *+ GetStatusText - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
ConstString CHttpWindows::GetStatusText(void)
	{
	return NULL;	//return m_StatusText;
	}	//	GetStatusText

/**************************************************************************
 *+ GetResponse - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
ConstString CHttpWindows::GetResponse(void)
	{
	return m_Response;
	}	//	GetResponse

/**************************************************************************
 *+ createRequest - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
HINTERNET CHttpWindows::createRequest(
	IN ConstString verb,				//	Operation verb, POST, GET, etc...
	IN ConstString fullUrl,			//	URL to crack 
	IN ConstString version /*=*/)	//	Http version
	{
	HINTERNET	hRequest(NULL);
	String		acceptTypes[2] = {TEXT("text/xml\0"), NULL}; 

	DWORD dwFlags(0L);
	Char hostName[2*MAX_PATH]=_T("");
	Char urlPath[4*MAX_PATH]=_T("");
	Char extra[4*MAX_PATH]=_T("");

	URL_COMPONENTS urlc;
	Memset((PVOID)&urlc, 0, sizeof(URL_COMPONENTS));

	//	Initialize the component structure.
	//
	urlc.dwStructSize		= sizeof(URL_COMPONENTS);
	urlc.lpszExtraInfo		= extra;
	urlc.dwExtraInfoLength	= sizeof(extra);
	urlc.lpszHostName		= hostName;
	urlc.dwHostNameLength	= sizeof(hostName);
	urlc.lpszUrlPath		= urlPath;
	urlc.dwUrlPathLength	= sizeof(urlPath);

	Char url[4*MAX_PATH];
	StrCpy(url, fullUrl);	//	Make a copy
	
	BOOL fOk = ::InternetCrackUrl(url, 0, dwFlags, &urlc);
	if (fOk == TRUE)
		{
		m_hConnection = ::InternetConnect(m_hInternet, 
										  urlc.lpszHostName, 
										  urlc.nPort, 
										  NULL,
										  NULL,
										  INTERNET_SERVICE_HTTP, 0, 0);
		
		if (m_hConnection != NULL)
			{
			dwFlags = (INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE);
			hRequest = ::HttpOpenRequest(m_hConnection, verb, urlc.lpszUrlPath, 
										 version,  NULL, (LPCTSTR*)acceptTypes, dwFlags, 0L);

			if (hRequest != NULL)
				{
				String XMLHeader = "Content-type: text/xml\r\n";
				::HttpAddRequestHeaders(hRequest, XMLHeader, StrLen(XMLHeader), HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE);
				}
			}
		}
		
	return hRequest;	
	}	//	createRequest

/**************************************************************************
 *+ cleanupRequest - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
void CHttpWindows::cleanupRequest(IN OUT HINTERNET& hRequest)
	{
	if (hRequest != NULL)
		{
		//	Close the request handle.
		//
		::InternetCloseHandle(hRequest);
		hRequest = NULL;
		}
	
	if (m_hConnection != NULL)
		{
		//	Close open connection.
		//
		::InternetCloseHandle(m_hConnection);
		m_hConnection = NULL;
		}
	}	//	cleanupRequest

/**************************************************************************
 *+ getStatusText - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
Boolean CHttpWindows::getStatusText(
	IN HINTERNET	hRequest, 
	IN String		status,
	IN Int			lenStatus)
	{
	Boolean fOk(False);

	if (status != NULL && lenStatus > 0)
		{
		DWORD len = lenStatus;
		if (::HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_TEXT, status, &len, NULL) == TRUE)
			{
			fOk = True;
			}
		}

	return fOk;
	}	//	getStatusText

/**************************************************************************
 *+ getStatusCode - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
DWord CHttpWindows::getStatusCode(IN HINTERNET hRequest)
	{
	DWord	returnCode(0L);
	Char	code[80];
	DWord	lenCode(StrLen(code));

	if (::HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE, code, &lenCode, NULL) == TRUE)
		{
		//	Convert the return code to a long so we can give it back to the caller.
		//
		returnCode = (DWord)AtoL(code);
		}

	return returnCode;
	}	//	getStatusCode

/**************************************************************************
 *+ getRawHeaders - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
Boolean CHttpWindows::getRawHeaders(
	IN HINTERNET	hRequest, 
	IN String		headers,
	IN Int			lenHeaders)
	{
	Boolean fOk(False);

	if (headers != NULL && lenHeaders > 0)
		{
		DWORD	len = lenHeaders;
		if (::HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, headers, &len, NULL) == TRUE)
			{
			fOk = True;
			}
		}
	
	return fOk;
	}	//	getRawHeaders

/**************************************************************************
 *+ getServerReply - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
Boolean CHttpWindows::getServerReply(
	IN HINTERNET	hRequest, 
	IN String		reply,
	IN Int			lenReply)
	{
	Boolean fOk(False);

	if (reply != NULL && lenReply > 0)
		{
		DWord	bytesRead(0L);
		Char	tempReply[MONSTER_BUFFER];

		Memset(tempReply, 0, MONSTER_BUFFER);
		if (::InternetReadFile(hRequest, tempReply, MONSTER_BUFFER, &bytesRead) == TRUE &&
			bytesRead <= (DWord)lenReply)
			{
			StrNCpy(reply, tempReply, bytesRead);
			fOk = True;
			}
		}

	return fOk;
	}	//	getServerReply

/**************************************************************************
 *+ getServerReplyInfo - One line description.
 *
 *	Abstract:
 *		Abstract text goes here.
 *
 *	Return Value:
 *		Return value description goes here.
 */
void CHttpWindows::getServerReplyInfo(IN HINTERNET hRequest)
	{
	Char	header[BIG_BUFFER];
	Int		headerLen(BIG_BUFFER);

	//	Grab the raw header.
	//
	this->getRawHeaders(hRequest, header, headerLen);

	//	Grab the server status code.
	//
	m_StatusCode = this->getStatusCode(hRequest);

	delete [] m_Response;
	
	//	Read the servers reply to our request.
	//
	m_Response = new Char[MONSTER_BUFFER];	//	rob::note - NEEDS TO BE CALCULATED!
	if (m_Response != NULL)
		{
		Memset(m_Response, 0, MONSTER_BUFFER);
		this->getServerReply(hRequest, m_Response, MONSTER_BUFFER);
		}
	}	//	getServerReplyInfo;
