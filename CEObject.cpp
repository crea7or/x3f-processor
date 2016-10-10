// Document modified at : Tuesday, May 30, 2006 03:31:24 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEObject.cpp: implementation of the CEObject class.
#include "stdafx.h"
#include "CEObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEObject::CEObject()
{
	SetOptions( 0 );
}

CEObject::~CEObject()
{

}

CEObject& CEObject::operator=(const CEObject& l_ceObject )
{
	m_dwordObjectOptions = l_ceObject.m_dwordObjectOptions;
	m_csObjectAlias = l_ceObject.m_csObjectAlias;
	m_csObjectDescription = l_ceObject.m_csObjectDescription;
	m_intImage = l_ceObject.m_intImage;

	return *this;
}

CEObject::CEObject( const CEObject &l_ceObject ) // copy
{ 
	*this = l_ceObject;
}

BOOL CEObject::CompareAlias( LPCTSTR lp_strAlias )
{
	BOOL l_boolResult = FALSE;
	if ( m_csObjectAlias.CompareNoCase( lp_strAlias ) == 0 )
	{
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

BOOL CEObject::Save( CEFile * lp_ceFile )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordVersion = GetObjectVersion();
	DWORD l_dwordType = GetObjectType();
	
	if ( lp_ceFile->Write( &l_dwordType, sizeof( l_dwordType )))
	{
		if ( lp_ceFile->Write( &l_dwordVersion, sizeof( l_dwordVersion )))
		{
			if ( lp_ceFile->WriteString( &m_csObjectAlias ))
			{
				if ( lp_ceFile->WriteString( &m_csObjectDescription ))
				{
					l_boolResult = lp_ceFile->Write( &m_dwordObjectOptions, sizeof( m_dwordObjectOptions ));
				}
			}
		}
	}
	return l_boolResult;
}

BOOL CEObject::Load( CEFile * lp_ceFile )
{
	BOOL l_boolResult = FALSE;
	DWORD l_dwordVersion, l_dwordType;

	 if ( lp_ceFile->Read( &l_dwordType, sizeof( l_dwordType )))
	{
		if ( lp_ceFile->Read( &l_dwordVersion, sizeof( l_dwordVersion )))
		{
			SetObjectVersion( l_dwordVersion );

			if ( lp_ceFile->ReadString( &m_csObjectAlias ))
			{
				if ( lp_ceFile->ReadString( &m_csObjectDescription ))
				{
					l_boolResult = lp_ceFile->Read( &m_dwordObjectOptions, sizeof( m_dwordObjectOptions ));
				}
			}
		}
	}
	return l_boolResult;
}
