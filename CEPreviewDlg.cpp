// Document modified at : Tuesday, December 05, 2006 09:41:03 PM , by user : Pavel Sokolov , from computer : CREA7OR
]// Document modified at : Thursday, March 31, 2005 04:00:22 AM , by user : Pavel Sokolov , from computer : CREA7OR
// CEPreviewDlg.cpp : implementation file
#include "stdafx.h"
#include "x3f.h"
#include "CEPreviewDlg.h"

#include "CMemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEPreviewDlg::CEPreviewDlg(CWnd* pParent /*=NULL*/)	: CDialog(CEPreviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEPreviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEPreviewDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEPreviewDlg, CDialog)
	//{{AFX_MSG_MAP(CEPreviewDlg)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CEPreviewDlg::OnOK() 
{
	
	CDialog::OnOK();
}

void CEPreviewDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

int CEPreviewDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if( CDialog::OnCreate( lpCreateStruct ) == -1 )
	{
		return -1;
	}
	
	CRect rect; GetClientRect( &rect );

	m_wndCanvas.Create( "Preview",
		                WS_VISIBLE | WS_CHILD | SS_OWNERDRAW,
						rect,
						this,
						80 );
	
	return 0;
}

HBRUSH CEPreviewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CEPreviewDlg::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
	{
		CMemDC *pMemDC = NULL;
		pMemDC = new CMemDC( lpDrawItemStruct->hDC );
		lpDrawItemStruct->hDC = pMemDC->m_hDC;

		CRect rect; GetClientRect( rect );
		HBRUSH hBrush = ::CreateSolidBrush( RGB(255, 255, 255) );
		
		::FillRect( lpDrawItemStruct->hDC, rect, hBrush );
		
		DeleteObject( hBrush );
//		CImageToolDoc *pDoc = (CImageToolDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
		
//		if( pDoc->m_pSelectedImage != NULL )
//		{
//			Graphics graphics( lpDrawItemStruct->hDC );
//			graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
//			graphics.DrawImage( pDoc->m_pSelectedImage,	
//				                 Rect( lpDrawItemStruct->rcItem.left, 
//									   lpDrawItemStruct->rcItem.top,
//									   lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left,
//									   lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top)); 
//		}

		delete pMemDC;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CEPreviewDlg::OnSize(UINT nType, int cx, int cy) 
{
//	CDialog::OnSize(nType, cx, cy);
	
	CDialog::OnSize(nType, cx, cy);
/*	
	CRect rc; GetClientRect( rc );

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	if( pFrame == NULL )
	{
		return;
	}

	CImageToolDoc* pDoc = (CImageToolDoc*)pFrame->GetActiveDocument();

	if( pDoc->m_pSelectedImage == NULL )
	{
		rc.SetRectEmpty();
		m_wndCanvas.MoveWindow( rc );
	}
	else
	{
		const int   nWidth    = rc.Width();
		const int   nHeight   = rc.Height();
		const float fRatio    = (float)nHeight/nWidth;
		const float fImgRatio = (float)pDoc->m_pSelectedImage->GetHeight()/pDoc->m_pSelectedImage->GetWidth();

		int XDest, YDest, nDestWidth, nDestHeight;
	
		if( fImgRatio > fRatio )
		{
			nDestWidth  = nHeight/fImgRatio;
			XDest       = (nWidth-nDestWidth)/2;
			YDest       = 0;
			nDestHeight = nHeight;
		}
		else
		{
			XDest       = 0;
			nDestWidth  = nWidth;
			nDestHeight = nWidth*fImgRatio;
			YDest       = (nHeight-nDestHeight)/2;
		}

		CRect rect(XDest, YDest, XDest+nDestWidth, YDest+nDestHeight);
		m_wndCanvas.MoveWindow( rect );
		m_wndCanvas.Invalidate();
	}
	*/
}
