// Document modified at : Tuesday, July 13, 2004 06:57:08 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEFileError.cpp: implementation of the CEFileError class.
#include "stdafx.h"
#include "CEFileError.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEFileError::CEFileError( LPCTSTR lp_strFile, BOOL l_boolShow ) : CEError( 0xFFFFFFFF, FALSE )
{
	CString l_csError, l_csTemp, l_csFile;
	if ( lp_strFile == NULL )
	{
		l_csFile = _T("Unnamed");
	}
	else
	{
		l_csFile = lp_strFile;
	}
	l_csTemp ="%s , %s ";
	l_csError.Format( l_csTemp, l_csFile, m_csError );
	m_csError = l_csError;
	if ( l_boolShow )
	{
		AfxMessageBox( l_csError , MB_ICONSTOP );
	}
}

CEFileError::~CEFileError()
{
}
