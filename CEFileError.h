// Document modified at : Sunday, February 02, 2003 03:49:07 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEFileError.h: interface for the CEFileError class.
#pragma once

#include "CEError.h"

class CEFileError : public CEError  
{
public:
	CEFileError( LPCTSTR lp_strFile = NULL, BOOL l_boolShow = TRUE );
	virtual ~CEFileError();
};
