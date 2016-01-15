// VctPpg.cpp : Implementation of the CVctPropPage property page class.

#include "stdafx.h"
#include "Vct.h"
#include "VctPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVctPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVctPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CVctPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVctPropPage, "VCT.VctPropPage.1",
	0xdd740511, 0x69df, 0x11d6, 0x97, 0xc7, 0x01, 0xc0, 0x4f, 0xe, 0x8a, 0xad)


/////////////////////////////////////////////////////////////////////////////
// CVctPropPage::CVctPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CVctPropPage

BOOL CVctPropPage::CVctPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VCT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CVctPropPage::CVctPropPage - Constructor

CVctPropPage::CVctPropPage() :
	COlePropertyPage(IDD, IDS_VCT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CVctPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CVctPropPage::DoDataExchange - Moves data between page and properties

void CVctPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CVctPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CVctPropPage message handlers
