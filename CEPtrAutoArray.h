// Document modified at : Saturday, March 06, 2004 03:00:05 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEOArray.h: interface for the CEOArray class.
#pragma once

#include "CEPtrArray.h"

template<class TYPE> 
class CEPtrAutoArray : public CEPtrArray< TYPE >
{
public:
	CEPtrAutoArray()
	{
	};
	virtual ~CEPtrAutoArray()
	{
		SelfRemoveAll();
	};
	const TYPE& operator[]( DWORD l_dwordIndex ) const
	{
		ASSERT( 0 <= l_dwordIndex && l_dwordIndex < GetSize());
		return ( GetData()[l_dwordIndex] );
	};
	const TYPE& GetAt( DWORD l_dwordIndex ) const
	{
		ASSERT( 0 <= l_dwordIndex && l_dwordIndex < GetSize());
		return ( GetData()[l_dwordIndex] );
	};
	TYPE& operator[]( DWORD l_dwordIndex )
	{
		ASSERT( 0 <= l_dwordIndex && l_dwordIndex < GetSize());
		return ( GetData()[l_dwordIndex] );
	};	
	void SelfRemoveAt( const DWORD nIndex )
	{
		if ( GetSize() > nIndex )
		{
			delete TYPE( GetAt( nIndex ));
			RemoveAt( nIndex );
		}
	};
	void SelfRemoveAll()
	{
		while( GetSize() > 0 )
		{
			SelfRemoveAt( 0 );
		};
	};
	DWORD Search( const TYPE l_typeType )
	{
		for ( DWORD l_dwordCnt = 0; l_dwordCnt < GetSize(); l_dwordCnt++ )
		{
			if ( GetAt( l_dwordCnt ) == l_typeType )
			{
				return l_dwordCnt;
			}
		}
		return DWORD( -1 );
	};
};
