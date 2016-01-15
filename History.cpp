// History.cpp : implementation file
//
// Show the game history in a dyamically updated scrolling dialog box.
//

#include "stdafx.h"
#include "vct.h"
#include "VctApp.h"
#include "History.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global static variable
extern CVctApplet theApplet;

// static pointers

class LogRecord;
LogRecord* m_Fwd = NULL;
LogRecord* m_Rev = NULL;

BOOL newestFirst = TRUE;

/////////////////////////////////////////////////////////////////////////////
// History dialog


History::History(CWnd* pParent /*=NULL*/)
	: CDialog(History::IDD, pParent)
{

	//{{AFX_DATA_INIT(History)
	//}}AFX_DATA_INIT
	m_Lines = 0;
}

History::~History() {
	m_history.Empty();
}

void
History::init() {
	if (newestFirst) {
		((CButton *)(this->GetDlgItem(IDC_RADIO_REV)))->SetCheck(BST_CHECKED);
		((CButton *)(this->GetDlgItem(IDC_RADIO_FWD)))->SetCheck(BST_UNCHECKED);
	}
	else {		
		((CButton *)(this->GetDlgItem(IDC_RADIO_FWD)))->SetCheck(BST_CHECKED);
		((CButton *)(this->GetDlgItem(IDC_RADIO_REV)))->SetCheck(BST_UNCHECKED);
	}
}


void History::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(History)
	DDX_Control(pDX, IDC_RADIO_REV, m_radio_rev);
	DDX_Control(pDX, IDC_RADIO_FWD, m_radio_fwd);
	DDX_Control(pDX, IDOK, m_button);
	DDX_Control(pDX, IDC_HISTORY, m_editbox);
	DDX_Text(pDX, IDC_HISTORY, m_history);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(History, CDialog)
	//{{AFX_MSG_MAP(History)
	ON_BN_CLICKED(IDC_RADIO_FWD, OnRadioFwd)
	ON_BN_CLICKED(IDC_RADIO_REV, OnRadioRev)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// History message handlers
//

void
History::DoUpdate() {
	m_history.Empty();
	m_Lines = 0;
	LogRecord* p; 
	if (newestFirst) {
		p = Log::getPrev(NULL);
		while(p) {
			if (p->isTrickRec()) {
				if (p->isInLastTrick()) {
					m_history += p->getStr();
					m_Lines++;
				}
			}
			else {
				m_history += p->getStr();
				m_Lines++;
			}
			p = Log::getPrev(p);
		}
	}
	else {
		p = Log::getNext(NULL);
		while(p) {
			if (p->isTrickRec()) {
				if (p->isInLastTrick()) {
					m_history += p->getStr();
					m_Lines++;
				}
			}
			else {
				m_history += p->getStr();
				m_Lines++;
			}
			p = Log::getNext(p);
		}
	}
	UpdateData(FALSE);
}

void
History::scroll() {

	// If showing oldest first, scroll to the bottom

	if (!newestFirst) {
		m_editbox.LineScroll(m_Lines, 0);
	}
}

void
History::PostNcDestroy() {
	m_history.Empty();
	CDialog::PostNcDestroy();
	theApplet.clrHistoryDlg();
	delete this;
}

void History::OnRadioFwd() 
{
	newestFirst = FALSE;
	init();
	DoUpdate();
}

void History::OnRadioRev() 
{
	newestFirst = TRUE;
	init();
	DoUpdate();	
}


void History::OnSize(UINT nType, int cx, int cy) 
{
	if (!m_editbox)
		return;
	
	CDialog::OnSize(nType, cx, cy);
	
	m_editbox.SetWindowPos  (&m_editbox,   7,  7, cx-14, cy-72, SWP_NOZORDER | SWP_SHOWWINDOW); 
	m_radio_fwd.SetWindowPos(&m_radio_fwd, 28, cy-60, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE); 
	m_radio_rev.SetWindowPos(&m_radio_rev, 104,cy-60, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE); 
	m_button.SetWindowPos   (&m_button,    67, cy-32, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE); 
}


/////////////////////////////////////////////////////////
// Write to the game transcript log
//
//void
//Log::scroll() {
//	History* h = theApplet.getHistoryDlg();
//	if (h) {
//		h->scroll();
//	}
//}

void
Log::writeLog( CString& line ) {
	writeLog( line, FALSE );
}

void
Log::writeLog( CString& line, BOOL trick ) {
	LogRecord* p = new LogRecord(trick);
	p->addStr( line );
	
	History* h = theApplet.getHistoryDlg();
	if (h) {
		h->DoUpdate();
		h->scroll();
	}
}

void
Log::writeLog( const char* line ) {
	writeLog( line, FALSE );
}

void
Log::writeLog( const char* line, BOOL trick ) {
	LogRecord* p = new LogRecord(trick);
	p->addStr( line );

	History* h = theApplet.getHistoryDlg();
	if (h) {
		h->DoUpdate();
		h->scroll();
	}
}

void
Log::update() {
	History* h = theApplet.getHistoryDlg();
	if (h) {
		h->DoUpdate();
		h->scroll();
	}
}

LogRecord::LogRecord( BOOL trickRec ) {
	if (!m_Fwd) {
		m_Fwd = this;
		this->next = NULL;
		m_Rev = this;
		this->prev = NULL;
	}
	else {
		LogRecord* p = m_Fwd;
		while (p->next) {
			p = p->next;
		}
		p->next = this;
		this->next = NULL;
		this->prev = m_Rev;
		m_Rev = this;
	}
	this->trickRec = trickRec;
	this->lastTrick = (trickRec) ? TRUE : FALSE;
}

LogRecord::~LogRecord() {
	LogRecord* p = m_Fwd;
	LogRecord* q = NULL;
	while (p != this) {
		q = p;
		p = p->next;
	}
	if (q) {
		q->next = p->next;
	}
	else {
		m_Fwd = p->next;
	}
	p = m_Rev;
	q = NULL;
	while (p != this) {
		q = p;
		p = p->prev;
	}
	if (q) {
		q->prev = p->prev;
	}
	else {
		m_Rev = p->prev;
	}
}

void
LogRecord::addStr( CString& rec ) {
	this->rec = rec;
	if (this->rec.Right(2) != "\r\n") {
		this->rec += "\r\n";
	}
}

void
LogRecord::addStr( const char* rec ) {
	this->rec = rec;
	if (this->rec.Right(2) != "\r\n") {
		this->rec += "\r\n";
	}
}

LogRecord*
Log::getNext( LogRecord* curr ) {
	return (curr) ? curr->getNext() : m_Fwd;
}

LogRecord*
Log::getPrev( LogRecord* curr ) {
	return (curr) ? curr->getPrev() : m_Rev;
}

void
Log::trickEnded() {
	int ctr = 1;
	for (LogRecord* p = m_Rev; p; p = p->getPrev()) {
		if (p->isTrickRec()) {
			if (ctr++ > 4) {
				p->clearLastTrick();
			}
		}
	}
	p = new LogRecord(FALSE);
	p->addStr("--------------------");
}

void
Log::removeAll() {
	for (LogRecord* p = m_Fwd; p; ) {
		LogRecord* q = p;
		p = p->getNext();
		delete q;
	}
	m_Fwd = NULL;
	m_Rev = NULL;
}

void
Log::setPref(BOOL n) {
	newestFirst = n;
}

BOOL
Log::getPref() {
	return newestFirst;
}

