; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CX3fDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "x3f.h"

ClassCount=4
Class1=CX3fApp
Class2=CX3fDlg

ResourceCount=5
Resource2=IDD_X3F_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDD_DIALOG_MATRIX
Class3=CEDialogApplyMatrix
Resource4=IDD_DIALOG_PREVIEW
Class4=CEPreviewDlg
Resource5=IDD_X3F_DIALOG (English (U.S.))

[CLS:CX3fApp]
Type=0
HeaderFile=x3f.h
ImplementationFile=x3f.cpp
Filter=N

[CLS:CX3fDlg]
Type=0
HeaderFile=x3fDlg.h
ImplementationFile=x3fDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECK_GAM



[DLG:IDD_X3F_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CX3fDlg

[DLG:IDD_X3F_DIALOG (English (U.S.))]
Type=1
Class=CX3fDlg
ControlCount=8
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_STATIC_LINK,static,1342308865
Control3=IDC_STATIC,static,1342177296
Control4=IDC_STATIC_UNP_T,static,1342308865
Control5=IDC_LIST_SECTIONS,SysListView32,1342242829
Control6=IDC_CHECK_GAM,button,1342242819
Control7=IDC_CHECK_MAT,button,1342242819
Control8=IDC_BUTTON2,button,1342242816

[DLG:IDD_DIALOG_MATRIX]
Type=1
Class=CEDialogApplyMatrix
ControlCount=34
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308864
Control3=IDC_STATIC,static,1342308864
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EDIT_RR,edit,1350631552
Control9=IDC_EDIT_RG,edit,1350631552
Control10=IDC_EDIT_RB,edit,1350631552
Control11=IDC_EDIT_GR,edit,1350631552
Control12=IDC_EDIT_GG,edit,1350631552
Control13=IDC_EDIT_GB,edit,1350631552
Control14=IDC_EDIT_BR,edit,1350631552
Control15=IDC_EDIT_BG,edit,1350631552
Control16=IDC_EDIT_BB,edit,1350631552
Control17=IDC_STATIC,static,1342177296
Control18=IDC_STATIC_UNPACK,static,1342308865
Control19=IDC_STATIC,static,1342308864
Control20=IDC_STATIC,static,1342308864
Control21=IDC_STATIC_HIGH_RED,static,1342308865
Control22=IDC_STATIC_LOW_RED,static,1342308865
Control23=IDC_STATIC_HIGH_GREEN,static,1342308865
Control24=IDC_STATIC_LOW_GREEN,static,1342308865
Control25=IDC_STATIC_HIGH_BLUE,static,1342308865
Control26=IDC_STATIC_LOW_BLUE,static,1342308865
Control27=IDC_STATIC,static,1342308864
Control28=IDC_STATIC_RED,static,1342308865
Control29=IDC_STATIC_GREEN,static,1342308865
Control30=IDC_STATIC_BLUE,static,1342308865
Control31=IDC_BUTTON_RT,button,1342242816
Control32=IDC_BUTTON_FLP,button,1476460544
Control33=IDC_BUTTON_FLPH,button,1476460544
Control34=IDC_BUTTON_DEFAULT,button,1342242816

[CLS:CEDialogApplyMatrix]
Type=0
HeaderFile=CEDialogApplyMatrix.h
ImplementationFile=CEDialogApplyMatrix.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK_GAMMA

[DLG:IDD_DIALOG_PREVIEW]
Type=1
Class=CEPreviewDlg
ControlCount=0

[CLS:CEPreviewDlg]
Type=0
HeaderFile=CEPreviewDlg.h
ImplementationFile=CEPreviewDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEPreviewDlg
VirtualFilter=dWC

