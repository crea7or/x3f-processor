// Document modified at : Sunday, February 19, 2012 11:44:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FTag.h: interface for the CEX3FTag class.
#pragma once

#include "CEMemoryBuffer.h"

#pragma pack(push,1)
typedef struct TAG_DATA
{
	DWORD m_dwordTagIdentifier;
	DWORD m_dwordTagIdentifierVersion;
	DWORD m_dwordTagSize;
	DWORD m_dwordTagOffsetName;
	DWORD m_dwordTagOffsetValue;
}TAG_DATA, *LPTAG_DATA;
#pragma pack(pop)

class CEX3FTag : public CEMemoryBuffer
{
public:
	CEX3FTag();
	virtual ~CEX3FTag();

	LPTAG_DATA GetTagDataStructure()
	{
		return LPTAG_DATA( GetMemoryBuffer());
	}

	LPCSTR GetTagName();

	virtual void Enum( CString* lp_csExport );

};

typedef CEX3FTag* LPX3FTAG;
