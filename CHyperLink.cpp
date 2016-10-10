// Document modified at : Monday, January 27, 2003 03:34:36 AM , by user : Pavel Sokolov , from computer : CREA7OR
#include "stdafx.h"
#include "CHyperLink.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHyperLink::CHyperLink()
{
    m_crLinkColour      = RGB( 0, 0, 238 );     // Blue
    m_crVisitedColour   = RGB( 85, 26, 139 );   // Purple
    m_boolVisited          = FALSE;              // Hasn't been visited yet.
    m_boolUnderline        = TRUE;               // Underline the link?
    m_boolAdjustToFit      = TRUE;               // Resize the window to fit the text?
}

CHyperLink::~CHyperLink()
{
    if (( HFONT )m_Font )
        m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP( CHyperLink, CStatic )
	//{{AFX_MSG_MAP( CHyperLink )
	ON_CONTROL_REFLECT( STN_CLICKED, OnClicked )
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperLink message handlers

BOOL CHyperLink::PreTranslateMessage( MSG* pMsg ) 
{
 //   m_ctrlToolTip.RelayEvent( pMsg );
    return CStatic::PreTranslateMessage( pMsg );
}

HBRUSH CHyperLink::CtlColor( CDC* pDC, UINT ) 
{
    //	ASSERT( nCtlColor == CTLCOLOR_STATIC );
    
    // Set the approriate colour
    if ( m_boolVisited )
        pDC->SetTextColor( m_crVisitedColour );
    else
        pDC->SetTextColor( m_crLinkColour );
    
    // Set underline font if required
    if ( m_boolUnderline ) {
        
        if ( !( HFONT )m_Font ) {			// Create font only once.
            LOGFONT lf;
            GetFont()->GetLogFont( &lf );
            lf.lfUnderline = TRUE;
            m_Font.CreateFontIndirect( &lf );
        }
        
        pDC->SelectObject( &m_Font );
    }
    
    // transparent text.
    pDC->SetBkMode( TRANSPARENT );
    return ( HBRUSH )GetStockObject( NULL_BRUSH );
}

BOOL CHyperLink::OnSetCursor( CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/ ) 
{
    ::SetCursor( m_hLinkCursor );
    return TRUE;
}

void CHyperLink::PreSubclassWindow() 
{
    // We want to get mouse clicks via STN_CLICKED
    DWORD dwStyle = GetStyle();
    ::SetWindowLong( m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY );
    
    // Set the URL as the window text
    if ( m_strURL.IsEmpty())
	{
        GetWindowText( m_strURL );
	}
    
    // Check that the window text isn't empty. If it is, set it as the URL.
    CString strWndText;
    GetWindowText( strWndText );
 //   if ( strWndText.IsEmpty()) 
//	{
 //      ASSERT( !m_strURL.IsEmpty());	// Window and URL both empty. DUH!
  //      SetWindowText( m_strURL );
   // }
    
    // Adjust size of window to fit URL if necessary
    PositionWindow();		
    
    // Load up the ( standard ) hyperlink cursor
    m_hLinkCursor = AfxGetApp()->LoadStandardCursor( IDC_ARROW );
    
    // Create the tooltip
  //  CRect rect; 
  //  GetClientRect( rect );
  //  m_ctrlToolTip.Create( this );
  //  m_ctrlToolTip.AddTool( this, m_strURL, rect, TOOLTIP_ID );

    CStatic::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink operations

void CHyperLink::SetURL( CString strURL )
{
    m_strURL = strURL;
    PositionWindow();
//    m_ctrlToolTip.UpdateTipText( strURL, this, TOOLTIP_ID );
}

// Move and resize the window so that the window is the same size
// as the hyperlink text. This stops the hyperlink cursor being active
// when it is not directly over the text. If the text is left justified
// then the window is merely shrunk, but if it is centred or right
// justified then the window will have to be moved as well.
//
// Suggested by Pål K. Tønder 

void CHyperLink::PositionWindow()
{
    if ( !m_boolAdjustToFit ) return;
    
    // Get the current window position
    CRect rect;
    GetWindowRect( rect );
    
    CWnd* pParent = GetParent();
    if ( pParent )
        pParent->ScreenToClient( rect );
    
    // Get the size of the window text
    CString strWndText;
    GetWindowText( strWndText );
    
    CDC* pDC = GetDC();
    CSize Extent = pDC->GetTextExtent( strWndText );
    ReleaseDC( pDC );
    
    // Get the text justification via the window style
    DWORD dwStyle = GetStyle();
    
    // Recalc the window size and position based on the text justification
    if ( dwStyle & SS_CENTERIMAGE )
	{
		rect.DeflateRect( 0, ( rect.Height() - Extent.cy )/2 );
	}
    else
	{
		rect.bottom = rect.top + Extent.cy;
	}
    
    if ( dwStyle & SS_CENTER )
	{
		rect.DeflateRect(( rect.Width() - Extent.cx )/2, 0 );
	}
    else
	{
		if ( dwStyle & SS_RIGHT )
		{
			rect.left  = rect.right - Extent.cx;
		}
		else // SS_LEFT = 0, so we can't test for it explicitly 
		{
			rect.right = rect.left + Extent.cx;
		}
	}    
    // Move the window
    SetWindowPos( NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER );
}

void CHyperLink::OnClicked()
{
    int result = ( int )GotoURL( m_strURL, SW_SHOW );
    m_boolVisited = ( result > HINSTANCE_ERROR );
    if ( !m_boolVisited ) 
	{
        MessageBeep( MB_ICONEXCLAMATION );	// Unable to follow link
    } 
	else 
	{
	    m_boolVisited = TRUE; 
	    Invalidate(); 
	}
}

HINSTANCE CHyperLink::GotoURL( LPCTSTR url, int showcmd )
{
    HINSTANCE result = ShellExecute( NULL, _T( "open" ), url, NULL,NULL, showcmd );
    return result;
}
