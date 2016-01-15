// ConfirmDlg.cpp : implementation file
//
// A slightly more sophisticated version of AfxMessageBox with Yes/No choice.

#include "stdafx.h"
#include "vct.h"
#include "ConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfirmDlg dialog


CConfirmDlg::CConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfirmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void
CConfirmDlg::init(CString confirmMsg) {
	m_sConfirmMsg = confirmMsg;
}


void CConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirmDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	SetDlgItemText(IDC_CONFIRM_MSG, m_sConfirmMsg);
}


BEGIN_MESSAGE_MAP(CConfirmDlg, CDialog)
	//{{AFX_MSG_MAP(CConfirmDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirmDlg message handlers
