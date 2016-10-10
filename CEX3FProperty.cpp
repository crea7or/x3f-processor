// Document modified at : Monday, December 04, 2006 06:28:55 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FProperty.cpp: implementation of the CEX3FProperty class.
#include "stdafx.h"
#include "CEX3FProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FProperty::CEX3FProperty()
{
}

CEX3FProperty::~CEX3FProperty()
{
}

void CEX3FProperty::SetName( LPWSTR lp_wstrName )
{
	Convert( lp_wstrName, &m_csName );
}

void CEX3FProperty::SetValue( LPWSTR lp_wstrValue )
{
	Convert( lp_wstrValue, &m_csValue );
}

void CEX3FProperty::Convert( LPWSTR lp_wstrValue, CString* lp_mfcString )
{
	DWORD l_dwordSize = wcslen( lp_wstrValue );
	//l_dwordSize++;

	LPSTR lp_strString = lp_mfcString->GetBufferSetLength( l_dwordSize );

	WideCharToMultiByte( CP_ACP, 0, lp_wstrValue , l_dwordSize , lp_strString , l_dwordSize, NULL, NULL );

	lp_mfcString->ReleaseBuffer( -1 );
}