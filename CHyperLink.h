// Document modified at : Monday, June 24, 2002 04:39:48 PM , by user : Pavel Sokolov , from computer : CREA7OR
#pragma once

class CHyperLink : public CStatic
{
    // Construction/destruction
public:
    CHyperLink();
    virtual ~CHyperLink();
    
    // Attributes
public:
    
    // Operations
public:
    
    void SetURL( CString strURL );
    void SetLinkCursor( HCURSOR hCursor ) { m_hLinkCursor = hCursor; }
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL( CHyperLink )
public:
    virtual BOOL PreTranslateMessage( MSG* pMsg );
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    HINSTANCE GotoURL( LPCTSTR url, int showcmd );
    void PositionWindow();
    
    // Protected attributes
protected:
    COLORREF m_crLinkColour, m_crVisitedColour;		// Hyperlink colours
    BOOL     m_boolVisited;							// Has it been visited?
    BOOL	 m_boolUnderline;							// underline hyperlink?
    BOOL	 m_boolAdjustToFit;						// Adjust window size to fit text?
    CString  m_strURL;								// hyperlink URL
    CFont	 m_Font;								// Underline font if necessary
    HCURSOR  m_hLinkCursor;							// Cursor for hyperlink
//    CToolTipCtrl m_ctrlToolTip;							// The tooltip
    
    // Generated message map functions
protected:
    //{{AFX_MSG( CHyperLink )
    afx_msg HBRUSH CtlColor( CDC* pDC, UINT nCtlColor );
    afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
    //}}AFX_MSG
    afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};
