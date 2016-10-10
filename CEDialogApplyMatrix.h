// Document modified at : Monday, July 09, 2007 11:22:34 PM , by user : Pavel Sokolov , from computer : CREA7OR
#if !defined(AFX_CEDIALOGAPPLYMATRIX_H__041F2DC1_CCB1_410A_A6A1_E1281748B7DF__INCLUDED_)
#define AFX_CEDIALOGAPPLYMATRIX_H__041F2DC1_CCB1_410A_A6A1_E1281748B7DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CEDialogApplyMatrix.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEDialogApplyMatrix dialog

#include "resource.h"

class CEDialogApplyMatrix : public CDialog
{
// Construction
public:
	CEDialogApplyMatrix(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEDialogApplyMatrix)
	enum { IDD = IDD_DIALOG_MATRIX };
//	float	m_floatBB;
//	float	m_floatBG;
//	float	m_floatBR;
//	float	m_floatGB;
//	float	m_floatGG;
//	float	m_floatGR;
//	float	m_floatRB;
//	float	m_floatRG;
//	float	m_floatRR;
//	BOOL	m_boolGamma;
	//}}AFX_DATA

	DWORD m_dwordNew;

	MATRIX l_stMatrix;

	DWORD m_dwordMS;

	DWORD m_dwordRlow;
	DWORD m_dwordRhigh;
	DWORD m_dwordGlow;
	DWORD m_dwordGhigh;
	DWORD m_dwordBlow;
	DWORD m_dwordBhigh;

	DWORD m_dwordRtot;
	DWORD m_dwordGtot;
	DWORD m_dwordBtot;

	
	void SetDefaultMatrix();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDialogApplyMatrix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEDialogApplyMatrix)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRt();
	afx_msg void OnButtonFlp();
	afx_msg void OnButtonFlph();
	virtual void OnCancel();
	afx_msg void OnButtonDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEDIALOGAPPLYMATRIX_H__041F2DC1_CCB1_410A_A6A1_E1281748B7DF__INCLUDED_)
