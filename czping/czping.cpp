// czping.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "czping.h"

//	Helper Macros.
//
#define PING_TemplateString		"<?xml version=\"1.0\"?><methodCall><methodName>weblogUpdates.ping</methodName><params><param><value>%s</value></param><param><value>%s</value></param></params></methodCall>\0"
#define PING_TemplateStringLen	StrLen(PING_TemplateString)

#define	LITTLE_BUFF					8	//	Padding.
#define CALCREQUESTSIZE(t, sn, su)	(t+sn+su+LITTLE_BUFF)

static Long prepareRequestBuffer(
	IN		String	SiteUpdateName,
	IN		Long	LenSiteUpdateName,
	IN		String	SiteUpdateURL,
	IN		Long	LenSiteUpdateURL,
	IN OUT	String*	RequestBufferPtrPtr,		//	pointer to a pointer, alloced here.
	IN OUT	Long*	RequestBufferLenPtr)		//	pointer to a pointer, alloced here.
	{
	Long Error(E_BadParam);

	if (NULL != SiteUpdateName &&
		0 != LenSiteUpdateName &&
		NULL != SiteUpdateURL &&
		0 != LenSiteUpdateURL &&
		NULL != RequestBufferPtrPtr &&
		NULL != RequestBufferLenPtr)
		{
		*RequestBufferLenPtr	= 0L;
		*RequestBufferPtrPtr	= NULL;
		Error					= E_OutOfMem;

		//	Calculate the amount of memory we're going to need for our request.
		//
		*RequestBufferLenPtr	= CALCREQUESTSIZE(PING_TemplateStringLen, LenSiteUpdateName, LenSiteUpdateURL);
		if (0 != *RequestBufferLenPtr)
			{
			//	Allocate the buffer.
			//
			*RequestBufferPtrPtr = new Char[*RequestBufferLenPtr];
			if (NULL != *RequestBufferPtrPtr)
				{
				//	We zero fill the buffer because we're going to return the actual
				//	length of the string based on the amount of data jammed into it
				//	To do that we use StrLen, which needs a zero terminated string.
				//
				::ZeroMemory(*RequestBufferPtrPtr, *RequestBufferLenPtr);

				//	Build the request string.
				//
				Sprintf(*RequestBufferPtrPtr, PING_TemplateString, SiteUpdateName, SiteUpdateURL);

				//	Return the number of bytes copied into the buffer, the string length really.
				//
				*RequestBufferLenPtr = StrLen(*RequestBufferPtrPtr);
				
				Error = SUCCESS;
				}
			}
		}

	return Error;
	}	//	prepareRequestBuffer

static void freeRequestBuffer(IN OUT String* RequestBufferPtrPtr)		//	pointer to a pointer, alloced here.
	{
	if (NULL != RequestBufferPtrPtr)
		{
		delete [] *RequestBufferPtrPtr;
		*RequestBufferPtrPtr = NULL;
		}
	}	//	freeRequestBuffer

CZPAPI(Long) WeblogsDotComPing(
	IN		String	SiteToPing,
	IN		Long	LenSiteToPing,
	IN		String	SiteUpdateName,
	IN		Long	LenSiteUpdateName,
	IN		String	SiteUpdateURL,
	IN		Long	LenSiteUpdateURL,
	IN OUT	String	ReturnString,
	IN OUT	Long*	ReturnStringLen)
	{
	Long	Error(FAILURE);
	Long	RequestBufferLen(0L);
	String	RequestBuffer = NULL;

	//	Taking a GOB of parameters we need to create the request buffer.
	//	We feed it RequestBuffer and IT allocates the memory for us, so 
	//	we eventually owe a delete on the buffer. Call freeRequestBuffer
	//	when finished, it knows what to do.
	//
	Error = prepareRequestBuffer(SiteUpdateName, LenSiteUpdateName, SiteUpdateURL, LenSiteUpdateURL, &RequestBuffer, &RequestBufferLen);
	if (SUCCESS == Error &&
		0 != RequestBufferLen &&
		NULL != RequestBuffer &&
		NULL != RequestBuffer[0])
		{
		CHttpWindows	httpRequest;
		if (httpRequest.Open() == eHTTPNOERROR)
			{
			//	Post the request.
			//
			httpRequest.PostRequest(SiteToPing, RequestBuffer, RequestBufferLen, NULL);
			if (NULL != ReturnString &&
				NULL != ReturnStringLen)
				{
				::ZeroMemory(ReturnString, *ReturnStringLen);

				//	Get the reply from the server, we're going to return this to the
				//	caller if we can.
				//
				ConstString ReplyBuffer = httpRequest.GetResponse();
				if (NULL != ReplyBuffer &&
					NULL != ReplyBuffer[0])
					{
					Long ReplyBufferLen(StrLen(ReplyBuffer));

					//	If the resulting buffer is LARGER than what we were given then we need to copy
					//	what we can, otherwise we copy the entire reply buffer.
					//
					StrNCpy(ReturnString, ReplyBuffer, ((*ReturnStringLen > ReplyBufferLen) ? ReplyBufferLen : *ReturnStringLen));

					//	This will tell the caller how many bytes we coppied into the return
					//	buffer.
					//
					*ReturnStringLen = ReplyBufferLen;
					}
				else
					{
					//	Whoops, nothing to return.
					//
					*ReturnStringLen = 0L;
					}
				}			
			}
		}

	if (NULL != RequestBuffer)
		{
		freeRequestBuffer(&RequestBuffer);
		}

	return Error;
	}	//	WeblogsDotComPing
