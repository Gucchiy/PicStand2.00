; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPicStandWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "picstand.h"
LastPage=0

ClassCount=10
Class1=CCustomButton
Class2=CPicStandApp
Class3=CPicStandDlg
Class4=CPicStandWnd
Class5=CPictureFileDlg
Class6=CStatusWnd
Class7=CStayButton
Class8=CVersionInfoDlg
Class9=CWideSettingDlg

ResourceCount=3
Resource1=IDM_CONTEXT_MENU
Resource2=IDD_VERSION_INFO
Class10=CCustomizeWnd
Resource3=IDD_CUSTOMIZE_WND

[CLS:CCustomButton]
Type=0
BaseClass=CWnd
HeaderFile=CustomButton.h
ImplementationFile=CustomButton.cpp
LastObject=IDM_CUSTOMIZEWND

[CLS:CPicStandApp]
Type=0
BaseClass=CWinApp
HeaderFile=PicStand.h
ImplementationFile=PicStand.cpp

[CLS:CPicStandDlg]
Type=0
BaseClass=CDialog
HeaderFile=PicStandDlg.h
ImplementationFile=PicStandDlg.cpp

[CLS:CPicStandWnd]
Type=0
BaseClass=CWnd
HeaderFile=PicStandWnd.h
ImplementationFile=PicStandWnd.cpp
Filter=W
VirtualFilter=WC
LastObject=IDM_STAY

[CLS:CPictureFileDlg]
Type=0
BaseClass=CFileDialog
HeaderFile=PictureFileDlg.h
ImplementationFile=PictureFileDlg.cpp

[CLS:CStatusWnd]
Type=0
BaseClass=CWnd
HeaderFile=StatusWnd.h
ImplementationFile=StatusWnd.cpp

[CLS:CStayButton]
Type=0
BaseClass=CWnd
HeaderFile=StayButton.h
ImplementationFile=StayButton.cpp

[CLS:CVersionInfoDlg]
Type=0
BaseClass=CDialog
HeaderFile=VersionInfoDlg.h
ImplementationFile=VersionInfoDlg.cpp

[CLS:CWideSettingDlg]
Type=0
BaseClass=CDialog
HeaderFile=WideSettingDlg.h
ImplementationFile=WideSettingDlg.cpp
LastObject=IDC_SLIDER_WIDE

[DLG:IDD_PICSTAND_DIALOG]
Type=1
Class=CPicStandDlg

[DLG:IDD_VERSION_INFO]
Type=1
Class=CVersionInfoDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177283

[MNU:IDM_CONTEXT_MENU]
Type=1
Class=?
Command1=IDM_TOPMOST
Command2=IDM_BOTTOMMOST
Command3=IDM_CASH_NEXT
Command4=IDM_CASH_PREV
Command5=IDM_CASH_DELETE
Command6=IDM_DISP_CASH
Command7=IDM_STAY
Command8=IDM_BARSTYLE
Command9=IDM_MUL2
Command10=IDM_MUL1
Command11=IDM_DIV2
Command12=IDM_SIZESETTING
Command13=IDM_CUSTOMIZEWND
Command14=IDM_FIXSIZE
Command15=IDM_FIXSIZE2
Command16=IDM_REG_STARTUP
Command17=IDM_VERSIONDLG
Command18=IDM_HELP
Command19=IDM_SUPPORT
Command20=IDM_CLOSE
CommandCount=20

[DLG:IDD_CUSTOMIZE_WND]
Type=1
Class=CCustomizeWnd
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SCROLLBAR_RED,scrollbar,1342242816
Control4=IDC_SCROLLBAR_GREEN,scrollbar,1342242816
Control5=IDC_SCROLLBAR_BLUE,scrollbar,1342242816
Control6=IDC_SCROLLBAR_WIDTH,scrollbar,1342242816
Control7=IDC_DEFAULT,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_EDIT_RED,edit,1350568064
Control11=IDC_EDIT_GREEN,edit,1350568064
Control12=IDC_EDIT_BLUE,edit,1350568064
Control13=IDC_EDIT_WIDTH,edit,1350568064
Control14=IDC_STATIC,static,1342181902
Control15=IDC_STATIC,static,1342181902
Control16=IDC_STATIC,static,1342181902

[CLS:CCustomizeWnd]
Type=0
HeaderFile=CustomizeWnd.h
ImplementationFile=CustomizeWnd.cpp
BaseClass=CDialog
Filter=D
LastObject=CCustomizeWnd
VirtualFilter=dWC

