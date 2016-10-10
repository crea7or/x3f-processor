// Document modified at : Tuesday, March 13, 2007 04:20:42 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FProperties.cpp: implementation of the CEX3FProperties class.
#include "stdafx.h"
#include "CEX3FProperties.h"
#include "CEX3F.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FProperties::CEX3FProperties()
{
	memset( &m_stData, 0, sizeof( CEX3FProperties::PROPERTY_DATA ));

}

CEX3FProperties::~CEX3FProperties()
{

}


BOOL CEX3FProperties::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
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
			lp_ceListCtrlItem->pszText= "Properties"; // Unpack3();
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

DWORD CEX3FProperties::Load( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_FILE;

	m_ceProperties.SelfRemoveAll();

	LPX3FPROPERTY lp_stProperty;

	LPDWORD lp_dwordOffsets;
	LPBYTE lp_byteSource;

	if ( lp_ceFile->Read( &m_stData, sizeof( CEX3FProperties::PROPERTY_DATA )))
	{
		DeleteMemory();
		mp_byteSectionData = CEHelper::AllocateBuffer( m_stSectionData.m_dwordLengthOfEntry - sizeof( CEX3FProperties::PROPERTY_DATA ));

		m_dwordSectionDataSize = m_stSectionData.m_dwordLengthOfEntry - sizeof( CEX3FProperties::PROPERTY_DATA );


		if ( lp_ceFile->Read( mp_byteSectionData, m_stSectionData.m_dwordLengthOfEntry - sizeof( CEX3FProperties::PROPERTY_DATA )))
		{
			l_dwordResult = ERROR_OK;
			lp_byteSource = mp_byteSectionData + ( 8 * m_stData.m_dwordNumberOfEntries );
			lp_dwordOffsets = LPDWORD( mp_byteSectionData );

			for ( DWORD l_dwordCnt = 0; l_dwordCnt < ( m_stData.m_dwordNumberOfEntries * 2 ); l_dwordCnt+= 2 )
			{
				lp_stProperty = new CEX3FProperty;
				lp_stProperty->SetName( LPWSTR( lp_byteSource + ( lp_dwordOffsets[ l_dwordCnt ] * 2 )));
				lp_stProperty->SetValue( LPWSTR( lp_byteSource + ( lp_dwordOffsets[ l_dwordCnt + 1 ] * 2 )));
				m_ceProperties.Add( lp_stProperty );
			}
		}
		else
		{
			DeleteMemory();
		}
	}
	return l_dwordResult;
}

BOOL CEX3FProperties::SaveSection()
{
	BOOL l_boolResult = TRUE;
	
	CFileDialog l_dlgFileSave( FALSE, "Section", NULL, NULL, "All Files (*.*)|*.*||", NULL);
	if ( l_dlgFileSave.DoModal() == IDOK )
	{
		CEFile l_ceFile;
		if ( l_ceFile.Open( l_dlgFileSave.GetPathName(), CEFile::eModeReadWrite | CEFile::eModeCreate ))
		{
			l_ceFile.Write( mp_byteSectionData, m_dwordSectionDataSize );
			l_ceFile.Close();
		}		
	}
	
	return l_boolResult;
}