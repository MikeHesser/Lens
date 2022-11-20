/************
* MODULE:		LensData.cpp
* PROJECT:		Lens (Demonstrationsprogramm zur Diplomarbeit
*					"Effiziente Berechnung der Tiefenschaerfe zur realistischen Darstellung
*					 von Bildern"
* DESCRIPTION:	Kernmodul, Zeige Linsensystem und berechne Linsendaten
* AUTHORS:		Mike Hesser
* BUGS:			-
* TO DO:			-
*************/

#include "LensData.h"
#include <math.h>

/*************
* DESCRIPTION:	Konstruktor, setze default Werte
* INPUT:			-
* OUTPUT:		-
*************/
CLens::CLens()
{
	f = 50.0f;			// Brennweite
	n = 1.2f;			// Blendenzahl
	Db = 60.0f;			// Abstand zur Bildebene
	c = 1.0f;			// Maximaler Durchmesser des Zerstreuungskreises
	ox = 300.0f;		// Horizontale Distanz Objekt <-> Linse
	oy = 0.0f;			// Vertikale Distanz Objekt <-> optische Achse
	cyiplane = 24.0f;	// Hoehe der Bildebene

	pDC = NULL;

	pr = 3;				// Radius des Objektpunktes (auf dem Bildschirm)
	xscale = 1.0;		// Skalierungsfaktoren fuer Szenenraum
	yscale = 1.0;
	iyscale = 4.0;		// Skalierungsfaktoren fuer Bildraum
	ixscale = 2.0;

	Calculate();
}

/*************
* DESCRIPTION: Aktualisierung der Daten
* INPUT:			-
* OUTPUT:		-
*************/
void CLens::Calculate()
{
	Kl = f/n;										// Tatsaechlicher Linsendurchmesser
	idx = 1/(1/f - 1/ox);						// Position des projizierten Punktes
	idy = -idx*oy/ox;
	K = ((float)fabs(idx - Db)*f)/(n*idx);	// Groesse des Zerstreuungskreises
	Ds = 1/(1/f - 1/Db);							// Entfernung der Schärfeebene
			
	Dv = f*Db/(Db + n*c - f);					// Entfernung zum Beginn des Schärfebereichs
	Dh = f*Db/(Db - n*c - f);					// Entfernung zum Ende des Schärfebereichs
}

void CLens::Line(float x1, float y1, float x2, float y2)
{
	pDC->MoveTo(int(xscale*x1), int(yscale*y1));
	pDC->LineTo(int(xscale*x2), int(yscale*y2));
}

/*************
* DESCRIPTION:	Zeichne Linsensystem
* INPUT:			dc		Display Context
*					pWnd	Zeiger auf Fenster
* OUTPUT:		-
*************/
void CLens::Display(CDC & dc, CWnd *pWnd)
{
	CBitmap *pOldBitmap, bitmap;
	CDC dcMem, *pDrawDC;
	CRect rc, rc2;
	CRgn rgn;
	int cntx, cnty, cxPlane, xP, h, cxLens2, cyLens2, wP, Kl2, xx, yy, r;
	float d;
	POINT poly[5];

	CPen penGrid(PS_SOLID, 0, RGB(140,140,140));
	CPen penLight(PS_SOLID, 0, RGB(134,135,146));
	CPen penLens(PS_SOLID, 1, RGB(0,0,0));
	CPen penBlack(PS_SOLID, 0, RGB(0,0,0));
	CBrush bshLight(RGB(134,135,146));
	CBrush bshLens(RGB(255,255,255));
	CBrush bshObject(RGB(255,255,255));

	pWnd->GetClientRect(rc);
	rc.bottom -= 150;
		
	cxPlane = int(0.2*rc.Width());

	// double buffering
	if (dcMem.CreateCompatibleDC(&dc))
	{
		if (bitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height()))
		{
			pDrawDC = &dcMem;

			// offset origin more because bitmap is just piece of the whole drawing
			dcMem.OffsetViewportOrg(-rc.left, -rc.top);
			pOldBitmap = dcMem.SelectObject(&bitmap);
			dcMem.SetBrushOrg(rc.left % 8, rc.top % 8);

			// might as well clip to the same rectangle
			dcMem.IntersectClipRect(rc);
		}
	}

	pDC = pDrawDC;

	rc.right -= cxPlane + 5;
	rgn.CreateRectRgnIndirect(rc);
	pDrawDC->SelectObject(rgn);
	pDrawDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), RGB(150,150,150));

	Calculate();

	xL = int(2*rc.Width()/2.6f);		// x-Position der Linse
	yL = rc.Height() >> 1;				// y-Position der Linse
	xP = xL + int(ixscale*Db);			// x-Position der Bildebene
	cyLens2 = int(0.5*f*iyscale);		// Halbe Hoehe der Linse
	cxLens2 = cyLens2/8;					// Halbe Breite der Linse
	wP = 2;

	cox = int(xL - ox*xscale);			// Bildschirmkoordinate des Objektpunktes
	coy = int(yL - oy*yscale);
	Kl2 = int(0.5*iyscale*Kl);			// Halbe Hoehe des tatsaechliche Linsendurchmesser
	cnty = int(Db*oy/fabs(ox)) + yL;

	// Zeichne den Bereich der Tiefenschaerfe
	xx = int(Dh);
	if (xx < 0)
		xx = xL;
	h = int(fabs(xx - Dv));
	if (h < 1)
		h = 1;
	pDrawDC->FillSolidRect(int(xL - xx), rc.top, h, rc.Height(), RGB(170,170,170));
	SetHelpRect(hlpDepthOfField, int(xL - xx), rc.top, int(xL - xx + h), rc.Height());

	// Linse
	pDC->SelectObject(bshLens);
	pDC->SelectObject(penLens);

	rgn.SetRectRgn(CRect(xL + 1, yL - cyLens2 - 2, xL + cxLens2+2, yL + cyLens2 + 2));
	pDrawDC->SelectObject(rgn);
	pDrawDC->Ellipse(xL - cxLens2 - 150, yL - cyLens2 - 100, xL + cxLens2+2, yL + cyLens2 + 100);
	rgn.SetRectRgn(CRect(xL - cxLens2, yL - cyLens2, xL, yL + cyLens2));
	pDrawDC->SelectObject(rgn);
	pDrawDC->Ellipse(xL - cxLens2, yL - cyLens2 - 100, xL + cxLens2 + 150, yL + cyLens2+100);

	SetHelpRect(hlpLens, xL - cxLens2, yL - cyLens2, xL + cxLens2, yL + cyLens2);

	rgn.SetRectRgn(rc);
	pDrawDC->SelectObject(rgn);

	pDC->SelectObject(penLight);
	pDC->SelectObject(bshLight);

	// Oberere Bereich des Lichtkegels
	xx = int(idx);
	yy = int(idy);
	if (idx < Db)
	{
		xx = int(Db);
		yy = int(-Db*(Kl2 - idy)/idx + Kl2);
	}

	poly[0].x = cox; poly[0].y = coy;
	poly[1].x = xL;  poly[1].y = yL - Kl2;
	poly[2].x = xL + int(xx*ixscale); poly[2].y = yL - yy;

	// Unterer Bereich des Lichtkegels
	xx = int(idx);
	yy = int(idy);
	if (idx < Db)
	{
		xx = int(Db);
		yy = int(-Db*(-Kl2 - idy)/idx - Kl2);
	}

	poly[3].x = xL + int(xx*ixscale); poly[3].y = yL - yy;
	poly[4].x = xL; poly[4].y = yL + Kl2;

	pDC->Polygon(poly, 5);

	// Raster
	pDC->SelectObject(penGrid);
	d = 20;
	while (xL - d > 0)
	{
		Line(float(xL - d), 0.0f, float(xL - d), float(rc.Height()));
		d += 10;
	}
	d = 0;
	while (yL - d > 0)
	{
		Line(0.0f, float(yL - d), float(xL - 20), float(yL - d));
		Line(0.0f, float(yL + d), float(xL - 20), float(yL + d));
		d += 10;
	}

	pDC->SelectObject(penBlack);

	// Brennpunkt
	h = xL + int(f*ixscale);
	pDrawDC->MoveTo(h, yL - 5);
	pDrawDC->LineTo(h, yL + 5);
	SetHelpRect(hlpFocalPoint, h - 2, yL - 5, h + 2, yL + 5);

	// X-Y Ansicht
	pDrawDC->SetBkMode(TRANSPARENT);
	pDrawDC->TextOut(rc.left + 10, rc.top + 10, "X-Y Ansicht");

	// Optische Achse
	pDrawDC->MoveTo(rc.left, yL); pDrawDC->LineTo(rc.right, yL);
	SetHelpRect(hlpOpticalAxis, rc.left, yL - 2, rc.right, yL + 2);

	// Schaerfeebene
	Line(float(xL - Ds), 0.0f, float(xL - Ds), float(rc.Height()));
	SetHelpRect(hlpSharpPlane, int(xL - Ds - 2), 0, int(xL - Ds + 2), rc.Height());

	// Bildebene
	pDrawDC->FillSolidRect(xP, yL - int(0.5*cyiplane*iyscale), wP, int(cyiplane*iyscale), RGB(0,0,0));
	SetHelpRect(hlpImagePlane, xP - 1, yL - int(0.5*cyiplane*iyscale), xP + wP + 1, yL + int(cyiplane*iyscale));

	// Blende
	pDrawDC->FillSolidRect(xL, yL - cyLens2, 2, int(cyLens2 - Kl2), RGB(0,0,0));
	pDrawDC->FillSolidRect(xL, yL + cyLens2, 2, int(-cyLens2 + Kl2), RGB(0,0,0));
	SetHelpRect(hlpAperture, xL, yL - cyLens2, xL + 2, yL + cyLens2);

	// Objektpunkt
	pDC->SelectObject(penBlack);
	pDC->SelectObject(bshObject);
	pDrawDC->Ellipse(cox - pr, coy - pr, cox + pr, coy + pr);
	SetHelpRect(hlpPoint, cox - pr, coy - pr, cox + pr, coy + pr);

	rc2.SetRect(rc.right, rc.top, rc.right + cxPlane, rc.bottom);
	rgn.SetRectRgn(rc2);
	pDrawDC->SelectObject(rgn);
	pDrawDC->FillSolidRect(rc2.left, rc2.top, 5, rc2.Height(), RGB(0,0,0));

	rgn.SetRectRgn(rc.right + 5, rc.top, rc.right + cxPlane, rc.bottom);
	pDrawDC->SelectObject(rgn);

	// Bildebene in der Vorderansicht
	pDrawDC->FillSolidRect(rc2.left, rc2.top, rc2.Width(), rc2.Height(), RGB(150,150,150));
	SetHelpRect(hlpImagePlaneF, rc2.left, rc2.top, rc2.right, rc2.bottom);

	pDrawDC->MoveTo(rc2.left, rc2.top + rc2.Height() >> 1);
	pDrawDC->LineTo(rc2.right, rc2.top + rc2.Height() >> 1);
	cntx = rc2.left + (rc2.Width() >> 1);
	r = int(iyscale*0.5*K);
	if (r < 1)
		r = 1;
	// Zerstreuungskreis
	pDrawDC->Ellipse(cntx - r, cnty - r, cntx + r, cnty + r);
	SetHelpRect(hlpCircleOfConfusion, cntx - r, cnty - r, cntx + r, cnty + r);

	// Z-Y Ansicht
	pDrawDC->SetBkMode(TRANSPARENT);
	pDrawDC->TextOut(rc2.left + 10,rc2.top + 10, "Bildebene");

	rc.right += cxPlane;
	rgn.SetRectRgn(rc);
	pDrawDC->SelectObject(rgn);
	if (pDrawDC != &dc)
	{
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0, 0);
		dc.SetMapMode(MM_TEXT);
		dcMem.SetViewportOrg(0, 0);
		dcMem.SetWindowOrg(0, 0);
		dcMem.SetMapMode(MM_TEXT);
		dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
		dcMem.SelectObject(pOldBitmap);
	}
}

/*************
* DESCRIPTION:	Setze Position des Objektpunktes
* INPUT:			x,y Koordinaten des Punktes
* OUTPUT:		-
*************/
void CLens::SetObject(int x, int y)
{
	ox = (xL - x)/xscale;
	oy = (yL - y)/yscale;

	if (ox <= f)
		ox = f + 1;
}

/*************
* DESCRIPTION:	Test ob der Bilschirmpunkt innerhalb des Objektpunktes ist
* INPUT:			x,y  Koord. des zu testenden Punktes
* OUTPUT:		true -> innerhalb sonst ausserhalb
*************/
bool CLens::Test(int x, int y)
{
	return PtInRect(CRect(cox - pr, coy - pr, cox + pr, coy + pr), CPoint(x, y)) != 0; 
}