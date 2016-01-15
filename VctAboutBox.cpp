// VctAboutBox.cpp : implementation file
//

#include "stdafx.h"
#include "vct.h"
#include "VctAboutBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVctAboutBox dialog


CVctAboutBox::CVctAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CVctAboutBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVctAboutBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVctAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVctAboutBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	CString build;
	build.Format(IDS_ABOUT_TITLE, PROD_MAJOR, PROD_MINOR, BUILD_NUM); 
	SetDlgItemText(IDC_ABOUT_TITLE, build);
}


BEGIN_MESSAGE_MAP(CVctAboutBox, CDialog)
	//{{AFX_MSG_MAP(CVctAboutBox)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVctAboutBox message handlers
