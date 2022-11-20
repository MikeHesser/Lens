/************
 * MODULE:      Help.cpp
 * PROJECT:     Lens (a demonstration program for my diploma)
 * DESCRIPTION: Implements the helper methods
 * AUTHORS:     Mike Hesser
 * BUGS:        -
 * TO DO:		 -
 *************/

#include "Help.h"
#include "afxtempl.h"

// array of help items
CArray<tHelp, tHelp> aHelp;

void SetHelpRect(int no, int l, int t, int r, int b)
{
	ASSERT(no >= 0 && no < _hlpEnd);

	aHelp[no].rc.SetRect(l, t, r, b);
}

void SetHelpRect(CWnd *pWnd, int nID, int nCID)
{
	ASSERT(pWnd);
	
	CWnd *pCtrl;
	CRect rc;

	pCtrl = pWnd->GetDlgItem(nCID);
	if (pCtrl)
	{
		pCtrl->GetWindowRect(rc);
		pWnd->ScreenToClient(rc);
		aHelp[nID].rc.SetRect(rc.left, rc.top, rc.right, rc.bottom);
	}
}

void AddHelp(int nID)
{
	tHelp h;

	h.nID = nID;
	h.rc.SetRect(0, 0, 0, 0);

	aHelp.Add(h);
}

int GetHelpID(CPoint & point)
{
	int i;

	for (i = 0; i < aHelp.GetSize(); i++)
	{
		if (aHelp[i].rc.PtInRect(point))
		return aHelp[i].nID;
	}

	return -1;
}

