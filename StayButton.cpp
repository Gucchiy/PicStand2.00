// StayButton.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "picstand.h"
#include "StayButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStayButton

CStayButton::CStayButton( UINT uDownBmpID, UINT uDownHighlightBmpID,
		UINT uUpBmpID, UINT uUpHighlightBmpID )
{
	m_uDownBmpID = uDownBmpID;
	m_pDownItem = NULL;

	m_uDownHighlightBmpID = uDownHighlightBmpID;
	m_pDownHighlightItem = NULL;
	
	m_uUpBmpID = uUpBmpID;
	m_pUpItem = NULL;

	m_uUpHighlightBmpID = uUpHighlightBmpID;
	m_pUpHighlightItem = NULL;

	m_bIsNowUp = TRUE;
	m_bIsNowHighlight = FALSE;

}

CStayButton::~CStayButton()
{
}

BOOL CStayButton::Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam, LPARAM lParam )
{
	m_pParentWnd = pParent;
	m_wParam = wParam;
	m_lParam = lParam;
	m_uMessage = ::RegisterWindowMessage( ITECH_MES_STRING );

	return CreateEx(
		WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT,
		AfxRegisterWndClass( CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW) ),
		_T( "CPicStandWnd" ),
		WS_VISIBLE | WS_CHILD, CRect( nPosX, nPosY, nPosX+1, nPosY+1 ), pParent, 0, NULL );
}

BEGIN_MESSAGE_MAP(CStayButton, CWnd)
	//{{AFX_MSG_MAP(CStayButton)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStayButton メッセージ ハンドラ

void CStayButton::PostNcDestroy() 
{
	CWnd::PostNcDestroy();
	delete this;
}

int CStayButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDownItem = new CCanvasItem( this, m_uDownBmpID );
	m_pDownHighlightItem = new CCanvasItem( this, m_uDownHighlightBmpID );
	m_pUpItem = new CCanvasItem( this, m_uUpBmpID );
	m_pUpHighlightItem = new CCanvasItem( this, m_uUpHighlightBmpID );

	CRect	WndRect = m_pUpItem->GetCanvasItemRect();
	SetWindowPos( NULL, 0, 0, WndRect.Width(), WndRect.Height(), SWP_NOZORDER | SWP_NOMOVE );
	
	return 0;
}

void CStayButton::OnDestroy() 
{
	CWnd::OnDestroy();

	delete m_pUpItem;
	delete m_pUpHighlightItem;
	delete m_pDownItem;
	delete m_pDownHighlightItem;
	
}

void CStayButton::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	CCanvasItem*	pItem = m_pUpItem;

	if( m_bIsNowUp ){

		if( m_bIsNowHighlight ){

			pItem = m_pUpHighlightItem;

		}else{

			pItem = m_pUpItem;
		}
	
	}else{

		if( m_bIsNowHighlight ){

			pItem = m_pDownHighlightItem;

		}else{

			pItem = m_pDownItem;
		}
	}

	pItem->DrawTo( &dc, 0, 0 );
}

void CStayButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bIsNowUp = ( m_bIsNowUp ) ? FALSE : TRUE ;
	RedrawWindow();
	if( m_pParentWnd ) m_pParentWnd->PostMessage( m_uMessage, m_wParam, m_bIsNowUp ? FALSE : TRUE );
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CStayButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CStayButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( GetCapture() == this ){

		CRect	WndRect;
		GetWindowRect( &WndRect );

		if( ( WndRect.Width() < point.x ) ||
			( WndRect.Height() < point.y ) ||
			( point.x < 0 ) ||
			( point.y < 0 ) ){

			ReleaseCapture();
			m_bIsNowHighlight = FALSE;
			RedrawWindow();

		}else{

			m_bIsNowHighlight = TRUE;
			RedrawWindow();

		}

	}else{
	
		SetCapture();
		m_bIsNowHighlight = TRUE;
		RedrawWindow();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}
