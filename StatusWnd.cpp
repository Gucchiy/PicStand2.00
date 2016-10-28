// StatusWnd.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "picstand.h"
#include "StatusWnd.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd

CStatusWnd::CStatusWnd( UINT uCanvasBmpID, UINT uHighlightBmpID )
{
	m_pCanvas = NULL;
	m_uCanvasBmpID = uCanvasBmpID;

	m_pHighlightItem = NULL;
	m_uHighlightBmpID = uHighlightBmpID;

	m_State = SWST_NUTORAL;

	m_pFont = NULL;
}

CStatusWnd::~CStatusWnd()
{
}

BOOL CStatusWnd::Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam, LPARAM lParam )
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

BEGIN_MESSAGE_MAP(CStatusWnd, CWnd)
	//{{AFX_MSG_MAP(CStatusWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStatusWnd メッセージ ハンドラ

void CStatusWnd::PostNcDestroy() 
{
	CWnd::PostNcDestroy();

	delete this;
}

int CStatusWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pCanvas = new CCanvas( this, m_uCanvasBmpID );
	m_pHighlightItem = new CCanvasItem( this, m_uHighlightBmpID );
	
	CRect	WndRect = m_pCanvas->GetCanvasRect();
	SetWindowPos( NULL, 0, 0, WndRect.Width(), WndRect.Height(), SWP_NOZORDER | SWP_NOMOVE );

	m_pFont = new CFont;
	m_pFont->CreateFont( WndRect.Height() - 6, 0, 0, 0, FW_HEAVY,
		FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DRAFT_QUALITY, DEFAULT_PITCH,_T( "ＭＳ Ｐゴシック" ) );
    
	return 0;
}

void CStatusWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	delete m_pCanvas;
	delete m_pHighlightItem;

	m_pFont->DeleteObject();
	delete m_pFont;
	
}

void CStatusWnd::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	CDC*	pCanvasDC = m_pCanvas->GetCanvasDC();

	switch( m_State ){

	case SWST_HIGHLIGHT:

		m_pHighlightItem->DrawTo( pCanvasDC, 0, 0 );
		break;

	default:

		m_pCanvas->ClearCanvas();
		break;	

	}
	m_pCanvas->DrawTo( &dc, 0, 0 );

	int	nOldBkMode = dc.SetBkMode( TRANSPARENT );

	CFont*	pOldFont = (CFont*)dc.SelectObject( m_pFont );

	CRect	WndRect;
	GetWindowRect( &WndRect );
	dc.SetTextColor( RGB_BACK_SHADOW );
	dc.DrawText( m_DispString, 
		CRect( 4, 4, WndRect.Width() - 4, WndRect.Height() - 4 ), DT_CENTER );
	dc.SelectObject( pOldFont );

	dc.SetBkMode( nOldBkMode );
}

void CStatusWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CStatusWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_State == SWST_HIGHLIGHT ){

		if( m_pParentWnd ) m_pParentWnd->PostMessage( m_uMessage, m_wParam, m_lParam );
	}
	m_State = SWST_NUTORAL;
	RedrawWindow();
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CStatusWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( GetCapture() == this ){

		CRect	WndRect;
		GetWindowRect( &WndRect );

		if( ( WndRect.Width() < point.x ) ||
			( WndRect.Height() < point.y ) ||
			( point.x < 0 ) ||
			( point.y < 0 ) ){

			ReleaseCapture();
			m_State = SWST_NUTORAL;
			RedrawWindow();

		}else{

			m_State = SWST_HIGHLIGHT;
			RedrawWindow();

		}

	}else{
	
		SetCapture();
		m_State = SWST_HIGHLIGHT;
		RedrawWindow();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CStatusWnd::SetDispString(const CString &DispString)
{
	if( DispString.IsEmpty() ){

		m_DispString = STATUSWND_DEFALT_STRING;
	
	}else{

		m_DispString = DispString;
	}
	InvalidateRect( NULL );
}
