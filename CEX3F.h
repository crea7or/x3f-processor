// Document modified at : Tuesday, March 13, 2007 03:35:54 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3F.h: interface for the CEX3F class.
#pragma once

#include "CEPtrAutoArray.h"
#include "CEX3FDirectory.h"
#include "CEMemoryBuffer.h"

	enum X3F_ERRORS
	{
		ERROR_OK = 0,
		ERROR_FILE = 1,
		ERROR_MATCH = 3,
		ERROR_UNKNOWN = 255,
		ERROR_NOT_IMPLEMENTED = 65535
	};


class CEX3F  
{
public:
	CEX3F();
	virtual ~CEX3F();

	DWORD Load( LPCTSTR lp_strFile );
	DWORD ParseImage( CEFile* lp_ceFile );

	DWORD LoadHeader();

	BOOL FillListCtrl( CEListCtrl* lp_ctrlSectionList );

	struct HEADER
	{
		DWORD m_dwordFileTypeIdentifier; // Contains "FOVb". Used to verify that this is an FOVb file.
		DWORD m_dwordFileFormatVersion; // Version of the file. Should be 2.2 right now.
		BYTE m_byteUniqueIdentifer[16]; // Guaranteed unique to each image. Formed from camera serial number / OUI, timestamp, and highspeed timer register. Can be used to identify images even if they are renamed. No, it's not UUID-compatible.
		DWORD m_dwordMarkBits; // Can be used to denote that images are marked into one or more subsets. File interface functions allow setting these bits and searching for files based on these bits. This feature will not be usable on writeonce media.
		DWORD m_dwordImageColumns; // Width of unrotated image in columns. This is the size output the user expects from this image, not the size of the raw image data. Not necessarily equal to the width of any image entry in the file; this supports images where the raw data has rectangular pixels.
		DWORD m_dwordImageRows; // Height of unrotated image in rows. This is the size output the user expects from this image, not the size of the raw image data. Not necessarily equal to the width of any image entry in the file; this supports images where the raw data has rectangular pixels.
		DWORD m_dwordRotation; // Image rotation in degrees clockwise from normal camera orientation. Valid values are 0, 90, 180, 270.
		// Version > 2.0
		BYTE m_byteWhiteValanceLabelString[32]; // Contains an ASCIIZ string label of the current white balance setting for this image.
		BYTE m_byteExtendedDataTypes[32]; // Contains 32 8-bit values indicating the types of the following extended data.
		DWORD m_dwordExtendedData[32]; // Contains 32 32-bit values of extended data.
	} m_stHeader;

	CEX3FDirectory m_ceDirectory;

};

typedef CEX3F* LPX3F;
