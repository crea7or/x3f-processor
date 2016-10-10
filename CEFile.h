// Document modified at : Sunday, June 20, 2004 02:08:22 AM , by user : Pavel Sokolov , from computer : CREA7OR
#pragma once

#define INVALID_SET_FILE_POINTER ((DWORD)-1)

class CEFile
{
public:
/*	enum CopyFlags
	{
		enNone =          0x0000,
		enOverwriteIfOld =          0x0001,
		enOverwriteIfNew =         0x0002,
		enOverwrite =         0x0003,
		enOverwriteReadOnly =         0x0004
	};*/
	enum OpenFlags
	{
	eModeRead =          0x0000,
	eModeWrite =         0x0001,
	eModeReadWrite =     0x0002,
	eShareCompat =       0x0000,
	eShareExclusive =    0x0010,
	eShareDenyWrite =    0x0020,
	eShareDenyRead =     0x0030,
	eShareDenyNone =     0x0040,
	eModeNoInherit =     0x0080,
	eModeCreate =        0x1000,
	eModeNoTruncate =    0x2000
	};
	enum SeekPosition 
	{
		eFileBegin = 0x0, 
		eFileCurrent = 0x1, 
		eFileEnd = 0x2 
	};

	enum ErrorExceptions
	{
		eErrorRead =  1,
		eErrorWrite,
		eErrorOpen,
		eErrorClose,
		eErrorSeek,
		eErrorFlush,
		eErrorGetSize,
		eErrorSetSize,
		eErrorSetAttributes,
		eErrorGetAttributes,
		eErrorSetTime,
		eErrorGetTime,
		eErrorLock,
		eErrorMove,
		eErrorDelete
	};

// Constructors
	CEFile( BOOL l_boolExceptions = FALSE , BOOL l_boolShowErrors = TRUE );
	CEFile& operator=( const CEFile& l_ceEntry );
	CEFile( const CEFile &l_ceEntry );
	virtual ~CEFile();


	virtual BOOL Open(LPCTSTR lp_strFileName, DWORD l_dwordOpenFlags );
	BOOL SeekToEnd( LPDWORD lp_dwordSeek = NULL )
	{
		return Seek( 0 , eFileEnd , lp_dwordSeek );
	}
	BOOL SeekToBegin()
	{
		return Seek( 0 , eFileBegin );
	}
	BOOL Seek(LONG l_longOffset, DWORD l_dwordFrom , LPDWORD lp_dwordNew = NULL );
	BOOL GetPosition( DWORD64* lp_dword64NewPosition );
	BOOL SetPosition64( const DWORD64 l_dword64Position );
	BOOL MovePosition64( const DWORD64 l_dword64Position );
	DWORD64 GetPosition64();

	BOOL SetLength( DWORD l_dwordNewLen );
	DWORD64 GetLength();
	BOOL GetStatus( WIN32_FIND_DATA* lp_stStatus);
	virtual BOOL Read( LPVOID lp_voidBuffer, const DWORD l_dwordCount );
	virtual BOOL Write( const LPVOID lp_voidBuffer, const DWORD l_dwordCount );

	BOOL ReadString( CString* lp_mfcString );
	BOOL WriteString( CString* lp_mfcString );

	BOOL LockRange( DWORD dwPos, DWORD dwCount );
	BOOL UnlockRange( DWORD dwPos, DWORD dwCount );
	BOOL Flush();
	BOOL Close();
	BOOL IsValid();
	LPCTSTR GetFileName()
	{
		return m_csFileName;
	};
	BOOL GetFileTime( LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime );
	BOOL SetFileTime( LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime );

// Static Operatiors
	static BOOL CopyFileRoutine( CEFile* lp_ceFromFile, CEFile* lp_ceToFile );
//	static DWORD IsFileAccessable( LPCSTR lp_strFileName );
//	static BOOL WaitForFileRelease( LPCSTR lp_strFileName, int l_intCount = 50 );

	static BOOL SetFileAttributes( LPCTSTR lp_strName, DWORD l_dwordAttr );
	static DWORD GetFileAttributes( LPCTSTR lp_strName );
	static BOOL Rename( LPCTSTR lpszOldName,	LPCTSTR lpszNewName );
	static BOOL GetCurrentFolder( CString* lp_csStrign );
	static CString GetCurrentFolder();
	static int GetFilesByMask( CStringArray* lp_csaNames , LPCTSTR lp_strPath , BOOL l_boolFolders = FALSE );
	static BOOL Remove( LPCTSTR lp_strFileName );
	static BOOL RemoveFolder( LPCTSTR lpszFolderName );
	static BOOL GetStatus( LPCTSTR lp_strFileName , WIN32_FIND_DATA* lp_stStatus );
//	static BOOL GetLength( LPCTSTR lp_strFileName , LPDWORD lp_dwordSize );
	static DWORD64 GetLength( LPCTSTR lp_strFileName );
	static BOOL IsAccessableFor( LPCTSTR lp_strFileName, DWORD l_dwordOpenFlags );
//	static DWORD64 GetLength();
	static BOOL IsExist( LPCTSTR lp_strName );
	static BOOL DeleteExist( LPCTSTR lp_strName );
	static BOOL IsDriveName( LPCTSTR lp_strName );
	static BOOL CreateFolder( LPCTSTR lp_strName );
//	static BOOL PickTheFolder( CWnd* lp_mfcWnd, CString *lp_csFolder );
	static BOOL ChooseFolder( CString* lp_csString );
	static BOOL ChooseSaveFileName( CString *lp_csFolder, LPCTSTR lp_strMask );
	static BOOL ChooseLoadFileName( CString *lp_csFolder, LPCTSTR lp_strMask );

/*	static void ReplaceBadSymbols( LPSTRING lp_csString );*/
	static BOOL IsDots( LPCTSTR lp_strName );
	static BOOL SafeEncryptFile( LPCTSTR lp_tstrName );


	struct OPENFILENAMEEX : public OPENFILENAME 
	{ 
		void*	pvReserved;
		DWORD	dwReserved;
		DWORD	FlagsEx;
	};

protected:

	HANDLE m_hFile;
	CString m_csFileName;
	BOOL m_boolCloseOnDelete;
	BOOL m_boolExceptions;
	BOOL m_boolShowErrors;

	static int __stdcall BrowseCtrlCallback( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData );


};

typedef CEFile* LPFILE;