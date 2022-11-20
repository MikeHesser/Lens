
#ifndef HELP_H
#define HELP_H

#include "stdafx.h"

enum
{
	hlpPoint,
	hlpFocalPoint,
	hlpOpticalAxis,
	hlpAperture,
	hlpLens,
	hlpImagePlane,
	hlpCircleOfConfusion,
	hlpSharpPlane,
	hlpDepthOfField,
	hlpQuit,
	hlpData,
	hlpImagePlaneF,
	hlpGeneral,
	_hlpEnd
};

typedef struct
{
	CRect rc;
	int nID;
} tHelp;

void SetHelpRect(int, int, int, int, int);
void SetHelpRect(CWnd *pWnd, int, int);
void AddHelp(int);
int GetHelpID(CPoint &);

#endif