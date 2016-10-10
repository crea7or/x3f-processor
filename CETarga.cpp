// Document modified at : Tuesday, March 15, 2005 11:14:53 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CETarga.cpp: implementation of the CETarga class.
#include "stdafx.h"
#include "CETarga.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CETarga::CETarga()
{
	memset( &m_stHeader, 0, sizeof( m_stHeader ));
	mp_byteImage = NULL;
	m_dwordSize = 0;
}

CETarga::~CETarga()
{
	DeleteMemory();
}

void CETarga::DeleteMemory()
{
	if ( mp_byteImage != NULL )
	{
		CEHelper::FreeBuffer( mp_byteImage );
		mp_byteImage = NULL;
		m_dwordSize = 0;
	}
}

BOOL CETarga::Save( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;

	CEFile l_ceFile;

	if ( l_ceFile.Open( lp_strName, CEFile::eModeReadWrite | CEFile::eModeCreate ))
	{
		l_ceFile.Write( &m_stHeader, sizeof( m_stHeader ));
		l_ceFile.Write( mp_byteImage, m_dwordSize );
		l_ceFile.Close();
	}

	return l_boolResult;
}
