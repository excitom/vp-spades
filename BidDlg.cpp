// BidDlg.cpp : implementation file
//
// Show Bid dialog box to a player
//

#include "stdafx.h"
#include "vct.h"
#include "VctApp.h"
#include "BidDlg.h"
#include "ConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global static variable
extern CVctApplet theApplet;

/////////////////////////////////////////////////////////////////////////////
// BidDlg dialog

BidDlg::BidDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BidDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BidDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_NilBid = FALSE;
	m_BidValue = 0;
	m_BidSelected = FALSE;
	m_bChanged = FALSE;
	m_ConfDlg = NULL;
}

void
BidDlg::PostNcDestroy() {
	if (m_ConfDlg) {
		m_ConfDlg->EndDialog(IDABORT);
		m_ConfDlg = NULL;
	}
	CDialog::PostNcDestroy();
	delete this;
	theApplet.clrBidDlg();
}

void BidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BidDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_SliderBid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BidDlg, CDialog)
	//{{AFX_MSG_MAP(BidDlg)
	ON_BN_CLICKED(IDNIL, OnNil)
	ON_BN_CLICKED(IDBID, OnBid)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BidDlg message handlers

void BidDlg::OnBid() 
{
	m_BidValue = m_SliderBid.GetPos();

	// If the slider wasn't moved, confirm that the player really wanted to bid

	if (!m_bChanged) {
		CString p1, p2, msg;
		p1.LoadString(IDS_BID_CONFIRM);
		p2.LoadString(IDS_CONFIRM);
		msg.Format("%s %d\n%s", p1, m_BidValue, p2);
		CConfirmDlg dlg;
		m_ConfDlg = &dlg;
		dlg.init(msg);
		int ret = dlg.DoModal();
		m_ConfDlg = NULL;
		if (ret != IDOK) {
			return;
		}
	}
	m_BidSelected = TRUE;
	ShowWindow(SW_HIDE);
}

void BidDlg::OnNil() 
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
	m_BidValue = 0;
	m_NilBid = TRUE;
	m_BidSelected = TRUE;
	ShowWindow(SW_HIDE);
}

void BidDlg::init(CString& hintString) {
	SetDlgItemText(IDC_PARTNER_HINT, hintString);
}

BOOL BidDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,210, 100,0,0, SWP_SHOWWINDOW | SWP_NOSIZE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BidDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

BEGIN_EVENTSINK_MAP(BidDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(BidDlg)
	ON_EVENT(BidDlg, IDC_SLIDER1, 2 /* Change */, OnChangeSlider, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void BidDlg::OnChangeSlider() 
{
	m_bChanged = TRUE;
}
