; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=HintDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vct.h"
LastPage=0
CDK=Y

ClassCount=15
Class1=ApproveDlg
Class2=BidDlg
Class3=BnOptDlg
Class4=CUbqGameBoard
Class5=HintDlg
Class6=History
Class7=CMsgBox
Class8=COptionDlg
Class9=CVctAboutBox
Class10=COptMenu
Class11=CVctCtrl
Class12=CVctPropPage

ResourceCount=13
Resource1=IDD_ABOUTBOX_VCT
Resource2=IDD_PROPPAGE_VCT
Resource3=IDD_MSGBOX
Resource4=IDD_BID
Resource5=IDD_BN_OPT
Resource6=IDD_HINT
Resource7=IDD_APPROVE
Resource8=IDD_TEXT_MSG
Resource9=IDD_HISTORY
Resource10=IDD_PASS
Class13=PassDialog
Resource11=IDD_OPTIONS
Class14=CConfirmDlg
Resource12=IDD_CONFIRM
Class15=TextMsgDlg
Resource13=IDR_MENU_OPT

[CLS:ApproveDlg]
Type=0
BaseClass=CDialog
HeaderFile=ApproveDlg.h
ImplementationFile=ApproveDlg.cpp
LastObject=ApproveDlg
Filter=D
VirtualFilter=dWC

[CLS:BidDlg]
Type=0
BaseClass=CDialog
HeaderFile=BidDlg.h
ImplementationFile=BidDlg.cpp
LastObject=BidDlg
Filter=D
VirtualFilter=dWC

[CLS:BnOptDlg]
Type=0
BaseClass=CDialog
HeaderFile=BnOptDlg.h
ImplementationFile=BnOptDlg.cpp
LastObject=BnOptDlg
Filter=D
VirtualFilter=dWC

[CLS:CUbqGameBoard]
Type=0
BaseClass=CWnd
HeaderFile=GameBrd.h
ImplementationFile=GameBrd.cpp

[CLS:HintDlg]
Type=0
BaseClass=CDialog
HeaderFile=HintDlg.h
ImplementationFile=HintDlg.cpp
LastObject=HintDlg
Filter=D
VirtualFilter=dWC

[CLS:History]
Type=0
BaseClass=CDialog
HeaderFile=History.h
ImplementationFile=History.cpp
Filter=D
LastObject=IDOK

[CLS:CMsgBox]
Type=0
BaseClass=CDialog
HeaderFile=MsgBox.h
ImplementationFile=MsgBox.cpp
LastObject=CMsgBox

[CLS:COptionDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptionDlg.h
ImplementationFile=OptionDlg.cpp

[CLS:CVctAboutBox]
Type=0
BaseClass=CDialog
HeaderFile=VctAboutBox.h
ImplementationFile=VctAboutBox.cpp

[CLS:COptMenu]
Type=0
HeaderFile=VctApp.h
ImplementationFile=VctApp.cpp

[CLS:CVctCtrl]
Type=0
BaseClass=COleControl
HeaderFile=VctCtl.h
ImplementationFile=VctCtl.cpp

[CLS:CVctPropPage]
Type=0
BaseClass=COlePropertyPage
HeaderFile=VctPpg.h
ImplementationFile=VctPpg.cpp

[DLG:IDD_APPROVE]
Type=1
Class=ApproveDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_APPROVE_MSG,static,1342308352
Control5=IDC_APPROVE,static,1342308352

[DLG:IDD_BID]
Type=1
Class=BidDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDBID,button,1342242817
Control3=IDNIL,button,1342242816
Control4=IDC_HINT_TEXT1,static,1342308352
Control5=IDC_SLIDER1,{F08DF954-8592-11D1-B16A-00C0F0283628},1342242816
Control6=IDC_HINT_TEXT2,static,1342308352
Control7=IDC_HINT_TEXT3,static,1342308352
Control8=IDC_PARTNER_HINT,static,1342308352

[DLG:IDD_BN_OPT]
Type=1
Class=BnOptDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDSHOW,button,1342242817
Control3=IDNIL,button,1342242816
Control4=IDC_BN_HINT,static,1342308352

[DLG:IDD_HINT]
Type=1
Class=HintDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDHINT,button,1342242817
Control3=IDNIL,button,1342242816
Control4=IDC_HINT_TEXT1,static,1342308352
Control5=IDC_SLIDER1,{F08DF954-8592-11D1-B16A-00C0F0283628},1342242816
Control6=IDC_HINT_TEXT2,static,1342308352
Control7=IDC_HINT_TEXT3,static,1342308352

[DLG:IDD_HISTORY]
Type=1
Class=History
ControlCount=4
Control1=IDOK,button,1342373889
Control2=IDC_HISTORY,edit,1353910468
Control3=IDC_RADIO_REV,button,1342308361
Control4=IDC_RADIO_FWD,button,1342308361

[DLG:IDD_MSGBOX]
Type=1
Class=CMsgBox
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_MESSAGE_TEXT,static,1342308352

[DLG:IDD_OPTIONS]
Type=1
Class=COptionDlg
ControlCount=22
Control1=IDC_STATIC,static,1342177283
Control2=IDC_GAME_PROP1,static,1342308352
Control3=IDC_PROP_SCORE,static,1342308352
Control4=IDC_NIL_SCORE1,static,1342308352
Control5=IDC_NIL_SCORE2,static,1342308352
Control6=IDC_NIL_SCORE3,static,1342308352
Control7=IDC_NIL_SCORE4,static,1342308352
Control8=IDC_NIL_SCORE5,static,1342308352
Control9=IDC_NIL_SCORE6,static,1342308352
Control10=IDC_RADIO_WIN_SCORE1,button,1342177289
Control11=IDC_RADIO_WIN_SCORE2,button,1342177289
Control12=IDC_NIL_RADIO1,button,1342177289
Control13=IDC_NIL_RADIO2,button,1342177289
Control14=IDC_NIL_RADIO3,button,1342177289
Control15=IDC_NIL_RADIO4,button,1342177289
Control16=IDC_BN_TEXT,static,1342308352
Control17=IDC_PROP_OK,button,1342242817
Control18=IDC_PROP_CANCEL,button,1342242816
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_NIL_TRICKS_COUNT,button,1342177289
Control22=IDC_NIL_SOLO,button,1342177289

[DLG:IDD_ABOUTBOX_VCT]
Type=1
Class=CVctAboutBox
ControlCount=12
Control1=IDC_STATIC,static,1342177283
Control2=IDC_ABOUT_TITLE,static,1342308352
Control3=IDC_ABOUT_COPYR,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_ABOUT_TEXT1,static,1342308352
Control6=IDC_ABOUT_TEXT2,static,1342308352
Control7=IDC_ABOUT_TEXT3,static,1342308352
Control8=IDC_ABOUT_TEXT4,static,1342308352
Control9=IDC_ABOUT_TEXT5,static,1342308352
Control10=IDC_ABOUT_TEXT6,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_VCT]
Type=1
Class=CVctPropPage
ControlCount=0

[MNU:IDR_MENU_OPT]
Type=1
Class=?
Command1=ID_MENU_NEW
Command2=ID_MENU_SOUND
Command3=ID_GAMEOPTIONS
Command4=ID_GAMEOPTIONS_ABOUTSPADES
Command5=ID_MENU_HELP
Command6=ID_MENU_HISTORY
Command7=ID_MENU_EXIT
CommandCount=7

[DLG:IDD_PASS]
Type=1
Class=PassDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308352

[CLS:PassDialog]
Type=0
HeaderFile=PassDialog.h
ImplementationFile=PassDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=PassDialog

[DLG:IDD_CONFIRM]
Type=1
Class=CConfirmDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_CONFIRM_MSG,static,1342308352

[CLS:CConfirmDlg]
Type=0
HeaderFile=ConfirmDlg.h
ImplementationFile=ConfirmDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConfirmDlg

[DLG:IDD_TEXT_MSG]
Type=1
Class=TextMsgDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_TEXT_MSG,static,1342308352

[CLS:TextMsgDlg]
Type=0
HeaderFile=TextMsgDlg.h
ImplementationFile=TextMsgDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=TextMsgDlg
VirtualFilter=dWC

