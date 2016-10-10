// Document modified at : Monday, December 04, 2006 05:47:51 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEMemoryBuffer.h: interface for the CEMemoryBuffer class.

#pragma once

class CEMemoryBuffer  
{
public:
	CEMemoryBuffer();
	virtual ~CEMemoryBuffer();

	LPBYTE AllocateMemory( DWORD l_dwordSize );
	void DeleteMemory();

	LPBYTE GetMemoryBuffer()
	{
		return mp_byteMemoryBuffer;
	}
	DWORD GetMemoryBufferSize()
	{
		return m_dwordMemoryBufferSize;
	}
	
protected:

	LPBYTE mp_byteMemoryBuffer;
	DWORD m_dwordMemoryBufferSize;

};

typedef CEMemoryBuffer* LPMEMORYBUFFER;
