// Document modified at : Monday, February 20, 2012 2:01:42 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTags.cpp: implementation of the CEX3FTags class.
#include "stdafx.h"
#include "CEX3FTags.h"
#include "CEX3F.h"
#include "CEX3FTagCMbM.h"
#include "CEX3FTagCMbT.h"
#include "CEX3FTagCMbP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FTags::CEX3FTags()
{
	memset( &m_stTagsInfo, 0, sizeof( CEX3FTags::TAGS_INFO ));

}

CEX3FTags::~CEX3FTags()
{

}


BOOL CEX3FTags::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
{
	BOOL l_boolResult = TRUE;
    if (lp_ceListCtrlItem->mask & LVIF_TEXT)
    {
		switch ( lp_ceListCtrlItem->iSubItem )
        {
		case 0:
			lp_ceListCtrlItem->pszText = LPTSTR( GetTextSectionType());
			break;
		case 1:
			lp_ceListCtrlItem->pszText= "Cam data"; // Unpack3();
			break;
			break;
		case 2:
			lp_ceListCtrlItem->pszText = LPTSTR( GetTextSectionLength());
			break;
        }
    }
	if ( lp_ceListCtrlItem->mask & LVIF_IMAGE )
	{
		//     lp_ceListCtrlItem->iImage = GetImage();
	}
	return l_boolResult;
}

DWORD CEX3FTags::Load( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_FILE;
	
	DWORD l_dwordDataSize, l_dwordCryptSbox, l_dwordCryptLCG;
	
	LPBYTE lp_byteTagMemory;
	LPDWORD lp_dwordSourceDwordData, lp_dwordEndDwordData;
	LPX3FTAG lp_ceTagContainer;
	
	m_ceTagValues.SelfRemoveAll();
	
	if ( lp_ceFile->Read( &m_stTagsInfo,  sizeof( CEX3FTags::TAGS_INFO )))
	{		
		DeleteMemory();
		l_dwordDataSize = ( m_stSectionData.m_dwordLengthOfEntry - sizeof( CEX3FTags::TAGS_INFO ));
		mp_byteSectionData = LPBYTE( malloc( l_dwordDataSize ));
		m_dwordSectionDataSize = l_dwordDataSize;
		if ( lp_ceFile->Read( mp_byteSectionData, l_dwordDataSize ))
		{
			if ( m_stTagsInfo.m_dwordTypeOfInfoData == 2 )
			{
				// Old sd9 - sd14 format
				l_dwordCryptLCG = m_stTagsInfo.m_dwordCryptKey;
				
				// LCG obfuscation + s'box
				for ( DWORD l_dwordCnt = 0; l_dwordCnt < l_dwordDataSize; l_dwordCnt++ )
				{
					l_dwordCryptLCG = (( l_dwordCryptLCG * 1597 ) + 51749 ) % 244944;
					l_dwordCryptSbox = DWORD( l_dwordCryptLCG * INT64( 301593171 ) >> 24 );
					mp_byteSectionData[ l_dwordCnt ] ^= (((( l_dwordCryptLCG << 8 ) - l_dwordCryptSbox ) >> 1 ) + l_dwordCryptSbox ) >> 17;
				}
				
				lp_dwordSourceDwordData = LPDWORD( mp_byteSectionData );
				lp_dwordEndDwordData = lp_dwordSourceDwordData + l_dwordDataSize;
				
				while( lp_dwordSourceDwordData < lp_dwordEndDwordData )
				{
					lp_ceTagContainer = NULL;
					switch( lp_dwordSourceDwordData[ 0 ])
					{
					case 0x54624D43: // CMbT - Text Tag Value
						lp_ceTagContainer = new CEX3FTagCMbT();
						break;
					case 0x4D624D43: // CMbM - Metrix
						lp_ceTagContainer = new CEX3FTagCMbM();
						break;
					case 0x50624D43: // CMbP - Pointers
						lp_ceTagContainer = new CEX3FTagCMbP();
						break;				
					}
					
					if ( lp_ceTagContainer != NULL )
					{
						lp_byteTagMemory = lp_ceTagContainer->AllocateMemory( lp_dwordSourceDwordData[ 2 ] );
						if ( lp_byteTagMemory != NULL)
						{
							memcpy( lp_byteTagMemory , LPBYTE( lp_dwordSourceDwordData ), lp_dwordSourceDwordData[ 2 ]);
							m_ceTagValues.Add( lp_ceTagContainer );
							lp_dwordSourceDwordData = LPDWORD( LPBYTE( lp_dwordSourceDwordData) + lp_dwordSourceDwordData[ 2 ] );
						}
					}
					else
					{
						break;
					}
				}
				/*
				CString l_csEx;
				for (  l_dwordCryptLCG = 0; l_dwordCryptLCG < m_ceTagValues.GetSize();  l_dwordCryptLCG++ )
				{
				m_ceTagValues.GetAt( l_dwordCryptLCG )->Enum( &l_csEx );
				}
				
				  CEFile l_ceFFF;
				  l_ceFFF.Open( "c:\\tags.txt", CEFile::eModeCreate | CEFile::eModeReadWrite );
				  l_ceFFF.Write( l_csEx.GetBuffer( 1 ), l_csEx.GetLength() );
				  l_ceFFF.Close();
				*/
				l_dwordResult = ERROR_OK;
			}
			else if ( m_stTagsInfo.m_dwordTypeOfInfoData == 4 )
			{
				// Old dp1 - ...
				//AfxMessageBox("4");
				
			}
		}
		else
		{		
			DeleteMemory();
		}
	}
	return l_dwordResult;
}


BOOL CEX3FTags::SaveSection()
{
	BOOL l_boolResult = TRUE;
	
	CString l_csEx;
	for (  DWORD l_dwordCryptLCG = 0; l_dwordCryptLCG < m_ceTagValues.GetSize();  l_dwordCryptLCG++ )
	{
		m_ceTagValues.GetAt( l_dwordCryptLCG )->Enum( &l_csEx );
	}

	CFileDialog l_dlgFileSave( FALSE, "Section", NULL, NULL, "All Files (*.*)|*.*||", NULL);
	if ( l_dlgFileSave.DoModal() == IDOK )
	{
		CEFile l_ceFile;
		if ( l_ceFile.Open( l_dlgFileSave.GetPathName(), CEFile::eModeReadWrite | CEFile::eModeCreate ))
		{
	//		l_ceFile.Write( mp_byteSectionData, m_dwordSectionDataSize );
			l_ceFile.Write( l_csEx.GetBuffer( 1 ), l_csEx.GetLength() );
			l_ceFile.Close();
		}		
	}
	
	return l_boolResult;
}