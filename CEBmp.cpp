// Document modified at : Tuesday, March 15, 2005 11:14:53 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEBmp.cpp: implementation of the CEBmp class.
#include "stdafx.h"
#include "CEBmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEBmp::CEBmp()
{
	memset( &m_stBitmapFileHeader, 0, sizeof( m_stBitmapFileHeader ));
	memset( &m_stBitmapInfoHeader, 0, sizeof( m_stBitmapInfoHeader ));
	mp_byteImage = NULL;
	m_dwordSize = 0;
	m_stBitmapFileHeader.bfType = 0x4d42;
	m_stBitmapFileHeader.bfOffBits = 0x36;
}

CEBmp::~CEBmp()
{
	DeleteMemory();
}

void CEBmp::DeleteMemory()
{
	if ( mp_byteImage != NULL )
	{
		CEHelper::FreeBuffer( mp_byteImage );
		mp_byteImage = NULL;
		m_dwordSize = 0;
	}
}


BOOL CEBmp::Save( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;

	CEFile l_ceFile;

	if ( l_ceFile.Open( lp_strName, CEFile::eModeReadWrite | CEFile::eModeCreate ))
	{
		m_stBitmapInfoHeader.biSize = sizeof( m_stBitmapInfoHeader );
		m_stBitmapFileHeader.bfSize = sizeof( m_stBitmapInfoHeader ) + sizeof( m_stBitmapFileHeader ) + m_dwordSize;

		l_ceFile.Write( &m_stBitmapFileHeader, sizeof( m_stBitmapFileHeader ));
		l_ceFile.Write( &m_stBitmapInfoHeader, sizeof( m_stBitmapInfoHeader ));
		l_ceFile.Write( mp_byteImage, m_dwordSize );
		l_ceFile.Close();
	}

	return l_boolResult;
}
