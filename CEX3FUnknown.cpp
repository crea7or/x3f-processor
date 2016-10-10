// Document modified at : Tuesday, March 13, 2007 04:18:09 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FUnknown.cpp: implementation of the CEX3FUnknown class.
#include "stdafx.h"
#include "CEX3FUnknown.h"

#include "CEX3F.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CEX3FUnknown::CEX3FUnknown()
{

}

CEX3FUnknown::~CEX3FUnknown()
{

}

BOOL CEX3FUnknown::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
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
			lp_ceListCtrlItem->pszText= "Unknown"; // Unpack3();
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

DWORD CEX3FUnknown::Load( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_FILE;

	DeleteMemory();
	mp_byteSectionData = CEHelper::AllocateBuffer( m_stSectionData.m_dwordLengthOfEntry );
	if ( lp_ceFile->Read( mp_byteSectionData, m_stSectionData.m_dwordLengthOfEntry ))
	{
		l_dwordResult = ERROR_OK;
	}
	else
	{		
		DeleteMemory();
	}

	return l_dwordResult;
}

BOOL CEX3FUnknown::SaveSection()
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