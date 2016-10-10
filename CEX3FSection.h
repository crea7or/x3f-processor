// Document modified at : Sunday, February 19, 2012 5:49:49 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FSection.h: interface for the CEX3FSection class.
#pragma once

#include "CEListComboItem.h"

class CEX3FSection : public CEListComboItem
{
public:
	CEX3FSection();
	virtual ~CEX3FSection();
	// Copy constructor
	CEX3FSection& operator=(const CEX3FSection& l_ceObject );
	CEX3FSection( const CEX3FSection &l_ceObject );

	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );

	void DeleteMemory();
	DWORD LoadSection( CEFile* lp_ceFile );

	virtual DWORD Load( CEFile* lp_ceFile );

	virtual BOOL SaveSection() { return FALSE; };

	struct SECTION_DATA
	{
		//
		DWORD m_dwordEntryOffsetFromStart;
		DWORD m_dwordLengthOfEntry;
		DWORD m_dwordTypeOfEntry;
		//
		static DWORD GetDataSize()
		{
			return ( sizeof( CEX3FSection::SECTION_DATA ));
		};
	} m_stSectionData;



	virtual LPCTSTR GetTextSectionType()
	{
		m_csTextSectionType.Format("%c%c%c%c", LOBYTE(LOWORD( m_stSectionData.m_dwordTypeOfEntry )),  HIBYTE(LOWORD( m_stSectionData.m_dwordTypeOfEntry )),  LOBYTE( HIWORD( m_stSectionData.m_dwordTypeOfEntry )), HIBYTE( HIWORD( m_stSectionData.m_dwordTypeOfEntry )));
		return m_csTextSectionType;
	}
	LPCTSTR GetTextSectionLength()
	{
		m_csTextSectionLength.Format("%d bytes", m_stSectionData.m_dwordLengthOfEntry );
		return m_csTextSectionLength;
	}


	CString m_csTextSectionType;
	CString m_csTextSectionLength;

	LPBYTE mp_byteSectionData;
	DWORD m_dwordSectionDataSize;

};

typedef CEX3FSection* LPX3FSECTION;
