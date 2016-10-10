// Document modified at : Monday, July 09, 2007 11:22:51 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEDialogApplyMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "x3f.h"
#include "CEDialogApplyMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEDialogApplyMatrix::CEDialogApplyMatrix( CWnd* pParent /*=NULL*/ ): CDialog(CEDialogApplyMatrix::IDD, pParent)
{

/*	m_floatBB = 0;
	m_floatBG = 0;
	m_floatBR = 0;
	m_floatGB = 0;
	m_floatGG = 0;
	m_floatGR = 0;
	m_floatRB = 0;
	m_floatRG = 0;
	m_floatRR = 0;
*/
	CEHelper::GetProfileBinary( "Matrix" , _T("m_floatBB"), LPBYTE( &l_stMatrix.m_floatBB ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatBG"), LPBYTE( &l_stMatrix.m_floatBG ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatBR"), LPBYTE( &l_stMatrix.m_floatBR ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatGB"), LPBYTE( &l_stMatrix.m_floatGB ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatGG"), LPBYTE( &l_stMatrix.m_floatGG ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatGR"), LPBYTE( &l_stMatrix.m_floatGR ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatRB"), LPBYTE( &l_stMatrix.m_floatRB ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatRG"), LPBYTE( &l_stMatrix.m_floatRG ), sizeof( float ));
	CEHelper::GetProfileBinary(  "Matrix" , _T("m_floatRR"), LPBYTE( &l_stMatrix.m_floatRR ), sizeof( float ));



	m_dwordNew = 0;
	CEHelper::GetProfileBinary(  "Settings" , _T("m_dwordNew"), LPBYTE( &m_dwordNew ), sizeof( m_dwordNew ));
	if ( m_dwordNew == 0 )
	{
		l_stMatrix.m_floatRR = float( 0.49353 );
		l_stMatrix.m_floatRG = float( 0.35804 );
		l_stMatrix.m_floatRB = float( 0.21204 );
		
		l_stMatrix.m_floatGR = float( -1.41747 );
		l_stMatrix.m_floatGG = float( 3.83130 );
		l_stMatrix.m_floatGB = float( -1.73962 );
		
		l_stMatrix.m_floatBR = float(  1.63282 );
		l_stMatrix.m_floatBG = float( -5.45389 );
		l_stMatrix.m_floatBB = float( 5.91316 );
	}

	m_dwordNew = 1;
	AfxGetApp()->WriteProfileBinary(  "Settings" , _T("m_dwordNew"), LPBYTE( &m_dwordNew ), sizeof( m_dwordNew ));
	

	//{{AFX_DATA_INIT(CEDialogApplyMatrix)
	//}}AFX_DATA_INIT



}


void CEDialogApplyMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDialogApplyMatrix)
	DDX_Text(pDX, IDC_EDIT_BB, 	l_stMatrix.m_floatBB);
	DDX_Text(pDX, IDC_EDIT_BG, 	l_stMatrix.m_floatBG);
	DDX_Text(pDX, IDC_EDIT_BR, 	l_stMatrix.m_floatBR);
	DDX_Text(pDX, IDC_EDIT_GB, 	l_stMatrix.m_floatGB);
	DDX_Text(pDX, IDC_EDIT_GG, 	l_stMatrix.m_floatGG);
	DDX_Text(pDX, IDC_EDIT_GR, 	l_stMatrix.m_floatGR);
	DDX_Text(pDX, IDC_EDIT_RB, 	l_stMatrix.m_floatRB);
	DDX_Text(pDX, IDC_EDIT_RG, 	l_stMatrix.m_floatRG);
	DDX_Text(pDX, IDC_EDIT_RR, 	l_stMatrix.m_floatRR);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEDialogApplyMatrix, CDialog)
	//{{AFX_MSG_MAP(CEDialogApplyMatrix)
	ON_BN_CLICKED(IDC_BUTTON_RT, OnButtonRt)
	ON_BN_CLICKED(IDC_BUTTON_FLP, OnButtonFlp)
	ON_BN_CLICKED(IDC_BUTTON_FLPH, OnButtonFlph)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEDialogApplyMatrix::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatBB"), LPBYTE( &l_stMatrix.m_floatBB ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatBG"), LPBYTE( &l_stMatrix.m_floatBG ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatBR"), LPBYTE( &l_stMatrix.m_floatBR ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatGB"), LPBYTE( &l_stMatrix.m_floatGB ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatGG"), LPBYTE( &l_stMatrix.m_floatGG ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatGR"), LPBYTE( &l_stMatrix.m_floatGR ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatRB"), LPBYTE( &l_stMatrix.m_floatRB ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatRG"), LPBYTE( &l_stMatrix.m_floatRG ), sizeof(float));
	AfxGetApp()->WriteProfileBinary( "Matrix" , _T("m_floatRR"), LPBYTE( &l_stMatrix.m_floatRR ), sizeof(float));

//	AfxGetApp()->WriteProfileBinary(  "Settings" , _T("m_boolGamma"), LPBYTE( &m_boolGamma ), sizeof( m_boolGamma ));


	CDialog::OnOK();
}




BOOL CEDialogApplyMatrix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


	CString l_csText;
	l_csText.Format("RAW unpacking: %d ms", m_dwordMS );
	SetDlgItemText( IDC_STATIC_UNPACK , l_csText );

	//	AfxMessageBox( l_csText );



	if ( m_dwordRlow != -1 )
	{
		l_csText.Format("%d", m_dwordRlow );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_LOW_RED , l_csText );


	if ( m_dwordGlow != -1 )
	{
		l_csText.Format("%d", m_dwordGlow );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_LOW_GREEN , l_csText );


	if ( m_dwordBlow != -1 )
	{
		l_csText.Format("%d", m_dwordBlow );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_LOW_BLUE , l_csText );


	///////// high
	if ( m_dwordRhigh != -1 )
	{
		l_csText.Format("%d", m_dwordRhigh );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_HIGH_RED , l_csText );


	if ( m_dwordGhigh != -1 )
	{
		l_csText.Format("%d", m_dwordGhigh );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_HIGH_GREEN , l_csText );


	if ( m_dwordBhigh != -1 )
	{
		l_csText.Format("%d", m_dwordBhigh );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_HIGH_BLUE , l_csText );



	///////// total
	if ( m_dwordRtot != -1 )
	{
		l_csText.Format("%d", m_dwordRtot );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_RED , l_csText );


	if ( m_dwordGtot != -1 )
	{
		l_csText.Format("%d", m_dwordGtot );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_GREEN , l_csText );


	if ( m_dwordBtot != -1 )
	{
		l_csText.Format("%d", m_dwordBtot );
	}
	else
	{
		l_csText = "NF";
	}
	SetDlgItemText( IDC_STATIC_BLUE , l_csText );

	
	return TRUE;
}


void CEDialogApplyMatrix::OnButtonRt() 
{
	float l_temp1, l_temp2;

	
	//m_floatGG;
	
	
	l_temp1 = l_stMatrix.m_floatRR;
	l_stMatrix.m_floatRR = l_stMatrix.m_floatGR;
	l_temp2 = l_stMatrix.m_floatRG;
	l_stMatrix.m_floatRG = l_temp1;

	l_temp1 = l_stMatrix.m_floatRB;
	l_stMatrix.m_floatRB = l_temp2;
	l_temp2 = l_stMatrix.m_floatGB;
	l_stMatrix.m_floatGB = l_temp1;


	l_temp1 = l_stMatrix.m_floatBB;
	l_stMatrix.m_floatBB = l_temp2;
	l_temp2 = l_stMatrix.m_floatBG;
	l_stMatrix.m_floatBG = l_temp1;

	l_temp1 = l_stMatrix.m_floatBR;
	l_stMatrix.m_floatBR = l_temp2;
	l_temp2 = l_stMatrix.m_floatGR;
	l_stMatrix.m_floatGR = l_temp1;

	l_stMatrix.m_floatRR = l_temp2;

	UpdateData( FALSE );
}

void CEDialogApplyMatrix::OnButtonFlp() 
{
	// TODO: Add your control notification handler code here
	float l_temp;

	l_temp = l_stMatrix.m_floatBB;
	l_stMatrix.m_floatBB = l_stMatrix.m_floatBR;
	l_stMatrix.m_floatBR = l_temp;
	
	l_temp = l_stMatrix.m_floatGB;
	l_stMatrix.m_floatGB = l_stMatrix.m_floatGR;
	l_stMatrix.m_floatGR = l_temp;
	
	l_temp = l_stMatrix.m_floatRB;
	l_stMatrix.m_floatRB = l_stMatrix.m_floatRR;
	l_stMatrix.m_floatRR = l_temp;

	UpdateData( FALSE );
}




void CEDialogApplyMatrix::OnButtonFlph() 
{
	float l_temp;
	
	l_temp = l_stMatrix.m_floatBB;
	l_stMatrix.m_floatBB = l_stMatrix.m_floatRB;
	l_stMatrix.m_floatRB = l_temp;
	
	l_temp = l_stMatrix.m_floatBG;
	l_stMatrix.m_floatBG = l_stMatrix.m_floatRG;
	l_stMatrix.m_floatRG = l_temp;
	
	l_temp = l_stMatrix.m_floatBR;
	l_stMatrix.m_floatBR = l_stMatrix.m_floatRR;
	l_stMatrix.m_floatRR = l_temp;
	
	UpdateData( FALSE );
	
}


void CEDialogApplyMatrix::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	SetDefaultMatrix();

	CDialog::OnCancel();
}

void CEDialogApplyMatrix::OnButtonDefault() 
{
	SetDefaultMatrix();

	UpdateData( FALSE );
}


void CEDialogApplyMatrix::SetDefaultMatrix() 
{
	
	l_stMatrix.m_floatRR = float( 0.49353 );
	l_stMatrix.m_floatRG = float( 0.35804 );
	l_stMatrix.m_floatRB = float( 0.21204 );
	
	l_stMatrix.m_floatGR = float( -1.41747 );
	l_stMatrix.m_floatGG = float( 3.83130 );
	l_stMatrix.m_floatGB = float( -1.73962 );
	
	l_stMatrix.m_floatBR = float(  1.63282 );
	l_stMatrix.m_floatBG = float( -5.45389 );
	l_stMatrix.m_floatBB = float( 5.91316 );
	/*
	m_floatBB = l_stMatrix.m_floatBB;
	m_floatBG = l_stMatrix.m_floatBG;
	m_floatBR = l_stMatrix.m_floatBR;
	m_floatGB = l_stMatrix.m_floatGB;
	m_floatGG = l_stMatrix.m_floatGG;
	m_floatGR = l_stMatrix.m_floatGR;
	m_floatRB = l_stMatrix.m_floatRB;
	m_floatRG = l_stMatrix.m_floatRG;
	
	m_floatRR = l_stMatrix.m_floatRR;
*/
}
