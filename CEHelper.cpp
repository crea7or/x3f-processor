// Document modified at : Wednesday, March 16, 2005 07:34:38 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEHelper.cpp: implementation of the CEHelper class.
#include "stdafx.h"
#include "CEHelper.h"
//#include <Shlobj.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR sm_tchars[ 17 ] ={ _T("0123456789ABCDEF")};

CEHelper::CEHelper()
{
}

CEHelper::~CEHelper()
{
}
/*
BOOL CEHelper::SaveString( CEFile* lp_ceFile, CString* lp_csString )
{
	BOOL l_boolResult = FALSE;

	DWORD l_dwordLength;
	l_dwordLength = DWORD( l_csString->GetLength());
	if ( lp_ceFile->Write( &l_dwordLength, sizeof( l_dwordLength )))
	{
		if ( l_dwordLength > 0 )
		{
			if ( lp_ceFile->Write( lp_csString->GetBuffer( 0 ), l_dwordLength ))
			{
				l_boolResult = TRUE;
			}
		}
		else
		{
			l_boolResult = TRUE;
		}
	}

	return l_boolResult;
}

BOOL CEHelper::LoadString( CEFile* lp_ceFile, CString* lp_csString )
{
	BOOL l_boolResult = FALSE;

	DWORD l_dwordLength;
	if ( lp_ceFile->Read(Write( &l_dwordLength, sizeof( l_dwordLength )))
	{
		if ( l_dwordLength > 0 )
		{
			if ( lp_ceFile->Write( lp_csString->GetBuffer( 0 ), l_dwordLength ))
			{
				l_boolResult = TRUE;
			}
		}
		else
		{
			l_boolResult = TRUE;
		}
	}

	return l_boolResult;
}
*/

BOOL CEHelper::StringToBuffer( LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize, CString* lp_mfcString )
{
	BOOL l_boolResult = FALSE;
	memset( lp_byteBuffer, 0 , l_dwordBufferSize );
	DWORD l_dwordLenght = lp_mfcString->GetLength();
	if ( l_dwordLenght > 0 )
	{
		if ( l_dwordLenght > l_dwordBufferSize )
		{
			l_dwordLenght = l_dwordBufferSize;
		}
		memcpy( lp_byteBuffer, lp_mfcString->GetBuffer( l_dwordLenght ), l_dwordLenght );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}


BOOL CEHelper::StringToBuffer( LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize, LPCTSTR lp_strString )
{
	BOOL l_boolResult = FALSE;
	memset( lp_byteBuffer, 0 , l_dwordBufferSize );
	DWORD l_dwordLenght = strlen( lp_strString );
	if ( l_dwordLenght > 0 )
	{
		if ( l_dwordLenght > l_dwordBufferSize )
		{
			l_dwordLenght = l_dwordBufferSize;
		}
		memcpy( lp_byteBuffer, lp_strString , l_dwordLenght );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

BOOL CEHelper::BufferToString( CString* lp_mfcString, LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize )
{
	BOOL l_boolResult = FALSE;
	lp_mfcString->Empty();
	DWORD l_dwordLenght = l_dwordBufferSize;
	LPTSTR lp_strString;
	for ( DWORD l_dwordCnt = 0; l_dwordCnt < l_dwordBufferSize; l_dwordCnt++ )
	{
		if ( lp_byteBuffer[ l_dwordCnt ] == 0 )
		{
			l_dwordLenght = l_dwordCnt;
			break;
		}
	}
	if ( l_dwordLenght > 0 )
	{
		lp_strString = lp_mfcString->GetBufferSetLength( l_dwordLenght );
		memcpy( lp_strString, lp_byteBuffer, l_dwordLenght );
		lp_mfcString->ReleaseBuffer( l_dwordLenght );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

void CEHelper::IpToString( CString* lp_csString, DWORD l_dwordIP )
{
	lp_csString->Empty();
	lp_csString->Format(_T("%d.%d.%d.%d"), LOBYTE( LOWORD( l_dwordIP )), HIBYTE( LOWORD( l_dwordIP )),LOBYTE( HIWORD( l_dwordIP )),HIBYTE( HIWORD( l_dwordIP )));
}

BOOL CEHelper::PathExtractFileName( CString* lp_csFilename, CString* lp_csPath )
{
	BOOL l_boolResult = FALSE;
	lp_csFilename->Empty();
	int l_intPosition = lp_csPath->ReverseFind( TCHAR( 92 ));
	if ( l_intPosition != -1 )
	{
		*lp_csFilename = lp_csPath->Right( lp_csPath->GetLength() - ( l_intPosition + 1 ));
		l_boolResult = TRUE;
	}
	else
	{
		*lp_csFilename = *lp_csPath;
	}
	return l_boolResult;
}

LPBYTE CEHelper::AllocateBuffer( DWORD l_dwordSize )
{
//	return LPBYTE( VirtualAlloc( NULL, l_dwordSize, MEM_COMMIT, PAGE_READWRITE ));
	return LPBYTE( malloc( l_dwordSize ));
}

void CEHelper::FreeBuffer( LPBYTE lp_byteBuffer )
{
//	VirtualFree( lp_byteBuffer, 0 , MEM_RELEASE );
	free( LPVOID( lp_byteBuffer ));
}

void CEHelper::ConvertBinaryToText( LPBYTE lp_byteData, DWORD l_dwordCount, CString* lp_mfcString ) // from binary to hex
{
//	lp_mfcString->Empty();
	BYTE l_byteDataHi, l_byteDataLow;
	TCHAR l_tcharChar;
	for ( DWORD l_dwordCnt = 0 ; l_dwordCnt < l_dwordCount; l_dwordCnt++ )
	{
		l_byteDataLow = lp_byteData[ l_dwordCnt ];
		l_byteDataHi =  BYTE ( l_byteDataLow >> 4 );
		l_byteDataLow &= 0x0F;
		l_tcharChar = sm_tchars[ l_byteDataHi ];
		*lp_mfcString += l_tcharChar;
		l_tcharChar = sm_tchars[ l_byteDataLow ];
		*lp_mfcString += l_tcharChar;		
	}
}

void CEHelper::ConvertTextToBinary( LPBYTE lp_byteData, DWORD l_dwordCount, CString* lp_mfcString ) // from text ( hex) to binary
{
	BYTE l_byteData, l_byteDataTemp = 0;
	BOOL l_boolPackSemaphore = FALSE;
	DWORD l_dwordIndex = 0;
	CString l_csHexData( *lp_mfcString );
	l_csHexData.MakeUpper();

	int l_intSize = l_dwordCount * 2;
	if ( l_csHexData.GetLength() < l_intSize )
	{
		l_intSize = l_csHexData.GetLength();
	}
	for ( int l_intCnt = 0 ; l_intCnt < l_intSize; l_intCnt++ )
	{
		l_byteData = l_csHexData.GetAt( l_intCnt );
		if ( l_byteData > 57 )
		{
			l_byteData -= 55;
		}
		else
		{
			l_byteData -= 48;
		}
		if ( l_boolPackSemaphore )
		{
			l_byteData |= l_byteDataTemp;
			lp_byteData[ l_dwordIndex ] = l_byteData;
			l_dwordIndex++;
			l_boolPackSemaphore = FALSE;
		}
		else
		{
			l_byteDataTemp = l_byteData;
			l_byteDataTemp <<= 4;
			l_boolPackSemaphore = TRUE;
		}
	}
}

//GetProcAddresses
//Argument1: hLibrary - Handle for the Library Loaded
//Argument2: lpszLibrary - Library to Load
//Argument3: nCount - Number of functions to load
//[Arguments Format]
//Argument4: Function Address - Function address we want to store
//Argument5: Function Name -  Name of the function we want
//[Repeat Format]
//
//Returns: FALSE if failure
//Returns: TRUE if successful
/*BOOL GetProcAddresses( HINSTANCE *hLibrary, LPCSTR lpszLibrary, INT nCount, ... )
{
    va_list va;
    va_start( va, nCount );

    if (( *hLibrary = LoadLibrary( lpszLibrary )) 
        != NULL )
    {
        FARPROC * lpfProcFunction = NULL;
        LPSTR lpszFuncName = NULL;
        INT nIdxCount = 0;
        while ( nIdxCount < nCount )
        {
            lpfProcFunction = va_arg( va, FARPROC* );
            lpszFuncName = va_arg( va, LPSTR );
            if (( *lpfProcFunction = 
                GetProcAddress( *hLibrary, 
                    lpszFuncName )) == NULL )
            {
                lpfProcFunction = NULL;
                return FALSE;
            }
            nIdxCount++;
        }
    }
    else
    {
        va_end( va );
        return FALSE;
    }
    va_end( va );
    return TRUE;
}
*/

int CEHelper::CountTheSymbols( LPCTSTR lp_strString, TCHAR l_charSymbol )
{
	int l_intResult = 0;
	int l_intSize = _tcslen( lp_strString );
	if ( l_intSize > 0 )
	{
		for ( int l_intCnt = 0; l_intCnt < l_intSize; l_intCnt++ )
		{
			if ( lp_strString[ l_intCnt ] == l_charSymbol )
			{
				l_intResult++;
			}
		}
	}
	return l_intResult;
}


void CEHelper::PlayBeep()
{
	// NT system check
	OSVERSIONINFO l_stOSVersionInfo;
    l_stOSVersionInfo.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
    VERIFY( GetVersionEx( &l_stOSVersionInfo ));
    if( l_stOSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        Beep( 1000, 500 );
    }
	else
	{
		for ( int l_intCnt = 0; l_intCnt < 500; l_intCnt++ )
		{
			Beep( 0 , 0 );
		}
	}
}

void CEHelper::WriteStringToRegistry( HKEY l_hRootKey ,  LPCTSTR lp_strSubKey , LPCTSTR lp_strValueName , LPCTSTR lp_strValue )
{
    HKEY l_hOpenKey = NULL;
    RegOpenKeyEx( l_hRootKey , lp_strSubKey, 0, KEY_WRITE | KEY_SET_VALUE , &l_hOpenKey );
    RegSetValueEx( l_hOpenKey, lp_strValueName , NULL, REG_SZ, LPBYTE ( lp_strValue ) , _tcslen( lp_strValue ));
	RegCloseKey( l_hOpenKey );
}

void CEHelper::DeleteStringFromRegistry( HKEY l_hRootKey , LPCTSTR lp_strSubKey , LPCTSTR lp_strValueName )
{
    HKEY l_hOpenKey = NULL;
    if ( RegOpenKeyEx( l_hRootKey , lp_strSubKey, 0, KEY_WRITE | KEY_SET_VALUE  , &l_hOpenKey ) == ERROR_SUCCESS )
	{
		RegDeleteValue( l_hOpenKey,  lp_strValueName );
	}
	RegCloseKey( l_hOpenKey );
}
/*
int CEHelper::MakeArrayOfLines( CStringArray* lp_csaLineArray ,  LPCTSTR lp_byteText , DWORD l_dwordSize )
{
	CString l_csLine;
	TCHAR l_tChar;
	l_dwordSize = ( l_dwordSize / sizeof( TCHAR ));
	DWORD l_dwordTemp = 0;

	#ifdef _UNICODE
	if (  lp_byteText[ l_dwordTemp ] != 0xFEFF )
	{
		return 0;
	}
	l_dwordTemp++;
	#endif

	for ( ; l_dwordTemp < l_dwordSize ; l_dwordTemp++ )
	{
		l_tChar = lp_byteText[ l_dwordTemp ];
		
		if (l_tChar > TCHAR( 31 ))
		{
			l_csLine+= l_tChar;
		}
		if ( l_tChar == TCHAR( 9 ))
		{
			l_csLine+= l_tChar;
		}

		if ( l_tChar == TCHAR( 10 ))
		{
			if ( ! l_csLine.IsEmpty())
			{
				lp_csaLineArray->Add( l_csLine );
				l_csLine.Empty();
			}
		}
	}
	if ( l_csLine.IsEmpty() == FALSE )
	{
		lp_csaLineArray->Add( l_csLine );
	}
	return static_cast< int >( lp_csaLineArray->GetSize());
}

*/
int CEHelper::MakeArrayOfLines( CStringArray* lp_csaLineArray ,  LPBYTE lp_byteText , DWORD l_dwordSize )
{
//	BOOL l_boolResult = FALSE;
//	lp_csaLineArray->RemoveAll();
	CString l_csLine;
	TCHAR l_tChar;
	for ( DWORD l_dwordTemp= 0 ; l_dwordTemp < l_dwordSize ; l_dwordTemp++ )
	{
		l_tChar = lp_byteText[ l_dwordTemp ];
		if ( BYTE( l_tChar ) > 31 )
		{
			l_csLine+= l_tChar;
		}
		if ( BYTE( l_tChar ) == 9 )
		{
			l_csLine+= l_tChar;
		}

		if ( l_tChar == 10 )
		{
			if ( ! l_csLine.IsEmpty())
			{
				lp_csaLineArray->Add( l_csLine );
				l_csLine.Empty();
			}
		}
	}
	if ( l_csLine.IsEmpty() == FALSE )
	{
		lp_csaLineArray->Add( l_csLine );
	}
	return static_cast< int >( lp_csaLineArray->GetSize());
}




void CEHelper::ArrayToCombo( CComboBox* lp_ctrlComboBox , CStringArray* lp_csaPaths , CPtrArray* lp_ptrArray , LPCTSTR lp_strSelect )
{
	int l_intAdded = 0;
	CString l_csIn, l_csOut;
	for ( int l_intCnt = 0;  l_intCnt < lp_csaPaths->GetSize();  l_intCnt++ )
	{
		l_intAdded = lp_ctrlComboBox->AddString( lp_csaPaths->GetAt( l_intCnt ));
		if ( lp_ptrArray != NULL )
		{
			lp_ctrlComboBox->SetItemDataPtr( l_intAdded , lp_ptrArray->GetAt( l_intCnt ));
		}
	}
	if ( lp_strSelect != NULL )
	{
		lp_ctrlComboBox->SelectString( -1, lp_strSelect );
	}
	else
	{
		lp_ctrlComboBox->SetCurSel( 0 );
	}
}

/*void CEHelper::ArrayPtrToCombo( CComboBox* lp_ctrlComboBox , CPrtArray* lp_ptrArray )
{
	int l_intAdded = 0;
	CString l_csIn, l_csOut;
	for ( int l_intCnt = 0;  l_intCnt < lp_ctrlComboBox->GetCount();  l_intCnt++ )
	{
		lp_ctrlComboBox->SetItemDataPtr( l_intCnt , lp_ptrArray->GetAt( l_intCnt ));
	}
}*/

void CEHelper::CompleteSlash( CString* lp_csString )
{
	if ( lp_csString->GetLength() > 1 )
	{
		if ( lp_csString->GetAt( lp_csString->GetLength() - 1 ) != TCHAR( 92 ))
		{
			*lp_csString += TCHAR( 92 );
		}
	}
}

void CEHelper::RemoveSlash( CString* lp_csString )
{
	if ( lp_csString->GetLength() > 1 )
	{
		if ( lp_csString->GetAt( lp_csString->GetLength() - 1 ) == TCHAR( 92 ))
		{
			lp_csString->Delete(( lp_csString->GetLength() - 1 ));
		}
	}
}

void CEHelper::RemoveForwardSlash( CString* lp_csString )
{
	if ( lp_csString->GetLength() > 1 )
	{
		if ( lp_csString->GetAt( 0 ) == TCHAR( 92 ))
		{
			lp_csString->Delete( 0 );
		}
	}
}

void CEHelper::MakeBytesSizeString( CString* lp_csString , DWORD64 l_dword64 )
{
	lp_csString->Empty();
	long double l_doubleValue = long double ( __int64( l_dword64 ));
	float l_floatValue;
	CString l_csValue, l_csType = " b";
	if ( l_doubleValue > 999999999999 )
	{
		l_doubleValue /= 1099511627776;
		l_csType = " Tb";
	}
	if ( l_doubleValue > 999999999 )
	{
		l_doubleValue /= 1073741824;
		l_csType = " Gb";
	}
	if ( l_doubleValue > 999999 )
	{
		l_doubleValue /= 1048576;
		l_csType = " Mb";
	}
	if ( l_doubleValue > 999 )
	{
		l_doubleValue /= 1024;
		l_csType = " Kb";
	}
	l_floatValue = float( l_doubleValue );
	l_csValue.Format( _T( "%f" ), l_floatValue );
	if ( l_csValue.GetLength() > 5 )
	{
		l_csValue = l_csValue.Left( 5 );
	}
	l_csValue += l_csType;
	*lp_csString = l_csValue;
}

DWORD64 CEHelper::MakeDword64( DWORD l_dwordLow , DWORD l_dwordHigh )
{
	DWORD64 l_dword64 = l_dwordHigh;
	l_dword64 = l_dword64 << 32;
	l_dword64 |= l_dwordLow;
	return l_dword64;
}

DWORD CEHelper::LODWORD( DWORD64* lp_dword64 )
{
	LPDWORD lp_dword = LPDWORD( lp_dword64 );
	return lp_dword[ 1 ];
}

DWORD CEHelper::HIDWORD( DWORD64* lp_dword64 )
{
	LPDWORD lp_dword = LPDWORD( lp_dword64 );
	return lp_dword[ 0 ];
}

BOOL CEHelper::GetHexFromText( LPCTSTR lp_tstrStr , DWORD l_dwordBytes , DWORD& l_dwordOutput )
{
	BYTE l_byteChar;
	l_dwordOutput = 0;
	DWORD l_dwordMult = 0x10;
	l_dwordMult <<= (( l_dwordBytes - 1 ) * 8 );
	CHAR l_charBuffer[ 32 ];
	CharToOemBuff( lp_tstrStr , l_charBuffer, ( l_dwordBytes * 2 * sizeof( TCHAR )));
	DWORD l_dwordOffset = 0;
	do
	{
		l_byteChar = l_charBuffer[ l_dwordOffset ];
		if (( l_byteChar < 48 ) || ( l_byteChar > 102 ) || (( l_byteChar > 57 ) && ( l_byteChar < 65 )) || (( l_byteChar > 70 ) && ( l_byteChar < 97 )) )
		{
			return FALSE;
		}

		 l_byteChar -= 48;
		if (  l_byteChar > 9 ) 
		{
			 l_byteChar &= ( ~32 );
			 l_byteChar -= 7;
		}
		l_dwordOutput = l_dwordOutput + (  l_byteChar * l_dwordMult );
		l_dwordMult >>= 4;
		l_dwordOffset++;
	}while ( l_dwordMult > 0 );
	return TRUE;
}

BOOL CEHelper::GetTextFromHex( CString* lp_csStr , DWORD l_dwordBytes , DWORD l_dwordInput )
{
	BYTE l_byteChar;
	DWORD l_dwordValue, l_dwordMask = 0xF0;
	lp_csStr->Empty();
	l_dwordBytes <<= 1;
	l_dwordMask <<= (( l_dwordBytes - 2 ) * 4 );
	for ( ; l_dwordBytes > 0 ; l_dwordBytes-- )
	{
		l_dwordValue = l_dwordInput & l_dwordMask;
		l_dwordValue >>= (( l_dwordBytes - 1 ) * 4 );
		l_byteChar = LOBYTE( l_dwordValue );
		l_byteChar += 48;
		if ( l_byteChar > 57 )
		{
			l_byteChar += 7;
		}
		lp_csStr->operator +=( TCHAR( l_byteChar ));
		l_dwordMask >>= 0x04;
	}
	return TRUE;
}

void CEHelper::PN( DWORD l_dwordNumber )
{
	CString l_csString;
	l_csString.Format( _T( "%d" ), l_dwordNumber );
	AfxMessageBox( l_csString );
}

void CEHelper::PrintArray(  CStringArray* lp_csString )
{
	CString l_csString;
	for ( int l_intCnt = 0 ; l_intCnt < lp_csString->GetSize(); l_intCnt++ )
	{
		l_csString += lp_csString->GetAt( l_intCnt );
		l_csString += "\r\n";
	}
	AfxMessageBox( l_csString );
}


/*
BOOL CEHelper::SearchStringInArray( CStringArray* lp_cStringsArray , CString l_csString , CString* lp_csOutput )
{
	BOOL l_boolResult = FALSE;
	CString l_csTemp;
	DWORD l_dwordSizeSrc = l_csString.GetLength();
	for ( DWORD l_dwordCnt = 0 ; l_dwordCnt < DWORD( lp_cStringsArray->GetSize()) ; l_dwordCnt++ )
	{
		l_csTemp = lp_cStringsArray->GetAt( l_dwordCnt );
		if ( DWORD( l_csTemp.GetLength()) >= l_dwordSizeSrc )
		{
			*lp_csOutput = LPCSTR( l_csTemp );
			l_csTemp = l_csTemp.Mid( 0 , l_dwordSizeSrc );
			if ( l_csTemp.CompareNoCase( l_csString ) == 0 )
			{
				*lp_csOutput = lp_csOutput->Mid( l_dwordSizeSrc , ( lp_csOutput->GetLength() - l_dwordSizeSrc ));
				if ( lp_csOutput->GetLength() > 0 )
				{
					l_boolResult = TRUE;
					break;
				}
			}
		}
	}
	return l_boolResult;
}

BOOL CEHelper::GetStringHex( CString* lp_csString  , DWORD  l_dwordNum , BYTE l_byteSigns ) // 8 by default
{
	BOOL l_boolResult = FALSE;
	BYTE l_byteTemp;
	lp_csString->Empty();
	for ( BYTE l_byteMakeSigns = 0; l_byteMakeSigns < l_byteSigns; l_byteMakeSigns++ )
	{
		
		l_byteTemp = BYTE( l_dwordNum & 0x0F );
		l_byteTemp += 48;
		if ( l_byteTemp > 57 )
		{
			l_byteTemp+= 7;
		}
		lp_csString->Insert( 0 , TCHAR( l_byteTemp ));
		l_dwordNum = l_dwordNum >> 0x04;
	}
	return l_boolResult;
}


BOOL CEHelper::CreateFoldersFromArray( CStringArray* lp_csaFolders )
{
	BOOL l_boolResult = TRUE;
	CString l_csFolder;
	for ( int l_intCnt = 0 ; l_intCnt < lp_csaFolders->GetSize(); l_intCnt++ )
	{
		if ( CreateDirectory( lp_csaFolders->GetAt( l_intCnt ) , NULL ) == 0 )
		{
			if ( GetLastError() != ERROR_ALREADY_EXISTS )
			{
				l_boolResult = FALSE;
			}
		}
	}
	return l_boolResult;
}
*/

/*BOOL CEHelper::IsValidObject( LPVOID lp_voidObject )
{
	BOOL l_boolResult = FALSE;
	try
	{
		const type_info& l_typeInfo = typeid( lp_voidObject );
		l_boolResult = TRUE;
	}
	catch( ... )
	{
	}
	return l_boolResult;
}*/
/*
BOOL CEHelper::CompareStringsByMask( CString* lp_csString , LPCTSTR lp_strMask, BOOL l_boolNoCase )
{
	BOOL l_boolResult = FALSE;
	BYTE l_byteCharSrc, l_byteMask;

	DWORD l_dwordLengthSrc = lp_csString->GetLength();
	DWORD l_dwordLengthMask = DWORD( strlen( lp_strMask ));
	if ( l_dwordLengthSrc >= l_dwordLengthMask )
	{
		l_dwordLengthSrc = l_dwordLengthMask ;
	}
	else
	{
		return l_boolResult;
	}
	for ( DWORD l_dwordIter = 0; l_dwordIter < l_dwordLengthSrc ; l_dwordIter++ )
	{
		l_boolResult = FALSE;
		l_byteCharSrc = lp_csString->GetAt( l_dwordIter );
		if ( lp_strMask[ l_dwordIter ]  == 42 )
		{
			l_boolResult = TRUE;
			continue;
		}
		if ( lp_strMask[ l_dwordIter ]  == 35 )
		{
			if ( l_byteCharSrc < 48 || l_byteCharSrc > 57 )
			{
				break;
			}
			else
			{
				l_boolResult = TRUE;
				continue;
			}
		}
		if ( l_boolNoCase )
		{
			l_byteMask = BYTE ( lp_strMask[ l_dwordIter ] & 32 );
			l_byteCharSrc |= l_byteMask;
		}
		if ( l_byteCharSrc != lp_strMask[ l_dwordIter ] )
		{
			break;
		}

		l_boolResult = TRUE;
	}
	return l_boolResult;
}
*/
void CEHelper::DeleteForceSpaces(  CString* lp_csString )
{
	while ( lp_csString->GetLength() > 0 )
	{
		if ( lp_csString->GetAt( 0 ) == 32 )
		{
			lp_csString->Delete( 0 );
		}
		else
		{
			break;
		}
	};
}

void CEHelper::DeleteBackwardSpaces(  CString* lp_csString )
{
	int l_intCnt = lp_csString->GetLength();
	while ( l_intCnt > 0 )
	{
		if ( lp_csString->GetAt( l_intCnt ) == 32 )
		{
			lp_csString->Delete( l_intCnt );
			l_intCnt--;
		}
		else
		{
			break;
		}
	};
}


BOOL CEHelper::GetProfileBinary( LPCTSTR lp_strSection, LPCTSTR lp_strValue, LPBYTE lp_byteData, UINT l_uintBytes )
{
	BOOL l_boolResult = FALSE;
	UINT	l_uintAllocatedSize;
	LPBYTE	lp_byteAllocatedBuffer;
	if ( AfxGetApp()->GetProfileBinary( lp_strSection , lp_strValue , &lp_byteAllocatedBuffer , &l_uintAllocatedSize ) == TRUE )
	{
		if ( l_uintAllocatedSize > 0 )
		{
			if ( l_uintAllocatedSize > l_uintBytes )
			{
				l_uintAllocatedSize = l_uintBytes;
			}
			memcpy( LPVOID( lp_byteData ), lp_byteAllocatedBuffer , l_uintAllocatedSize );
			delete [] lp_byteAllocatedBuffer;
			l_boolResult = TRUE;
		}
	}
	return l_boolResult;
}

BOOL CEHelper::CopyTextToClipboard( LPCWSTR lp_wstrText, BOOL l_boolClearClipboard )
{
	BOOL l_boolResult = FALSE;
	if ( l_boolClearClipboard )
	{
		ClearClipboard();
	}
	LPWSTR lp_wstrString;
	int l_intString = wcslen( lp_wstrText );
	if ( l_intString > 0 )
	{
		if ( OpenClipboard( NULL ))
		{
			HGLOBAL l_hglbCopy;
			l_hglbCopy = GlobalAlloc( GMEM_MOVEABLE, ( l_intString + 1 ) * sizeof( WCHAR )); 
			if ( l_hglbCopy != NULL ) 
			{ 
				// Lock the handle and copy the text to the buffer. 
				lp_wstrString = LPWSTR( GlobalLock( l_hglbCopy )); 
				memcpy( lp_wstrString, lp_wstrText, l_intString * sizeof( TCHAR )); 
				lp_wstrString[l_intString] = ( TCHAR ) 0;    // null character 
				GlobalUnlock( l_hglbCopy ); 
				// Place the handle on the clipboard. 
				SetClipboardData( CF_TEXT, l_hglbCopy );
				l_boolResult = TRUE;
			}
			CloseClipboard(); 
		}
	}
	return l_boolResult;
}

BOOL CEHelper::ClearClipboard()
{
	BOOL l_boolResult = FALSE;
	if ( OpenClipboard( NULL ))
	{
		if ( EmptyClipboard())
		{
			l_boolResult = TRUE;
		}
		CloseClipboard();
	}
	return l_boolResult;
}

/*
BOOL CEHelper::CompareNonEqualStrigns( CString* lp_csSource , CString* lp_csTemplate )
{
	BOOL l_boolResult = FALSE;
	CString l_csName;
	int l_intTemplate = lp_csTemplate->GetLength();
	int l_intSource = lp_csSource->GetLength();
	if ( l_intSource >= l_intTemplate && l_intTemplate > 0 )
	{
		l_csName = lp_csSource->Mid( 0 , l_intTemplate );
		if ( l_csName.CompareNoCase( *lp_csTemplate ) == 0 )
		{
			l_boolResult = TRUE;
		}
	}
	return l_boolResult;
}

BOOL CEHelper::GetCurrentTimeString( CString* lp_csTime )
{
	SYSTEMTIME l_stSysTime;
	GetSystemTime( &l_stSysTime );
	CString l_csDate, l_csTime;
	GetDateString( &l_stSysTime , &l_csDate );
	GetTimeString( &l_stSysTime , &l_csTime );
	lp_csTime->Format( "%s %s",  l_csDate , l_csTime );
	return TRUE;
}

BOOL CEHelper::GetDateString( SYSTEMTIME* lp_stSys , CString* lp_csDate )
{ //"dd MMMM yyyy" 
	GetDateFormat( LOCALE_SYSTEM_DEFAULT , LOCALE_NOUSEROVERRIDE  | DATE_LONGDATE , lp_stSys , 0, lp_csDate->GetBufferSetLength( 256 ) , 256 );
	lp_csDate->ReleaseBuffer();
	return TRUE;
}

BOOL CEHelper::GetTimeString( SYSTEMTIME* lp_stSys , CString* lp_csTime )
{ // "HH':'mm':'ss tt"
	GetTimeFormat( LOCALE_SYSTEM_DEFAULT , LOCALE_NOUSEROVERRIDE  , lp_stSys , 0 , lp_csTime->GetBufferSetLength( 256 ) , 256 );
	lp_csTime->ReleaseBuffer();
	return TRUE;
}
*/
