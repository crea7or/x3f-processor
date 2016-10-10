// x3f.h : main header file for the X3F application
//

#if !defined(AFX_X3F_H__0AC3EA51_55D7_47D7_9DF7_0021D22F2999__INCLUDED_)
#define AFX_X3F_H__0AC3EA51_55D7_47D7_9DF7_0021D22F2999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CX3fApp:
// See x3f.cpp for the implementation of this class
//

class CX3fApp : public CWinApp
{
public:
	CX3fApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CX3fApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CX3fApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_X3F_H__0AC3EA51_55D7_47D7_9DF7_0021D22F2999__INCLUDED_)
