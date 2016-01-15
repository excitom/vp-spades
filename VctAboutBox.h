#if !defined(AFX_VCTABOUTBOX_H__8A6F1DE1_F54C_4960_BE9C_E3AA43F552BD__INCLUDED_)
#define AFX_VCTABOUTBOX_H__8A6F1DE1_F54C_4960_BE9C_E3AA43F552BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VctAboutBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVctAboutBox dialog

class CVctAboutBox : public CDialog
{
// Construction
public:
	CVctAboutBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVctAboutBox)
	enum { IDD = IDD_ABOUTBOX_VCT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVctAboutBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVctAboutBox)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTABOUTBOX_H__8A6F1DE1_F54C_4960_BE9C_E3AA43F552BD__INCLUDED_)
