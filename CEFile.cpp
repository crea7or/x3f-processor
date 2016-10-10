// Document modified at : Tuesday, July 13, 2004 06:56:33 PM , by user : Pavel Sokolov , from computer : CREA7OR
#include "stdafx.h"
#include "CEFile.h"
#include "CEFileError.h"
#include "CEHelper.h"

//#include "CEItem.h"

CEFile::CEFile( BOOL l_boolExceptions, BOOL l_boolShowErrors )
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_boolCloseOnDelete = TRUE;
	m_boolExceptions = l_boolExceptions;
	m_boolShowErrors = l_boolShowErrors;
}
/*
CEFile::CEFile( HFILE l_hFile )
{
	m_hFile = HANDLE( l_hFile );
	m_boolCloseOnDelete = FALSE;
	m_boolExceptions = TRUE;
	m_boolShowErrors = TRUE;
}
*/
CEFile& CEFile::operator=( const CEFile& l_ceEntry )
{
	m_boolCloseOnDelete = FALSE;
	m_hFile = l_ceEntry.m_hFile;
	m_boolExceptions = l_ceEntry.m_boolExceptions;
	m_boolShowErrors = l_ceEntry.m_boolShowErrors;
	return *this;
}

CEFile::CEFile( const CEFile &l_ceEntry )
{
	*this = l_ceEntry;
}

CEFile::~CEFile()
{
	if ( m_hFile != INVALID_HANDLE_VALUE && m_boolCloseOnDelete )
	{
		Close();
	}
}

BOOL CEFile::Open( LPCTSTR lp_strFileName, DWORD l_dwordOpenFlags )
{
	BOOL l_boolResult = FALSE;

	if ( m_hFile != INVALID_HANDLE_VALUE && m_boolCloseOnDelete )
	{
		Close();
	}
	m_hFile = INVALID_HANDLE_VALUE;
	m_csFileName.Empty();
	m_csFileName = lp_strFileName;
	// map read/write mode
	DWORD l_dwordAccess = 0;
	switch ( l_dwordOpenFlags & 3 )
	{
	case eModeRead:
		l_dwordAccess = GENERIC_READ;
		break;
	case eModeWrite:
		l_dwordAccess = GENERIC_WRITE;
		break;
	case eModeReadWrite:
		l_dwordAccess = GENERIC_READ | GENERIC_WRITE;
		break;
	default:
		ASSERT( FALSE );  // invalid share mode
	}
	
	// map share mode
	DWORD l_dwordShareMode = 0;
	switch ( l_dwordOpenFlags & 0x70 )    // map compatibility mode to exclusive
	{
	case eShareCompat:
	case eShareExclusive:
		l_dwordShareMode = 0;
		break;
	case eShareDenyWrite:
		l_dwordShareMode = FILE_SHARE_READ;
		break;
	case eShareDenyRead:
		l_dwordShareMode = FILE_SHARE_WRITE;
		break;
	case eShareDenyNone:
		l_dwordShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
		break;
	default:
		ASSERT( FALSE );  // invalid share mode?
	}
	
	// map modeNoInherit flag
	SECURITY_ATTRIBUTES l_saAttr;
	l_saAttr.nLength = sizeof( l_saAttr );
	l_saAttr.lpSecurityDescriptor = NULL;
	l_saAttr.bInheritHandle = ( l_dwordOpenFlags & eModeNoInherit ) == 0;
	
	// map creation flags
	DWORD l_dwordCreateFlag;
	if ( l_dwordOpenFlags & eModeCreate )
	{
		if ( l_dwordOpenFlags & eModeNoTruncate )
		{
			l_dwordCreateFlag = OPEN_ALWAYS;
		}
		else
		{
			l_dwordCreateFlag = CREATE_ALWAYS;
		}
	}
	else
	{
		l_dwordCreateFlag = OPEN_EXISTING;
	}
	// attempt file creation
	HANDLE l_hFile = ::CreateFile( LPCTSTR( m_csFileName ), l_dwordAccess, l_dwordShareMode, &l_saAttr, l_dwordCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( l_hFile != INVALID_HANDLE_VALUE )
	{
		m_hFile = l_hFile;
		m_boolCloseOnDelete = TRUE;
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorOpen;
		}
	}
	return l_boolResult;
}

BOOL CEFile::Read( LPVOID lp_voidBuffer, const DWORD l_dwordCount )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordReadFrom = 0;
	if ( l_dwordCount == 0 )
	{
		l_boolResult = TRUE;
	}
	else
	{
		if (( ::ReadFile( m_hFile, lp_voidBuffer, l_dwordCount, &l_dwordReadFrom, NULL ) > 0 ) && ( l_dwordReadFrom == l_dwordCount ))
		{	
			l_boolResult = TRUE;
		}
		else
		{
			CEFileError l_ceError( GetFileName(), m_boolShowErrors );
			if ( m_boolExceptions )
			{
				throw eErrorRead;
			}
		}
	}
	return l_boolResult;
}

BOOL CEFile::Write( const LPVOID lp_voidBuffer, const DWORD l_dwordCount )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordWritten = 0;
	if ( l_dwordCount == 0 )
	{
		l_boolResult = TRUE;
	}
	else
	{
		if ( ::WriteFile( m_hFile, lp_voidBuffer, l_dwordCount, &l_dwordWritten, NULL ) &&  ( l_dwordWritten == l_dwordCount  ))
		{
			l_boolResult = TRUE;
		}
		else
		{
			CEFileError l_ceError( GetFileName(), m_boolShowErrors );
			if ( m_boolExceptions )
			{
				throw eErrorWrite;
			}
		}
	}
	return l_boolResult;
}

BOOL CEFile::ReadString( CString* lp_mfcString )
{
	BOOL l_boolResult = FALSE;
	lp_mfcString->Empty();
	DWORD l_dwordRead = 0;
	if ( Read( &l_dwordRead, sizeof( l_dwordRead )))
	{	
		l_boolResult = TRUE;
		if ( l_dwordRead > 0 )
		{
			if ( ! Read( lp_mfcString->GetBufferSetLength( int( l_dwordRead )), l_dwordRead ))
			{
				l_boolResult = FALSE;
			}
			lp_mfcString->ReleaseBuffer( l_dwordRead );
		}
	}
	return l_boolResult;
}

BOOL CEFile::WriteString( CString* lp_mfcString )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordWrite = DWORD( lp_mfcString->GetLength());
	if ( Write( &l_dwordWrite, sizeof( l_dwordWrite )))
	{	
		l_boolResult = TRUE;
		if ( l_dwordWrite > 0 )
		{
			if ( ! Write( LPVOID( lp_mfcString->GetBuffer( l_dwordWrite )), l_dwordWrite ))
			{
				l_boolResult = FALSE;
			}
		}
	}
	return l_boolResult;
}

BOOL CEFile::SetPosition64( const DWORD64 l_dword64Position )
{
	BOOL l_boolResult = FALSE;
	DWORD64 l_dword64Move = l_dword64Position;
	DWORD l_dwordStartingPoint = FILE_BEGIN;
	LONG l_longMoveTo;
	do
	{
		if ( l_dword64Move > 0x7FFFFFF )
		{
			l_longMoveTo = 0x7FFFFFF;
		}	
		else
		{
			l_longMoveTo = LONG( l_dword64Move );
		}
		l_boolResult = Seek( l_longMoveTo, l_dwordStartingPoint );
		if ( l_boolResult )
		{
			l_dwordStartingPoint = FILE_CURRENT;
		}
		else
		{
			break;
		}
		l_dword64Move -= l_longMoveTo;
	}while( l_dword64Move != 0 );
	return l_boolResult;
}

BOOL CEFile::MovePosition64( const DWORD64 l_dword64Position )
{
	BOOL l_boolResult = FALSE;
	DWORD64 l_dword64Move = l_dword64Position;
	DWORD l_dwordStartingPoint = FILE_CURRENT;
	LONG l_longMoveTo;
	do
	{
		if ( l_dword64Move > 0x7FFFFFF )
		{
			l_longMoveTo = 0x7FFFFFF;
		}	
		else
		{
			l_longMoveTo = LONG( l_dword64Move );
		}
		l_boolResult = Seek( l_longMoveTo, l_dwordStartingPoint );
		if ( l_boolResult )
		{
			l_dwordStartingPoint = FILE_CURRENT;
		}
		else
		{
			break;
		}
		l_dword64Move -= l_longMoveTo;
	}while( l_dword64Move != 0 );
	return l_boolResult;
}




DWORD64 CEFile::GetPosition64()
{
	DWORD64 l_dword64Position = 0;
	LONG l_longHigh = 0;
	DWORD l_dwordLow;
	l_dwordLow = ::SetFilePointer(m_hFile, 0, &l_longHigh, FILE_CURRENT);
	if (( l_dwordLow == INVALID_SET_FILE_POINTER ) && ( GetLastError() != NO_ERROR ))
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorSeek;
		}
	}
	else
	{
		l_dword64Position = CEHelper::MakeDword64( l_dwordLow, l_longHigh );
	}
	return l_dword64Position;
}

BOOL CEFile::Seek( LONG l_longOffset, DWORD l_dwordFrom , LPDWORD lp_dwordNew )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordNew = ::SetFilePointer( m_hFile, l_longOffset, NULL, l_dwordFrom );
	if ( l_dwordNew != INVALID_SET_FILE_POINTER )
	{
		l_boolResult = TRUE;
		if ( lp_dwordNew != NULL )
		{
			*lp_dwordNew  = l_dwordNew;
		}
	}
	else
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorSeek;
		}
	}
	return l_boolResult;
}

BOOL CEFile::GetPosition( DWORD64* lp_dword64NewPosition )
{
	BOOL l_boolResult = FALSE;
	LONG l_longHigh = 0;
	DWORD l_dwordLow;
	l_dwordLow = ::SetFilePointer(m_hFile, 0, &l_longHigh, FILE_CURRENT);
	if (( l_dwordLow == INVALID_SET_FILE_POINTER ) && ( GetLastError() != NO_ERROR ))
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorSeek;
		}
	}
	else
	{
		*lp_dword64NewPosition = CEHelper::MakeDword64( l_dwordLow, l_longHigh );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

BOOL CEFile::Flush()
{
	BOOL l_boolResult = FALSE;
	if ( ::FlushFileBuffers( m_hFile ))
	{	
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorFlush;
		}
	}
	return l_boolResult;
}

BOOL CEFile::Close()
{
	BOOL l_boolResult = TRUE;
	if ( m_hFile != INVALID_HANDLE_VALUE )
	{
		if( ! ::CloseHandle( m_hFile ))
		{
			CEFileError l_ceError( GetFileName(), m_boolShowErrors );
			if ( m_boolExceptions )
			{
				throw eErrorClose;
			}
			l_boolResult = FALSE;
		}
		m_hFile = INVALID_HANDLE_VALUE;
		m_boolCloseOnDelete = FALSE;
		m_csFileName.Empty();
	}
	return l_boolResult;
}

DWORD64 CEFile::GetLength()
{
	DWORD64 l_dword64size = 0;
	DWORD l_dwordHi, l_dwordLo;
	l_dwordLo = ::GetFileSize( m_hFile, &l_dwordHi );
	// If we failed ... 
	if ( l_dwordLo == INVALID_FILE_SIZE && ( GetLastError()) != NO_ERROR )
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorGetSize;
		}
    }
	// End of error handler. 
	else
	{	
		l_dword64size = CEHelper::MakeDword64( l_dwordLo , l_dwordHi );
	}
	return l_dword64size;
}

DWORD64 CEFile::GetLength( LPCTSTR lp_strFileName )
{
	DWORD64 l_dword64size = 0;
	DWORD l_dwordHi = 0, l_dwordLo = 0;

	HANDLE l_hFile;
	// map modeNoInherit flag
	SECURITY_ATTRIBUTES l_saAttr;
	l_saAttr.nLength = sizeof( l_saAttr );
	l_saAttr.lpSecurityDescriptor = NULL;
	l_saAttr.bInheritHandle = 0;
	// attempt file creation
	l_hFile = ::CreateFile( lp_strFileName, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, &l_saAttr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( l_hFile != INVALID_HANDLE_VALUE )
	{
		l_dwordLo = ::GetFileSize( l_hFile, &l_dwordHi );
		::CloseHandle( l_hFile );
	}
	l_dword64size = CEHelper::MakeDword64( l_dwordLo , l_dwordHi );
	return l_dword64size;
}

BOOL CEFile::IsAccessableFor( LPCTSTR lp_strFileName, DWORD l_dwordOpenFlags )
{
	BOOL l_boolResult;
	CEFile l_ceFile;
	l_boolResult = l_ceFile.Open( lp_strFileName, l_dwordOpenFlags );
	if ( l_boolResult )
	{
		l_ceFile.Close();
	}
	return l_boolResult;
}


BOOL CEFile::IsValid()
{
	if ( m_hFile != INVALID_HANDLE_VALUE )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL CEFile::CreateFolder( LPCTSTR lp_strName )
{
	if ( CreateDirectory( lp_strName , NULL ) == FALSE )
	{
		if ( GetLastError() != ERROR_ALREADY_EXISTS )
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CEFile::SetFileAttributes( LPCTSTR lp_strName, DWORD l_dwordAttr )
{
	BOOL l_boolResult;
	l_boolResult = ::SetFileAttributes( lp_strName, l_dwordAttr );
	if ( ! l_boolResult )
	{
		CEFileError l_ceError( lp_strName, TRUE );
//		if ( m_boolExceptions )
//		{
			throw eErrorSetAttributes;
//		}
	}
	return l_boolResult;
}

BOOL CEFile::SafeEncryptFile( LPCTSTR lp_tstrName )
{
	BOOL l_boolResult = FALSE;
	HINSTANCE l_hInst = ::LoadLibrary( _T("ADVAPI32.DLL"));
	BOOL ( PASCAL *lp_fnEncryptFile )( LPCTSTR  );
	#ifdef _UNICODE
	( FARPROC& )lp_fnEncryptFile = GetProcAddress( l_hInst, "EncryptFileW");
	#else
	( FARPROC& )lp_fnEncryptFile = GetProcAddress( l_hInst, "EncryptFileA");
	#endif

	if ( lp_fnEncryptFile != NULL )
	{
		l_boolResult = lp_fnEncryptFile( lp_tstrName );
	}
	::FreeLibrary( l_hInst );
	return l_boolResult;
}

DWORD CEFile::GetFileAttributes( LPCTSTR lp_strName )
{
	DWORD l_dwordAttr = 0;
	l_dwordAttr = ::GetFileAttributes( lp_strName );
	if ( l_dwordAttr == INVALID_FILE_ATTRIBUTES )
	{
		CEFileError l_ceError( lp_strName, TRUE );
//		if ( m_boolExceptions )
//		{
			throw eErrorGetAttributes;
//		}
	}	
	return l_dwordAttr;
}

BOOL CEFile::GetFileTime( LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime )
{
	BOOL l_boolResult;
	l_boolResult = ::GetFileTime( m_hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime );
	if ( ! l_boolResult )
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorGetTime;
		}
	}
	return l_boolResult;
}

BOOL CEFile::SetFileTime( LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime )
{
	BOOL l_boolResult;
	l_boolResult = ::SetFileTime( m_hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime );
	if ( ! l_boolResult )
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorSetTime;
		}
	}
	return l_boolResult;
}

BOOL CEFile::GetStatus( WIN32_FIND_DATA* lp_stStatus )
{
	return GetStatus( m_csFileName , lp_stStatus );
}

BOOL CEFile::GetStatus( LPCTSTR lp_strFileName, WIN32_FIND_DATA* lp_stStatus )
{
	BOOL l_boolResult = FALSE;
	HANDLE l_hFind = FindFirstFile( lp_strFileName, lp_stStatus );
	if ( l_hFind != INVALID_HANDLE_VALUE )
	{
		l_boolResult = TRUE;
	}
	FindClose( l_hFind );
	return l_boolResult;
}

BOOL CEFile::IsExist( LPCTSTR lp_strName )
{
	WIN32_FIND_DATA l_stStatus;
	return ( GetStatus( lp_strName, &l_stStatus ));
}

BOOL CEFile::DeleteExist( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;
	if ( IsExist(  lp_strName ))
	{
		l_boolResult = CEFile::Remove(  lp_strName );
	}
	return l_boolResult;
}

BOOL CEFile::LockRange( DWORD l_dwordPos, DWORD l_dwordCount )
{
	BOOL l_boolResult = FALSE;
	if ( ::LockFile( m_hFile, l_dwordPos, 0, l_dwordCount, 0 ))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorLock;
		}
	}
	return l_boolResult;
}

BOOL CEFile::UnlockRange( DWORD l_dwordPos, DWORD l_dwordCount )
{
	BOOL l_boolResult = FALSE;
	if ( ::UnlockFile( m_hFile, l_dwordPos, 0, l_dwordCount, 0 ))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( GetFileName(), m_boolShowErrors );
		if ( m_boolExceptions )
		{
			throw eErrorLock;
		}
	}
	return l_boolResult;
}

BOOL CEFile::SetLength( DWORD l_dwordNewLen )
{
	BOOL l_boolResult = FALSE;
	if ( Seek( l_dwordNewLen, eFileBegin ))
	{
		if ( ::SetEndOfFile( m_hFile ))
		{
			l_boolResult = TRUE;
		}
		else
		{
			CEFileError l_ceError( GetFileName(), m_boolShowErrors );
			if ( m_boolExceptions )
			{
				throw eErrorSetSize;
			}
		}
	}
	return l_boolResult;
}


BOOL CEFile::Rename( LPCTSTR lp_strOldName, LPCTSTR lp_strNewName )
{
	BOOL l_boolResult = FALSE;
	CString l_csPathOld = lp_strOldName;
	CString l_csPathNew = lp_strNewName;
	if ( ::MoveFile( LPCTSTR( l_csPathOld ), LPCTSTR( l_csPathNew )))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( lp_strOldName, TRUE );
//		if ( m_boolExceptions )
//		{
			throw eErrorMove;
//		}
	}
	return l_boolResult;
}

BOOL CEFile::Remove( LPCTSTR lpszFileName )
{
	BOOL l_boolResult = FALSE;
//	CString l_csPath = lpszFileName;
	if( ::DeleteFile( lpszFileName))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( lpszFileName, TRUE );
//		if ( m_boolExceptions )
//		{
			throw eErrorDelete;
//		}
	}
	return l_boolResult;
}

BOOL CEFile::RemoveFolder( LPCTSTR lpszFolderName )
{
	BOOL l_boolResult = FALSE;
//	CString l_csPath = lpszFileName;
	if( ::RemoveDirectory( lpszFolderName ))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEFileError l_ceError( lpszFolderName, TRUE );
//		if ( m_boolExceptions )
//		{
			throw eErrorDelete;
//		}
	}
	return l_boolResult;
}

int CEFile::GetFilesByMask( CStringArray* lp_csaNames , LPCTSTR lp_strPath , BOOL l_boolFodlers )
{
	BOOL l_boolDir = FALSE;
    WIN32_FIND_DATA l_stFindFileData;
    HANDLE l_hHandle;
    l_hHandle =  FindFirstFile( lp_strPath , &l_stFindFileData );
    while( l_hHandle != INVALID_HANDLE_VALUE )  // First file find for enumeration
    {
		if (( l_stFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) > 0 )
		{
			l_boolDir = TRUE;
		}
		else
		{
			l_boolDir = FALSE;
		}
		if ( l_boolFodlers == l_boolDir )
		{
			if( _tcscmp( l_stFindFileData.cFileName, _T( "." )) != 0 && _tcscmp( l_stFindFileData.cFileName, _T( ".." )) != 0 ) 
			{
	            lp_csaNames->Add(  l_stFindFileData.cFileName );
			}
		}
        if ( ! FindNextFile( l_hHandle, &l_stFindFileData ))
        {
			break;
        }
    }
    FindClose( l_hHandle );
	return lp_csaNames->GetSize();
}

BOOL CEFile::GetCurrentFolder( CString* lp_csString )
{
	BOOL l_boolResult = FALSE;
	lp_csString->Empty();
	DWORD l_dwordBufferSize = ::GetCurrentDirectory( 0 , NULL );
	l_dwordBufferSize++;
	if ( ::GetCurrentDirectory( l_dwordBufferSize , lp_csString->GetBufferSetLength(  l_dwordBufferSize )))
	{
		l_boolResult = TRUE;
	}
	else
	{
		CEError l_ceError( 0xFFFFFFFF, TRUE );
	}
	lp_csString->ReleaseBuffer();
	CEHelper::CompleteSlash( lp_csString );
	return l_boolResult;
}

CString CEFile::GetCurrentFolder()
{
	CString l_csPath;
	if( ! GetCurrentFolder( &l_csPath ))
	{
		l_csPath.Empty();
	}
	return l_csPath;
}
/*
BOOL CEFile::NormalizingPath( CString* lp_csString )
{
	BOOL l_boolResult = FALSE;
	if ( lp_csString->GetLength() < 2 )
	{
		CEError l_ceError( MAKEWORD( 2 , SHARED_ERROR ));
		return l_boolResult;
	}

	lp_csString->Replace( TCHAR( 47 ), TCHAR( 92 ));
	CString l_csCurFolder;
	GetCurrentFolder( &l_csCurFolder );

	if ( CEHelper::CompareStringsByMask( lp_csString, _T( "\\\\*" )))
	{
		l_boolResult =TRUE;
	}
	if ( CEHelper::CompareStringsByMask( lp_csString, _T( "*:" )))
	{
		if ( lp_csString->GetLength() == 2 )
		{
			*lp_csString += TCHAR( 92 );
		}
		l_boolResult =TRUE;
	}
	if ( ! l_boolResult )
	{
		if ( lp_csString->GetAt( 0 ) == TCHAR( 92 ))
		{
			*lp_csString = lp_csString->Right( lp_csString->GetLength() - 1 );
		}
		*lp_csString = l_csCurFolder + LPCTSTR( *lp_csString );
		l_boolResult =TRUE;
	}
	return l_boolResult;
}
*/
BOOL CEFile::IsDriveName( LPCTSTR lp_strName )
{
	BOOL l_boolResult = FALSE;
	int l_intSize = _tcslen( lp_strName );
	if ( l_intSize == 2 )
	{
		if ( lp_strName[ 1 ] == 0x3a )
		{
			l_boolResult = TRUE;
		}
	}
	else if ( l_intSize > 4 )
	{
		if ( lp_strName[ 0 ] == 92 && lp_strName[ 1 ] == 92 ) // Shared resource
		{
			if ( CEHelper::CountTheSymbols( lp_strName, 92 ) == 3 )
			{
				l_boolResult = TRUE;
			}
		}
	}
	return l_boolResult;
}

BOOL CEFile::ChooseFolder( CString* lp_csString )
{
	BOOL l_boolResult = FALSE;

	TCHAR			m_szSelectedFolder[MAX_PATH];

	LPMALLOC		pMalloc;
	BROWSEINFO		bi;
	LPITEMIDLIST	pidl;
	memset( &m_szSelectedFolder, 0 , MAX_PATH );
	memset( &bi, 0, sizeof( bi ));

	CString l_csTitle;
	l_csTitle = "Select folder :";

	LPCTSTR lpszStartPath = NULL;

	// Gets the Shell's default allocator
	if ( ::SHGetMalloc( &pMalloc ) == NOERROR )
	{
		// Get help on BROWSEINFO struct - it's got all the bit settings.
		bi.pidlRoot = NULL;
		bi.pszDisplayName = m_szSelectedFolder;
		bi.lpszTitle = l_csTitle;
		bi.ulFlags = 0x40|BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
		bi.lpfn = BrowseCtrlCallback;
		bi.lParam = ( LPARAM )lpszStartPath;
		// This next call issues the dialog box.
		if (( pidl = ::SHBrowseForFolder( &bi )) != NULL )
		{
			if ( ::SHGetPathFromIDList( pidl, m_szSelectedFolder ))
			{ 
				// At this point pszBuffer contains the selected path
				*lp_csString = m_szSelectedFolder;
				l_boolResult = TRUE;
			} // if
			// Free the PIDL allocated by SHBrowseForFolder.
			pMalloc->Free( pidl );
		} // if
		// Release the shell's allocator.
		pMalloc->Release();
	} // if

	return l_boolResult;
} // End of SelectFolder

int __stdcall CEFile::BrowseCtrlCallback( HWND hwnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData )
{
	if ( uMsg == BFFM_INITIALIZED && lpData != NULL )
	{
		::SendMessage( hwnd, BFFM_SETSELECTION, TRUE, lpData );
	}
	else // uMsg == BFFM_SELCHANGED
	{
	}

	return 0;
} // End of BrowseCtrlCallback


BOOL CEFile::ChooseLoadFileName( CString *lp_csFolder, LPCTSTR lp_strMask )
{
	BOOL l_boolReturn = FALSE;
	CFileDialog dlg( TRUE , NULL, NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST|OFN_ENABLESIZING|OFN_NOCHANGEDIR , lp_strMask);
	if ( dlg.DoModal() == IDOK )
	{
		*lp_csFolder = dlg.GetPathName();
		l_boolReturn = TRUE;
	}
	return l_boolReturn;
}

BOOL CEFile::ChooseSaveFileName( CString *lp_csFolder, LPCTSTR lp_strMask )
{
	BOOL l_boolReturn = FALSE;
	CFileDialog dlg( FALSE , NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST|OFN_ENABLESIZING|OFN_NOCHANGEDIR , lp_strMask);
	if ( dlg.DoModal() == IDOK )
	{
		*lp_csFolder = dlg.GetPathName();
		l_boolReturn = TRUE;
	}

	return l_boolReturn;
}


/*
void CEFile::SelectFile
{
	OPENFILENAMEEX	l_stOpenFilenameEx;
	memset( &l_stOpenFilenameEx,0, sizeof( l_stOpenFilenameEx ));

	DWORD	l_dwordWinMajor = ( DWORD )( LOBYTE( LOWORD( ::GetVersion())));
	if ( l_dwordWinMajor >= 5 )
	{
		l_stOpenFilenameEx.lStructSize = sizeof( l_stOpenFilenameEx );
	}
	else
	{
		l_stOpenFilenameEx.lStructSize = sizeof( OPENFILENAME );
	}
	// Execute dialog
	if ( m_bOpenFileDialog )
	{
		bRetValue = ::GetOpenFileName( &m_ofn );
	}
	else
	{
		bRetValue = ::GetSaveFileName( &m_ofn );
	}
}*/


/*void CEFile::ReplaceBadSymbols( LPSTRING lp_csString )
{
	lp_csString->Replace( _T( 0x3A ), _T( 0x2D )); //  : -> -
	lp_csString->Replace( _T( 0x2F ), _T( 0x2D )); //  / -> -
	lp_csString->Replace( _T( 0x5C ), _T( 0x2D )); //  \ -> -
	lp_csString->Replace( _T( 0x7C ), _T( 0x2D )); //  | -> -
	lp_csString->Replace( _T( 0x3C ), _T( 0x28 )); //  < -> (
	lp_csString->Replace( _T( 0x3E ), _T( 0x28 )); //  > -> )
	lp_csString->Replace( _T( 0x22 ), _T( 0x27 )); //  " -> '
	lp_csString->Replace( _T( 0x2A ), _T( 0x2B )); //  * -> +
	lp_csString->Replace( _T( 0x3F ), _T( 0x2D )); //  ? -> - 

}*/

BOOL CEFile::IsDots( LPCTSTR lp_strName )
{
	if( _tcscmp( lp_strName , _T( "." )) != 0 && _tcscmp( lp_strName, _T( ".." )) != 0 ) 
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
/*
DWORD CEFile::IsFileAccessable( LPCSTR lp_strFileName )
{
	DWORD l_dwordResult = ERROR_SUCCESS;
	HANDLE l_hFile = ::CreateFile( lp_strFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( l_hFile != INVALID_HANDLE_VALUE ) 
	{ 
		CloseHandle( l_hFile );
	}
	else
	{
		l_dwordResult = GetLastError();
	}
	return l_dwordResult;
}

BOOL CEFile::WaitForFileRelease( LPCSTR lp_strFileName, int l_intCount )
{
	BOOL l_boolResult = FALSE;
	for ( int l_intCnt = 0 ; l_intCnt < l_intCount; l_intCnt++ )
	{
		if ( IsFileAccessable( lp_strFileName ) == ERROR_SUCCESS )
		{
			l_boolResult = TRUE;
			break;
		}
		SleepEx( 0 , TRUE );
	}
	return l_boolResult;
}*/

BOOL CEFile::CopyFileRoutine( CEFile* lp_ceFromFile, CEFile* lp_ceToFile )
{
	BOOL l_boolResult = FALSE;

	LPBYTE lp_byteBuffer;
	DWORD l_dwordBufferSize;

	DWORD64 l_dword64ReadBytes;
	DWORD64 l_dword64FileLength;
	l_dword64FileLength = lp_ceFromFile->GetLength() - lp_ceFromFile->GetPosition64();

	l_dwordBufferSize = DWORD( l_dword64FileLength );
	if ( l_dword64FileLength >  8388608 )
	{
		l_dwordBufferSize = 8388608;
	}

	lp_byteBuffer = LPBYTE( malloc( l_dwordBufferSize ));

	l_boolResult = TRUE;
	while( l_dword64FileLength != 0 )
	{
		l_dword64ReadBytes  = l_dword64FileLength;
		if ( l_dword64FileLength > l_dwordBufferSize )
		{
			l_dword64ReadBytes = l_dwordBufferSize;
		}
		if ( lp_ceFromFile->Read( lp_byteBuffer, DWORD( l_dword64ReadBytes )))
		{
			if ( lp_ceToFile->Write( lp_byteBuffer, DWORD( l_dword64ReadBytes )))
			{
				l_dword64FileLength -= l_dword64ReadBytes;
			}
			else
			{
				l_boolResult = FALSE;
				break;
			}
		}
		else
		{
			l_boolResult = FALSE;
			break;
		}
	};

	free( lp_byteBuffer );

	return l_boolResult;
}