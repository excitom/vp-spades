#if !defined(AFX_BIDDLG_H__DD95FEBA_0141_4643_BA45_987B0D43492E__INCLUDED_)
#define AFX_BIDDLG_H__DD95FEBA_0141_4643_BA45_987B0D43492E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BidDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BidDlg dialog

class BidDlg : public CDialog
{
private:
	BOOL m_NilBid;
	char m_BidValue;
	BOOL m_BidSelected;
	BOOL m_bChanged;
	class CConfirmDlg*	m_ConfDlg;

// Construction
public:
	BidDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BidDlg)
	enum { IDD = IDD_BID };
	CSliderCtrl	m_SliderBid;
	//}}AFX_DATA

	char	getBid() { return m_BidValue; }
	BOOL	nilBid() { return m_NilBid; }
	void	init(CString& hintString);
	BOOL	bidWasSelected() { return m_BidSelected; }
	void	PostNcDestroy();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BidDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BidDlg)
	afx_msg void OnNil();
	afx_msg void OnBid();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnChangeSlider();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIDDLG_H__DD95FEBA_0141_4643_BA45_987B0D43492E__INCLUDED_)
