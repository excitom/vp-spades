#if !defined(AFX_HISTORY_H__7E26B36C_AE69_4CF1_ACF8_1210E4153780__INCLUDED_)
#define AFX_HISTORY_H__7E26B36C_AE69_4CF1_ACF8_1210E4153780__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// History.h : header file
//

#include "Log.h"

/////////////////////////////////////////////////////////////////////////////
// History dialog

class History : public CDialog
{
private:
	CString m_history;
	int		m_Lines;

// Construction
public:
	History(CWnd* pParent = NULL);   // standard constructor
	~History();
	void	DoUpdate();
	void	PostNcDestroy();
	void	init();
	void	scroll();

// Dialog Data
	//{{AFX_DATA(History)
	enum { IDD = IDD_HISTORY };
	CButton	m_radio_rev;
	CButton	m_radio_fwd;
	CButton	m_button;
	CEdit	m_editbox;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(History)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(History)
	afx_msg void OnRadioFwd();
	afx_msg void OnRadioRev();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORY_H__7E26B36C_AE69_4CF1_ACF8_1210E4153780__INCLUDED_)
