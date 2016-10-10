// Document modified at : Monday, July 09, 2007 11:22:42 PM , by user : Pavel Sokolov , from computer : CREA7OR
// x3fDlg.h : header file
//

#if !defined(AFX_X3FDLG_H__5FEEE24B_1AA4_4D82_8778_D7294F6590E5__INCLUDED_)
#define AFX_X3FDLG_H__5FEEE24B_1AA4_4D82_8778_D7294F6590E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHyperLink.h"

#include "CEX3F.h"
#include "CEX3FSECTION.h"

class CX3fDlg : public CDialog
{
// Construction
public:
	CX3fDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CX3fDlg)
	enum { IDD = IDD_X3F_DIALOG };
	CEListCtrl	m_ctrlSectionList;
	CHyperLink	m_ctrlHyperLink;
	BOOL	m_boolGamma;
	BOOL	m_boolMatrix;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CX3fDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	static void SetColumns( CEListCtrl* lp_ceListCtrl );
	void SaveSection();



	CEX3F l_ceX3f;

	// Generated message map functions
	//{{AFX_MSG(CX3fDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnRightClickListSections(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSections(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_X3FDLG_H__5FEEE24B_1AA4_4D82_8778_D7294F6590E5__INCLUDED_)
