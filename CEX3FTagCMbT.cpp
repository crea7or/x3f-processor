// Document modified at : Tuesday, December 05, 2006 03:33:05 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbT.cpp: implementation of the CEX3FTagCMbT class.
#include "stdafx.h"
#include "CEX3FTagCMbT.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FTagCMbT::CEX3FTagCMbT()
{

}

CEX3FTagCMbT::~CEX3FTagCMbT()
{

}

LPCSTR CEX3FTagCMbT::GetTextValue()
{
	if ( GetMemoryBuffer() != NULL )
	{
		return LPCSTR( GetMemoryBuffer() + GetTagDataStructure()->m_dwordTagOffsetValue + 4 );
	}
	else
	{
		return NULL;
	}
}


void CEX3FTagCMbT::Enum( CString* lp_csExport )
{
	CEX3FTag::Enum( lp_csExport );
	*lp_csExport += " = ";
	if ( GetTextValue() != NULL )
	{
		*lp_csExport += GetTextValue();
	}
	*lp_csExport += "\r\n\r\n";
}
