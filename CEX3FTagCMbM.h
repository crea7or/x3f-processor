// Document modified at : Sunday, February 19, 2012 11:44:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTagCMbM.h: interface for the CEX3FTagCMbM class.
#pragma once

#include "CEX3FTag.h"

#pragma pack(push,1)
typedef struct TAG_M_DATA_ARRAY
{
	DWORD m_dwordValuesCount;
	DWORD m_dwordValuesNameOffset;
	DWORD m_dwordValuesIndex;
}TAG_M_DATA_ARRAY, *LPTAG_M_DATA_ARRAY;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct TAG_M_DATA
{
	DWORD m_dwordValuesType;
	DWORD m_dwordDimensions;
	DWORD m_dwordValuesOffset;
	TAG_M_DATA_ARRAY m_stValuesArray[];
}TAG_M_DATA, *LPTAG_M_DATA;
#pragma pack(pop)

//type, dim, offset-vales, howmany-values, pointed-by-offsetm, val-index, 

// Metrics section
class CEX3FTagCMbM : public CEX3FTag  
{
public:
	CEX3FTagCMbM();
	virtual ~CEX3FTagCMbM();

	LPBYTE GetTagValue();

	LPTAG_M_DATA GetTagMStructure()
	{
		return LPTAG_M_DATA( GetMemoryBuffer() + GetTagDataStructure()->m_dwordTagOffsetValue );
	}

	DWORD GetSizeOfValue();

	virtual void Enum( CString* lp_csExport );

};

typedef CEX3FTagCMbM* LPX3FTAGCMBM;
