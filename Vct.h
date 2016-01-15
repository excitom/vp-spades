#if !defined(AFX_VCT_H__DD740516_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_)
#define AFX_VCT_H__DD740516_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Vct.h : main header file for VCT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVctApp : See Vct.cpp for implementation.

class CVctApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

#define BUILD_NUM	23
#define PROD_MAJOR	1
#define PROD_MINOR	0

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCT_H__DD740516_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED)
