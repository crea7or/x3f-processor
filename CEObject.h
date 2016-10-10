// Document modified at : Tuesday, May 30, 2006 03:30:15 AM , by user : Pavel Sokolov , from computer : CREA7OR
// Document modified at : Saturday, July 05, 2003 08:13:58 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEObject.h: interface for the CEObject class.
#pragma once

class CEObject  
{
public:
	CEObject();
	virtual ~CEObject();
	// Copy constructor
	CEObject& operator=(const CEObject& l_ceObject );
	CEObject( const CEObject &l_ceObject );

	BOOL CompareAlias( LPCTSTR );

	LPCTSTR GetAlias()
	{
		return m_csObjectAlias;
	};

	BOOL Save( CEFile * lp_ceFile );
	BOOL Load( CEFile * lp_ceFile );

	void SetAlias( LPCTSTR lp_strAlias )
	{
		m_csObjectAlias = lp_strAlias;
	};
	DWORD GetOptions()
	{
		return m_dwordObjectOptions;
	};
	virtual void SetOptions( const DWORD l_dwordOptions )
	{
		m_dwordObjectOptions = l_dwordOptions;
	};
	LPCTSTR GetDescription()
	{
		return m_csObjectDescription;
	};
	void SetDescription( LPCTSTR lp_strDescription )
	{
		m_csObjectDescription = lp_strDescription;
	};

	virtual int GetImage()
	{
		return m_intImage;
	};
	virtual void SetImage( const int l_intImage )
	{
		m_intImage = l_intImage;
	};

	virtual DWORD GetObjectType()
	{
		return 0;
	};
	virtual DWORD GetObjectVersion()
	{
		return 0;
	};
	virtual void SetObjectVersion( DWORD /*l_dwordObjectVersion*/ )
	{
	};

protected:

	DWORD m_dwordObjectOptions;
	CString m_csObjectAlias;
	CString m_csObjectDescription;
	int m_intImage;

};

typedef CEObject* LPOBJECT;
