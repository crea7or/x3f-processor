// Document modified at : Tuesday, March 13, 2007 04:35:16 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3F.cpp: implementation of the CEX3F class.
#include "stdafx.h"
#include "CEX3F.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3F::CEX3F()
{
	memset( &m_stHeader, 0, sizeof( CEX3F::HEADER ));
}

CEX3F::~CEX3F()
{

}

DWORD CEX3F::Load( LPCTSTR lp_strFile )
{
	DWORD l_dwordResult = ERROR_UNKNOWN;

	m_ceDirectory.m_ceSections.SelfRemoveAll();

	memset( &m_stHeader, 0, sizeof( m_stHeader ));

	CEFile l_ceFile;

	if ( l_ceFile.Open(  lp_strFile, CEFile::eModeRead ))
	{
		if ( l_ceFile.Read( &m_stHeader, sizeof( m_stHeader )))
		{
			if ( m_stHeader.m_dwordFileTypeIdentifier == 0x62564f46 ) //"FOVb"
			{
				if ( m_stHeader.m_dwordFileFormatVersion < 0x0202 )
				{
					// Seek back to fit an 2.0 verion header
					l_ceFile.Seek( - ( 32*6 ), CEFile::eFileCurrent, NULL );
				}
				l_dwordResult = ParseImage( &l_ceFile );
			}
			else
			{
				l_dwordResult = ERROR_MATCH;
			}
		}
		else
		{
			l_dwordResult = ERROR_FILE;
		}

		l_ceFile.Close();
	}
	else
	{
		l_dwordResult = ERROR_FILE;
	}

	return l_dwordResult;
}

DWORD CEX3F::ParseImage( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_UNKNOWN;
	DWORD64 l_dword64CurrentOffset, l_dword64FileSize, l_dword64NewOffset;

	l_dword64FileSize = lp_ceFile->GetLength();
	lp_ceFile->GetPosition( &l_dword64CurrentOffset );

	l_dword64NewOffset = l_dword64FileSize - 76;

	lp_ceFile->SetPosition64( l_dword64NewOffset );

	l_dwordResult = m_ceDirectory.Parse( lp_ceFile );

	return l_dwordResult;
}


BOOL CEX3F::FillListCtrl( CEListCtrl* lp_ctrlSectionList )
{
	BOOL l_boolResult = FALSE;

	lp_ctrlSectionList->DeleteAllItems();

	DWORD l_dwordSize = m_ceDirectory.m_ceSections.GetSize();
	for ( DWORD l_dwordCnt =0; l_dwordCnt < l_dwordSize; l_dwordCnt++)
	{
		lp_ctrlSectionList->CtrlAddItem( m_ceDirectory.m_ceSections.GetAt( l_dwordCnt ));
	}

	return l_boolResult;
}
