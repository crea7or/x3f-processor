// Document modified at : Wednesday, March 30, 2005 10:30:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
#if !defined(AFX_CEPREVIEWDLG_H__DF229325_904C_4552_8F17_D1F7D54E5C21__INCLUDED_)
#define AFX_CEPREVIEWDLG_H__DF229325_904C_4552_8F17_D1F7D54E5C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CEPreviewDlg : public CDialog
{
// Construction
public:
	CEPreviewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEPreviewDlg)
	enum { IDD = IDD_DIALOG_PREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	CStatic m_wndCanvas;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEPreviewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEPreviewDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEPREVIEWDLG_H__DF229325_904C_4552_8F17_D1F7D54E5C21__INCLUDED_)
