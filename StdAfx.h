// Document modified at : Monday, July 09, 2007 09:46:05 PM , by user : Pavel Sokolov , from computer : CREA7OR
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__13350016_3087_44DC_8035_E5A5B3E94A0D__INCLUDED_)
#define AFX_STDAFX_H__13350016_3087_44DC_8035_E5A5B3E94A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#pragma warning( disable : 4731 )
#pragma warning( disable : 4200 )

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

//#include <afxtempl.h>        // MFC Automation classes
//#include <afxpriv.h>
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <Shlwapi.h>
#include <Shellapi.h>
#include <shlobj.h>


#include "CEFile.h"
#include "CEFileError.h"
#include "CEHelper.h"

#include "CEPtrAutoArray.h"

#include "CEMMtimer.h"

#include "CEListCtrl.h"
#include "CEListComboItem.h"


struct MATRIX
{
	float m_floatRR;
	float m_floatRG;
	float m_floatRB;
	//
	float m_floatGR;
	float m_floatGG;
	float m_floatGB;
	//
	float m_floatBR;
	float m_floatBG;
	float m_floatBB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__13350016_3087_44DC_8035_E5A5B3E94A0D__INCLUDED_)
