#if !defined(AFX_APPROVEDLG_H__48E18430_A7DE_46C9_B125_19E1413AA988__INCLUDED_)
#define AFX_APPROVEDLG_H__48E18430_A7DE_46C9_B125_19E1413AA988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ApproveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ApproveDlg dialog

class ApproveDlg : public CDialog
{
private:
	CString	m_sApproveMsg;
	BOOL    approved;

// Construction
public:
	ApproveDlg(CWnd* pParent = NULL);   // standard constructor
	void init(CString approveMsg);
	BOOL getApproved();

// Dialog Data
	//{{AFX_DATA(ApproveDlg)
	enum { IDD = IDD_APPROVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ApproveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ApproveDlg)
	afx_msg void OnNo();
	afx_msg void OnYes();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPROVEDLG_H__48E18430_A7DE_46C9_B125_19E1413AA988__INCLUDED_)
