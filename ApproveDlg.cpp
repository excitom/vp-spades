// ApproveDlg.cpp : implementation file
//
// Prompt the game leader to approve/disprove of someone sitting in the wrong seat of a restarted game.
//

// This a slightly more sophisticated version of AfxMessageBox with two buttons (Yes and No)

#include "stdafx.h"
#include "vct.h"
#include "ApproveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ApproveDlg dialog


ApproveDlg::ApproveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ApproveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ApproveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void
ApproveDlg::init(CString approveMsg) {
	m_sApproveMsg = approveMsg;
}

void ApproveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ApproveDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	SetDlgItemText(IDC_APPROVE_MSG, m_sApproveMsg);
}


BEGIN_MESSAGE_MAP(ApproveDlg, CDialog)
	//{{AFX_MSG_MAP(ApproveDlg)
	ON_BN_CLICKED(IDCANCEL, OnNo)
	ON_BN_CLICKED(IDOK, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void ApproveDlg::OnNo() 
{
	approved = FALSE;
	CDialog::OnCancel();
}

void ApproveDlg::OnYes() 
{
	approved = TRUE;
	CDialog::OnOK(); 
}

BOOL ApproveDlg::getApproved() {
	return approved;
}

BOOL ApproveDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,0,0,0,0, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
