// Document modified at : Wednesday, March 07, 2007 02:13:25 PM , by user : Pavel Sokolov , from computer : CREA7OR
#pragma once


#ifdef new
#undef new
#define _REDEF_NEW
#endif

#ifndef _INC_NEW
#include <new.h>
#endif

#ifdef _DEBUG
#define ASSERT_VALID_CEZEO( lp_ptrObject ) lp_ptrObject->AssertValid();
#else
#define ASSERT_VALID_CEZEO( lp_ptrObject )
#endif


template<class TYPE>
inline void ConstructElements( TYPE* pElements, DWORD nCount )
{
	ASSERT( nCount == 0 || AfxIsValidAddress( pElements, nCount * sizeof( TYPE )));
	
	// first do bit-wise zero initialization
	memset(( void* )pElements, 0, nCount * sizeof( TYPE ));
	
	// then call the constructor( s )
	for ( ; nCount--; pElements++ )
	{
		::new(( void* )pElements ) TYPE;
	}
}

template<class TYPE>
inline void DestructElements( TYPE* pElements, DWORD nCount )
{
	ASSERT( nCount == 0 || AfxIsValidAddress( pElements, nCount * sizeof( TYPE )));
	
	// call the destructor( s )
	for ( ; nCount--; pElements++ )
	{
		pElements->~TYPE();
	}
}

template<class TYPE>
inline void CopyElements( TYPE* pDest, const TYPE* pSrc, DWORD nCount )
{
	ASSERT( nCount == 0 || AfxIsValidAddress( pDest, nCount * sizeof( TYPE )));
	ASSERT( nCount == 0 || AfxIsValidAddress( pSrc, nCount * sizeof( TYPE )));
	
	// default is element-copy using assignment
	while ( nCount-- )
	{
		*pDest++ = *pSrc++;
	}
}

template<class TYPE>
BOOL CompareElements( const TYPE* pElement1, const TYPE* pElement2 )
{
	ASSERT( AfxIsValidAddress( pElement1, sizeof( TYPE ), FALSE ));
	ASSERT( AfxIsValidAddress( pElement2, sizeof( TYPE ), FALSE ));
	
	return *pElement1 == *pElement2;
}

template<class TYPE>
class CEPtrArray
{
public:
	// Construction
	CEPtrArray();
	virtual ~CEPtrArray();
	
	// Attributes
	DWORD GetSize() const;
	DWORD GetUpperBound() const;
	void SetSize( DWORD nNewSize, DWORD nGrowBy = -1 );
	
	// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();
	
	// Accessing elements
	TYPE GetAt( DWORD nIndex ) const;
	void SetAt( DWORD nIndex, TYPE newElement );
	TYPE& ElementAt( DWORD nIndex );
	
	// Direct Access to the element data ( may return NULL )
	const TYPE* GetData() const;
	TYPE* GetData();
	
	// Potentially growing the array
	void SetAtGrow( DWORD nIndex, TYPE newElement );
	DWORD Add( TYPE newElement );
	DWORD Append( const CEPtrArray& src );
	void Copy( const CEPtrArray& src );
	
	// overloaded operator helpers
	TYPE operator[]( DWORD nIndex ) const;
	TYPE& operator[]( DWORD nIndex );
	
	// Operations that move elements around
	void InsertAt( DWORD nIndex, TYPE newElement, DWORD nCount = 1 );
	void RemoveAt( DWORD nIndex, DWORD nCount = 1 );
	void InsertAt( DWORD nStartIndex, CEPtrArray* pNewArray );
	
	// Implementation
protected:

#ifdef _DEBUG
	void AssertValid() const;
#endif
	
	TYPE* m_pData;	 // the actual array of data
	DWORD m_nSize;	   // # of elements ( upperBound - 1 )
	DWORD m_nMaxSize;  // max allocated
	DWORD m_nGrowBy;   // grow amount
	
};

/////////////////////////////////////////////////////////////////////////////
// CEPtrArray<TYPE> inline functions

template<class TYPE>
inline DWORD CEPtrArray<TYPE>::GetSize() const
{ 
	return m_nSize; 
}
template<class TYPE>
inline DWORD CEPtrArray<TYPE>::GetUpperBound() const
{
	return m_nSize-1;
}
template<class TYPE>
inline void CEPtrArray<TYPE>::RemoveAll()
{ 
	SetSize( 0, DWORD( -1 )); 
}
template<class TYPE>
inline TYPE CEPtrArray<TYPE>::GetAt( DWORD nIndex ) const
{ 
	ASSERT( nIndex >= 0 && nIndex < m_nSize );
	return m_pData[nIndex]; 
}
template<class TYPE>
inline void CEPtrArray<TYPE>::SetAt( DWORD nIndex, TYPE newElement )
{ 
	ASSERT( nIndex >= 0 && nIndex < m_nSize );
	m_pData[nIndex] = newElement; 
}
template<class TYPE>
inline TYPE& CEPtrArray<TYPE>::ElementAt( DWORD nIndex )
{ 
	ASSERT( nIndex >= 0 && nIndex < m_nSize );
	return m_pData[nIndex]; 
}
template<class TYPE>
inline const TYPE* CEPtrArray<TYPE>::GetData() const
{
	return ( const TYPE* )m_pData; 
}
template<class TYPE>
inline TYPE* CEPtrArray<TYPE>::GetData()
{ 
	return ( TYPE* )m_pData; 
}
template<class TYPE>
inline DWORD CEPtrArray<TYPE>::Add( TYPE newElement )
{ 
	DWORD nIndex = m_nSize;
	SetAtGrow( nIndex, newElement );
	return nIndex; 
}
template<class TYPE>
inline TYPE CEPtrArray<TYPE>::operator[]( DWORD nIndex ) const
{ 
	return GetAt( nIndex );
}
template<class TYPE>
inline TYPE& CEPtrArray<TYPE>::operator[]( DWORD nIndex )
{ 
	return ElementAt( nIndex );
}

/////////////////////////////////////////////////////////////////////////////
// CEPtrArray<TYPE> out-of-line functions

template<class TYPE>
CEPtrArray<TYPE>::CEPtrArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE>
CEPtrArray<TYPE>::~CEPtrArray()
{
	ASSERT_VALID_CEZEO( this );
	
	if ( m_pData != NULL )
	{
		DestructElements<TYPE>( m_pData, m_nSize );
		delete[] ( BYTE* )m_pData;
	}
}

template<class TYPE>
void CEPtrArray<TYPE>::SetSize( DWORD nNewSize, DWORD nGrowBy )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( nNewSize >= 0 );
	
	if ( nGrowBy != -1 )
		m_nGrowBy = nGrowBy;  // set new size
	
	if ( nNewSize == 0 )
	{
		// shrink to nothing
		if ( m_pData != NULL )
		{
			DestructElements<TYPE>( m_pData, m_nSize );
			delete[] ( BYTE* )m_pData;
			m_pData = NULL;
		}
		m_nSize = m_nMaxSize = 0;
	}
	else if ( m_pData == NULL )
	{
		// create one with exact size
		m_pData = ( TYPE* ) new BYTE[nNewSize * sizeof( TYPE )];
		ConstructElements<TYPE>( m_pData, nNewSize );
		m_nSize = m_nMaxSize = nNewSize;
	}
	else if ( nNewSize <= m_nMaxSize )
	{
		// it fits
		if ( nNewSize > m_nSize )
		{
			// initialize the new elements
			ConstructElements<TYPE>( &m_pData[m_nSize], nNewSize-m_nSize );
		}
		else if ( m_nSize > nNewSize )
		{
			// destroy the old elements
			DestructElements<TYPE>( &m_pData[nNewSize], m_nSize-nNewSize );
		}
		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		DWORD nGrowBy = m_nGrowBy;
		if ( nGrowBy == 0 )
		{
			// heuristically determine growth when nGrowBy == 0
			//	( this avoids heap fragmentation in many situations )
			nGrowBy = m_nSize / 8;
			nGrowBy = ( nGrowBy < 4 ) ? 4 : (( nGrowBy > 1024 ) ? 1024 : nGrowBy );
		}
		DWORD nNewMax;
		if ( nNewSize < m_nMaxSize + nGrowBy )
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush
		
		ASSERT( nNewMax >= m_nMaxSize );  // no wrap around
		TYPE* pNewData = ( TYPE* ) new BYTE[nNewMax * sizeof( TYPE )];
		
		// copy new data from old
		memcpy( pNewData, m_pData, m_nSize * sizeof( TYPE ));
		
		// construct remaining elements
		ASSERT( nNewSize > m_nSize );
		ConstructElements<TYPE>( &pNewData[m_nSize], nNewSize-m_nSize );
		
		// get rid of old stuff ( note: no destructors called )
		delete[] ( BYTE* )m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

template<class TYPE>
DWORD CEPtrArray<TYPE>::Append( const CEPtrArray& src )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( this != &src );   // cannot append to itself
	
	DWORD nOldSize = m_nSize;
	SetSize( m_nSize + src.m_nSize );
	CopyElements<TYPE>( m_pData + nOldSize, src.m_pData, src.m_nSize );
	return nOldSize;
}

template<class TYPE>
void CEPtrArray<TYPE>::Copy( const CEPtrArray& src )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( this != &src );   // cannot append to itself
	
	SetSize( src.m_nSize );
	CopyElements<TYPE>( m_pData, src.m_pData, src.m_nSize );
}

template<class TYPE>
void CEPtrArray<TYPE>::FreeExtra()
{
	ASSERT_VALID_CEZEO( this );
	
	if ( m_nSize != m_nMaxSize )
	{
		// shrink to desired size
		TYPE* pNewData = NULL;
		if ( m_nSize != 0 )
		{
			pNewData = ( TYPE* ) new BYTE[m_nSize * sizeof( TYPE )];
			// copy new data from old
			memcpy( pNewData, m_pData, m_nSize * sizeof( TYPE ));
		}
		
		// get rid of old stuff ( note: no destructors called )
		delete[] ( BYTE* )m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template<class TYPE>
void CEPtrArray<TYPE>::SetAtGrow( DWORD nIndex, TYPE newElement )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( nIndex >= 0 );
	
	if ( nIndex >= m_nSize )
		SetSize( nIndex+1, DWORD( -1 ));
	m_pData[nIndex] = newElement;
}

template<class TYPE>
void CEPtrArray<TYPE>::InsertAt( DWORD nIndex, TYPE newElement, DWORD nCount /*=1*/ )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( nIndex >= 0 );	  // will expand to meet need
	ASSERT( nCount > 0 );	  // zero or negative size not allowed
	
	if ( nIndex >= m_nSize )
	{
		// adding after the end of the array
		SetSize( nIndex + nCount, DWORD( -1 ));   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		DWORD nOldSize = m_nSize;
		SetSize( m_nSize + nCount, DWORD( -1 ));  // grow it to new size
		// destroy DWORDial data before copying over it
		DestructElements<TYPE>( &m_pData[nOldSize], nCount );
		// shift old data up to fill gap
		memmove( &m_pData[nIndex+nCount], &m_pData[nIndex], ( nOldSize-nIndex ) * sizeof( TYPE ));
		// re-init slots we copied from
		ConstructElements<TYPE>( &m_pData[nIndex], nCount );
	}
	
	// insert new value in the gap
	ASSERT( nIndex + nCount <= m_nSize );
	while ( nCount-- )
	{
		m_pData[nIndex++] = newElement;
	}
}

template<class TYPE>
void CEPtrArray<TYPE>::RemoveAt( DWORD nIndex, DWORD nCount )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( nIndex >= 0 );
	ASSERT( nCount >= 0 );
	ASSERT( nIndex + nCount <= m_nSize );
	
	// just remove a range
	DWORD nMoveCount = m_nSize - ( nIndex + nCount );
	DestructElements<TYPE>( &m_pData[nIndex], nCount );
	if ( nMoveCount )
	{
		memmove( &m_pData[nIndex], &m_pData[nIndex + nCount], nMoveCount * sizeof( TYPE ));
	}
	m_nSize -= nCount;
}

template<class TYPE>
void CEPtrArray<TYPE>::InsertAt( DWORD nStartIndex, CEPtrArray* pNewArray )
{
	ASSERT_VALID_CEZEO( this );
	ASSERT( pNewArray != NULL );
	ASSERT_VALID_CEZEO( pNewArray );
	ASSERT( nStartIndex >= 0 );
	
	if ( pNewArray->GetSize() > 0 )
	{
		InsertAt( nStartIndex, pNewArray->GetAt( 0 ), pNewArray->GetSize());
		for ( DWORD i = 0; i < pNewArray->GetSize(); i++ )
		{
			SetAt( nStartIndex + i, pNewArray->GetAt( i ));
		}
	}
}


#ifdef _DEBUG

template<class TYPE>
void CEPtrArray<TYPE>::AssertValid() const
{
	if ( m_pData == NULL )
	{
		ASSERT( m_nSize == 0 );
		ASSERT( m_nMaxSize == 0 );
	}
	else
	{
		ASSERT( m_nSize >= 0 );
		ASSERT( m_nMaxSize >= 0 );
		ASSERT( m_nSize <= m_nMaxSize );
	}
}
#endif //_DEBUG

