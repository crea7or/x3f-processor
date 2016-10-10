// Document modified at : Monday, July 09, 2007 11:24:23 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FProperties.h: interface for the CEX3FProperties class.
#pragma once

#include "CEX3FProperty.h"
#include "CEX3FSection.h"

class CEX3FProperties : public CEX3FSection
{
public:
	CEX3FProperties();
	virtual ~CEX3FProperties();

	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );

	DWORD Load( CEFile* lp_ceFile );

	virtual BOOL SaveSection( );


	struct PROPERTY_DATA
	{
		DWORD m_dwordSectionIdentifier; // Should be "SECp" . 0x70434553
		DWORD m_dwordPropertyListFormatVersion; //  version Should be 2.0 for now.
		DWORD m_dwordNumberOfEntries; // Number of property entries
		DWORD m_dwordCharacterFormat; //  for all entries in this table. 0 = CHAR16 Unicode.
		DWORD m_dwordRESERVED;
		DWORD m_dwordTotalLength;//  of name/value data in characters.
	} m_stData;

	CEPtrAutoArray < LPX3FPROPERTY > m_ceProperties;

};

typedef CEX3FProperties* LPX3FPROPERTIES;
