// Document modified at : Monday, December 04, 2006 05:48:04 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEMemoryBuffer.cpp: implementation of the CEMemoryBuffer class.

#include "stdafx.h"
#include "CEMemoryBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEMemoryBuffer::CEMemoryBuffer()
{
	mp_byteMemoryBuffer = NULL;
	m_dwordMemoryBufferSize = 0;
}

CEMemoryBuffer::~CEMemoryBuffer()
{
	DeleteMemory();
}

LPBYTE CEMemoryBuffer::AllocateMemory( DWORD l_dwordSize )
{
	DeleteMemory();
	mp_byteMemoryBuffer = LPBYTE( malloc( l_dwordSize ));
	if ( mp_byteMemoryBuffer != NULL )
	{
		m_dwordMemoryBufferSize = l_dwordSize;
	}
	return mp_byteMemoryBuffer;
}

void CEMemoryBuffer::DeleteMemory()
{
	if ( mp_byteMemoryBuffer != NULL )
	{
		free( mp_byteMemoryBuffer );
		mp_byteMemoryBuffer = NULL;
		m_dwordMemoryBufferSize = 0;
	}	
}