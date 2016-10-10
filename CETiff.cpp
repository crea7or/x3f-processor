// Document modified at : Tuesday, November 28, 2006 04:06:37 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CETiff.cpp: implementation of the CETiff class.
#include "stdafx.h"
#include "CETiff.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CETiff::CETiff()
{
	
	BYTE m_byteSoftwareName[]={"CEZEO X3F PROCESSOR"};

	
	memset( &m_stHeader, 0, sizeof( m_stHeader ));
	mp_byteImage = NULL;
	m_dwordSize = 0;

	memset( LPVOID( &m_stHeader )  , 0, sizeof(m_stHeader));
	memset( LPVOID( &m_stFirstDir ) , 0, sizeof(m_stFirstDir));


	m_stHeader.l_wordEndian = 0x4949;
	m_stHeader.l_word42 = 42;
	m_stHeader.l_dwordDirectoryOffset = 8;


	m_stFirstDir.m_wordNumberofDirectoryEntries = 0x0F; // 000B   8 9 
	
//	m_stFirstDir.m_ifdNewSubfileType.m_wordTag = 0xFE; // 00FE 0004     10      154
//	m_stFirstDir.m_ifdNewSubfileType.m_wordType = 4; // 00FE 0004     10      154
//	m_stFirstDir.m_ifdNewSubfileType.m_dwordCount = 1; // 00FE 0004     10      154
//	m_stFirstDir.m_ifdNewSubfileType.m_dwordOffset = 0x8DC;

	m_stFirstDir.m_ifdImageWidth.m_wordTag = 0x100; // 0100 0004            22		158
	m_stFirstDir.m_ifdImageWidth.m_wordType = 3; // 0100 0004            22		158
	m_stFirstDir.m_ifdImageWidth.m_dwordCount = 1; // 0100 0004            22		158
	m_stFirstDir.m_ifdImageWidth.m_dwordOffset = 2268;//2304; //2268 0100 0004            22		158

	m_stFirstDir.m_ifdImageLength.m_wordTag = 0x101; // 0101 0004           34		162
	m_stFirstDir.m_ifdImageLength.m_wordType = 3; // 0101 0004           34		162
	m_stFirstDir.m_ifdImageLength.m_dwordCount = 1; // 0101 0004           34		162
	m_stFirstDir.m_ifdImageLength.m_dwordOffset = 1512;//1531; // 0101 0004           34		162

	m_stFirstDir.m_ifdCompression.m_wordTag = 0x103; // 0103 0003           46		166
	m_stFirstDir.m_ifdCompression.m_wordType = 3; // 0103 0003           46		166
	m_stFirstDir.m_ifdCompression.m_dwordCount = 1; // 0103 0003           46		166
	m_stFirstDir.m_ifdCompression.m_dwordOffset = 1; // 0103 0003           46		166

	m_stFirstDir.m_ifdPhotometricInterpretation.m_wordTag = 0x106; // 0106 0003     58		 168
	m_stFirstDir.m_ifdPhotometricInterpretation.m_wordType = 3; // 0106 0003     58		 168
	m_stFirstDir.m_ifdPhotometricInterpretation.m_dwordCount = 1; // 0106 0003     58		 168
	m_stFirstDir.m_ifdPhotometricInterpretation.m_dwordOffset = 2; // 0106 0003     58		 168

	m_stFirstDir.m_ifdRowsPerStrip.m_wordTag = 0x116; //  0116 0004          70	170
	m_stFirstDir.m_ifdRowsPerStrip.m_wordType = 4; //  0116 0004          70	170
	m_stFirstDir.m_ifdRowsPerStrip.m_dwordCount = 1; //  0116 0004          70	170
	m_stFirstDir.m_ifdRowsPerStrip.m_dwordOffset = 1531; //  0116 0004          70	170

	m_stFirstDir.m_ifdXResolution.m_wordTag = 0x11A; // 011A 0005              82	174
	m_stFirstDir.m_ifdXResolution.m_wordType = 5; // 011A 0005              82	174
	m_stFirstDir.m_ifdXResolution.m_dwordCount = 1; // 011A 0005              82	174
	m_stFirstDir.m_ifdXResolution.m_dwordOffset = 190; // 011A 0005              82	174

	m_stFirstDir.m_ifdYResolution.m_wordTag = 0x11B; // 011B 0005               94		182
	m_stFirstDir.m_ifdYResolution.m_wordType = 5; // 011B 0005               94		182
	m_stFirstDir.m_ifdYResolution.m_dwordCount = 1; // 011B 0005               94		182
	m_stFirstDir.m_ifdYResolution.m_dwordOffset = 198; // 011B 0005               94		182

	m_stFirstDir.m_ifdSoftware.m_wordTag = 0x131; // 0131 0002                  106	190
	m_stFirstDir.m_ifdSoftware.m_wordType = 2; // 0131 0002                  106	190
	m_stFirstDir.m_ifdSoftware.m_dwordCount = 20; // 0131 0002                  106	190
	m_stFirstDir.m_ifdSoftware.m_dwordOffset = 206;// 0131 0002                  106	190

	m_stFirstDir.m_ifdStripOffsets.m_wordTag = 0x111; // 0111 0004             118		210
	m_stFirstDir.m_ifdStripOffsets.m_wordType = 4; // 0111 0004             118		210
	m_stFirstDir.m_ifdStripOffsets.m_dwordCount = 1; // 0111 0004             118		210
	m_stFirstDir.m_ifdStripOffsets.m_dwordOffset = 0xF0;//232;//238; // 0111 0004             118		210
///////////  230


	m_stFirstDir.m_ifdStripByteCounts.m_wordTag = 0x117; // 0117 0003       130		214
	m_stFirstDir.m_ifdStripByteCounts.m_wordType = 4; // 0117 0003       130		214
	m_stFirstDir.m_ifdStripByteCounts.m_dwordCount = 1; // 0117 0003       130		214
	m_stFirstDir.m_ifdStripByteCounts.m_dwordOffset =  1512*2268*6;     // 1531*2304*3*2
////// 234



	m_stFirstDir.m_ifdResolutionUnit.m_wordTag =0x128 ; //  0128   0003      142
	m_stFirstDir.m_ifdResolutionUnit.m_wordType = 3; //  0128   0003      142
	m_stFirstDir.m_ifdResolutionUnit.m_dwordCount = 1; //  0128   0003      142
	m_stFirstDir.m_ifdResolutionUnit.m_dwordOffset = 2; ; //  0128   0003      142

	m_stFirstDir.m_ifdSamplesPerPixel.m_wordTag = 0x115; // 0115  0003     154
	m_stFirstDir.m_ifdSamplesPerPixel.m_wordType = 3; // 0115  0003     154
	m_stFirstDir.m_ifdSamplesPerPixel.m_dwordCount = 1; // 0115  0003     154
	m_stFirstDir.m_ifdSamplesPerPixel.m_dwordOffset = 3; ; // 0115  0003     154

	m_stFirstDir.m_ifdBitsPerSample.m_wordTag = 0x102; // 0102  0003       166
	m_stFirstDir.m_ifdBitsPerSample.m_wordType = 3; // 0102  0003       166
	m_stFirstDir.m_ifdBitsPerSample.m_dwordCount = 3; // 0102  0003       166
	m_stFirstDir.m_ifdBitsPerSample.m_dwordOffset = 226; // value 0102  0003       166

	m_stFirstDir.m_ifdPlanarConfiguration.m_wordTag = 0x11C;
	m_stFirstDir.m_ifdPlanarConfiguration.m_wordType = 3;
	m_stFirstDir.m_ifdPlanarConfiguration.m_dwordCount = 1;
	m_stFirstDir.m_ifdPlanarConfiguration.m_dwordOffset = 1;



	m_stFirstDir.m_ifdNextIFDoffset.m_wordTag = 0;// 00000000             142
	m_stFirstDir.m_ifdNextIFDoffset.m_wordType = 0;// 00000000             142
	m_stFirstDir.m_ifdNextIFDoffset.m_dwordCount = 0;// 00000000             142
	m_stFirstDir.m_ifdNextIFDoffset.m_dwordOffset = 0;// 00000000             142
        
	m_stFirstDir.m_dwordXResolutionFraction = 0x16800000; //
	m_stFirstDir.m_dwordXResolutionDenominator = 0x00200000; //
	m_stFirstDir.m_dwordYResolutionFraction = 0x16800000; //
	m_stFirstDir.m_dwordYResolutionDenominator = 0x00200000; //
//	m_stFirstDir.m_byteSoftware[0] = 49; // CEZEO X3F PROCESSOR 
	m_stFirstDir.m_dwordOffsetOfTheImage = 0;// 240; // 210 = 1531*4 + 216 + 2304*3*2
	m_stFirstDir.m_dwordSizeOfTheImage = 0; // 214  = all of 2304*3*2

	m_stFirstDir.m_wordBitsPerSample[0] = 16;
	m_stFirstDir.m_wordBitsPerSample[1] = 16;
	m_stFirstDir.m_wordBitsPerSample[2] = 16;


	memcpy( m_stFirstDir.m_byteSoftware, m_byteSoftwareName, sizeof( m_byteSoftwareName ));

}

CETiff::~CETiff()
{
	DeleteMemory();
}

void CETiff::DeleteMemory()
{
	if ( mp_byteImage != NULL )
	{
		CEHelper::FreeBuffer( mp_byteImage );
		mp_byteImage = NULL;
		m_dwordSize = 0;
	}
}

BOOL CETiff::Save( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;

	CEFile l_ceFile;

	if ( l_ceFile.Open( lp_strName, CEFile::eModeReadWrite | CEFile::eModeCreate ))
	{
		l_ceFile.Write( &m_stHeader, sizeof( m_stHeader ));
		l_ceFile.Write( &m_stFirstDir, sizeof( m_stFirstDir ));
		l_ceFile.Write( mp_byteImage, m_dwordSize );
		l_ceFile.Close();
	}

	return l_boolResult;
}
