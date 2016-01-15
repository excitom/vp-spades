// OptionDlg.cpp : implementation file
//
// Show the game options dialog box.

#include "stdafx.h"
#include "vct.h"
#include "OptionDlg.h"
#include "card.h"
#include "deck.h"
#include "hands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog


COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	//{{AFX_MSG_MAP(COptionDlg)
	ON_BN_CLICKED(IDC_NIL_RADIO1, OnNilRadio1)
	ON_BN_CLICKED(IDC_NIL_RADIO2, OnNilRadio2)
	ON_BN_CLICKED(IDC_NIL_RADIO3, OnNilRadio3)
	ON_BN_CLICKED(IDC_NIL_RADIO4, OnNilRadio4)
	ON_BN_CLICKED(IDC_PROP_OK, OnOptionOK)
	ON_BN_CLICKED(IDC_PROP_CANCEL, OnOptionCancel)
	ON_BN_CLICKED(IDC_RADIO_WIN_SCORE1, OnRadioWinScore1)
	ON_BN_CLICKED(IDC_RADIO_WIN_SCORE2, OnRadioWinScore2)
	ON_BN_CLICKED(IDC_NIL_SOLO, OnNilSolo)
	ON_BN_CLICKED(IDC_NIL_TRICKS_COUNT, OnNilTricksCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void
COptionDlg::init( CHands* h, BOOL leader, BOOL started ) {
	hands = h;

	targetScore    = hands->targetScore;
	nilScore       = hands->nilScore;
	blindNilScore  = hands->blindNilScore;
	doubleNilBonus = hands->doubleNilBonus;
	doubleBnBonus  = hands->doubleBnBonus;
	nilBidSolo     = hands->nilBidSolo;

	this->leader = leader;
	this->started = started;
}
	
BOOL
COptionDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	if (targetScore == 250) {
		((CButton *)(this->GetDlgItem(IDC_RADIO_WIN_SCORE1)))->SetCheck(BST_CHECKED);
	}
	else {		
		((CButton *)(this->GetDlgItem(IDC_RADIO_WIN_SCORE2)))->SetCheck(BST_CHECKED);
	}

	if (doubleNilBonus == 0) {
		((CButton *)(this->GetDlgItem(IDC_NIL_RADIO1)))->SetCheck(BST_CHECKED);
	}
	else {		
		((CButton *)(this->GetDlgItem(IDC_NIL_RADIO2)))->SetCheck(BST_CHECKED);
	}
	
	if (doubleBnBonus == 0) {
		((CButton *)(this->GetDlgItem(IDC_NIL_RADIO3)))->SetCheck(BST_CHECKED);
	}
	else {		
		((CButton *)(this->GetDlgItem(IDC_NIL_RADIO4)))->SetCheck(BST_CHECKED);
	}
		
	if (nilBidSolo) {
		((CButton *)(this->GetDlgItem(IDC_NIL_SOLO)))->SetCheck(BST_CHECKED);
	}
	else {		
		((CButton *)(this->GetDlgItem(IDC_NIL_TRICKS_COUNT)))->SetCheck(BST_CHECKED);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// COptionDlg message handlers

void COptionDlg::OnNilRadio1() 
{
	doubleNilBonus = 0;
	OnInitDialog();			// refresh the button states
}

void COptionDlg::OnNilRadio2() 
{
	doubleNilBonus = 100;
	OnInitDialog();
}

void COptionDlg::OnNilRadio3() 
{
	doubleBnBonus = 0;
	OnInitDialog();
}

void COptionDlg::OnNilRadio4() 
{
	doubleBnBonus = 200;
	OnInitDialog();
}

void COptionDlg::OnRadioWinScore1()
{
	targetScore = 250;
	OnInitDialog();
}

void COptionDlg::OnRadioWinScore2() 
{
	targetScore = 500;
	OnInitDialog();
}

void COptionDlg::OnOptionOK() 
{
	if (!leader) {
		AfxMessageBox(IDS_OPT_LDR_ONLY);
		return;
	}
	if (started) {
		AfxMessageBox(IDS_OPT_STARTED);
		return;
	}
	hands->targetScore    = targetScore;
	hands->nilScore       = nilScore;
	hands->blindNilScore  = blindNilScore;
	hands->doubleNilBonus = doubleNilBonus;
	hands->doubleBnBonus  = doubleBnBonus;
	hands->nilBidSolo     = nilBidSolo;
	
	CDialog::OnOK();	
}

void COptionDlg::OnOptionCancel() 
{
	CDialog::OnCancel();
}

void COptionDlg::OnNilSolo() 
{
	nilBidSolo = TRUE;
	OnInitDialog();
}

void COptionDlg::OnNilTricksCount() 
{
	nilBidSolo = FALSE;
	OnInitDialog();
}
