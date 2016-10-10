// Document modified at : Sunday, February 19, 2012 11:44:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTag.cpp: implementation of the CEX3FTag class.

#include "stdafx.h"
#include "CEX3FTag.h"
#include "CEX3F.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEX3FTag::CEX3FTag()
{
}

CEX3FTag::~CEX3FTag()
{

}

LPCSTR CEX3FTag::GetTagName()
{
	if ( GetMemoryBuffer() != NULL )
	{
		return LPCSTR( GetMemoryBuffer() + GetTagDataStructure()->m_dwordTagOffsetName );
	}
	else
	{
		return NULL;
	}
}



void CEX3FTag::Enum( CString* lp_csExport )
{
	*lp_csExport += "\r\n\r\n" ;
	*lp_csExport += "Tag: ";
	*lp_csExport += CHAR( LOBYTE( LOWORD( GetTagDataStructure()->m_dwordTagIdentifier )));
	*lp_csExport += CHAR( HIBYTE( LOWORD( GetTagDataStructure()->m_dwordTagIdentifier )));
	*lp_csExport += CHAR( LOBYTE( HIWORD( GetTagDataStructure()->m_dwordTagIdentifier )));
	*lp_csExport += CHAR( HIBYTE( HIWORD( GetTagDataStructure()->m_dwordTagIdentifier )));
	*lp_csExport += "\r\n";
	*lp_csExport += "Tag name: ";
	*lp_csExport += GetTagName();
	*lp_csExport += "\r\n";
//	*lp_csExport += "Tag Value: ";
//	*lp_csExport += GetTagValue();


}