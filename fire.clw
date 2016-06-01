; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFireView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fire.h"
LastPage=0

ClassCount=7
Class1=CFireApp
Class2=CFireDoc
Class3=CFireView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_PORTSCAN_FORM (English (U.S.))
Resource2=IDD_FIRE_FORM
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CAddRuleDlg
Resource4=IDR_MENU1
Resource5=IDD_ADDRULE
Class7=CPortScanDlg
Resource6=IDR_MAINFRAME (English (U.S.))
Resource7=IDD_FIRE_FORM (English (U.S.))
Resource8=IDD_ABOUTBOX (English (U.S.))
Resource9=IDR_MENU1 (English (U.S.))
Resource10=IDD_ADDRULE (English (U.S.))

[CLS:CFireApp]
Type=0
HeaderFile=fire.h
ImplementationFile=fire.cpp
Filter=N
LastObject=CFireApp

[CLS:CFireDoc]
Type=0
HeaderFile=fireDoc.h
ImplementationFile=fireDoc.cpp
Filter=N

[CLS:CFireView]
Type=0
HeaderFile=fireView.h
ImplementationFile=fireView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_START


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_BLOCKPING




[CLS:CAboutDlg]
Type=0
HeaderFile=fire.cpp
ImplementationFile=fire.cpp
Filter=D
LastObject=CAboutDlg

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_HELP
Command9=ID_HELP_FINDER
Command10=ID_CONTEXT_HELP
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_FIRE_FORM]
Type=1
Class=CFireView
ControlCount=9
Control1=IDC_ADDRULE,button,1342242816
Control2=IDC_VIEWRULES,button,1342242816
Control3=IDC_LIST_RESULT,SysListView32,1350631681
Control4=IDC_BLOCKALL,button,1073807360
Control5=IDC_BLOCKPING,button,1073807360
Control6=IDC_START,button,1073807360
Control7=IDC_ALLOWALL,button,1073807360
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_ADDRULE]
Type=1
Class=CAddRuleDlg
ControlCount=20
Control1=IDC_SADD,edit,1350631552
Control2=IDC_DADD,edit,1350631552
Control3=IDC_SPORT,edit,1350631552
Control4=IDC_DPORT,edit,1350631552
Control5=IDC_COMBO1,combobox,1344340226
Control6=IDC_COMBO2,combobox,1344340226
Control7=IDC_ADD,button,1342242816
Control8=IDC_ADDSAVE,button,1342242816
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352

[CLS:CAddRuleDlg]
Type=0
HeaderFile=AddRuleDlg.h
ImplementationFile=AddRuleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddRuleDlg
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=CMainFrame
Command1=ID_APP_ABOUT
Command2=ID_POPUP_MINIMIZE
Command3=ID_POPUP_MAXIMIZE
Command4=ID_POPUP_EXIT
CommandCount=4

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_Start
Command2=ID_STOP
Command3=ID_BLOCKALL
Command4=ID_ALLOWALL
Command5=ID_BLOCKPING
Command6=ID_APP_ABOUT
Command7=ID_ICON
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EXIT
Command2=ID_TOOLS_PORTSCANNER
Command3=ID_HELP_FINDER
Command4=ID_APP_ABOUT
CommandCount=4

[CLS:CPortScanDlg]
Type=0
HeaderFile=PortScanDlg.h
ImplementationFile=PortScanDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPortScanDlg
VirtualFilter=dWC

[DLG:IDD_FIRE_FORM (English (U.S.))]
Type=1
Class=CFireView
ControlCount=9
Control1=IDC_ADDRULE,button,1342242816
Control2=IDC_VIEWRULES,button,1342242816
Control3=IDC_LIST_RESULT,SysListView32,1350631681
Control4=IDC_BLOCKALL,button,1073807360
Control5=IDC_BLOCKPING,button,1073807360
Control6=IDC_START,button,1073807360
Control7=IDC_ALLOWALL,button,1073807360
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_Start
Command2=ID_STOP
Command3=ID_BLOCKALL
Command4=ID_ALLOWALL
Command5=ID_BLOCKPING
Command6=ID_APP_ABOUT
Command7=ID_ICON
CommandCount=7

[MNU:IDR_MENU1 (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_ABOUT
Command2=ID_POPUP_MINIMIZE
Command3=ID_POPUP_MAXIMIZE
Command4=ID_POPUP_EXIT
CommandCount=4

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_EXIT
CommandCount=1

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_HELP
Command9=ID_HELP_FINDER
Command10=ID_CONTEXT_HELP
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_ADDRULE (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_SADD,edit,1350631552
Control2=IDC_DADD,edit,1350631552
Control3=IDC_SPORT,edit,1350631552
Control4=IDC_DPORT,edit,1350631552
Control5=IDC_COMBO1,combobox,1344340226
Control6=IDC_COMBO2,combobox,1344340226
Control7=IDC_ADDSAVE,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352

[DLG:IDD_PORTSCAN_FORM (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_IP_ADDRESS,SysIPAddress32,1342242816
Control2=IDC_RADIO_SINGLE,button,1342308361
Control3=IDC_EDIT_SINGLE_PORT,edit,1350631552
Control4=IDC_RADIO_RANGE,button,1342177289
Control5=IDC_EDIT_SINGLE_PORT_FROM,edit,1350631552
Control6=IDC_EDIT_SINGLE_PORT_TO,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_ATTEMPTS,edit,1350631552
Control9=IDC_BUTTON_SCAN,button,1342242817
Control10=IDC_BUTTON_STOP,button,1342242816
Control11=IDC_LIST_RESULT,SysListView32,1350631689
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC_IP,static,1342308352
Control14=IDC_STATIC,static,1342181390
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_PROGRESS,msctls_progress32,1350565888
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATUS_BAR,static,1342181376

