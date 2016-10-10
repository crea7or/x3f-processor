// Document modified at : Tuesday, March 13, 2007 04:18:09 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FUnknown.h: interface for the CEX3FUnknown class.
#pragma once

#include "CEX3FSection.h"

class CEX3FUnknown : public CEX3FSection
{
public:
	CEX3FUnknown();
	virtual ~CEX3FUnknown();

	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );


	DWORD Load( CEFile* lp_ceFile );

	virtual BOOL SaveSection();


};

typedef CEX3FUnknown* LPX3FUNKNOWN;
