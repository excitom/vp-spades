#if !defined(AFX_OPTIONDLG1_H__C64A6771_B221_4812_9588_411C8192580A__INCLUDED_)
#define AFX_OPTIONDLG1_H__C64A6771_B221_4812_9588_411C8192580A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog

class CHands;

class COptionDlg : public CDialog
{
private:
	
	int    targetScore;
	int    nilScore;
	int    blindNilScore;
	int    doubleNilBonus;
	int    doubleBnBonus;
	BOOL   nilBidSolo;
	CHands* hands;
	BOOL	leader;
	BOOL	started;

// Construction
public:
	COptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_OPTIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	BOOL	OnInitDialog();
	void	init( CHands* h, BOOL leader, BOOL started );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionDlg)
	afx_msg void OnNilRadio1();
	afx_msg void OnNilRadio2();
	afx_msg void OnNilRadio3();
	afx_msg void OnNilRadio4();
	afx_msg void OnOptionOK();
	afx_msg void OnOptionCancel();
	afx_msg void OnRadioWinScore1();
	afx_msg void OnRadioWinScore2();
	afx_msg void OnNilSolo();
	afx_msg void OnNilTricksCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONDLG1_H__C64A6771_B221_4812_9588_411C8192580A__INCLUDED_)
