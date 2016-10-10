// Document modified at : Saturday, February 01, 2003 07:40:42 AM , by user : Pavel Sokolov , from computer : CREA7OR
#pragma once

class CEError  
{
public:
	CEError( DWORD l_dwordError = 0xFFFFFFFF, BOOL l_booAutoShow = FALSE );
	virtual ~CEError();

	DWORD GetErrorNumber()
	{
		return m_dwordError;
	};
	LPCTSTR GetError()
	{
		return m_csError;
	};
	BOOL IsSystemError()
	{
		return m_boolSystemError;
	};
	void Complete();
	virtual void Show();

protected:

	BOOL m_boolSystemError;
	CString m_csError;
	DWORD m_dwordError;

};
