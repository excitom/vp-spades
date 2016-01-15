#if !defined(AFX_TEXTMSGDLG_H__9278E31D_E1BD_4351_8C35_1ABC2818E26A__INCLUDED_)
#define AFX_TEXTMSGDLG_H__9278E31D_E1BD_4351_8C35_1ABC2818E26A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextMsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TextMsgDlg dialog

class TextMsgDlg : public CDialog
{
private:
	CString	m_sTextMsg;

// Construction
public:
	TextMsgDlg(CWnd* pParent = NULL);   // standard constructor
	void init(CString textMsg);

// Dialog Data
	//{{AFX_DATA(TextMsgDlg)
	enum { IDD = IDD_TEXT_MSG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TextMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TextMsgDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTMSGDLG_H__9278E31D_E1BD_4351_8C35_1ABC2818E26A__INCLUDED_)
