// Document modified at : Tuesday, November 28, 2006 04:06:37 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CETiff.h: interface for the CETiff class.
#pragma once


class CETiff  
{
public:
	CETiff();
	virtual ~CETiff();

	#pragma pack ( 1 )
	struct TIFF_HEADER
	{
		WORD l_wordEndian; // 4949
		WORD l_word42; // 42
		DWORD l_dwordDirectoryOffset; // 8
	} m_stHeader;
	#pragma pack ()


	#pragma pack ( 1 )
	struct TIFF_IFD
	{
		WORD m_wordTag;
		WORD m_wordType;
		DWORD m_dwordCount;
		DWORD m_dwordOffset;
	};
#pragma pack ()

#pragma pack ( 1 )
	struct TIFF_FIRST_DIR
	{
		WORD m_wordNumberofDirectoryEntries; // 000B   8 

		TIFF_IFD m_ifdImageWidth; // 0100 0004            22		158
		TIFF_IFD m_ifdImageLength; // 0101 0004           34		162
		TIFF_IFD m_ifdBitsPerSample; // 0102  0003       130
		TIFF_IFD m_ifdCompression; // 0103 0003           46		166
		TIFF_IFD m_ifdPhotometricInterpretation; // 0106 0003     58		 168
		TIFF_IFD m_ifdStripOffsets; // 0111 0004             82		210
		TIFF_IFD m_ifdSamplesPerPixel; // 0115  0003     118
		TIFF_IFD m_ifdStripByteCounts; // 0117 0003       94		214
		TIFF_IFD m_ifdXResolution; // 011A 0005            142	174
		TIFF_IFD m_ifdYResolution; // 011B 0005             154 		182
		TIFF_IFD m_ifdPlanarConfiguration; // 011C   00FE 0004     10      154
		TIFF_IFD m_ifdResolutionUnit; //  0128   0003      106
		TIFF_IFD m_ifdSoftware; // 0131 0002                 166	190
		TIFF_IFD m_ifdNextIFDoffset;// 00000000            178

      	TIFF_IFD m_ifdRowsPerStrip; //  0116 0004          70	170
		
		DWORD m_dwordXResolutionFraction; //  190
		DWORD m_dwordXResolutionDenominator; //  194
		DWORD m_dwordYResolutionFraction;  // 198
		DWORD m_dwordYResolutionDenominator; //  202
		BYTE m_byteSoftware[20]; // CEZEO X3F PROCESSOR //  204
		WORD m_wordBitsPerSample[3]; //   226
		DWORD m_dwordOffsetOfTheImage; // 232  = 1531*4 + 216 + 1531*2   / + 2304*3*2
		DWORD m_dwordSizeOfTheImage; //  236 = all of 2304*3*2
	} m_stFirstDir;
	#pragma pack ()


	LPBYTE mp_byteImage;
	DWORD m_dwordSize;

	void DeleteMemory();

	BOOL Save( LPCTSTR lp_strname );
};

typedef CETiff* LPTIFF;
