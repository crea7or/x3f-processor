# Microsoft Developer Studio Project File - Name="x3f" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=x3f - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "x3f.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "x3f.mak" CFG="x3f - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "x3f - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "x3f - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "x3f - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W4 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "x3f - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "x3f - Win32 Release"
# Name "x3f - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\x3f.cpp
# End Source File
# Begin Source File

SOURCE=.\x3f.rc
# End Source File
# Begin Source File

SOURCE=.\x3fDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\x3f.h
# End Source File
# Begin Source File

SOURCE=.\x3fDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\handy.cur
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\x3f.ico
# End Source File
# Begin Source File

SOURCE=.\res\x3f.rc2
# End Source File
# End Group
# Begin Group "X3F Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEX3F.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3F.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FDirectory.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FDirectory.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FImage.cpp

!IF  "$(CFG)" == "x3f - Win32 Release"

# ADD CPP /FAcs

!ELSEIF  "$(CFG)" == "x3f - Win32 Debug"

# ADD CPP /FAs

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CEX3FImage.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FProperties.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FProperty.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FSection.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FSection.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FTag.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FTag.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbM.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbM.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbP.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbP.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbT.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FTagCMbT.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FTags.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FTags.h
# End Source File
# Begin Source File

SOURCE=.\CEX3FUnknown.cpp
# End Source File
# Begin Source File

SOURCE=.\CEX3FUnknown.h
# End Source File
# End Group
# Begin Group "Helper Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEError.cpp
# End Source File
# Begin Source File

SOURCE=.\CEError.h
# End Source File
# Begin Source File

SOURCE=.\CEFile.cpp
# End Source File
# Begin Source File

SOURCE=.\CEFile.h
# End Source File
# Begin Source File

SOURCE=.\CEFileError.cpp
# End Source File
# Begin Source File

SOURCE=.\CEFileError.h
# End Source File
# Begin Source File

SOURCE=.\CEHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\CEHelper.h
# End Source File
# Begin Source File

SOURCE=.\CEMemoryBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CEMemoryBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CEMMtimer.cpp
# End Source File
# Begin Source File

SOURCE=.\CEMMtimer.h
# End Source File
# Begin Source File

SOURCE=.\CEPtrArray.h
# End Source File
# Begin Source File

SOURCE=.\CEPtrAutoArray.h
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\CEBmp.h
# End Source File
# Begin Source File

SOURCE=.\CETarga.cpp
# End Source File
# Begin Source File

SOURCE=.\CETarga.h
# End Source File
# Begin Source File

SOURCE=.\CETiff.cpp
# End Source File
# Begin Source File

SOURCE=.\CETiff.h
# End Source File
# End Group
# Begin Group "Interface Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEListComboItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CEListComboItem.h
# End Source File
# Begin Source File

SOURCE=.\CEListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CEListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CEObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CEObject.h
# End Source File
# Begin Source File

SOURCE=.\CHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\CHyperLink.h
# End Source File
# End Group
# Begin Group "Dialogs Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CEDialogApplyMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\CEDialogApplyMatrix.h
# End Source File
# Begin Source File

SOURCE=.\CEPreviewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CEPreviewDlg.h
# End Source File
# End Group
# End Target
# End Project
