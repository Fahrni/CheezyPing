/*	HTTPWIN.H - One line description.
 *	Copyright (C) 2001 Rob Fahrni.  All rights reserved.
 *
 */
#ifndef _HTTPWIN_H
#define _HTTPWIN_H

class CHttpWindows :
	public CHttpBase
	{
private:
	HINTERNET	m_hInternet;
	HINTERNET	m_hConnection;
	DWord		m_StatusCode;
	String		m_Response;

private:	//	methods
	HINTERNET createRequest(IN ConstString verb, IN ConstString fullUrl, IN ConstString version /*=*/);
	void cleanupRequest(IN HINTERNET& hRequest);
	Boolean getStatusText(IN HINTERNET hRequest, IN String status, IN Int lenStatus);
	DWord getStatusCode(IN HINTERNET hRequest);
	Boolean getRawHeaders(IN HINTERNET hRequest, IN String status, IN Int lenStatus);
	Boolean getServerReply(IN HINTERNET hRequest, IN String status, IN Int lenStatus);
	void getServerReplyInfo(IN HINTERNET hRequest);

public:
	CHttpWindows();
	virtual ~CHttpWindows();

	virtual HTTPRC Open(void);
	virtual void Close(void);

	virtual HTTPRC SendRequest(IN ConstString verb, IN ConstString fullUrl, IN ConstString request, IN Int requestLen, IN ConstString version);
	virtual HTTPRC PostRequest(IN ConstString fullUrl, IN ConstString request, IN Int requestLen, IN ConstString version);

	virtual DWord GetStatusCode(void);
	virtual ConstString GetStatusText(void);
	virtual ConstString GetResponse(void);
	};	//	CHttpWindows

typedef CHttpWindows*	PCHttpWindows;
#endif	//	_HTTPWIN_H