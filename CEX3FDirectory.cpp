// Document modified at : Sunday, February 19, 2012 3:19:29 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FDirectory.cpp: implementation of the CEX3FDirectory class.
#include "stdafx.h"
#include "CEX3FDirectory.h"
#include "CEX3F.h"

#include "CEX3FProperties.h"
#include "CEX3FImage.h"
#include "CEX3FUnknown.h"
#include "CEX3FTags.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FDirectory::CEX3FDirectory()
{
	memset( &m_stData, 0, sizeof( CEX3FDirectory::DATA ));
}

CEX3FDirectory::~CEX3FDirectory()
{

}

DWORD CEX3FDirectory::Parse( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_OK;

	LPX3FSECTION lp_ceSection;
	CEX3FSection m_ceFirstSection;
	DWORD64 l_dword64Offset;

	if ( ! lp_ceFile->Read( &m_stData, m_stData.GetDataSize()))
	{
		return l_dwordResult;
	}

	if ( m_stData.m_dwordSectionIdentifier != 0x64434553 || m_stData.m_dwordNumberOfDirectoryEntries < 1 )
	{
		return ERROR_MATCH;
	}

	for ( DWORD l_dwordEntries = 0; l_dwordEntries < m_stData.m_dwordNumberOfDirectoryEntries; l_dwordEntries++ )
	{

		l_dwordResult = m_ceFirstSection.LoadSection( lp_ceFile );
		//
		l_dword64Offset = lp_ceFile->GetPosition64();
		//

		if ( l_dwordResult == ERROR_OK )
		{
			switch( m_ceFirstSection.m_stSectionData.m_dwordTypeOfEntry )
			{
			case 0x504F5250:  // PROP
				lp_ceSection = new CEX3FProperties;				
				break;
			case 0x47414D49: // IMAG
			case 0x32414D49: // IMA2
				lp_ceSection = new CEX3FImage;
				break;
			case 0x464d4143: // CAMF
				lp_ceSection = new CEX3FTags;
				break;
			default:
				lp_ceSection = new CEX3FUnknown;
				break;
			};
			
			*lp_ceSection = m_ceFirstSection;

			lp_ceFile->SetPosition64( m_ceFirstSection.m_stSectionData.m_dwordEntryOffsetFromStart );

			l_dwordResult = lp_ceSection->Load( lp_ceFile );

			if ( l_dwordResult != ERROR_OK )
			{
				delete lp_ceSection;
				break;
			}
			else
			{
				m_ceSections.Add( lp_ceSection );
			}
		}

		lp_ceFile->SetPosition64( l_dword64Offset );

	}

	return l_dwordResult;
}

BOOL CEX3FDirectory::SavePlainImage( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordImage;
	LPX3FIMAGE lp_ceImage;

	for ( DWORD l_dwordCnt =0; l_dwordCnt < m_ceSections.GetSize(); l_dwordCnt++ )
	{
		l_dwordImage = m_ceSections.GetAt( l_dwordCnt )->m_stSectionData.m_dwordTypeOfEntry;
		if ( l_dwordImage == 0x47414D49 || l_dwordImage == 0x32414D49 )
		{
			lp_ceImage = LPX3FIMAGE( m_ceSections.GetAt( l_dwordCnt ));
		
			//l_dwordImage = lp_ceImage->m_stData.m_dwordDataFormat ;
			
			if ( lp_ceImage->m_stData.m_dwordDataFormat == 18 )
			{
				lp_ceImage->Unpack();
				if ( lp_strName != NULL )
				{
//					l_boolResult = lp_ceImage->SaveTiff( lp_strName );
					//l_boolResult = lp_ceImage->SaveBmp( lp_strName );
				}
				break;
			}
			
			
			
			/*
			if ( lp_ceImage->m_stData.m_dwordDataFormat == 11 )
			{
				lp_ceImage->Unpack();
				l_boolResult = lp_ceImage->SaveBmp( lp_strName );
				break;
			}
			*/
			
			

		}
	}

	return l_boolResult;
}
