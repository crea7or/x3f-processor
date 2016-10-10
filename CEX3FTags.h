// Document modified at : Tuesday, March 13, 2007 04:18:09 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTags.h: interface for the CEX3FTags class.
#pragma once

#include "CEX3FSection.h"
#include "CEX3FTag.h"

class CEX3FTags : public CEX3FSection  
{
public:
	CEX3FTags();
	virtual ~CEX3FTags();

	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );

	virtual BOOL SaveSection();

	struct TAGS_INFO
	{		
		DWORD m_dwordSectionIdentifier; // Section identifier Should be "SECc" . 0x63434553
		DWORD m_dwordSectionFormatVersion; // Image format version Should be 2.0 for now.
		DWORD m_dwordTypeOfInfoData;
		DWORD m_dwordReserved;
		DWORD m_dwordInfoType; // FCEb
		DWORD m_dwordInfoTypeVersion;
		DWORD m_dwordCryptKey;
	} m_stTagsInfo;

	DWORD Load( CEFile* lp_ceFile );
	
	CEPtrAutoArray < LPX3FTAG > m_ceTagValues;

};

typedef CEX3FTags* LPX3FTAGS;
