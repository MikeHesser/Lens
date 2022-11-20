/************
* MODULE:      LensData.h
* PROJECT:		Lens (Demonstrationsprogramm zur Diplomarbeit
*					"Effiziente Berechnung der Tiefenschaerfe zur realistischen Darstellung
*					 von Bildern"
* DESCRIPTION: definition file
* AUTHORS:     Mike Hesser
*************/

#ifndef LENSDATA_H
#define LENSDATA_H

#include "stdafx.h"
#include "Help.h"

class CLens
{
	CDC *pDC;
	int cox, coy, xL, yL, pr;

public:
	float K, c, Ds, xscale, yscale;
	float	n, Db, f, Kl, ox, oy, idx, idy, Dv, Dh;
	float cyiplane, ixscale, iyscale;

	CLens();
	void Calculate();
	void Display(CDC &, CWnd *);
	bool Test(int, int);
	void SetObject(int, int);

private:
	void Line(float, float, float, float);
};

#endif