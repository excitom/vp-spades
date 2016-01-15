#if !defined(AFX_PASSDIALOG_H__17CD0E08_6017_4817_8695_711C661258BD__INCLUDED_)
#define AFX_PASSDIALOG_H__17CD0E08_6017_4817_8695_711C661258BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PassDialog dialog

class PassDialog : public CDialog
{
// Construction
public:
	PassDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PassDialog)
	enum { IDD = IDD_PASS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PassDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PassDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSDIALOG_H__17CD0E08_6017_4817_8695_711C661258BD__INCLUDED_)
