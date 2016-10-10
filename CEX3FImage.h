// Document modified at : Sunday, February 19, 2012 5:50:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FImage.h: interface for the CEX3FImage class.
#pragma once

#include "CEX3FSection.h"

class CEX3FImage : public CEX3FSection
{
public:
	CEX3FImage();
	virtual ~CEX3FImage();
	
	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );

	DWORD Load( CEFile* lp_ceFile );

	
	BOOL SaveTga( LPCTSTR lp_strName );
	BOOL SaveTiff( LPCTSTR lp_strName );
	BOOL SaveBmp( LPCTSTR lp_strName );
	
	virtual LPCTSTR GetTextSectionType()
	{
		m_csTextSectionType.Format("%c%c%c%c - %d", LOBYTE(LOWORD( m_stSectionData.m_dwordTypeOfEntry )),  HIBYTE(LOWORD( m_stSectionData.m_dwordTypeOfEntry )),  LOBYTE( HIWORD( m_stSectionData.m_dwordTypeOfEntry )), HIBYTE( HIWORD( m_stSectionData.m_dwordTypeOfEntry )), m_stData.m_dwordDataFormat );
		return m_csTextSectionType;
	}

	virtual BOOL SaveSection( );

	struct IMAGE_DATA
	{
		static DWORD GetDataSize()
		{
			return ( sizeof( DWORD ) * 7 );
		};
		
		DWORD m_dwordSectionIdentifier; // Section identifier Should be "SECi" . 0x69434553
		DWORD m_dwordImageFormatVersion; // Image format version Should be 2.0 for now.
		DWORD m_dwordTypeOfImageData; // Type of image data 2 = processed for preview (others RESERVED)
		DWORD m_dwordDataFormat; // Data format 3 = uncompressed 24-bit 8/8/8 RGB  : 11 = Huffman-encoded DPCM 8/8/8 RGB : 18 = JPEG-compressed 8/8/8 RGB (others RESERVED)
		DWORD m_dwordImageColumns; // Image columns Image width / row size in pixels
		DWORD m_dwordImageRows; // Image rows Image height in pixels
		DWORD m_dwordRowSize; // Row size in bytes Will always be a multiple of 4 (32-bit aligned). A value of zero here means that rows are variable-length (as in Huffman data).
	} m_stData;
	

	BOOL Unpack();
	BOOL Unpack3();
	BOOL Unpack30();
	BOOL Unpack11();
	BOOL Unpack18();
	BOOL Unpack6();

    struct HUFF_NODE 
	{
		DWORD m_dwordChild[2];
		DWORD m_dwordIndex;
	} ;
	
	HUFF_NODE  m_arrayHuffTree[2048];

	LPDWORD mp_dwordHuffKey;
	LPDWORD mp_dwordHuffTable;
	DWORD m_dwordHuffNewNode;


	void HuffMakeTree( DWORD l_dwordNowNode, DWORD l_dwordCode, DWORD l_dwordSize = 1024 );

	///////////////



	void ApplyMatrix( LPBYTE lp_byteDestination, MATRIX* lp_stMatrix );

	BOOL m_boolUnpacked;

	DWORD FindValue( DWORD (*m_dwordHistogram)[3][65536] ,  BYTE l_byteArray /* 0-R 1-g 2-b */, DWORD l_boolLowHighAll ); // 0 - low, high = 1 , all =2


#pragma pack(push,1)
	struct RGB24 
	{
        byte R;
        byte G;
		byte B;
    };
    
	struct RGB24A 
	{
        byte R;
        byte G;
		byte B;
		byte A;
    };

    struct RGB48 
	{
        WORD R;
        WORD G;
        WORD B;
    };
#pragma pack(pop)
	
};

typedef CEX3FImage* LPX3FIMAGE;
