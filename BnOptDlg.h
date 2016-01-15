#if !defined(AFX_BNOPT_H__A2A03833_C798_4262_90FC_8A36E4943560__INCLUDED_)
#define AFX_BNOPT_H__A2A03833_C798_4262_90FC_8A36E4943560__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BnOptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BnOpt dialog

class BnOptDlg : public CDialog
{
private:
	BOOL m_NilBid;
	BOOL m_bOptSelected;

// Construction
public:
	BnOptDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BnOptDlg)
	enum { IDD = IDD_BN_OPT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL nilBid() { return m_NilBid; }
	BOOL optWasSelected() { return m_bOptSelected; }
	void	init(CString& hintString);
	void	PostNcDestroy();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BnOptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BnOptDlg)
	afx_msg void OnShow();
	afx_msg void OnNil();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BNOPT_H__A2A03833_C798_4262_90FC_8A36E4943560__INCLUDED_)
