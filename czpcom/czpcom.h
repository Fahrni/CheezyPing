/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 02 11:23:34 2003
 */
/* Compiler settings for D:\Solutions\RobMisc\CheezyPing\czpcom\czpcom.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __czpcom_h__
#define __czpcom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICZPUtl_FWD_DEFINED__
#define __ICZPUtl_FWD_DEFINED__
typedef interface ICZPUtl ICZPUtl;
#endif 	/* __ICZPUtl_FWD_DEFINED__ */


#ifndef __Utilities_FWD_DEFINED__
#define __Utilities_FWD_DEFINED__

#ifdef __cplusplus
typedef class Utilities Utilities;
#else
typedef struct Utilities Utilities;
#endif /* __cplusplus */

#endif 	/* __Utilities_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICZPUtl_INTERFACE_DEFINED__
#define __ICZPUtl_INTERFACE_DEFINED__

/* interface ICZPUtl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICZPUtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E614490-96A1-4249-9833-C1ADB88F59B4")
    ICZPUtl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ping( 
            BSTR SiteToPing,
            BSTR SiteUpdateName,
            BSTR SiteUpdateURL,
            BSTR __RPC_FAR *ResultString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICZPUtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICZPUtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICZPUtl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICZPUtl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICZPUtl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICZPUtl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICZPUtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICZPUtl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Ping )( 
            ICZPUtl __RPC_FAR * This,
            BSTR SiteToPing,
            BSTR SiteUpdateName,
            BSTR SiteUpdateURL,
            BSTR __RPC_FAR *ResultString);
        
        END_INTERFACE
    } ICZPUtlVtbl;

    interface ICZPUtl
    {
        CONST_VTBL struct ICZPUtlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICZPUtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICZPUtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICZPUtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICZPUtl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICZPUtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICZPUtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICZPUtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICZPUtl_Ping(This,SiteToPing,SiteUpdateName,SiteUpdateURL,ResultString)	\
    (This)->lpVtbl -> Ping(This,SiteToPing,SiteUpdateName,SiteUpdateURL,ResultString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICZPUtl_Ping_Proxy( 
    ICZPUtl __RPC_FAR * This,
    BSTR SiteToPing,
    BSTR SiteUpdateName,
    BSTR SiteUpdateURL,
    BSTR __RPC_FAR *ResultString);


void __RPC_STUB ICZPUtl_Ping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICZPUtl_INTERFACE_DEFINED__ */



#ifndef __Cheezy_LIBRARY_DEFINED__
#define __Cheezy_LIBRARY_DEFINED__

/* library Cheezy */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Cheezy;

EXTERN_C const CLSID CLSID_Utilities;

#ifdef __cplusplus

class DECLSPEC_UUID("80FCCD51-1590-4463-866F-C8CAC2BF1305")
Utilities;
#endif
#endif /* __Cheezy_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
