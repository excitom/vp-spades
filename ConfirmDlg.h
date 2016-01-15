#if !defined(AFX_CONFIRMDLG_H__BF717D1F_E8AB_4241_82BA_C79007FB1E49__INCLUDED_)
#define AFX_CONFIRMDLG_H__BF717D1F_E8AB_4241_82BA_C79007FB1E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfirmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfirmDlg dialog

class CConfirmDlg : public CDialog
{
private:
	CString	m_sConfirmMsg;

// Construction
public:
	CConfirmDlg(CWnd* pParent = NULL);   // standard constructor
	void init(CString confirmMsg);

// Dialog Data
	//{{AFX_DATA(CConfirmDlg)
	enum { IDD = IDD_CONFIRM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfirmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfirmDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIRMDLG_H__BF717D1F_E8AB_4241_82BA_C79007FB1E49__INCLUDED_)
