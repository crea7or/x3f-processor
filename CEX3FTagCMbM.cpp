// Document modified at : Sunday, February 19, 2012 11:45:24 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbM.cpp: implementation of the CEX3FTagCMbM class.
#include "stdafx.h"
#include "CEX3FTagCMbM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FTagCMbM::CEX3FTagCMbM()
{

}

CEX3FTagCMbM::~CEX3FTagCMbM()
{

}

LPBYTE CEX3FTagCMbM::GetTagValue()
{
	if ( GetMemoryBuffer() != NULL )
	{
		return LPBYTE( GetMemoryBuffer() + GetTagDataStructure()->m_dwordTagOffsetValue );
	}
	else
	{
		return NULL;
	}
}

DWORD CEX3FTagCMbM::GetSizeOfValue()
{
	DWORD l_dwordResult = 0;
	if ( GetTagMStructure() != NULL )
	{
		switch ( GetTagMStructure()->m_dwordValuesType )
		{
		case 0:
			l_dwordResult = sizeof( WORD );
			break;
		case 1:
			l_dwordResult = sizeof( DWORD );
			break;
		case 2:
			l_dwordResult = sizeof( DWORD );
			break;
		case 3:
			l_dwordResult = sizeof( FLOAT );
			break;
		case 6:
			l_dwordResult = sizeof( FLOAT );
			break;
		}

	}
	return l_dwordResult;
}


void CEX3FTagCMbM::Enum( CString* lp_csExport )
{
	CEX3FTag::Enum( lp_csExport );

	*lp_csExport += "Tag Value: ";

	CString l_csValue;

	if ( GetTagMStructure() != NULL )
	{
		switch ( GetTagMStructure()->m_dwordValuesType )
		{
		case 0:
			//l_dwordResult = sizeof( WORD );
			{
			LPWORD lp_wordVal = LPWORD( GetTagValue());
			l_csValue.Format("%d", *lp_wordVal );
			}
			break;
		case 1:
			{
			LPDWORD lp_wordVal = LPDWORD( GetTagValue());
			l_csValue.Format("%d", *lp_wordVal );
//			l_dwordResult = sizeof( DWORD );
			}
			break;
		case 2:
			{
			LPDWORD lp_wordVal = LPDWORD( GetTagValue());
			l_csValue.Format("%d", *lp_wordVal );
//			l_dwordResult = sizeof( DWORD );
			}
			break;
		case 3:
			{
			FLOAT* lp_wordVal = (FLOAT*)( GetTagValue());
			l_csValue.Format("%f", *lp_wordVal );
//			l_dwordResult = sizeof( FLOAT );
			}
			break;
		case 6:
			{
			FLOAT* lp_wordVal = (FLOAT*)( GetTagValue());
			l_csValue.Format("%f", *lp_wordVal );
//			l_dwordResult = sizeof( FLOAT );
			}
			break;
		}		
	}

	*lp_csExport += l_csValue;

	*lp_csExport += "\r\n";




/*	
	LPCSTR lp_strValue;
	LPDWORD lp_dwordOffset = LPDWORD( &GetTagPStructure()->m_dwordTagFirstOffsetOfName );
	for ( DWORD l_dwordCnt = 0; l_dwordCnt < ( GetTagPStructure()->m_dwordTagPointersCount * 2 ); l_dwordCnt+= 2 )
	{
		lp_strValue = LPSTR( GetMemoryBuffer() + GetTagPStructure()->m_dwordTagFirstPointerOffset );
		lp_strValue += lp_dwordOffset[ l_dwordCnt ];
		*lp_csExport += lp_strValue;
		*lp_csExport += " = ";
		lp_strValue = LPSTR( GetMemoryBuffer() + GetTagPStructure()->m_dwordTagFirstPointerOffset );
		lp_strValue += lp_dwordOffset[ l_dwordCnt  + 1 ];
		*lp_csExport += lp_strValue;
		*lp_csExport += "\r\n";
	}
*/
	*lp_csExport += "\r\n";
}
