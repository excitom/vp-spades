// PassDialog.cpp : implementation file
//

#include "stdafx.h"
#include "vct.h"
#include "PassDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// PassDialog dialog
//
// Show the dialog box to confirm that a partner has passed cards to a team mate.
//

PassDialog::PassDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PassDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(PassDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PassDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PassDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PassDialog, CDialog)
	//{{AFX_MSG_MAP(PassDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL PassDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowPos(&this->wndTop,0,0,0,0, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
