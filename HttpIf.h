/*	HTTPIF.H - One line description.
 *	Copyright (C) 2001 Rob Fahrni.  All rights reserved.
 *
 */
#ifndef _HTTPIF_H
#define _HTTPIF_H

typedef long	HTTPRC;

#define STR_PostVerb	"POST\0"
#define STR_HttpVersion	"HTTP/1.0\0"

enum eHTTP
	{
	eHTTPNOERROR		= 0,
	eHTTPCONNECTIONFAIL = 2,
	};


class CHttpBase
	{
public:
	CHttpBase() {}
	virtual ~CHttpBase() {}

	virtual HTTPRC Open(void) = 0;
	virtual void Close(void) = 0;

	virtual HTTPRC SendRequest(IN ConstString verb, IN ConstString fullUrl, IN ConstString request, IN Int requestLen, IN ConstString version) = 0;
	virtual HTTPRC PostRequest(IN ConstString fullUrl, IN ConstString request, IN Int requestLen, IN ConstString version) = 0;

	virtual DWord GetStatusCode(void) = 0;
	virtual ConstString GetStatusText(void) = 0;
	virtual ConstString GetResponse(void) = 0;
	};	//	CHttpBase
typedef CHttpBase*	PCHttpBase;

#endif	//	_HTTPIF_H