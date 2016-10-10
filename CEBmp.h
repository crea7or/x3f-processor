// Document modified at : Tuesday, January 18, 2005 05:29:12 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEBmp.h: interface for the CEBmp class.
#pragma once

class CEBmp  
{
public:
	CEBmp();
	~CEBmp();

	BITMAPFILEHEADER m_stBitmapFileHeader;
	BITMAPINFOHEADER m_stBitmapInfoHeader;

	LPBYTE mp_byteImage;
	DWORD m_dwordSize;

	void DeleteMemory();
	BOOL Save( LPCTSTR lp_strname );

};

typedef CEBmp* LPBMP;
