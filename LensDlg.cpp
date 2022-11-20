/************
 * MODULE:      LensDlg.cpp
 * PROJECT:     Lens (a demonstration program for my diploma)
 * DESCRIPTION: Implements the dialog methods
 * AUTHORS:     Mike Hesser
 * BUGS:        -
 * TO DO:		 -
 *************/

#include "stdafx.h"
#include "Lens.h"
#include "LensDlg.h"
#include "LensData.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLensDlg Dialogfeld

CLensDlg::CLensDlg(CWnd* pParent /*=NULL*/)
	: CSizingDialog(CLensDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLensDlg)
	m_F = 0.0f;
	m_N = 0.0f;
	m_Prec = 0.0f;
	m_IP = 0.0f;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bSelect = false;
	bMove = false;
	currentID = 0;

	AddHelp(IDS_POINT);
	AddHelp(IDS_FOCALPOINT);
	AddHelp(IDS_OPTICALAXIS);
	AddHelp(IDS_APERTURE);
	AddHelp(IDS_LENS);
	AddHelp(IDS_IMAGEPLANE);
	AddHelp(IDS_CONFCIRCLE);
	AddHelp(IDS_SHARPPLANE);
	AddHelp(IDS_DEPTHOFFIELD);
	AddHelp(IDS_QUIT);
	AddHelp(IDS_DATA);
	AddHelp(IDS_IMAGEPLANEF);
	AddHelp(IDS_GENERAL);
}

void CLensDlg::DoDataExchange(CDataExchange* pDX)
{
	CSizingDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_wndOK);

	//{{AFX_DATA_MAP(CLensDlg)
	DDX_Control(pDX, IDC_S8, m_S8);
	DDX_Control(pDX, IDC_SH, m_wndH);
	DDX_Control(pDX, IDC_STATIC7, m_S7);
	DDX_Control(pDX, IDC_IP, m_wndIP);
	DDX_Control(pDX, IDC_DATA, m_lbList);
	DDX_Control(pDX, IDC_STATIC6, m_S6);
	DDX_Control(pDX, IDC_PREC, m_wndPrec);
	DDX_Control(pDX, IDC_STATIC5, m_S5);
	DDX_Control(pDX, IDC_STATIC4, m_S4);
	DDX_Control(pDX, IDC_N, m_wndN);
	DDX_Control(pDX, IDC_F, m_wndF);
	DDX_Control(pDX, IDC_STATIC1, m_S1);
	DDX_Text(pDX, IDC_F, m_F);
	DDV_MinMaxFloat(pDX, m_F, 1.f, 500.f);
	DDX_Text(pDX, IDC_N, m_N);
	DDV_MinMaxFloat(pDX, m_N, 1.f, 100.f);
	DDX_Text(pDX, IDC_PREC, m_Prec);
	DDV_MinMaxFloat(pDX, m_Prec, 1.e-006f, 5.f);
	DDX_Text(pDX, IDC_IP, m_IP);
	DDV_MinMaxFloat(pDX, m_IP, 10.f, 100.f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLensDlg, CSizingDialog)
	//{{AFX_MSG_MAP(CLensDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_EN_KILLFOCUS(IDC_F, OnUpdate)
	ON_EN_KILLFOCUS(IDC_N, OnUpdate)
	ON_EN_KILLFOCUS(IDC_PREC, OnUpdate)
	ON_EN_KILLFOCUS(IDC_IP, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLensDlg Nachrichten-Handler

BOOL CLensDlg::OnInitDialog()
{
	m_F = lens.f;
	m_N = lens.n;
	m_IP = lens.Db;
	m_Prec = lens.c;

	CSizingDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	AddSzControl(m_wndOK, mdResize, mdRepos); 
	AddSzControl(m_wndIP, mdNone, mdRepos); 
	AddSzControl(m_S1, mdNone, mdRepos); 
	AddSzControl(m_S4, mdNone, mdRepos);
	AddSzControl(m_S5, mdNone, mdRepos);
	AddSzControl(m_S6, mdNone, mdRepos);
	AddSzControl(m_S7, mdNone, mdRepos);
	AddSzControl(m_S8, mdResize, mdRepos);
	AddSzControl(m_wndH, mdResize, mdRepos);
	AddSzControl(m_wndF, mdNone, mdRepos);
	AddSzControl(m_wndN, mdNone, mdRepos);
	AddSzControl(m_wndPrec, mdNone, mdRepos);
	AddSzControl(m_lbList, mdNone, mdRepos);

	return FALSE;
}

void CLensDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CSizingDialog::OnSysCommand(nID, lParam);
	}
}

void CLensDlg::OnPaint() 
{
	CString s;
	CPaintDC dc(this); // Gerätekontext für Zeichnen

	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		lens.Display(dc, this);

		m_lbList.ResetContent();

		s.Format("Z-Kreis (K):\t%g", lens.K);
		m_lbList.AddString(s);
		s.Format("Distanz (Do):\t%g", lens.ox);
		m_lbList.AddString(s);
		s.Format("S-Ebene (Ds):\t%g", lens.Ds);
		m_lbList.AddString(s);
		s.Format("Vorne (Dv):\t%g", lens.Dv);
		m_lbList.AddString(s);
		if (lens.Dh < 0.0f)
			s.Format("Hinten (Dh): \tunendlich");
		else
			s.Format("Hinten (Dh):\t%g", lens.Dh);

		m_lbList.AddString(s);

		m_lbList.UpdateWindow();
	
		
		CSizingDialog::OnPaint();
	}
}

HCURSOR CLensDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CLensDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint pnt;
	CString s;

	if (nHitTest == HTCLIENT)
	{
		GetCursorPos(&pnt);
		ScreenToClient(&pnt);

		if (bMove)
			SetCursor(AfxGetApp()->LoadCursor(IDC_HANDCLOSED));
		else
		{
			if (lens.Test(pnt.x, pnt.y))
			{
				SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
				bSelect = true;
			}
			else
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
				bSelect = false;
			}
		}
		return false;
	}
	return CSizingDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CLensDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString s;
	int nID;

	nID = GetHelpID(point);

	if (nFlags & MK_LBUTTON)
	{
		if (bSelect)
			bMove = true;

		if (bMove)
		{
			lens.SetObject(point.x, point.y);
			nID = IDS_POINT;
			Invalidate(false);
		}
	}
	else
		bMove = false;
	
	if (nID != currentID)
	{
		s.LoadString(nID);
		SetDlgItemText(IDC_SH, s);
		currentID = nID;
	}

	CSizingDialog::OnMouseMove(nFlags, point);
}

void CLensDlg::OnSize(UINT nType, int cx, int cy) 
{
	SetHelpRect(hlpGeneral, 0, 0, cx, cy);
	CSizingDialog::OnSize(nType, cx, cy);
}

void CLensDlg::OnUpdate() 
{
	UpdateData();

	lens.f = m_F;
	lens.n = m_N;
	lens.Db = m_IP;
	lens.c = m_Prec;

	Invalidate(false);	
}
