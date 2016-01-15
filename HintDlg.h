#if !defined(AFX_HINTDLG_H__75E1950F_FE7E_4940_9B12_2407ADAFCBA3__INCLUDED_)
#define AFX_HINTDLG_H__75E1950F_FE7E_4940_9B12_2407ADAFCBA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HintDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HintDlg dialog

class HintDlg : public CDialog
{
private:
	BOOL m_NilBid;
	char m_HintValue;
	BOOL m_HintSelected;
	BOOL m_bChanged;
	class CConfirmDlg*	m_ConfDlg;

// Construction
public:
	HintDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HintDlg)
	enum { IDD = IDD_HINT };
	CSliderCtrl	m_SliderHint;
	//}}AFX_DATA

	BOOL hintWasSelected() { return m_HintSelected; }
	BOOL nilBid() { return m_NilBid; }
	char getHint() { return m_HintValue; }
	void	PostNcDestroy();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(HintDlg)
	afx_msg void OnChangeSliderHint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnHint();
	afx_msg void OnNil();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HINTDLG_H__75E1950F_FE7E_4940_9B12_2407ADAFCBA3__INCLUDED_)
