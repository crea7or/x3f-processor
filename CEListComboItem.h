// Document modified at : Sunday, December 18, 2005 06:49:03 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEListComboItem.h: interface for the CEListComboItem class.
#pragma once

#include "CEObject.h"

class CEListComboItem : public CEObject
{
public:
	CEListComboItem();
	virtual ~CEListComboItem();

	// Copy constructor
	CEListComboItem& operator=(const CEListComboItem& l_ceListComboItem );
	CEListComboItem( const CEListComboItem &l_ceListComboItem );

	virtual BOOL GetDisplayInformationComboBoxEx( COMBOBOXEXITEM* lp_ceComboBoxExItem );
	virtual BOOL GetDisplayInformationListCtrl( LVITEM* lp_ceListCtrlItem );

	void SetComboItem( const int l_intComboItem )
	{
		m_intComboItem = l_intComboItem;
	};
	int GetComboItem() const
	{
		return m_intComboItem;
	};
	void SetListItem( const int l_intListItem )
	{
		m_intListItem = l_intListItem;
	};
	int GetListItem() const
	{
		return m_intListItem;
	};

protected:

	int m_intListItem;
	int m_intComboItem;

};

typedef CEListComboItem* LPLISTCOMBOITEM;
