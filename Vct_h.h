
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Dec 26 09:51:43 2005
 */
/* Compiler settings for Vct.odl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Vct_h_h__
#define __Vct_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DVct_FWD_DEFINED__
#define ___DVct_FWD_DEFINED__
typedef interface _DVct _DVct;
#endif 	/* ___DVct_FWD_DEFINED__ */


#ifndef ___DVctEvents_FWD_DEFINED__
#define ___DVctEvents_FWD_DEFINED__
typedef interface _DVctEvents _DVctEvents;
#endif 	/* ___DVctEvents_FWD_DEFINED__ */


#ifndef __Vct_FWD_DEFINED__
#define __Vct_FWD_DEFINED__

#ifdef __cplusplus
typedef class Vct Vct;
#else
typedef struct Vct Vct;
#endif /* __cplusplus */

#endif 	/* __Vct_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __VCTLib_LIBRARY_DEFINED__
#define __VCTLib_LIBRARY_DEFINED__

/* library VCTLib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_VCTLib,0xDD74050D,0x69DF,0x11D6,0x97,0xC7,0x01,0xC0,0x4F,0x0E,0x8A,0xAD);

#ifndef ___DVct_DISPINTERFACE_DEFINED__
#define ___DVct_DISPINTERFACE_DEFINED__

/* dispinterface _DVct */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DVct,0xDD74050E,0x69DF,0x11D6,0x97,0xC7,0x01,0xC0,0x4F,0x0E,0x8A,0xAD);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DD74050E-69DF-11D6-97C7-01C04F0E8AAD")
    _DVct : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DVctVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DVct * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DVct * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DVct * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DVct * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DVct * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DVct * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DVct * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DVctVtbl;

    interface _DVct
    {
        CONST_VTBL struct _DVctVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DVct_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DVct_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DVct_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DVct_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DVct_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DVct_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DVct_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DVct_DISPINTERFACE_DEFINED__ */


#ifndef ___DVctEvents_DISPINTERFACE_DEFINED__
#define ___DVctEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DVctEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DVctEvents,0xDD74050F,0x69DF,0x11D6,0x97,0xC7,0x01,0xC0,0x4F,0x0E,0x8A,0xAD);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DD74050F-69DF-11D6-97C7-01C04F0E8AAD")
    _DVctEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DVctEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DVctEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DVctEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DVctEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DVctEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DVctEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DVctEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DVctEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DVctEventsVtbl;

    interface _DVctEvents
    {
        CONST_VTBL struct _DVctEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DVctEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DVctEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DVctEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DVctEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DVctEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DVctEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DVctEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DVctEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Vct,0xDD740510,0x69DF,0x11D6,0x97,0xC7,0x01,0xC0,0x4F,0x0E,0x8A,0xAD);

#ifdef __cplusplus

class DECLSPEC_UUID("DD740510-69DF-11D6-97C7-01C04F0E8AAD")
Vct;
#endif
#endif /* __VCTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


