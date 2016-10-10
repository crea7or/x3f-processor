// Document modified at : Tuesday, January 18, 2005 05:20:51 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CETarga.h: interface for the CETarga class.
#pragma once

class CETarga  
{
public:
	CETarga();
	~CETarga();

#pragma pack ( 1 )
	struct TGA_HEADER
	{
	    BYTE  identsize;          // size of ID field that follows 18 byte header (0 usually)
	    BYTE  colourmaptype;      // type of colour map 0=none, 1=has palette
	    BYTE  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
	    WORD colourmapstart;     // first colour map entry in palette
	    WORD colourmaplength;    // number of colours in palette
	    BYTE  colourmapbits;      // number of bits per palette entry 15,16,24,32
		WORD xstart;             // image x origin
		WORD ystart;             // image y origin
		WORD width;              // image width in pixels
		WORD height;             // image height in pixels
		BYTE  bits;               // image bits per pixel 8,16,24,32
		BYTE  descriptor;         // image descriptor bits (vh flip bits)
	    // pixel data follows header
	} m_stHeader;
#pragma pack()

	LPBYTE mp_byteImage;
	DWORD m_dwordSize;

	void DeleteMemory();

	BOOL Save( LPCTSTR lp_strname );

};

typedef CETarga* LPTARGA;
