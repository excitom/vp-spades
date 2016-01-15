// BnOptDlg.cpp : implementation file
//
// Show Blind Nil option dialog box to a player.
//

#include "stdafx.h"
#include "vct.h"
#include "VctApp.h"
#include "BnOptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global static variable
extern CVctApplet theApplet;

/////////////////////////////////////////////////////////////////////////////
// BnOpt dialog


BnOptDlg::BnOptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BnOptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BnOptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bOptSelected = FALSE;
}

void
BnOptDlg::PostNcDestroy() {
	CDialog::PostNcDestroy();
	delete this;
	theApplet.clrBnOptDlg();
}

void BnOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BnOptDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BnOptDlg, CDialog)
	//{{AFX_MSG_MAP(BnOptDlg)
	ON_BN_CLICKED(IDSHOW, OnShow)
	ON_BN_CLICKED(IDNIL, OnNil)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BnOpt message handlers

void BnOptDlg::OnShow() 
{
	m_NilBid = FALSE;
	m_bOptSelected = TRUE;
	ShowWindow(SW_HIDE);
}

void BnOptDlg::OnNil() 
{
	m_NilBid = TRUE;
	m_bOptSelected = TRUE;
	ShowWindow(SW_HIDE);
}

BOOL BnOptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,210, 100,0,0, SWP_SHOWWINDOW | SWP_NOSIZE);
	//SetWindowPos(&CWnd::wndTopMost, 210, 100, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE); 
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BnOptDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void BnOptDlg::init(CString& hintString) {
	SetDlgItemText(IDC_BN_HINT, hintString);
}