; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLensDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Lense.h"

ClassCount=4
Class1=CLenseApp
Class2=CLensDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LENSE_DIALOG
Resource4=IDD_LENS_DIALOG (Englisch (USA))
Class4=CCanvas
Resource5=IDD_ABOUTBOX (Englisch (USA))

[CLS:CLenseApp]
Type=0
HeaderFile=Lense.h
ImplementationFile=Lense.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=LenseDlg.h
ImplementationFile=LenseDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_LENSE_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CLensDlg

[DLG:IDD_ABOUTBOX (Englisch (USA))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889

[CLS:CCanvas]
Type=0
HeaderFile=Canvas.h
ImplementationFile=Canvas.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CCanvas

[DLG:IDD_LENS_DIALOG (Englisch (USA))]
Type=1
Class=CLensDlg
ControlCount=13
Control1=IDOK,button,1342193665
Control2=IDC_STATIC1,button,1342177287
Control3=IDC_STATIC4,static,1342308354
Control4=IDC_F,edit,1350631552
Control5=IDC_STATIC5,static,1342308354
Control6=IDC_N,edit,1350631552
Control7=IDC_STATIC6,static,1342308354
Control8=IDC_PREC,edit,1350631552
Control9=IDC_DATA,listbox,1352728961
Control10=IDC_STATIC7,static,1342308354
Control11=IDC_IP,edit,1350631552
Control12=IDC_SH,static,1342308352
Control13=IDC_S8,button,1342177287

[CLS:CLensDlg]
Type=0
HeaderFile=lensdlg.h
ImplementationFile=lensdlg.cpp
BaseClass=CSizingDialog
LastObject=CLensDlg
Filter=D
VirtualFilter=dWC

