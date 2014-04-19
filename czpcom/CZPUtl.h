// CZPUtl.h : Declaration of the CCZPUtl

#ifndef __CZPUTL_H_
#define __CZPUTL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCZPUtl
class ATL_NO_VTABLE Utilities : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Utilities, &CLSID_Utilities>,
	public IDispatchImpl<ICZPUtl, &IID_ICZPUtl, &LIBID_Cheezy>
	{
public:
	Utilities() {}

DECLARE_REGISTRY_RESOURCEID(IDR_CZPUTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(Utilities)
	COM_INTERFACE_ENTRY(ICZPUtl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// Utilities
public:
	STDMETHOD(Ping)(BSTR SiteToPing, BSTR SiteUpdateName, BSTR SiteUpdateURL, BSTR* ResultString);
	};	//	CCZPUtl

#endif //__CZPUTL_H_
