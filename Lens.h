// Lens.h : Haupt-Header-Datei f�r die Anwendung Lens
//

#if !defined(AFX_Lens_H__9CC07651_9397_11D2_8A9C_A9DBCABB344B__INCLUDED_)
#define AFX_Lens_H__9CC07651_9397_11D2_8A9C_A9DBCABB344B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CLensApp:
// Siehe Lens.cpp f�r die Implementierung dieser Klasse
//

class CLensApp : public CWinApp
{
public:
	CLensApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CLensApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CLensApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_Lens_H__9CC07651_9397_11D2_8A9C_A9DBCABB344B__INCLUDED_)
