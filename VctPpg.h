#if !defined(AFX_VCTPPG_H__DD740520_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_)
#define AFX_VCTPPG_H__DD740520_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VctPpg.h : Declaration of the CVctPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CVctPropPage : See VctPpg.cpp.cpp for implementation.

class CVctPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVctPropPage)
	DECLARE_OLECREATE_EX(CVctPropPage)

// Constructor
public:
	CVctPropPage();

// Dialog Data
	//{{AFX_DATA(CVctPropPage)
	enum { IDD = IDD_PROPPAGE_VCT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CVctPropPage)
	afx_msg void OnRadioWinScore1();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTPPG_H__DD740520_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED)
