// Document modified at : Sunday, February 12, 2006 04:17:08 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEListComboItem.cpp: implementation of the CEListComboItem class.

#include "stdafx.h"
#include "CEListComboItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEListComboItem::CEListComboItem()
{
	SetComboItem( -1 );
	SetListItem( -1 );
}

CEListComboItem::~CEListComboItem()
{

}

CEListComboItem& CEListComboItem::operator=(const CEListComboItem& l_ceListComboItem )
{
	CEObject::operator =( l_ceListComboItem );
	m_intListItem = l_ceListComboItem.m_intListItem;
	m_intComboItem =  l_ceListComboItem.m_intComboItem;
	return *this;
}

CEListComboItem::CEListComboItem( const CEListComboItem &l_ceListComboItem ) // copy
{ 
	*this = l_ceListComboItem;
}

BOOL CEListComboItem::GetDisplayInformationComboBoxEx( COMBOBOXEXITEM* lp_ceComboBoxExItem )
{
	BOOL l_boolResult = FALSE;
	if (lp_ceComboBoxExItem->mask & CBEIF_TEXT )
    {
		lp_ceComboBoxExItem->pszText = LPTSTR( GetAlias());
		lp_ceComboBoxExItem->cchTextMax = m_csObjectAlias.GetLength();
	}
	if ( lp_ceComboBoxExItem->mask & CBEIF_IMAGE )
	{
        lp_ceComboBoxExItem->iImage = GetImage();
	}
	if ( lp_ceComboBoxExItem->mask & CBEIF_SELECTEDIMAGE )
	{
        lp_ceComboBoxExItem->iSelectedImage  = GetImage();
	}

	return l_boolResult;
}

BOOL CEListComboItem::GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem  )
{
	BOOL l_boolResult = TRUE;
    if (lp_ceListCtrlItem->mask & LVIF_TEXT)
    {
       switch ( lp_ceListCtrlItem->iSubItem )
        {
            case 0:
				lp_ceListCtrlItem->pszText = LPTSTR( GetAlias());
                break;
            case 1:
				lp_ceListCtrlItem->pszText = LPTSTR( GetDescription());
				break;
        }
    }
	if ( lp_ceListCtrlItem->mask & LVIF_IMAGE )
	{
        lp_ceListCtrlItem->iImage = GetImage();
	}
	return l_boolResult;
}
