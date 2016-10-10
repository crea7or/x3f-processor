// Document modified at : Saturday, January 07, 2006 12:06:30 AM , by user : Pavel Sokolov , from computer : CREA7OR
#pragma once

#include "CEListComboItem.h"

class CEListCtrl : public CListCtrl
{
// Construction
public:
	CEListCtrl();
	virtual ~CEListCtrl();

	void SubclassList( UINT l_uintID , CWnd* lp_cWnd );

	BOOL CtrlAddItem( const LPLISTCOMBOITEM lp_ceListItem );
	BOOL CtrlDeleteItem( const LPLISTCOMBOITEM lp_ceListItem );
	int GetSelectedItems( CDWordArray* lp_mfcDwordArray );
	LPLISTCOMBOITEM GetSelectedItem();

	int FindByData( const DWORD l_dwordData );

	void ApplySetting();

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual BOOL DeleteAllItems();
	virtual BOOL DeleteItem( int nItem );
	void AllowAutoResize( const BOOL l_boolResize )
	{
		m_boolAllowAutoResize = l_boolResize;
	};
	void CheckColumnsWidth();

	void SetColumnsCallbackFunction(void (*lpSetColumns)( CEListCtrl* ))
	{
		mpSetColumns = lpSetColumns;
	}

protected:

	// pointer to the function that will check columns
	void (*mpSetColumns)( CEListCtrl* );

	int GetColumnsCount();
	int GetColumnsSize();

	CRect m_mfcWndRect;
	BOOL m_boolShowed;
	BOOL m_boolAllowAutoResize;

	// Generated message map functions
protected:
	//{{AFX_MSG(CEListCtrl)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


typedef CEListCtrl* LPLISTCTRL;
