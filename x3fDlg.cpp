// Document modified at : Wednesday, February 15, 2012 2:58:55 AM , by user : Pavel Sokolov , from computer : CREA7OR
// x3fDlg.cpp : implementation file
//

#include "stdafx.h"
#include "x3f.h"
#include "x3fDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CX3fDlg::CX3fDlg(CWnd* pParent /*=NULL*/) : CDialog(CX3fDlg::IDD, pParent)
{
//	m_boolCrop = AfxGetApp()->GetProfileInt( "Matrix" , _T("m_boolCrop"), TRUE );

	//{{AFX_DATA_INIT(CX3fDlg)	 
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_boolGamma = AfxGetApp()->GetProfileInt( "Processor Settings" , _T("m_boolGamma"),  TRUE );
	m_boolMatrix = AfxGetApp()->GetProfileInt( "Processor Settings" , _T("m_boolMatrix"),  FALSE );

}

void CX3fDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CX3fDlg)
	DDX_Control(pDX, IDC_LIST_SECTIONS, m_ctrlSectionList);
	DDX_Control(pDX, IDC_STATIC_LINK, m_ctrlHyperLink);
	DDX_Check(pDX, IDC_CHECK_GAM, m_boolGamma);
	DDX_Check(pDX, IDC_CHECK_MAT, m_boolMatrix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CX3fDlg, CDialog)
	//{{AFX_MSG_MAP(CX3fDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SECTIONS, OnRightClickListSections)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SECTIONS, OnDblclkListSections)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CX3fDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlHyperLink.SetURL( _T("http://www.cezeo.com/?inref=x3f_processor") );
	m_ctrlHyperLink.SetLinkCursor( AfxGetApp()->LoadCursor( IDC_CURSOR_HAND ));

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	



	m_ctrlSectionList.ApplySetting();

	m_ctrlSectionList.SetColumnsCallbackFunction( &SetColumns );
	
	
	CString l_csColumn;
	LVCOLUMN l_stColumn;
	
	CRect l_mfcListRect;
	m_ctrlSectionList.GetWindowRect( &l_mfcListRect);
	int l_intListCtrlSize = l_mfcListRect.Width() - ( GetSystemMetrics( SM_CXEDGE ) * 2 );
	
	int l_intWidth1_3 = ( l_intListCtrlSize / 3 );
	
	l_stColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH; 
	l_stColumn.fmt = LVCFMT_LEFT; 
	l_csColumn = "Name";
	l_stColumn.cx = l_intWidth1_3;
    l_stColumn.pszText = l_csColumn.GetBuffer( 1 );
	l_stColumn.cchTextMax = l_csColumn.GetLength();
	m_ctrlSectionList.InsertColumn( 0, &l_stColumn ); 
	
	l_csColumn = "Type";
	l_stColumn.cx = l_intWidth1_3;
    l_stColumn.pszText = l_csColumn.GetBuffer( 1 );
	l_stColumn.cchTextMax = l_csColumn.GetLength();
	m_ctrlSectionList.InsertColumn( 1, &l_stColumn );

	l_csColumn = "Size";
	l_stColumn.fmt = LVCFMT_RIGHT; 
	l_stColumn.cx = l_intListCtrlSize - ( l_intWidth1_3 * 2 );
    l_stColumn.pszText = l_csColumn.GetBuffer( 1 );
	l_stColumn.cchTextMax = l_csColumn.GetLength();
	m_ctrlSectionList.InsertColumn( 2, &l_stColumn );

	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_ctrlSectionList.AllowAutoResize( TRUE );
	m_ctrlSectionList.CheckColumnsWidth();
	m_ctrlSectionList.UpdateWindow();
	
//	m_ceSoftwareInfoCollector.CollectNetworkInformation();
//	m_ceSoftwareInfoCollector.FillListCtrl( &m_ctrlSectionList );
//	m_ctrlSectionList.CheckColumnsWidth();

	
	GetDlgItem( IDC_CHECK_GAM )->EnableWindow( FALSE );
	GetDlgItem( IDC_CHECK_MAT )->EnableWindow( FALSE );

	GetDlgItem( IDC_BUTTON2 )->EnableWindow( FALSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CX3fDlg::SetColumns( CEListCtrl* lp_ceListCtrl )
{
	CRect l_mfcListRect;
	lp_ceListCtrl->GetClientRect( &l_mfcListRect);
	int l_intListCtrlSize = l_mfcListRect.Width();// - ( GetSystemMetrics( SM_CXEDGE ) * 2 );
	int l_intWidth1_3= ( l_intListCtrlSize / 3 );
	
	lp_ceListCtrl->SetColumnWidth( 0, l_intWidth1_3 ); 
	lp_ceListCtrl->SetColumnWidth( 1, l_intWidth1_3 ); 
	lp_ceListCtrl->SetColumnWidth( 2, l_intListCtrlSize - ( l_intWidth1_3 * 2 ));
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CX3fDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CX3fDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CX3fDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	AfxGetApp()->WriteProfileInt( "Processor Settings", _T("m_boolGamma"),  m_boolGamma );
	AfxGetApp()->WriteProfileInt( "Processor Settings" , _T("m_boolMatrix"),  m_boolMatrix );


	CDialog::OnCancel();
}

void CX3fDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	AfxGetApp()->WriteProfileInt( "Processor Settings", _T("m_boolGamma"),  m_boolGamma );
	AfxGetApp()->WriteProfileInt( "Processor Settings" , _T("m_boolMatrix"),  m_boolMatrix );
	

	CDialog::OnOK();
}

void CX3fDlg::OnButton1() 
{
	UpdateData();

//	AfxGetApp()->WriteProfileInt( "Matrix" , _T("m_boolCrop"), m_boolCrop );

	CWaitCursor l_mfcCursor;

	CEMMtimer l_ceMMtimer;

	DWORD l_dwordVal = 0;



	CString l_csFilenameInput,l_csFilenameOutput;

	CFileDialog l_dlgFileOpen( TRUE, NULL, NULL, NULL, "X3F Files (*.X3F)|*.X3F||", NULL);
	if ( l_dlgFileOpen.DoModal() == IDOK )
	{
		l_csFilenameInput = l_dlgFileOpen.GetPathName();
		l_csFilenameOutput = l_csFilenameInput + ".jpg";
		l_ceMMtimer.StartTimer();
		l_ceX3f.Load( l_csFilenameInput );

		l_ceX3f.FillListCtrl( &m_ctrlSectionList );

//		l_ceMMtimer.StopTimer();
//		l_dwordVal = l_ceMMtimer.GetDifference();
//
//		CFileDialog l_dlgFileSave( FALSE, "tif", NULL, NULL, "TIFF Files (*.TIF)|*.TIF||", NULL);
//		if ( l_dlgFileSave.DoModal() == IDOK )
//		{
//			l_ceMMtimer.StartTimer();
//			l_ceX3f.m_ceDirectory.SavePlainImage( l_csFilenameOutput );
//			l_ceMMtimer.StopTimer();
//			l_dwordVal = l_ceMMtimer.GetDifference();
//		}

		
		GetDlgItem( IDC_CHECK_GAM )->EnableWindow( TRUE );
		GetDlgItem( IDC_CHECK_MAT )->EnableWindow( TRUE );

		GetDlgItem( IDC_BUTTON2 )->EnableWindow( TRUE );
	}



//	l_ceX3f.Load( "L:\\temp\\IMG03486.X3F");
//	l_ceX3f.m_ceDirectory.SavePlainImage( NULL );

	CString l_csString;
	l_csString.Format("Load/Save/Unpack time: %d ms", l_dwordVal);
	SetDlgItemText( IDC_STATIC_UNP_T, l_csString );
}

void CX3fDlg::OnRightClickListSections(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{

	SaveSection();
	*pResult = 0;
}

void CX3fDlg::SaveSection()
{
	UpdateData();

	LPLISTCOMBOITEM lp_ceListCombo = m_ctrlSectionList.GetSelectedItem();
	
	if ( lp_ceListCombo != NULL )
	{		
		LPX3FSECTION lp_ceSection = dynamic_cast< LPX3FSECTION >( lp_ceListCombo );
		if ( lp_ceSection != NULL )
		{

			AfxGetApp()->WriteProfileInt( "Processor Settings", _T("m_boolGamma"),  m_boolGamma );
			AfxGetApp()->WriteProfileInt( "Processor Settings" , _T("m_boolMatrix"),  m_boolMatrix );
	
			lp_ceSection->SaveSection();

			
			GetDlgItem( IDC_CHECK_GAM )->EnableWindow( FALSE );
			GetDlgItem( IDC_CHECK_MAT )->EnableWindow( FALSE );
		}
	}
}

void CX3fDlg::OnDblclkListSections(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SaveSection();
	*pResult = 0;
}

void CX3fDlg::OnButton2() 
{
	SaveSection();
	
}
