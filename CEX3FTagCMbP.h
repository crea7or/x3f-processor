// Document modified at : Tuesday, December 05, 2006 05:47:52 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbP.h: interface for the CEX3FTagCMbP class.
#pragma once

#include "CEX3FTag.h"

#pragma pack(push,1)
typedef struct TAG_P_DATA_ARRAY
{
	DWORD m_dwordAddOffsetOfName;
	DWORD m_dwordAddOffsetOfValue;
}TAG_P_DATA_ARRAY, *LPTAG_P_DATA_ARRAY;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct TAG_P_DATA
{
	DWORD m_dwordPointersCount;
	DWORD m_dwordOffsetOfValues;
	TAG_P_DATA_ARRAY m_stValuesArray[];
}TAG_P_DATA, *LPTAG_P_DATA;
#pragma pack(pop)


// Pointers section
class CEX3FTagCMbP : public CEX3FTag  
{
public:
	CEX3FTagCMbP();
	virtual ~CEX3FTagCMbP();

	LPTAG_P_DATA GetTagPStructure()
	{
		return LPTAG_P_DATA( GetMemoryBuffer() + GetTagDataStructure()->m_dwordTagOffsetValue );
	}

	virtual void Enum( CString* lp_csExport );

};

typedef CEX3FTagCMbP* LPX3FTAGCMBP;
