

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ChromeOps.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ChromeOps_i_h__
#define __ChromeOps_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IComponentRegistrar_FWD_DEFINED__
#define __IComponentRegistrar_FWD_DEFINED__
typedef interface IComponentRegistrar IComponentRegistrar;

#endif 	/* __IComponentRegistrar_FWD_DEFINED__ */


#ifndef __IChromeOpsSoft_FWD_DEFINED__
#define __IChromeOpsSoft_FWD_DEFINED__
typedef interface IChromeOpsSoft IChromeOpsSoft;

#endif 	/* __IChromeOpsSoft_FWD_DEFINED__ */


#ifndef __CompReg_FWD_DEFINED__
#define __CompReg_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompReg CompReg;
#else
typedef struct CompReg CompReg;
#endif /* __cplusplus */

#endif 	/* __CompReg_FWD_DEFINED__ */


#ifndef __ChromeOpsSoft_FWD_DEFINED__
#define __ChromeOpsSoft_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChromeOpsSoft ChromeOpsSoft;
#else
typedef struct ChromeOpsSoft ChromeOpsSoft;
#endif /* __cplusplus */

#endif 	/* __ChromeOpsSoft_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComponentRegistrar_INTERFACE_DEFINED__
#define __IComponentRegistrar_INTERFACE_DEFINED__

/* interface IComponentRegistrar */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IComponentRegistrar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a817e7a2-43fa-11d0-9e44-00aa00b6770a")
    IComponentRegistrar : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Attach( 
            /* [in] */ BSTR bstrPath) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterAll( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnregisterAll( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetComponents( 
            /* [out] */ SAFEARRAY * *pbstrCLSIDs,
            /* [out] */ SAFEARRAY * *pbstrDescriptions) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterComponent( 
            /* [in] */ BSTR bstrCLSID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnregisterComponent( 
            /* [in] */ BSTR bstrCLSID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IComponentRegistrarVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentRegistrar * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentRegistrar * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentRegistrar * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponentRegistrar * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponentRegistrar * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponentRegistrar * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponentRegistrar * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, Attach)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Attach )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrPath);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, RegisterAll)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterAll )( 
            IComponentRegistrar * This);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, UnregisterAll)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnregisterAll )( 
            IComponentRegistrar * This);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, GetComponents)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetComponents )( 
            IComponentRegistrar * This,
            /* [out] */ SAFEARRAY * *pbstrCLSIDs,
            /* [out] */ SAFEARRAY * *pbstrDescriptions);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, RegisterComponent)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterComponent )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrCLSID);
        
        DECLSPEC_XFGVIRT(IComponentRegistrar, UnregisterComponent)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnregisterComponent )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrCLSID);
        
        END_INTERFACE
    } IComponentRegistrarVtbl;

    interface IComponentRegistrar
    {
        CONST_VTBL struct IComponentRegistrarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentRegistrar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComponentRegistrar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComponentRegistrar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComponentRegistrar_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IComponentRegistrar_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IComponentRegistrar_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IComponentRegistrar_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IComponentRegistrar_Attach(This,bstrPath)	\
    ( (This)->lpVtbl -> Attach(This,bstrPath) ) 

#define IComponentRegistrar_RegisterAll(This)	\
    ( (This)->lpVtbl -> RegisterAll(This) ) 

#define IComponentRegistrar_UnregisterAll(This)	\
    ( (This)->lpVtbl -> UnregisterAll(This) ) 

#define IComponentRegistrar_GetComponents(This,pbstrCLSIDs,pbstrDescriptions)	\
    ( (This)->lpVtbl -> GetComponents(This,pbstrCLSIDs,pbstrDescriptions) ) 

#define IComponentRegistrar_RegisterComponent(This,bstrCLSID)	\
    ( (This)->lpVtbl -> RegisterComponent(This,bstrCLSID) ) 

#define IComponentRegistrar_UnregisterComponent(This,bstrCLSID)	\
    ( (This)->lpVtbl -> UnregisterComponent(This,bstrCLSID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComponentRegistrar_INTERFACE_DEFINED__ */


#ifndef __IChromeOpsSoft_INTERFACE_DEFINED__
#define __IChromeOpsSoft_INTERFACE_DEFINED__

/* interface IChromeOpsSoft */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IChromeOpsSoft;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8ebd25f7-377d-457d-8d9b-65e8f8b8daae")
    IChromeOpsSoft : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ping( 
            /* [in] */ BSTR str,
            /* [retval][out] */ BSTR *ret) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE chromeBind( 
            /* [in] */ BSTR host,
            /* [in] */ int port,
            /* [retval][out] */ int *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE pushArgs( 
            /* [in] */ BSTR arg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE launch( 
            /* [in] */ BSTR chromeFullPath,
            /* [in] */ int tryBind,
            /* [retval][out] */ int *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE findTargetList( 
            /* [retval][out] */ BSTR *targetList) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE switchTab( 
            /* [in] */ BSTR tabId,
            /* [retval][out] */ int *ret) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getOuterHTML( 
            /* [in] */ BSTR selector,
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE navigate( 
            /* [in] */ BSTR url,
            /* [in] */ BSTR referrer) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE isLoadingFinished( 
            /* [retval][out] */ int *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE runScript( 
            /* [in] */ BSTR expression,
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE captureScreenshot( 
            /* [in] */ BSTR format,
            /* [in] */ int quality,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ float scale,
            /* [in] */ BSTR imgFullPath) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE inputText( 
            /* [in] */ BSTR selector,
            /* [in] */ BSTR txt) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getCookies( 
            /* [in] */ BSTR urls,
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setCookie( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [in] */ BSTR url,
            /* [in] */ BSTR domain,
            /* [in] */ BSTR path,
            /* [in] */ int secure,
            /* [in] */ int httpOnly,
            /* [in] */ BSTR sameSite,
            /* [in] */ int expires) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setCookies( 
            /* [in] */ BSTR jsonCookies) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clearBrowserCache( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE clearBrowserCookies( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setCacheDisabled( 
            /* [in] */ int cacheDisabled) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IChromeOpsSoftVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChromeOpsSoft * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChromeOpsSoft * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChromeOpsSoft * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChromeOpsSoft * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChromeOpsSoft * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChromeOpsSoft * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChromeOpsSoft * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, ping)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ping )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR str,
            /* [retval][out] */ BSTR *ret);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, chromeBind)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *chromeBind )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR host,
            /* [in] */ int port,
            /* [retval][out] */ int *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, pushArgs)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *pushArgs )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR arg);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, launch)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *launch )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR chromeFullPath,
            /* [in] */ int tryBind,
            /* [retval][out] */ int *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, findTargetList)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *findTargetList )( 
            IChromeOpsSoft * This,
            /* [retval][out] */ BSTR *targetList);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, switchTab)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *switchTab )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR tabId,
            /* [retval][out] */ int *ret);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, getOuterHTML)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getOuterHTML )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR selector,
            /* [retval][out] */ BSTR *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, navigate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *navigate )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR url,
            /* [in] */ BSTR referrer);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, isLoadingFinished)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *isLoadingFinished )( 
            IChromeOpsSoft * This,
            /* [retval][out] */ int *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, runScript)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *runScript )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR expression,
            /* [retval][out] */ BSTR *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, captureScreenshot)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *captureScreenshot )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR format,
            /* [in] */ int quality,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ float scale,
            /* [in] */ BSTR imgFullPath);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, inputText)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *inputText )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR selector,
            /* [in] */ BSTR txt);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, getCookies)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *getCookies )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR urls,
            /* [retval][out] */ BSTR *retVal);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, setCookie)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setCookie )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value,
            /* [in] */ BSTR url,
            /* [in] */ BSTR domain,
            /* [in] */ BSTR path,
            /* [in] */ int secure,
            /* [in] */ int httpOnly,
            /* [in] */ BSTR sameSite,
            /* [in] */ int expires);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, setCookies)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setCookies )( 
            IChromeOpsSoft * This,
            /* [in] */ BSTR jsonCookies);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, clearBrowserCache)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *clearBrowserCache )( 
            IChromeOpsSoft * This);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, clearBrowserCookies)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *clearBrowserCookies )( 
            IChromeOpsSoft * This);
        
        DECLSPEC_XFGVIRT(IChromeOpsSoft, setCacheDisabled)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *setCacheDisabled )( 
            IChromeOpsSoft * This,
            /* [in] */ int cacheDisabled);
        
        END_INTERFACE
    } IChromeOpsSoftVtbl;

    interface IChromeOpsSoft
    {
        CONST_VTBL struct IChromeOpsSoftVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChromeOpsSoft_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IChromeOpsSoft_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IChromeOpsSoft_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IChromeOpsSoft_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IChromeOpsSoft_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IChromeOpsSoft_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IChromeOpsSoft_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IChromeOpsSoft_ping(This,str,ret)	\
    ( (This)->lpVtbl -> ping(This,str,ret) ) 

#define IChromeOpsSoft_chromeBind(This,host,port,retVal)	\
    ( (This)->lpVtbl -> chromeBind(This,host,port,retVal) ) 

#define IChromeOpsSoft_pushArgs(This,arg)	\
    ( (This)->lpVtbl -> pushArgs(This,arg) ) 

#define IChromeOpsSoft_launch(This,chromeFullPath,tryBind,retVal)	\
    ( (This)->lpVtbl -> launch(This,chromeFullPath,tryBind,retVal) ) 

#define IChromeOpsSoft_findTargetList(This,targetList)	\
    ( (This)->lpVtbl -> findTargetList(This,targetList) ) 

#define IChromeOpsSoft_switchTab(This,tabId,ret)	\
    ( (This)->lpVtbl -> switchTab(This,tabId,ret) ) 

#define IChromeOpsSoft_getOuterHTML(This,selector,retVal)	\
    ( (This)->lpVtbl -> getOuterHTML(This,selector,retVal) ) 

#define IChromeOpsSoft_navigate(This,url,referrer)	\
    ( (This)->lpVtbl -> navigate(This,url,referrer) ) 

#define IChromeOpsSoft_isLoadingFinished(This,retVal)	\
    ( (This)->lpVtbl -> isLoadingFinished(This,retVal) ) 

#define IChromeOpsSoft_runScript(This,expression,retVal)	\
    ( (This)->lpVtbl -> runScript(This,expression,retVal) ) 

#define IChromeOpsSoft_captureScreenshot(This,format,quality,x,y,width,height,scale,imgFullPath)	\
    ( (This)->lpVtbl -> captureScreenshot(This,format,quality,x,y,width,height,scale,imgFullPath) ) 

#define IChromeOpsSoft_inputText(This,selector,txt)	\
    ( (This)->lpVtbl -> inputText(This,selector,txt) ) 

#define IChromeOpsSoft_getCookies(This,urls,retVal)	\
    ( (This)->lpVtbl -> getCookies(This,urls,retVal) ) 

#define IChromeOpsSoft_setCookie(This,name,value,url,domain,path,secure,httpOnly,sameSite,expires)	\
    ( (This)->lpVtbl -> setCookie(This,name,value,url,domain,path,secure,httpOnly,sameSite,expires) ) 

#define IChromeOpsSoft_setCookies(This,jsonCookies)	\
    ( (This)->lpVtbl -> setCookies(This,jsonCookies) ) 

#define IChromeOpsSoft_clearBrowserCache(This)	\
    ( (This)->lpVtbl -> clearBrowserCache(This) ) 

#define IChromeOpsSoft_clearBrowserCookies(This)	\
    ( (This)->lpVtbl -> clearBrowserCookies(This) ) 

#define IChromeOpsSoft_setCacheDisabled(This,cacheDisabled)	\
    ( (This)->lpVtbl -> setCacheDisabled(This,cacheDisabled) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IChromeOpsSoft_INTERFACE_DEFINED__ */



#ifndef __ChromeOpsLib_LIBRARY_DEFINED__
#define __ChromeOpsLib_LIBRARY_DEFINED__

/* library ChromeOpsLib */
/* [custom][version][uuid] */ 


EXTERN_C const IID LIBID_ChromeOpsLib;

EXTERN_C const CLSID CLSID_CompReg;

#ifdef __cplusplus

class DECLSPEC_UUID("bd6c7821-d56c-4b78-87fc-52713f38eecd")
CompReg;
#endif

EXTERN_C const CLSID CLSID_ChromeOpsSoft;

#ifdef __cplusplus

class DECLSPEC_UUID("c44295a9-d02c-49aa-95a1-f1bbabb8527a")
ChromeOpsSoft;
#endif
#endif /* __ChromeOpsLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


