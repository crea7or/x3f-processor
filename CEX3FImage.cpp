// Document modified at : Sunday, February 19, 2012 3:23:17 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FImage.cpp: implementation of the CEX3FImage class.
#include "stdafx.h"
#include "CEX3FImage.h"
#include "CEX3F.h"
#include "CETarga.h"
#include "CEBmp.h"
#include "CETiff.h"
#include "CEDialogApplyMatrix.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
#include "Jpeg/ximajpg.h"

#ifdef _DEBUG
#pragma message( "Linking CxImage.lib" )
#pragma comment( lib, "JpegMD/CxImage.lib" )
#pragma message( "Linking jpeg.lib" )
#pragma comment( lib, "JpegMD/jpeg.lib" )
#endif

#ifndef _DEBUG
#pragma message( "Linking CxImage.lib" )
#pragma comment( lib, "Jpeg/CxImage.lib" )
#pragma message( "Linking jpeg.lib" )
#pragma comment( lib, "Jpeg/jpeg.lib" )
#endif
*/


CEX3FImage::CEX3FImage()
{
	memset( &m_stData, 0, sizeof( CEX3FImage::IMAGE_DATA ));
	m_boolUnpacked = FALSE;
}

CEX3FImage::~CEX3FImage()
{
	
}

BOOL CEX3FImage::SaveSection()
{
	BOOL l_boolResult = TRUE;

	Unpack();

	if ( m_stData.m_dwordDataFormat == 18 )
	{
		// jpeg
		CFileDialog l_dlgFileSave( FALSE, "jpg", NULL, NULL, "Jpeg Files (*.JPG)|*.JPG||", NULL);
		if ( l_dlgFileSave.DoModal() == IDOK )
		{
			 SaveTiff( l_dlgFileSave.GetPathName());
		}
	}
	else if ( m_stData.m_dwordDataFormat == 3 || m_stData.m_dwordDataFormat == 11)
	{
		// bmp
		CFileDialog l_dlgFileSave( FALSE, "bmp", NULL, NULL, "BITMAP Files (*.BMP)|*.BMP||", NULL);
		if ( l_dlgFileSave.DoModal() == IDOK )
		{
			SaveBmp( l_dlgFileSave.GetPathName());
		}
	}
	else 
	{
		// tiff
		CFileDialog l_dlgFileSave( FALSE, "tif", NULL, NULL, "TIFF Files (*.TIF)|*.TIF||", NULL);
		if ( l_dlgFileSave.DoModal() == IDOK )
		{
			 SaveTiff( l_dlgFileSave.GetPathName());
		}
	}

	return l_boolResult;
}

BOOL CEX3FImage::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
{
	BOOL l_boolResult = TRUE;
    if (lp_ceListCtrlItem->mask & LVIF_TEXT)
    {
		switch ( lp_ceListCtrlItem->iSubItem )
        {
		case 0:
			lp_ceListCtrlItem->pszText = LPTSTR( GetTextSectionType());
			break;
		case 1:
			{
				switch( m_stData.m_dwordDataFormat )
				{
				case 3:
						lp_ceListCtrlItem->pszText= "Small preview"; // Unpack3();
					break;
				case 11:
						lp_ceListCtrlItem->pszText = "Med preview"; //Unpack11();
					break;
				case 18:
						lp_ceListCtrlItem->pszText = "Jpg preview";//Unpack18();
					break;
				case 6:
						lp_ceListCtrlItem->pszText = "RAW image"; //Unpack6();
					break;
				case 30:
					lp_ceListCtrlItem->pszText = "RAW DP1"; //Unpack6();
					break;
				default:
					lp_ceListCtrlItem->pszText = "Unknown"; // 30
					//CEHelper::PN( m_stData.m_dwordDataFormat );
					break;
				}

	//		lp_ceListCtrlItem->pszText = LPTSTR( GetDescription());
			
			}
			break;
		case 2:
			lp_ceListCtrlItem->pszText = LPTSTR( GetTextSectionLength());
			break;
        }
    }
	if ( lp_ceListCtrlItem->mask & LVIF_IMAGE )
	{
   //     lp_ceListCtrlItem->iImage = GetImage();
	}
	return l_boolResult;
}


DWORD CEX3FImage::Load( CEFile* lp_ceFile )
{
	DWORD l_dwordResult = ERROR_FILE;
	
	if ( lp_ceFile->Read( &m_stData, m_stData.GetDataSize()))
	{
		DeleteMemory();
		m_dwordSectionDataSize = m_stSectionData.m_dwordLengthOfEntry - m_stData.GetDataSize();
		
		mp_byteSectionData = LPBYTE( malloc( m_dwordSectionDataSize ));
		
		if ( lp_ceFile->Read( mp_byteSectionData, m_dwordSectionDataSize ))
		{
			l_dwordResult = ERROR_OK;
		}
		else
		{		
			DeleteMemory();
		}
	}
	return l_dwordResult;
}

	/*
	 enum X3F_DATA_FORMAT
    {
        Unknown = -1,
        RAW = 3,         // uncompressed 24bit rgb
        Huffman1024 = 6, //
        Huffman256 = 11, // huffman encoded
        Jpeg = 18        // 24 bit jpeg
    };
	*/


BOOL CEX3FImage::Unpack()
{
	BOOL l_boolResult = FALSE;
	if ( m_boolUnpacked == FALSE )
	{
		switch( m_stData.m_dwordDataFormat )
		{
		case 3:
			l_boolResult= Unpack3();
			break;
		case 11:
			l_boolResult = Unpack11();
			break;
		case 18:
			l_boolResult = Unpack18();
			break;
		case 6:
			l_boolResult = Unpack6();
			break;
		case 30:
			l_boolResult = Unpack30();
			break;
		default:
			l_boolResult = FALSE;
			break;			
		}
		m_boolUnpacked = l_boolResult;
	}
	
	return l_boolResult;
}

BOOL CEX3FImage::Unpack30()
{
	BOOL l_boolResult = FALSE;

//	RGB24* lp_byteRgbSrc;
//	RGB24* lp_byteRgbDst;
	DWORD l_dwordTrueRowSizeBytes;
	LPBYTE lp_byteFlipData;
	DWORD l_d;
	
	l_dwordTrueRowSizeBytes = m_stData.m_dwordImageColumns * 3;
	if (( l_dwordTrueRowSizeBytes & 0x03 ) > 0 ) // test to 4 bytes padding for the each row
	{
		l_dwordTrueRowSizeBytes += ( 0x04 - ( l_dwordTrueRowSizeBytes & 0x03 ));
	}
	
	l_d = m_dwordSectionDataSize;
	lp_byteFlipData = mp_byteSectionData;
	

//	CEFile l_ceFile;
//	l_ceFile.Open( "c:\\dp1raw.bin", CEFile::eModeCreate | CEFile::eModeReadWrite );
//	l_ceFile.Write( lp_byteFlipData, m_dwordSectionDataSize );
//	l_ceFile.Close();
	
	l_boolResult = TRUE;

	return l_boolResult;
}	

BOOL CEX3FImage::Unpack3()
{
	// input: Plain RGB uncompressed small
	// output: BMP 24bp
	BOOL l_boolResult = FALSE;

	RGB24* lp_byteRgbSrc;
	RGB24* lp_byteRgbDst;
	DWORD l_dwordTrueRowSizeBytes;
	LPBYTE lp_byteFlipData;

	l_dwordTrueRowSizeBytes = m_stData.m_dwordImageColumns * 3;
	if (( l_dwordTrueRowSizeBytes & 0x03 ) > 0 ) // test to 4 bytes padding for the each row
	{
		l_dwordTrueRowSizeBytes += ( 0x04 - ( l_dwordTrueRowSizeBytes & 0x03 ));
	}

	lp_byteFlipData = LPBYTE( malloc( m_dwordSectionDataSize ));

	//memcpy(  lp_byteFlipData, mp_byteSectionData, m_dwordSectionDataSize );

	for ( DWORD l_dwordRow = 0; l_dwordRow < m_stData.m_dwordImageRows; l_dwordRow++)
	{
		lp_byteRgbSrc = ( RGB24* )( mp_byteSectionData + ( l_dwordTrueRowSizeBytes * l_dwordRow ));
		lp_byteRgbDst = ( RGB24* )(( lp_byteFlipData + ( l_dwordTrueRowSizeBytes * (( m_stData.m_dwordImageRows - 1 ) - l_dwordRow ))));

		for ( DWORD l_dwordCol = 0; l_dwordCol < m_stData.m_dwordImageColumns; l_dwordCol++ )
		{
			lp_byteRgbDst[ l_dwordCol ].B = lp_byteRgbSrc[ l_dwordCol ].R;
			lp_byteRgbDst[ l_dwordCol ].G = lp_byteRgbSrc[ l_dwordCol ].G;
			lp_byteRgbDst[ l_dwordCol ].R = lp_byteRgbSrc[ l_dwordCol ].B;
		}
	}

	free( mp_byteSectionData );
	mp_byteSectionData = lp_byteFlipData;

	l_boolResult = TRUE;
	return l_boolResult;
}

BOOL CEX3FImage::Unpack18()
{
	// input: JPEG
	// output: JPEG
	BOOL l_boolResult = TRUE;


//	CxImage image( mp_byteSectionData , m_dwordSectionDataSize , CXIMAGE_FORMAT_JPG);
//	AfxMessageBox( image.GetLastError());
//	DWORD l_dwordNewImageSize = image.GetSize();


	return l_boolResult;
}

BOOL CEX3FImage::Unpack11()
{
	// input: Huffmap DPCM RGB compressed med
	// output: BMP 24bp
	BOOL l_boolResult = FALSE;
	
	LPBYTE lp_byteSource, lp_byteDestination;
	DWORD l_dwordTrueRowSizeBytes = m_stData.m_dwordImageColumns * 3;
	DWORD l_dwordImageBufferSize;//, l_dwordAccessCounter = 0;
	lp_byteSource = mp_byteSectionData + ( 256 * sizeof( DWORD ));
	l_dwordImageBufferSize = ( m_stData.m_dwordImageRows  * l_dwordTrueRowSizeBytes );
	
	lp_byteDestination = LPBYTE( malloc( l_dwordImageBufferSize * 2 ));
	memset( lp_byteDestination, 0, l_dwordImageBufferSize * 2 );
		
	mp_dwordHuffKey = LPDWORD( mp_byteSectionData );
	memset( m_arrayHuffTree, 0 , sizeof( m_arrayHuffTree ));
	m_dwordHuffNewNode = 0;
	HuffMakeTree( 0, 0, 256 );
	// new 32b
	
	LPBYTE lp_byteAsmValues = LPBYTE( malloc ( 56 ));
	memset( lp_byteAsmValues, 0, 56 );
	LPDWORD lp_dwordAsmValues = LPDWORD( lp_byteAsmValues );
	
	/*
	00+00 - lp_byteTree ( 4 byte ) ( 4 byte )
	01+04 - counter ( 4 byte )
	02+08 - counter ( 4 byte )
	03+12 - lp_bytePixel ( 3 dword value  )
	04+16
	05+20
	06+24 - lp_rgb48value ( 4 byte )
	07+28 - lp_rgb48 ( 4 byte )
	08+32 - l_dwordTrueRowSizeBytes ( 4 byte )
	09+36 - l_dwordImageColumns ( 4 byte )
	10+40 - l_dwordImageRows ( 4 byte )
	11+44 - lp_byteTree ( 4 byte )
	12+48 - lp_dwordSource
	13+52 - table
	*/
	
	// new 32b
	lp_dwordAsmValues[ 6 ] = DWORD(( lp_byteDestination - l_dwordTrueRowSizeBytes ));//+ l_dwordImageBufferSize )); // lp_rgb48value
	lp_dwordAsmValues[ 7 ] = DWORD(( lp_byteDestination - l_dwordTrueRowSizeBytes ));//+ l_dwordImageBufferSize )); // lp_rgb48
	lp_dwordAsmValues[ 8 ] = DWORD( l_dwordTrueRowSizeBytes );
	lp_dwordAsmValues[ 9 ] = DWORD( m_stData.m_dwordImageColumns );
	lp_dwordAsmValues[ 10 ] = DWORD( m_stData.m_dwordImageRows );
	lp_dwordAsmValues[ 0 ] = DWORD( m_arrayHuffTree );
	lp_dwordAsmValues[ 12 ] = DWORD( lp_byteSource );
	lp_dwordAsmValues[ 13 ] = DWORD( mp_dwordHuffTable );
	

	_asm
	{			
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push ebp
		//////////
		mov ebp, lp_byteAsmValues
		xor edi,edi // l_dwordBits
		mov esi, [ebp+48]
		mov ecx, [ebp+40] //		for ( int row = 0; row < int( m_stData.m_dwordImageRows ); row++ ) 
		ALIGN 16
main_loop:
		mov [ ebp + 8 ], ecx
		xor eax,eax
		mov ecx, ebp
		mov [ecx+12], eax
		mov [ecx+16], ax
		mov eax, [ ebp + 24 ] // lp_rgb48value //			lp_rgb48 = ( RGB48* )(DWORD( lp_rgb48value ) - l_dwordTrueRowSizeBytes );
		add eax, [ ebp + 32 ] // l_dwordTrueRowSizeBytes 
		mov [ebp+28], eax //			lp_rgb48value = lp_rgb48;
		mov [ebp+24], eax
		xor ebx,ebx //			l_dwordOneBit = 0;
		mov ecx, [ebp+36 ] // l_dwordImageColumns  //			for ( int col = 0; col < int( m_stData.m_dwordImageColumns ); col++ ) 
		nop
columns_cucle:
		mov [ ebp + 4 ], ecx
		xor ecx,ecx //				for ( int c = 0; c < 3; c++ ) 
colors_cucle:
		push ecx
		mov edx,[ebp] // edx
		/////////////////////////////////
		mov ecx,ebx
		xor ebx,ebx
get_the_pixel:
		// bits count - decode to byte offset + bit to test
		mov eax,edi
		cmp ecx,ebx				//if ( l_dwordOneBit == 0 )       //  <! ======== and ebx, ebx
		jnz one_bit_not_null
		mov eax, [ esi ]
		bswap eax
		inc esi
		inc esi
		inc esi
		inc esi
		mov edi,eax
		//ALIGN 4
one_bit_not_null:
		//	l_dwordOneBit = ( l_dwordOneBit - 1 ) & 0x1f;	
		dec ecx //				 l_dwordOneBit - 1
		and ecx,0x1F  //    l_dwordOneBit & 0x1f
		shr eax, cl // cl
		and eax,0x01//ecx
		mov edx, DWORD PTR [eax*4+edx]	//	l_dwordInd = tree[ l_dwordInd ].child[ ( l_dwordBits >> l_dwordOneBit ) & 0x01 ];	
		cmp DWORD PTR [edx], ebx //			for ( l_dwordInd = 0; tree[l_dwordInd].child[0] > 0; ) 
		jz no_get_the_pixel
		cmp ecx,ebx				//if ( l_dwordOneBit == 0 )       //  <! ======== and ebx, ebx				
		mov eax,edi
		jnz one_bit_not_null
		jmp get_the_pixel
no_get_the_pixel:
		/////////////////////////////////
		///// write_pixel: ////
		/////////////////////////////////
		mov ebx,ecx
		mov eax, [edx + 8 ]
		mov edx,[esp]
		pop ecx	
		add edx, 12 //12
		inc ecx	
		add edx, ebp				
		add al,[edx]
		cmp ecx,3
		mov [edx], al
		jnz colors_cucle
		/////////////////////////////////
		//// write complete pixel  ///
		/////////////////////////////////
		mov edx,[ebp+28] 
		mov eax,[ebp+12]
		mov [edx],eax
		add edx,3 // to fit bmp
		mov [ebp+28],edx
		mov ecx, [ebp+4]
		dec ecx
		jnz columns_cucle
		cmp ebx, 0
		jnz to_main_loop
		add esi,4
to_main_loop:
		mov ecx, [ ebp + 8 ]
		dec ecx
		jnz main_loop
		/////////
		pop ebp
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
	
	free( lp_byteAsmValues );
	

	RGB24* lp_byteRgbSrc;
	RGB24* lp_byteRgbDst;
	LPBYTE lp_byteFlipData;
	
	
	DWORD l_dwordTrueRowSizeBytesPadded;
	l_dwordTrueRowSizeBytesPadded = m_stData.m_dwordImageColumns * 3;
	if (( l_dwordTrueRowSizeBytesPadded & 0x03 ) > 0 ) // test to 4 bytes padding for the each row
	{
		l_dwordTrueRowSizeBytesPadded += ( 0x04 - ( l_dwordTrueRowSizeBytesPadded & 0x03 ));
	}
	
	DWORD l_dwordDataSizePadded = ( m_stData.m_dwordImageRows * l_dwordTrueRowSizeBytesPadded );
	
	lp_byteFlipData = LPBYTE( malloc( l_dwordDataSizePadded ));
	
	for ( DWORD l_dwordRow = 0; l_dwordRow < m_stData.m_dwordImageRows; l_dwordRow++)
	{
		lp_byteRgbSrc = ( RGB24* )( lp_byteDestination + ( l_dwordTrueRowSizeBytes * l_dwordRow ));
		lp_byteRgbDst = ( RGB24* )(( lp_byteFlipData + l_dwordDataSizePadded ) - ( l_dwordTrueRowSizeBytesPadded * ( l_dwordRow + 1 )));
		
		for ( DWORD l_dwordCol = 0; l_dwordCol < m_stData.m_dwordImageColumns; l_dwordCol++ )
		{
			lp_byteRgbDst[ l_dwordCol ].B = lp_byteRgbSrc[ l_dwordCol ].R;
			lp_byteRgbDst[ l_dwordCol ].G = lp_byteRgbSrc[ l_dwordCol ].G;
			lp_byteRgbDst[ l_dwordCol ].R = lp_byteRgbSrc[ l_dwordCol ].B;
		}
	}
	
	free( lp_byteDestination );
	free( mp_byteSectionData );
	mp_byteSectionData = lp_byteFlipData;
	m_dwordSectionDataSize = l_dwordDataSizePadded;
		
	l_boolResult = TRUE;
	return l_boolResult;
}

BOOL CEX3FImage::Unpack6()
{
	// input: Huffman DPCM 48
	// outpub: RGB 16bit

	BOOL l_boolResult = FALSE;

//	CEFile l_ceFile;
//	l_ceFile.Open( "c:\\sd14raw.bin", CEFile::eModeCreate | CEFile::eModeReadWrite );
//	l_ceFile.Write( mp_byteSectionData, m_dwordSectionDataSize );
//	l_ceFile.Close();


	LPBYTE lp_byteSource, lp_byteDestination, lp_byteOffsets;
	
	//########################################
	DWORD l_dwordTrueRowSizeBytes = m_stData.m_dwordImageColumns * 3 * 2;// Because 16 BIT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	DWORD l_dwordImageBufferSize;
	lp_byteSource = mp_byteSectionData + ( 1024 * sizeof( DWORD )) + ( 1024 * sizeof ( WORD ));
	l_dwordImageBufferSize = ( m_stData.m_dwordImageRows  * l_dwordTrueRowSizeBytes );
	lp_byteOffsets = ( mp_byteSectionData + m_dwordSectionDataSize ) - ( m_stData.m_dwordImageRows * sizeof( DWORD ));
	
	lp_byteDestination = LPBYTE( malloc( l_dwordImageBufferSize )); //
	memset( lp_byteDestination, 0, l_dwordImageBufferSize );		
	
	LPDWORD lp_dwordDwordTable = LPDWORD( malloc( 1024 * sizeof( DWORD )));
	DWORD l_dwordVal = 0;
	LPWORD lp_wordTable = LPWORD( mp_byteSectionData );
	for ( DWORD l_dwordIndex = 0; l_dwordIndex < 1024; l_dwordIndex++ )
	{
		l_dwordVal = WORD( lp_wordTable[ l_dwordIndex ] );
		lp_dwordDwordTable[ l_dwordIndex ] = l_dwordVal;
	}
	
	mp_dwordHuffTable = lp_dwordDwordTable;
	mp_dwordHuffKey = LPDWORD( mp_byteSectionData + ( 1024 * sizeof( WORD )));
	m_dwordHuffNewNode = 0;
	memset( m_arrayHuffTree, 0 , sizeof( m_arrayHuffTree ));


	HuffMakeTree( 0, 0 );

	// m_dwordHuffNewNode
	
	LPBYTE lp_byteAsmValues = LPBYTE( malloc( 60 ));
	LPDWORD lp_dwordAsmValues = LPDWORD( lp_byteAsmValues );
	
	memset( lp_byteAsmValues, 0,60 );			
	
	/*
	00+00 - lp_byteTree ( 4 byte ) ( 4 byte )
	01+04 - counter ( 4 byte )
	02+08 - counter ( 4 byte )
	03+12 - lp_bytePixel ( 3 dword value  )
	04+16
	05+20
	06+24 - lp_rgb48value ( 4 byte )
	07+28 - lp_rgb48 ( 4 byte )
	08+32 - l_dwordTrueRowSizeBytes ( 4 byte )
	09+36 - l_dwordImageColumns ( 4 byte )
	10+40 - l_dwordImageRows ( 4 byte )
	11+44 - lp_byteTree ( 4 byte )
	12+48 - lp_dwordSource
	13+52 - table
	14+56 - offsets
	*/
	
	lp_dwordAsmValues[ 6 ] = DWORD(( lp_byteDestination - l_dwordTrueRowSizeBytes ));//+ l_dwordImageBufferSize )); // lp_rgb48value
	lp_dwordAsmValues[ 7 ] = DWORD(( lp_byteDestination - l_dwordTrueRowSizeBytes ));//+ l_dwordImageBufferSize )); // lp_rgb48
	lp_dwordAsmValues[ 8 ] = DWORD( l_dwordTrueRowSizeBytes );
	lp_dwordAsmValues[ 9 ] = DWORD( m_stData.m_dwordImageColumns );
	lp_dwordAsmValues[ 10 ] = DWORD( m_stData.m_dwordImageRows );
	lp_dwordAsmValues[ 0 ] = DWORD( m_arrayHuffTree );
	lp_dwordAsmValues[ 12 ] = DWORD( lp_byteSource );
	lp_dwordAsmValues[ 13 ] = DWORD( mp_dwordHuffTable );
	lp_dwordAsmValues[ 14 ] = DWORD( lp_byteOffsets );

	CEMMtimer m_ceMMtimer;
	m_ceMMtimer.StartTimer();

/*
	DWORD l_dwordAccessCounter = 0;
	RGB48* lp_rgb24 = ( RGB48* ) lp_byteDestination;
	WORD byte_pixel[3];
	DWORD l_dwordOneBit = 0, l_dwordBits = 0;
	HUFF_NODE* lp_stHuff = m_arrayHuffTree;
	HUFF_NODE* lp_stHuffST = m_arrayHuffTree;


	for ( int row1 = 0; row1 < int( m_stData.m_dwordImageRows ); row1++ ) 
	{	
		l_dwordOneBit = 0;
		memset( byte_pixel, 0 , sizeof(byte_pixel));
		
		for ( int col = 0; col < int( m_stData.m_dwordImageColumns ); col++ ) 
		{
			for ( int c = 0; c < 3; c++ ) 
			{ 
				lp_stHuff = m_arrayHuffTree;
				while( lp_stHuff->m_dwordChild[0] > 0 )
				{
					if ( l_dwordOneBit == 0 ) 
					{
						l_dwordBits = ((( DWORD )lp_byteSource[ l_dwordAccessCounter + 3] ) | (( DWORD )lp_byteSource[ l_dwordAccessCounter +2] << 8 ) | (( DWORD )lp_byteSource[ l_dwordAccessCounter +1] << 16 ) | (( DWORD )lp_byteSource[ l_dwordAccessCounter ] << 24 ));
						l_dwordAccessCounter+= 4;
					}  
					l_dwordOneBit = ( l_dwordOneBit - 1 ) & 0x1f;
					lp_stHuff = (HUFF_NODE*)lp_stHuff->m_dwordChild[( l_dwordBits >> l_dwordOneBit ) & 1];
				}; 

				byte_pixel[c] += WORD( lp_stHuff->m_dwordIndex );
			}
			lp_rgb24->R = byte_pixel[2];
			lp_rgb24->G = byte_pixel[1];
			lp_rgb24->B = byte_pixel[0];      
			lp_rgb24++;
		}
		if ( l_dwordOneBit == 0 )
		{
			l_dwordAccessCounter+= 4;
		}
	 }
	m_ceMMtimer.StopTimer();
	m_ceMMtimer.ShowTimer();
*/


	_asm
	{			
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push ebp
		//////////
		mov ebp, lp_byteAsmValues
		xor edi,edi // l_dwordBits

		mov ecx, [ebp+40] //		for ( int row = 0; row < int( m_stData.m_dwordImageRows ); row++ ) 
		ALIGN 16
main_loop:

		mov [ ebp + 8 ], ecx

		mov esi, [ebp+48]
		mov eax,[ebp+56]
		add esi,[eax]
		add eax,4
		mov [ebp+56], eax

		xor eax,eax

		mov ecx, ebp
		mov [ecx+12], eax
		mov [ecx+16], ax
		mov eax, [ ebp + 24 ] // lp_rgb48value //			lp_rgb48 = ( RGB48* )(DWORD( lp_rgb48value ) - l_dwordTrueRowSizeBytes );
		add eax, [ ebp + 32 ] // l_dwordTrueRowSizeBytes 
		mov [ebp+28], eax //			lp_rgb48value = lp_rgb48;
		mov [ebp+24], eax
		xor ebx,ebx //			l_dwordOneBit = 0;
		mov ecx, [ebp+36 ] // l_dwordImageColumns  //			for ( int col = 0; col < int( m_stData.m_dwordImageColumns ); col++ ) 
		nop
columns_cucle:
		mov [ ebp + 4 ], ecx
		xor ecx,ecx //				for ( int c = 0; c < 3; c++ ) 
colors_cucle:
		push ecx
		mov edx,[ebp] // edx
		/////////////////////////////////
		mov ecx,ebx
		xor ebx,ebx

		mov eax,edi

get_the_pixel:
		// bits count - decode to byte offset + bit to test

		cmp ecx,ebx				//if ( l_dwordOneBit == 0 )       //  <! ======== and ebx, ebx
		jnz one_bit_not_null
		mov eax, [ esi ]
		bswap eax
		inc esi
		inc esi
		inc esi
		inc esi
		mov edi,eax
		//ALIGN 4
one_bit_not_null:
		//	l_dwordOneBit = ( l_dwordOneBit - 1 ) & 0x1f;	
		dec ecx //				 l_dwordOneBit - 1
		and ecx,0x1F  //    l_dwordOneBit & 0x1f
		shr eax, cl // cl
		and eax,0x01//ecx
		mov edx, DWORD PTR [eax*4+edx]	//	l_dwordInd = tree[ l_dwordInd ].child[ ( l_dwordBits >> l_dwordOneBit ) & 0x01 ];	
		cmp DWORD PTR [edx], ebx //			for ( l_dwordInd = 0; tree[l_dwordInd].child[0] > 0; ) 
		jz no_get_the_pixel
		cmp ecx,ebx				//if ( l_dwordOneBit == 0 )       //  <! ======== and ebx, ebx				
		mov eax,edi
		jnz one_bit_not_null
		jmp get_the_pixel
no_get_the_pixel:
		/////////////////////////////////
		///// write_pixel: ////
		/////////////////////////////////
		mov ebx,ecx
		mov eax, [edx + 8 ]
		mov edx,[esp]
		add edx, edx
		pop ecx	
		add edx, 12
		inc ecx	
		add edx, ebp				
		add ax,[edx]
		cmp ecx,3
		mov [edx], ax
		jnz colors_cucle
		/////////////////////////////////
		//// write complete pixel  ///
		/////////////////////////////////
		mov edx,[ebp+28] 
		mov eax,[ebp+12]
		mov [edx],eax
		mov ax,[ebp+16]
		mov [edx+4],ax
		add edx,6
		mov [ebp+28],edx



		mov ecx, [ebp+4]
		dec ecx
		jnz columns_cucle
		cmp ebx, 0
		jnz to_main_loop
		add esi,4
to_main_loop:
		mov ecx, [ ebp + 8 ]
		dec ecx
		jnz main_loop
		/////////
		pop ebp
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

	
	m_ceMMtimer.StopTimer();
//	m_ceMMtimer.ShowTimer();


	free( lp_byteAsmValues );
	free( LPBYTE( lp_dwordDwordTable ));
/*
	// Crop to 2268 x 1512
	LPBYTE lp_byteRawSrc = lp_byteDestination + (( 8 * 2304 + 18 ) * 6 );
	LPBYTE lp_byteRawDst = lp_byteDestination;
	_asm
	{			
		push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi
			push ebp
			
			mov ebx, 1512
			mov esi, lp_byteRawSrc
			mov edi, lp_byteRawDst
mov_loop:
			mov ecx, 3402 // words moving
			cld
			rep movsd
			add esi, 216
			dec ebx
			jnz mov_loop
			
			pop ebp
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
	}	
	m_stData.m_dwordImageRows = 1512;
	m_stData.m_dwordImageColumns = 2268;
	// Crop to 2268 x 1512
*/	

	
	BOOL m_boolGamma = AfxGetApp()->GetProfileInt( "Processor Settings" , _T("m_boolGamma"),  TRUE );
	BOOL m_boolMatrix = AfxGetApp()->GetProfileInt( "Processor Settings" , _T("m_boolMatrix"),  FALSE );

	
	DWORD l_dwordHistogram[3][65536];

	int row, col;

	// build histogramm
	RGB48* lp_rgb48_t = ( RGB48* )( lp_byteDestination );
	memset( l_dwordHistogram, 0, sizeof( l_dwordHistogram ));
	for ( row = 0; row < int( m_stData.m_dwordImageRows ); row++ ) 
	{	
		for ( col = 0; col < int( m_stData.m_dwordImageColumns ); col++ ) 
		{
			if ( lp_rgb48_t->R > 0x7FFF )
			{
				lp_rgb48_t->R ^= 0xFFFF;
			}
			if (  lp_rgb48_t->G > 0x7FFF )
			{
				lp_rgb48_t->G ^= 0xFFFF;
			}
			if ( lp_rgb48_t->B > 0x7FFF )
			{
				lp_rgb48_t->B ^= 0xFFFF;
			}
			l_dwordHistogram[0][ lp_rgb48_t->R ] += 1;
			l_dwordHistogram[1][ lp_rgb48_t->G ] += 1;
			l_dwordHistogram[2][ lp_rgb48_t->B ] += 1;
			lp_rgb48_t++;
		}
	}
	// build histogramm



// applying the matrix

	CEDialogApplyMatrix dlg;
	dlg.m_dwordRlow = FindValue( &l_dwordHistogram, 0, 0 );
	dlg.m_dwordRhigh = FindValue( &l_dwordHistogram, 0, 1 );
	dlg.m_dwordGlow = FindValue(  &l_dwordHistogram, 1, 0 );
	dlg.m_dwordGhigh = FindValue( &l_dwordHistogram, 1, 1 );
	dlg.m_dwordBlow = FindValue(  &l_dwordHistogram, 2, 0 );
	dlg.m_dwordBhigh = FindValue( &l_dwordHistogram, 2, 1 );
	// total
	dlg.m_dwordRtot = FindValue( &l_dwordHistogram, 0,2 );
	dlg.m_dwordGtot = FindValue( &l_dwordHistogram, 1,2 );
	dlg.m_dwordBtot = FindValue( &l_dwordHistogram, 2,2 );
	//

	if ( m_boolMatrix )
	{

	dlg.DoModal();
	//


	// applying the matrix
	/*
	MATRIX l_stMatrix;
	l_stMatrix.m_floatRR = float( 0.49353 );
	l_stMatrix.m_floatRG = float( 0.35804 );
	l_stMatrix.m_floatRB = float( 0.21204 );
	
	l_stMatrix.m_floatGR = float( -1.41747 );
	l_stMatrix.m_floatGG = float( 3.83130 );
	l_stMatrix.m_floatGB = float( -1.73962 );
	
	l_stMatrix.m_floatBR = float(  1.63282 );
	l_stMatrix.m_floatBG = float( -5.45389 );
	l_stMatrix.m_floatBB = float( 5.91316 );

	ApplyMatrix( lp_byteDestination, &l_stMatrix );
*/
	ApplyMatrix( lp_byteDestination, &dlg.l_stMatrix );
	}
	// apply gamma 			
	DWORD c=0;
	WORD lut[0x10000];
	DWORD perc, val, total, i;
	float white=0, r;
	float bright=1.0;	
				
	perc = int( m_stData.m_dwordImageColumns * m_stData.m_dwordImageRows * 0.01 );		/* 99th percentile white point */

	
	for ( c = 0; c < 3; c++ )
	{
		for (val=0x2000, total=0; --val > 32; )
		{
			if ((total += l_dwordHistogram[c][val]) > perc)
			{
				break;
			}
		}
		if (white < val)
		{
			white = float( val );
		}
	}
				
	white *= 8 / bright;
	for ( i=0; i < 0x10000; i++) 
	{
		r = i / white;
//		val = DWORD( 65536 * ( !use_gamma ? r :	r <= 0.018 ? r*4.5 : pow(r,0.45)*1.099-0.099 ));
		if ( r <= 0.018 )
		{
			r = float( r*4.5 );
		}
		else
		{
			r= float( pow(r,0.45)*1.099-0.099 );
		}
		val = DWORD( 0x7FFF * r );
				
		if (val > 0x7FFF)
		{
			val = 0x7FFF;
		}
		lut[i] = WORD( val );
	}
	
	DWORD l_dwordImageRows, l_dwordImageCols;
				
	// apply gamma 
	RGB48* lp_rgb48_t1 = ( RGB48* )( lp_byteDestination );
	if ( m_boolGamma)
	{
		for ( l_dwordImageRows = 0; l_dwordImageRows < m_stData.m_dwordImageRows; l_dwordImageRows++) 
		{
			for (l_dwordImageCols=0; l_dwordImageCols < m_stData.m_dwordImageColumns; l_dwordImageCols++)
			{						
				lp_rgb48_t1->R = WORD( WORD( lut[ lp_rgb48_t1->R ] ) * 2 );
				lp_rgb48_t1->G = WORD( WORD( lut[ lp_rgb48_t1->G ] ) * 2 );
				lp_rgb48_t1->B = WORD( WORD( lut[ lp_rgb48_t1->B ] ) * 2 );
				lp_rgb48_t1++;
			}
		}
	}
	// apply gamma 
		
	free( mp_byteSectionData );
		
	mp_byteSectionData = lp_byteDestination;
	m_dwordSectionDataSize = m_stData.m_dwordImageRows  * l_dwordTrueRowSizeBytes;

	l_boolResult = TRUE;
	return l_boolResult;
}


void CEX3FImage::ApplyMatrix( LPBYTE lp_byteDestination, MATRIX* lp_stMatrix  )
{
	float l_fR, l_fG, l_fB;
	RGB48* lp_rgb48 = ( RGB48* )( lp_byteDestination );
	
	for ( int row = 0; row < int( m_stData.m_dwordImageRows ); row++ ) 
	{	
		for ( int col = 0; col < int( m_stData.m_dwordImageColumns ); col++ ) 
		{
			l_fR = ( lp_stMatrix->m_floatRR * lp_rgb48->R ) + ( lp_stMatrix->m_floatRG * lp_rgb48->G ) + ( lp_stMatrix->m_floatRB * lp_rgb48->B );
			if ( l_fR < 0 )
			{
				l_fR = 0;
			}
			l_fG = ( lp_stMatrix->m_floatGR * lp_rgb48->R ) + ( lp_stMatrix->m_floatGG * lp_rgb48->G ) + (lp_stMatrix->m_floatGB * lp_rgb48->B );
			if ( l_fG < 0 )
			{
				l_fG = 0;
			}
			l_fB = ( lp_stMatrix->m_floatBR * lp_rgb48->R ) + ( lp_stMatrix->m_floatBG * lp_rgb48->G ) + ( lp_stMatrix->m_floatBB * lp_rgb48->B );
			if ( l_fB < 0 )
			{
				l_fB = 0;
			}
			
			lp_rgb48->R = WORD( l_fR );
			lp_rgb48->G = WORD( l_fG );
			lp_rgb48->B = WORD ( l_fB );
			
			lp_rgb48++;
		}
	}
}



void CEX3FImage::HuffMakeTree( DWORD l_dwordNowNode, DWORD l_dwordCode, DWORD l_dwordSize  ) 
{
	if ( l_dwordCode == 0 )
	{
		m_dwordHuffNewNode = l_dwordNowNode + 1;
	}
	else 
	{
		m_dwordHuffNewNode++;  
		for ( DWORD i = 0; i < l_dwordSize; i++ ) 
		{
			if ( mp_dwordHuffKey[i] == l_dwordCode ) 
			{
				if ( l_dwordSize == 1024)
				{
					m_arrayHuffTree[l_dwordNowNode].m_dwordIndex = mp_dwordHuffTable[ i ]; // tabe is dwords
				}
				else
				{
					m_arrayHuffTree[l_dwordNowNode].m_dwordIndex = i; // just index
				}
				return;
			}
		}
	}
	DWORD length = ( l_dwordCode >> 27 );
	if ( length < 27 ) 
	{
		l_dwordCode = (( length + 1 ) << 27 ) | (( l_dwordCode & 0x3ffffff ) << 1 );
		m_arrayHuffTree[l_dwordNowNode].m_dwordChild[0] = ( m_dwordHuffNewNode * sizeof( HUFF_NODE )) + DWORD( m_arrayHuffTree );
		HuffMakeTree( m_dwordHuffNewNode, l_dwordCode, l_dwordSize );
		m_arrayHuffTree[l_dwordNowNode].m_dwordChild[1] = ( m_dwordHuffNewNode * sizeof( HUFF_NODE )) + DWORD( m_arrayHuffTree );
		HuffMakeTree( m_dwordHuffNewNode, l_dwordCode + 1, l_dwordSize );
	}
}

BOOL CEX3FImage::SaveTga( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;
	
	CETarga l_ceTarga;
	
	l_ceTarga.m_stHeader.imagetype = 2;
	l_ceTarga.m_stHeader.bits = 24;
	l_ceTarga.m_stHeader.height = SHORT( m_stData.m_dwordImageRows );
	l_ceTarga.m_stHeader.width = SHORT( m_stData.m_dwordImageColumns );
	
	DWORD l_dwordSize = m_stData.m_dwordImageRows * m_stData.m_dwordImageColumns * 3 ;
	l_ceTarga.m_dwordSize = l_dwordSize;// m_stData.m_dwordImageRows * m_stData.m_dwordImageColumns * 3;
		
	l_ceTarga.mp_byteImage = mp_byteSectionData;
	
	l_boolResult = l_ceTarga.Save( lp_strName );
	
	l_ceTarga.mp_byteImage = NULL; // To prevent double free
		
	
	return l_boolResult;
}


BOOL CEX3FImage::SaveTiff( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;

	
	if ( m_stData.m_dwordDataFormat != 18 )
	{

	CETiff l_ceTiff;
	if (  m_stData.m_dwordDataFormat == 6 )
	{
		l_ceTiff.m_stFirstDir.m_ifdStripByteCounts.m_dwordOffset = m_stData.m_dwordImageColumns * m_stData.m_dwordImageRows * 6 ;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[0] = 16;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[1] = 16;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[2] = 16;
	}
	else
	{
		l_ceTiff.m_stFirstDir.m_ifdStripByteCounts.m_dwordOffset = m_stData.m_dwordImageColumns * m_stData.m_dwordImageRows * 3 ;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[0] = 8;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[1] = 8;
		l_ceTiff.m_stFirstDir.m_wordBitsPerSample[2] = 8;
	}	



	l_ceTiff.m_stFirstDir.m_ifdImageWidth.m_dwordOffset = m_stData.m_dwordImageColumns;
	l_ceTiff.m_stFirstDir.m_ifdImageLength.m_dwordOffset = m_stData.m_dwordImageRows;
	l_ceTiff.m_stFirstDir.m_ifdRowsPerStrip.m_dwordOffset = m_stData.m_dwordImageRows;

	l_ceTiff.m_dwordSize = l_ceTiff.m_stFirstDir.m_ifdStripByteCounts.m_dwordOffset;

	l_ceTiff.mp_byteImage = mp_byteSectionData;

	l_boolResult = l_ceTiff.Save( lp_strName );
	
	l_ceTiff.mp_byteImage = NULL; // To prevent double free
	}
	else
	{
		// jpeg
		CEFile l_ceFile;
		
		if ( l_ceFile.Open( lp_strName, CEFile::eModeReadWrite | CEFile::eModeCreate ))
		{
			l_ceFile.Write( mp_byteSectionData, m_dwordSectionDataSize );
			l_ceFile.Close();
		}

	}
	return l_boolResult;
}

BOOL CEX3FImage::SaveBmp( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;
	
	CEBmp l_ceBmp;	
	l_ceBmp.m_stBitmapInfoHeader.biWidth = m_stData.m_dwordImageColumns;
	l_ceBmp.m_stBitmapInfoHeader.biHeight = m_stData.m_dwordImageRows;
	l_ceBmp.m_stBitmapInfoHeader.biPlanes = 1;
	l_ceBmp.m_stBitmapInfoHeader.biBitCount = 24;
	l_ceBmp.m_stBitmapInfoHeader.biCompression = BI_RGB;
	l_ceBmp.m_stBitmapInfoHeader.biSizeImage = 0;
	l_ceBmp.m_stBitmapInfoHeader.biXPelsPerMeter = 72;
	l_ceBmp.m_stBitmapInfoHeader.biYPelsPerMeter = 72;
	l_ceBmp.m_stBitmapInfoHeader.biClrUsed = 0;
	l_ceBmp.m_stBitmapInfoHeader.biClrImportant = 0;
	





	l_ceBmp.m_dwordSize =  m_dwordSectionDataSize;
	l_ceBmp.mp_byteImage = mp_byteSectionData;


	l_boolResult = l_ceBmp.Save( lp_strName );
	
	l_ceBmp.mp_byteImage = NULL; // To prevent double free
		
	return l_boolResult;
}


DWORD CEX3FImage::FindValue( DWORD (*m_dwordHistogram)[3][65536], BYTE l_byteArray /* 0-R 1-g 2-b */, DWORD l_boolLowHighAll ) // 0 - low, high = 1 , all =2
{
	DWORD l_dwordResult = 0xFFFFFFFF;
	DWORD l_dwordCnt = 0;

//	DWORD m_dwordHistogram[3][65536];
//	memcpy( m_dwordHistogram, l_dwordHistogram, ( 3 * 65536 * sizeof( DWORD )));

	//////////////////////////////////////////////
	if ( l_boolLowHighAll == 0 ) // low
	{
		l_dwordCnt = 0;
		do
		{
			if ( (*m_dwordHistogram)[l_byteArray][ l_dwordCnt ] != 0 )
			{
				l_dwordResult = l_dwordCnt;
				break;
			}
			l_dwordCnt++;
		}while( l_dwordCnt < 65536 );
	}

	//////////////////////////////////////////////
	if ( l_boolLowHighAll == 1 ) // high
	{
		l_dwordCnt = 65536;
		do
		{
			l_dwordCnt--;
			if ( (*m_dwordHistogram)[l_byteArray][ l_dwordCnt ] != 0 )
			{
				l_dwordResult = l_dwordCnt;
				break;
			}
		}while( l_dwordCnt > 0 );
	}

	//////////////////////////////////////////////
	if ( l_boolLowHighAll == 2 ) // all
	{
		l_dwordResult = 0;
		l_dwordCnt = 0;
		do
		{
			if ( (*m_dwordHistogram)[l_byteArray][ l_dwordCnt ] != 0 )
			{
				l_dwordResult++;
			}
			l_dwordCnt++;
		}while( l_dwordCnt <65536 );
	}

	return l_dwordResult;
}
