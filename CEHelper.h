// Document modified at : Tuesday, March 15, 2005 11:08:48 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEHelper.h: interface for the CEHelper class.
#pragma once

class CEHelper  
{
public:
	CEHelper();
	~CEHelper();

/*	static BOOL SearchStringInArray( CStringArray* lp_cStringsArray , CString l_csString , CString* lp_csOutput );*/
	static int MakeArrayOfLines( CStringArray* lp_csaLineArray ,  LPBYTE lp_byteText , DWORD l_dwordSize );
	static void ArrayToCombo( CComboBox* lp_ctrlComboBox ,CStringArray* lp_csaArray , CPtrArray* lp_ptrArray = NULL ,  LPCTSTR lp_strSelect = NULL );
	static void CompleteSlash( CString* lp_csString );
	static void RemoveSlash( CString* lp_csString );
	static void RemoveForwardSlash( CString* lp_csString );
	static int CountTheSymbols( LPCTSTR lp_strString, TCHAR l_charSymbol );

	static void PlayBeep();

	static BOOL GetProfileBinary( LPCTSTR lp_strSection, LPCTSTR lp_strValue, LPBYTE lp_byteData, UINT l_uintBytes );

	static LPBYTE AllocateBuffer( DWORD l_dwordSize );
	static void FreeBuffer( LPBYTE lp_byteBuffer );

	static BOOL StringToBuffer( LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize, CString* lp_mfcString );
	static BOOL StringToBuffer( LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize, LPCTSTR lp_strString );
	static BOOL BufferToString( CString* lp_mfcString, LPBYTE lp_byteBuffer, DWORD l_dwordBufferSize );
/*
	static BOOL SaveString( CEFile* lp_ceFile, CString* lp_csString );
	static BOOL LoadString( CEFile* lp_ceFile, CString* lp_csString );
*/


/*	static BOOL DeleteForceSpaces( CString* lp_csString );
	static BOOL DeleteBackwardSpaces(  CString* lp_csString );
	static BOOL CompareNonEqualStrigns( CString* lp_csSource , CString* lp_csTemplate );
	static BOOL GetStringHex( CString* lp_csString  , DWORD  l_dwordNum , BYTE l_byteSigns );// 8 by default
	static BOOL GetCurrentTimeString( CString* lp_csTime );
	static BOOL GetDateString( SYSTEMTIME* lp_stSys , CString* lp_csDate );
	static BOOL GetTimeString( SYSTEMTIME* lp_stSys , CString* lp_csTime );*/
/*	static BOOL CreateFoldersFromArray( CStringArray* lp_csaFolders );*/

	static void MakeBytesSizeString( CString* lp_csString , DWORD64 l_dword64 );
	static DWORD64 MakeDword64( DWORD l_dwordLow , DWORD l_dwordHigh );

	static DWORD LODWORD( DWORD64* lp_dword64 );
	static DWORD HIDWORD( DWORD64* lp_dword64 );

	static void DeleteForceSpaces(  CString* lp_csString );
	static void DeleteBackwardSpaces(  CString* lp_csString );
//	static BOOL CompareStringsByMask( CString* lp_csString , LPCTSTR lp_strMask , BOOL l_boolNoCase = TRUE );
	static BOOL GetHexFromText( LPCTSTR lp_strStr , DWORD l_dwordBytes , DWORD& l_dwordOutput );
	static BOOL GetTextFromHex( CString* lp_csStr , DWORD l_dwordBytes , DWORD l_dwordInput );
	
	static void WriteStringToRegistry( HKEY l_hRootKey ,  LPCTSTR lp_strSubKey , LPCTSTR lp_strValueName , LPCTSTR lp_strValue );
	static void DeleteStringFromRegistry( HKEY l_hRootKey , LPCTSTR lp_strSubKey , LPCTSTR lp_strValueName );

	static BOOL CopyTextToClipboard( LPCWSTR lp_strText, BOOL l_boolClearClipboard = TRUE );
	static BOOL ClearClipboard();

	static BOOL PathExtractFileName( CString* lp_csFilename, CString* lp_csPath );

	static void ConvertBinaryToText( LPBYTE lp_byteData, DWORD l_dwordCount, CString* lp_mfcString );
	static void ConvertTextToBinary( LPBYTE lp_byteData, DWORD l_dwordCount, CString* lp_mfcString );

	static void IpToString( CString* lp_csString, DWORD l_dwordIP );



	// Debug
	static void PN( DWORD );
	static void PrintArray(  CStringArray* lp_csString );


};

