// Document modified at : Tuesday, March 13, 2007 03:01:10 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEZEO Time Stamp AddIn. Document modified at : 17 јпрель 2002 г. 05:22:42 , by user : Pavel Sokolov , from computer : CREA7OR
// CEListCtrl.cpp : implementation file
#include "stdafx.h"
#include "resource.h"
#include "CEListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEListCtrl::CEListCtrl()
{
	m_boolShowed = FALSE;
	m_boolAllowAutoResize = FALSE;
//	SetImageList( Core()->GetSkin()->GetContactListImages(), TVSIL_NORMAL );
	mpSetColumns = NULL;
}

CEListCtrl::~CEListCtrl()
{
}

BEGIN_MESSAGE_MAP( CEListCtrl, CListCtrl )
	//{{AFX_MSG_MAP( CEListCtrl )
	ON_NOTIFY_REFLECT( LVN_GETDISPINFO, OnGetdispinfo )
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CEListCtrl::CtrlAddItem( const LPLISTCOMBOITEM lp_ceItem )
{
	BOOL l_boolResult = FALSE;
	LVITEM l_stListItem;
	memset( &l_stListItem, 0 , sizeof( LVITEM ));

	l_stListItem.mask = LVIF_PARAM | LVIF_TEXT | LVIF_IMAGE;
	l_stListItem.iImage = I_IMAGECALLBACK;
	l_stListItem.pszText = LPSTR_TEXTCALLBACK;
	l_stListItem.lParam = LPARAM( lp_ceItem );
	l_stListItem.iItem = GetItemCount();

	int l_intItem = InsertItem( &l_stListItem );
	if ( l_intItem != -1 )
	{
		lp_ceItem->SetListItem( l_intItem );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

BOOL CEListCtrl::CtrlDeleteItem( const LPLISTCOMBOITEM lp_ceItem )
{
	int l_intItem;
	BOOL l_boolResult = FALSE;
	l_intItem = FindByData( reinterpret_cast< DWORD >( lp_ceItem ));
	if ( l_intItem != -1 )
	{
		DeleteItem( l_intItem );
		l_boolResult = TRUE;
	}
	return l_boolResult;
}

int CEListCtrl::FindByData( const DWORD l_dwordData )
{
	int l_intItem = -1, l_intCounter;
	int l_intItemsCount = GetItemCount();
//	LPLISTITEM lp_ceListItem;
	for ( l_intCounter = 0; l_intCounter < l_intItemsCount; l_intCounter++ )
	{
		if ( GetItemData( l_intCounter ) == l_dwordData )
		{
			l_intItem = l_intCounter;
			break;
		}
	}
	return l_intItem;
}

BOOL CEListCtrl::DeleteAllItems()
{
	BOOL l_boolResult = FALSE;
	l_boolResult = CListCtrl::DeleteAllItems();
	if ( l_boolResult )
	{
		int l_intItemsCount = GetItemCount();
		LPLISTCOMBOITEM lp_ceListItem;
		for ( int l_intIndex = 0; l_intIndex < l_intItemsCount; l_intIndex++ )
		{
			lp_ceListItem = reinterpret_cast< LPLISTCOMBOITEM >( GetItemData( l_intIndex ));
//			if ( CEEntry::IsValid( lp_ceListItem ))
//			{
				lp_ceListItem->SetListItem( -1 );
//			}
		}
	}
//	CheckColumnsWidth();
	return l_boolResult;
}

BOOL CEListCtrl::DeleteItem( int nItem )
{
	BOOL l_boolResult = FALSE;
	l_boolResult = CListCtrl::DeleteItem( nItem );
//	CheckColumnsWidth();
	return l_boolResult;
}

void CEListCtrl::OnGetdispinfo( NMHDR* pNMHDR, LRESULT* pResult )
{
	LV_DISPINFO* pLVDispInfo = ( LV_DISPINFO* )pNMHDR;
    LVITEM* pItem = &pLVDispInfo->item;
	LPLISTCOMBOITEM lp_ceListItem =  reinterpret_cast< LPLISTCOMBOITEM >( pItem->lParam );
//	if ( CEEntry::IsValid( lp_ceListItem ))
//	{
	    lp_ceListItem->GetDisplayInformationListCtrl( pItem );
//	}
//	else
//	{
//		DeleteItem( pItem->iItem );
//		TRACE( "Not valid pointer for displaying\n\r" );
//	}
	*pResult = 0;
}

void CEListCtrl::SubclassList( UINT l_uintID , CWnd* lp_cWnd )
{
	SubclassDlgItem( l_uintID , lp_cWnd );
}

int CEListCtrl::GetSelectedItems( CDWordArray* lp_mfcDwordArray ) 
{
	int l_intCount;
	int l_intSelected = -1;
	l_intCount = GetSelectedCount();
	while( l_intCount )
	{
		l_intSelected = GetNextItem( l_intSelected, LVNI_SELECTED );
		if ( l_intSelected != -1 )
		{
			lp_mfcDwordArray->Add( DWORD( l_intSelected ));
		}
		else
		{
			break;
		}
		l_intCount--;
	}
	return l_intCount;
}

LPLISTCOMBOITEM CEListCtrl::GetSelectedItem() 
{
	LPLISTCOMBOITEM lp_ceItem = NULL;
	CDWordArray l_mfcDwordArray;
	GetSelectedItems( &l_mfcDwordArray );
	if ( l_mfcDwordArray.GetSize() == 1 )
	{
		lp_ceItem = reinterpret_cast< LPLISTCOMBOITEM >( GetItemData( l_mfcDwordArray.GetAt( 0 )));
	}
	return lp_ceItem;
}

void CEListCtrl::ApplySetting()
{
	DWORD l_dwordFlags = LVS_EX_FULLROWSELECT;
//	if ( Core()->GetInterfaceSet()->m_boolListCtrlGrid )
//	{
		l_dwordFlags |= LVS_EX_GRIDLINES;
//	}
	SetExtendedStyle( l_dwordFlags );
}

void CEListCtrl::OnSize( UINT nType, int cx, int cy ) 
{
	CListCtrl::OnSize( nType, cx, cy );
}

int CEListCtrl::GetColumnsSize()
{
	int l_intSize = 0;
	int l_intCount = GetColumnsCount();
	if ( l_intCount > 0 )
	{
		for ( int l_intCnt = 0 ; l_intCnt < l_intCount; l_intCnt++ )
		{
			l_intSize += GetColumnWidth( l_intCnt );
		}
	}
	return l_intSize;
}

int CEListCtrl::GetColumnsCount()
{
	int l_intColumns = 0;
	CHeaderCtrl* lp_mfcListHeader = GetHeaderCtrl();
	l_intColumns = lp_mfcListHeader->GetItemCount();
	if ( l_intColumns < 0 )
	{
		l_intColumns = 0;
	}
	return l_intColumns;
}


void CEListCtrl::OnWindowPosChanging( WINDOWPOS FAR* lpwndpos ) 
{
	CListCtrl::OnWindowPosChanging( lpwndpos );
}

void CEListCtrl::OnWindowPosChanged( WINDOWPOS FAR* lpwndpos ) 
{
	if ( m_boolAllowAutoResize )
	{
		if ( m_hWnd != NULL )
		{
			if ((( lpwndpos->flags & SWP_NOSIZE )) == 0 && (( lpwndpos->flags & SWP_SHOWWINDOW ) == 0 ))
			{			
				SetRedraw( FALSE );      // turn drawing back on 
				CheckColumnsWidth();
				SetRedraw( TRUE );      // turn drawing back on 
			}
		}
	}
}

void CEListCtrl::CheckColumnsWidth() 
{
	if ( m_boolAllowAutoResize )
	{
		int l_intSizesDifference;
		CRect l_mfcNewClientRect;
		GetClientRect( l_mfcNewClientRect );
		l_intSizesDifference = l_mfcNewClientRect.Width() - GetColumnsSize();
		if ( l_intSizesDifference != 0 )
		{

//			int l_intListCtrlSize;
//			l_intListCtrlSize = l_mfcNewClientRect.Width() / 3;
//			SetColumnWidth( 0, l_intListCtrlSize );
//			SetColumnWidth( 1, ( l_mfcNewClientRect.Width() - l_intListCtrlSize ));

//			SetColumnsWidth();
			if ( mpSetColumns != NULL )
			{
				(*mpSetColumns)( this );
			}

		}
	}
}
