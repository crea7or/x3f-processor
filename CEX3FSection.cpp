// Document modified at : Tuesday, March 13, 2007 04:18:39 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FSection.cpp: implementation of the CEX3FSection class.
#include "stdafx.h"
#include "CEX3FSection.h"
#include "CEX3F.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FSection::CEX3FSection()
{
	mp_byteSectionData = NULL;
	m_dwordSectionDataSize = 0;
	memset( &m_stSectionData, 0, sizeof( CEX3FSection::SECTION_DATA ));
}

CEX3FSection::~CEX3FSection()
{
	DeleteMemory();
}

void CEX3FSection::DeleteMemory()
{
	if ( mp_byteSectionData != NULL )
	{
		CEHelper::FreeBuffer( mp_byteSectionData );
		mp_byteSectionData = NULL;
		m_dwordSectionDataSize = 0;
	}
}




DWORD CEX3FSection::Load( CEFile* /*lp_ceFile*/ )
{
	return ERROR_NOT_IMPLEMENTED;
}


CEX3FSection& CEX3FSection::operator=(const CEX3FSection& l_ceObject )
{
	m_stSectionData = l_ceObject.m_stSectionData;
	return *this;
}

CEX3FSection::CEX3FSection( const CEX3FSection &l_ceObject )
{ 
	*this = l_ceObject;
}

DWORD CEX3FSection::LoadSection( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_FILE;

	DeleteMemory();

	if ( lp_ceFile->Read( &m_stSectionData, m_stSectionData.GetDataSize()))
	{
		l_dwordResult = ERROR_OK;
	}

	return l_dwordResult;
}


BOOL CEX3FSection::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
{
	BOOL l_boolResult = TRUE;
    if (lp_ceListCtrlItem->mask & LVIF_TEXT)
    {
		switch ( lp_ceListCtrlItem->iSubItem )
        {
		case 0:
			lp_ceListCtrlItem->pszText = LPTSTR( GetTextSectionType());
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