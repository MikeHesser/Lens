// LenseDlg.h : Header-Datei
//

#ifndef LENSEDLG_H
#define LENSEDLG_H

#include "CSizingDialog.h"
#include <afxtempl.h>
#include "LensData.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CLensDlg : public CSizingDialog
{
	bool bSelect, bMove;

// Konstruktion
public:
	CLensDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CLensDlg)
	enum { IDD = IDD_LENS_DIALOG };
	CButton	m_S8;
	CStatic	m_wndH;
	CStatic	m_S7;
	CEdit	m_wndIP;
	CListBox	m_lbList;
	CStatic	m_S6;
	CEdit	m_wndPrec;
	CStatic	m_S5;
	CStatic	m_S4;
	CEdit	m_wndN;
	CEdit	m_wndF;
	CScrollBar	m_slb_n;
	CEdit	m_sle_n;
	CButton	m_S1;
	CStatic	m_ID;
	float	m_F;
	float	m_N;
	float	m_Prec;
	float	m_IP;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CLensDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;
	CLens lens;
	CButton m_wndOK;
	int currentID;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CLensDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif
