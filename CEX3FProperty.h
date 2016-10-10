// Document modified at : Saturday, December 02, 2006 08:03:49 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEX3FProperty.h: interface for the CEX3FProperty class.
#pragma once

class CEX3FProperty  
{
public:
	CEX3FProperty();
	virtual ~CEX3FProperty();

	void SetName( LPWSTR lp_wstrName );
	void SetValue( LPWSTR lp_wstrValue );
	void Convert( LPWSTR lp_wstrValue, CString* lp_mfcString );

	CString m_csName;
	CString m_csValue;

};

typedef CEX3FProperty* LPX3FPROPERTY;
