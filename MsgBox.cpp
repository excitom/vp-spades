// MsgBox.cpp : implementation file
//

// This a slightly more sophisticated version of AfxMessageBox with a single button (OK)

#include "stdafx.h"
#include "vct.h"
#include "MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgBox dialog


CMsgBox::CMsgBox(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void
CMsgBox::init( CString s ) {
	m_sMessageText = s;
}

void CMsgBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	SetDlgItemText(IDC_MESSAGE_TEXT, m_sMessageText);
}


BEGIN_MESSAGE_MAP(CMsgBox, CDialog)
	//{{AFX_MSG_MAP(CMsgBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgBox message handlers

BOOL CMsgBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,0,0,0,0, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

