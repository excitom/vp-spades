// HintDlg.cpp : implementation file
//
// Show Hint dialog box to a player.
//

#include "stdafx.h"
#include "vct.h"
#include "VctApp.h"
#include "HintDlg.h"
#include "ConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global static variable
extern CVctApplet theApplet;

/////////////////////////////////////////////////////////////////////////////
// HintDlg dialog


HintDlg::HintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(HintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(HintDlg)
	//}}AFX_DATA_INIT
	m_NilBid = FALSE;
	m_HintValue = 0;
	m_HintSelected = FALSE;
	m_bChanged = FALSE;
	m_ConfDlg = NULL;
}

void
HintDlg::PostNcDestroy() {
	if (m_ConfDlg) {
		m_ConfDlg->EndDialog(IDABORT);
		m_ConfDlg = NULL;
	}
	CDialog::PostNcDestroy();
	delete this;
	theApplet.clrHintDlg();
}

void HintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HintDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_SliderHint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HintDlg, CDialog)
	//{{AFX_MSG_MAP(HintDlg)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDHINT, OnHint)
	ON_BN_CLICKED(IDNIL, OnNil)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HintDlg message handlers

BEGIN_EVENTSINK_MAP(HintDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(HintDlg)
	ON_EVENT(HintDlg, IDC_SLIDER1, 2 /* Change */, OnChangeSliderHint, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void HintDlg::OnChangeSliderHint() 
{
	m_bChanged = TRUE;
}

void HintDlg::OnNil() 
{
	CString p;
	p.LoadString(IDS_NIL_CONFIRM);
	CConfirmDlg dlg;
	m_ConfDlg = &dlg;
	dlg.init(p);
	int ret = dlg.DoModal();
	m_ConfDlg = NULL;
	if (ret != IDOK) {
		return;
	}
	m_HintValue = 0;
	m_NilBid = TRUE;
	m_HintSelected = TRUE;
	ShowWindow(SW_HIDE);
}

void HintDlg::OnHint() 
{
	m_HintValue = m_SliderHint.GetPos();

	// If the slider wasn't moved, confirm that the player really meant to hint

	if (!m_bChanged) {
		CString p1, p2, msg;
		p1.LoadString(IDS_HINT_CONFIRM);
		p2.LoadString(IDS_CONFIRM);
		msg.Format("%s %d\n%s", p1, m_HintValue, p2);
		CConfirmDlg dlg;
		m_ConfDlg = &dlg;
		dlg.init(msg);
		int ret = dlg.DoModal();
		m_ConfDlg = NULL;
		if (ret != IDOK) {
			return;
		}
	}
	m_HintSelected = TRUE;
	ShowWindow(SW_HIDE);
}

BOOL HintDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,210,100,0,0, SWP_SHOWWINDOW | SWP_NOSIZE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void HintDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
