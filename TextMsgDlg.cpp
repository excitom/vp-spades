// TextMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vct.h"
#include "TextMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TextMsgDlg dialog


TextMsgDlg::TextMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TextMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TextMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void
TextMsgDlg::init(CString textMsg) {
	m_sTextMsg = textMsg;
}

BOOL TextMsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,0,0,0,0, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TextMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TextMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	SetDlgItemText(IDC_TEXT_MSG, m_sTextMsg);
}


BEGIN_MESSAGE_MAP(TextMsgDlg, CDialog)
	//{{AFX_MSG_MAP(TextMsgDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

