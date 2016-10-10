// Document modified at : Tuesday, December 05, 2006 05:47:52 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbP.cpp: implementation of the CEX3FTagCMbP class.
#include "stdafx.h"
#include "CEX3FTagCMbP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FTagCMbP::CEX3FTagCMbP()
{

}

CEX3FTagCMbP::~CEX3FTagCMbP()
{

}


void CEX3FTagCMbP::Enum( CString* lp_csExport )
{
	CEX3FTag::Enum( lp_csExport );
	*lp_csExport += "\r\n";

	LPCSTR lp_strValue;
	lp_strValue = LPSTR( GetMemoryBuffer() + GetTagPStructure()->m_dwordOffsetOfValues );
	for ( DWORD l_dwordCnt = 0; l_dwordCnt < GetTagPStructure()->m_dwordPointersCount; l_dwordCnt++ )
	{
		*lp_csExport += LPCSTR( lp_strValue + GetTagPStructure()->m_stValuesArray[ l_dwordCnt ].m_dwordAddOffsetOfName );
		*lp_csExport += " = ";
		*lp_csExport += LPCSTR( lp_strValue + GetTagPStructure()->m_stValuesArray[ l_dwordCnt ].m_dwordAddOffsetOfValue );
		*lp_csExport += "\r\n";
	}
	*lp_csExport += "\r\n";
}

