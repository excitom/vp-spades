# Microsoft Developer Studio Project File - Name="Vct" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Vct - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Vct.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Vct.mak" CFG="Vct - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Vct - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Vct - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Vct - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Vct - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Vct - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../Release/Spades"
# PROP Intermediate_Dir "../../Release/Spades"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "c:\games\image32\imgCode" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /fo"..\..\Release\Spades\Spades.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/Mega.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 c:\games\image32\Release\image32.lib wsock32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../Release/Spades/spades.ocx"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\../../Release/Spades
TargetPath=\games\games-Source\Release\Spades\spades.ocx
InputPath=\games\games-Source\Release\Spades\spades.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Vct - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../Debug/Spades"
# PROP Intermediate_Dir "../../Debug/Spades"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "c:\games\image32\imgCode" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib c:\games\image32\debug\image32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\../../Debug/Spades
TargetPath=\games\games-Source\Debug\Spades\Vct.ocx
InputPath=\games\games-Source\Debug\Spades\Vct.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Vct - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./image32\imgCode" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib ./image32/Debug/image32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\Vct.ocx
InputPath=.\DebugU\Vct.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Vct - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./image32\imgCode" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 wsock32.lib ./image32/Release/image32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Vct.ocx
InputPath=.\ReleaseU\Vct.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Vct - Win32 Release"
# Name "Vct - Win32 Debug"
# Name "Vct - Win32 Unicode Debug"
# Name "Vct - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ApproveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BidDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Bmp.cpp
# End Source File
# Begin Source File

SOURCE=.\BnOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Canim.cpp
# End Source File
# Begin Source File

SOURCE=.\CAniTime.cpp
# End Source File
# Begin Source File

SOURCE=.\card.cpp
# End Source File
# Begin Source File

SOURCE=.\checksum.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfirmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSound.cpp
# End Source File
# Begin Source File

SOURCE=.\deck.cpp
# End Source File
# Begin Source File

SOURCE=.\GameApp.cpp
# End Source File
# Begin Source File

SOURCE=.\GameArea.cpp
# End Source File
# Begin Source File

SOURCE=.\GameBrd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\GameImg.cpp
# End Source File
# Begin Source File

SOURCE=.\GameInst.cpp
# End Source File
# Begin Source File

SOURCE=.\GameMIM.cpp
# End Source File
# Begin Source File

SOURCE=.\GamePce.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSlot.cpp
# End Source File
# Begin Source File

SOURCE=.\GameText.cpp
# End Source File
# Begin Source File

SOURCE=.\hands.cpp
# End Source File
# Begin Source File

SOURCE=.\HintDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\History.cpp
# End Source File
# Begin Source File

SOURCE=.\LightNdr.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBox.cpp
# End Source File
# Begin Source File

SOURCE=.\mt19937ar.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjComm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PassDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextMsgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Vct.cpp
# End Source File
# Begin Source File

SOURCE=.\Vct.def
# End Source File
# Begin Source File

SOURCE=.\Vct.odl
# End Source File
# Begin Source File

SOURCE=.\Vct.rc
# End Source File
# Begin Source File

SOURCE=.\VctAboutBox.cpp
# End Source File
# Begin Source File

SOURCE=.\VctApp.cpp
# End Source File
# Begin Source File

SOURCE=.\VctComm.cpp
# End Source File
# Begin Source File

SOURCE=.\VctCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\VctPpg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ApproveDlg.h
# End Source File
# Begin Source File

SOURCE=.\BidDlg.h
# End Source File
# Begin Source File

SOURCE=.\Bmp.h
# End Source File
# Begin Source File

SOURCE=.\BnOptDlg.h
# End Source File
# Begin Source File

SOURCE=.\Canim.h
# End Source File
# Begin Source File

SOURCE=.\CAniTime.h
# End Source File
# Begin Source File

SOURCE=.\card.h
# End Source File
# Begin Source File

SOURCE=.\checksum.h
# End Source File
# Begin Source File

SOURCE=.\ConfirmDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSound.h
# End Source File
# Begin Source File

SOURCE=.\deck.h
# End Source File
# Begin Source File

SOURCE=.\GameApp.h
# End Source File
# Begin Source File

SOURCE=.\GameArea.h
# End Source File
# Begin Source File

SOURCE=.\GameBrd.h
# End Source File
# Begin Source File

SOURCE=.\GameBtn.h
# End Source File
# Begin Source File

SOURCE=.\GameImg.h
# End Source File
# Begin Source File

SOURCE=.\GameInst.h
# End Source File
# Begin Source File

SOURCE=.\GameMIM.h
# End Source File
# Begin Source File

SOURCE=.\GamePce.h
# End Source File
# Begin Source File

SOURCE=.\GameSlot.h
# End Source File
# Begin Source File

SOURCE=.\GameText.h
# End Source File
# Begin Source File

SOURCE=.\hands.h
# End Source File
# Begin Source File

SOURCE=.\HintDlg.h
# End Source File
# Begin Source File

SOURCE=.\History.h
# End Source File
# Begin Source File

SOURCE=.\LightNdr.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\MsgBox.h
# End Source File
# Begin Source File

SOURCE=.\ObjComm.h
# End Source File
# Begin Source File

SOURCE=.\OptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\PassDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\str816.h
# End Source File
# Begin Source File

SOURCE=.\TextMsgDlg.h
# End Source File
# Begin Source File

SOURCE=.\Ubique.h
# End Source File
# Begin Source File

SOURCE=.\Vct.h
# End Source File
# Begin Source File

SOURCE=.\VctAboutBox.h
# End Source File
# Begin Source File

SOURCE=.\VctApp.h
# End Source File
# Begin Source File

SOURCE=.\VctComm.h
# End Source File
# Begin Source File

SOURCE=.\VctCtl.h
# End Source File
# Begin Source File

SOURCE=.\VctPpg.h
# End Source File
# Begin Source File

SOURCE=.\VpClbSet.h
# End Source File
# Begin Source File

SOURCE=.\VpOLE.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\2c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\2d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\2h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\2s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\3c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\3d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\3h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\3s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\4c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\4d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\4h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\4s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\5c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\5d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\5h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\5s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\6c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\6d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\6h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\6s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\7c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\7d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\7h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\7s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\8c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\8d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\8h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\8s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\9c.gif
# End Source File
# Begin Source File

SOURCE=.\Res\9d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\9h.gif
# End Source File
# Begin Source File

SOURCE=.\Res\9s.gif
# End Source File
# Begin Source File

SOURCE=.\Res\ac.gif
# End Source File
# Begin Source File

SOURCE=.\Res\ad.gif
# End Source File
# Begin Source File

SOURCE=.\Res\ah.gif
# End Source File
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\Res\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_d.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_l.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_l_off.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_r.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_u.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrow_u_off.gif
# End Source File
# Begin Source File

SOURCE=.\Res\as.gif
# End Source File
# Begin Source File

SOURCE=.\Res\b.gif
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\blank_card.gif
# End Source File
# Begin Source File

SOURCE=.\Res\blue_frame.gif
# End Source File
# Begin Source File

SOURCE=.\Res\blue_frame_hi.gif
# End Source File
# Begin Source File

SOURCE=.\board.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\cardtable.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\chair_empty.gif
# End Source File
# Begin Source File

SOURCE=.\Res\chair_hilite.gif
# End Source File
# Begin Source File

SOURCE=.\Res\dealer_off.GIF
# End Source File
# Begin Source File

SOURCE=.\Res\dealer_on.GIF
# End Source File
# Begin Source File

SOURCE=.\game_bg.gif
# End Source File
# Begin Source File

SOURCE=.\Res\GAMEGRP.gif
# End Source File
# Begin Source File

SOURCE=.\Res\jc.gif
# End Source File
# Begin Source File

SOURCE=.\Res\jd.gif
# End Source File
# Begin Source File

SOURCE=.\Res\jh.gif
# End Source File
# Begin Source File

SOURCE=.\Res\js.gif
# End Source File
# Begin Source File

SOURCE=.\Res\kc.gif
# End Source File
# Begin Source File

SOURCE=.\Res\kd.gif
# End Source File
# Begin Source File

SOURCE=.\Res\kh.gif
# End Source File
# Begin Source File

SOURCE=.\Res\ks.gif
# End Source File
# Begin Source File

SOURCE=.\meg_bg.gif
# End Source File
# Begin Source File

SOURCE=.\mega.bmp
# End Source File
# Begin Source File

SOURCE=.\megBoard.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\opt_btn_over.gif
# End Source File
# Begin Source File

SOURCE=.\Res\opt_btn_up.gif
# End Source File
# Begin Source File

SOURCE=.\Res\option_down.gif
# End Source File
# Begin Source File

SOURCE=.\Res\option_up.gif
# End Source File
# Begin Source File

SOURCE=.\Res\qc.gif
# End Source File
# Begin Source File

SOURCE=.\Res\qd.gif
# End Source File
# Begin Source File

SOURCE=.\Res\qh.gif
# End Source File
# Begin Source File

SOURCE=.\Res\qs.gif
# End Source File
# Begin Source File

SOURCE=.\Res\tc.gif
# End Source File
# Begin Source File

SOURCE=.\Res\td.gif
# End Source File
# Begin Source File

SOURCE=.\Res\th.gif
# End Source File
# Begin Source File

SOURCE=.\Res\ts.gif
# End Source File
# Begin Source File

SOURCE=.\Vct.ico
# End Source File
# Begin Source File

SOURCE=.\Res\VctCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\VctCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\yellow_frame.gif
# End Source File
# Begin Source File

SOURCE=.\Res\yellow_frame_hi.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\awcrap.WAV
# End Source File
# Begin Source File

SOURCE=.\Res\blindnil.wav
# End Source File
# Begin Source File

SOURCE=.\Res\playcard1.wav
# End Source File
# Begin Source File

SOURCE=.\Res\shuffle.wav
# End Source File
# Begin Source File

SOURCE=.\Res\yourturn.wav
# End Source File
# Begin Source File

SOURCE=.\Res\yturn.WAV
# End Source File
# End Target
# End Project
# Section Vct : {F08DF954-8592-11D1-B16A-00C0F0283628}
# 	2:21:DefaultSinkHeaderFile:slider.h
# 	2:16:DefaultSinkClass:CSlider
# End Section
# Section Vct : {F08DF952-8592-11D1-B16A-00C0F0283628}
# 	2:5:Class:CSlider
# 	2:10:HeaderFile:slider.h
# 	2:8:ImplFile:slider.cpp
# End Section
# Section Vct : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture1.h
# 	2:8:ImplFile:picture1.cpp
# End Section
