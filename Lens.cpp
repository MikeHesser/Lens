/************
 * MODULE:      Lens.cpp
 * PROJECT:     Lens (a demonstration program for my diploma)
 * DESCRIPTION: main class methods
 * AUTHORS:     Mike Hesser
 * BUGS:        -
 * TO DO:		 -
 *************/

#include "stdafx.h"
#include "Lens.h"
#include "LensDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLensApp

BEGIN_MESSAGE_MAP(CLensApp, CWinApp)
	//{{AFX_MSG_MAP(CLensApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLensApp Konstruktion

CLensApp::CLensApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CLensApp-Objekt

CLensApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLensApp Initialisierung

BOOL CLensApp::InitInstance()
{
	// Standardinitialisierung

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CLensDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
