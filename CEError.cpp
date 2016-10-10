// Document modified at : Tuesday, February 24, 2004 05:02:00 AM , by user : Pavel Sokolov , from computer : CREA7OR
#include "stdafx.h"
#include "CEError.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEError::CEError( DWORD l_dwordError, BOOL l_booAutoShow )
{
	if ( l_dwordError == 0xFFFFFFFF )
	{
		Complete();
		m_boolSystemError = TRUE;
	}
	else
	{
		m_boolSystemError = FALSE;
	}
	if ( l_booAutoShow )
	{
		Show();
	}
}

CEError::~CEError()
{
}

void CEError::Complete()
{
	m_csError.Empty();
	m_dwordError = ::GetLastError();
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,  NULL, m_dwordError,  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  m_csError.GetBufferSetLength( 1024 ),  1023,  NULL );
	m_csError.ReleaseBuffer();
}

void CEError::Show()
{
	AfxMessageBox( m_csError, MB_ICONSTOP );
}