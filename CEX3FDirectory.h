// Document modified at : Monday, November 20, 2006 06:17:13 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FDirectory.h: interface for the CEX3FDirectory class.
#pragma once

#include "CEX3FSection.h"

class CEX3FDirectory  
{
public:
	CEX3FDirectory();
	virtual ~CEX3FDirectory();

	DWORD Parse( CEFile* lp_ceFile );

	struct DATA
	{
		//
		DWORD m_dwordSectionIdentifier; // Contains "SECd". 0x64434553
		DWORD m_dwordSectionVersion; // Section version. Should be 2.0 for now.
		DWORD m_dwordNumberOfDirectoryEntries;
		//
		static DWORD GetDataSize()
		{
			return ( sizeof( DWORD ) * 3 );
		};
	} m_stData;

	BOOL SavePlainImage( LPCTSTR lp_strName );

	CEPtrAutoArray < LPX3FSECTION > m_ceSections;

};

typedef CEX3FDirectory* LPX3FDIRECTORY;
