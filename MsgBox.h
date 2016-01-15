#if !defined(AFX_MSGBOX_H__CF95FDFD_DBDF_40BA_AC5F_6252B7DDEACC__INCLUDED_)
#define AFX_MSGBOX_H__CF95FDFD_DBDF_40BA_AC5F_6252B7DDEACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgBox dialog

class CMsgBox : public CDialog
{
private:
	CString m_sMessageText;

// Construction
public:
	CMsgBox(CWnd* pParent = NULL);   // standard constructor
	void init( CString s );

// Dialog Data
	//{{AFX_DATA(CMsgBox)
	enum { IDD = IDD_MSGBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgBox)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOX_H__CF95FDFD_DBDF_40BA_AC5F_6252B7DDEACC__INCLUDED_)
