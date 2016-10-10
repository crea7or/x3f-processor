// Document modified at : Tuesday, December 05, 2006 03:11:23 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbT.h: interface for the CEX3FTagCMbT class.
#pragma once

#include "CEX3FTag.h"

//Text Section
class CEX3FTagCMbT : public CEX3FTag  
{
public:
	CEX3FTagCMbT();
	virtual ~CEX3FTagCMbT();

	LPCSTR GetTextValue();

	virtual void Enum( CString* lp_csExport );

};

typedef CEX3FTagCMbT* LPX3FTAGCMBT;
