// CustomButton.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "CustomButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomButton

CCustomButton::CCustomButton(
	UINT uCanvasBmpID, UINT uHighlightBmpID, UINT uPushBmpID )
{
	m_pCanvas = NULL;
	m_uCanvasBmpID = uCanvasBmpID;

	m_pHighlightItem = NULL;
	m_uHighlightBmpID = uHighlightBmpID;
	
	m_pPushItem = NULL;
	m_uPushBmpID = uPushBmpID;

	m_State = CBST_NUTORAL;
}

CCustomButton::~CCustomButton()
{
}

BOOL CCustomButton::Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam, LPARAM lParam )
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

BEGIN_MESSAGE_MAP(CCustomButton, CWnd)
	//{{AFX_MSG_MAP(CCustomButton)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomButton メッセージ ハンドラ

int CCustomButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pCanvas = new CCanvas( this, m_uCanvasBmpID );
	m_pHighlightItem = new CCanvasItem( this, m_uHighlightBmpID );
	m_pPushItem = new CCanvasItem( this, m_uPushBmpID );
	
	CRect	WndRect = m_pCanvas->GetCanvasRect();
	SetWindowPos( NULL, 0, 0, WndRect.Width(), WndRect.Height(), SWP_NOZORDER | SWP_NOMOVE );

	return 0;
}

void CCustomButton::OnDestroy() 
{
	CWnd::OnDestroy();

	delete m_pCanvas;
	delete m_pHighlightItem;
	delete m_pPushItem;
	
}

void CCustomButton::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CDC*	pCanvasDC = m_pCanvas->GetCanvasDC();

	switch( m_State ){

	case CBST_HIGHLIGHT:

		m_pHighlightItem->DrawTo( pCanvasDC, 0, 0 );
		break;

	case CBST_PUSH:

		m_pPushItem->DrawTo( pCanvasDC, 0, 0 );
		break;

	default:

		m_pCanvas->ClearCanvas();
		break;	

	}
	m_pCanvas->DrawTo( &dc, 0, 0 );
	
}

void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_State = CBST_PUSH;
	RedrawWindow();
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( GetCapture() == this ){

		ReleaseCapture();
	}

	if( m_State == CBST_PUSH ){

		if( m_pParentWnd ){

			m_pParentWnd->PostMessage( m_uMessage, m_wParam, m_lParam );
		}
	}

	m_State = CBST_NUTORAL;
	RedrawWindow();

	CWnd::OnLButtonUp(nFlags, point);
}

void CCustomButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( nFlags & MK_LBUTTON ){

		if( GetCapture() == this ){

			CRect	WndRect;
			GetWindowRect( &WndRect );

			if( ( WndRect.Width() < point.x ) ||
				( WndRect.Height() < point.y ) ||
				( point.x < 0 ) ||
				( point.y < 0 ) ){

				m_State = CBST_NUTORAL;
				RedrawWindow();

			}else{

				m_State = CBST_PUSH;
				RedrawWindow();

			}

		}else{
		
			m_State = CBST_NUTORAL;
			RedrawWindow();
		}

	}else{

		if( GetCapture() == this ){

			CRect	WndRect;
			GetWindowRect( &WndRect );

			if( ( WndRect.Width() < point.x ) ||
				( WndRect.Height() < point.y ) ||
				( point.x < 0 ) ||
				( point.y < 0 ) ){

				ReleaseCapture();
				m_State = CBST_NUTORAL;
				RedrawWindow();
			}

		}else{
		
			SetCapture();
			m_State = CBST_HIGHLIGHT;
			RedrawWindow();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CCustomButton::PostNcDestroy() 
{
	CWnd::PostNcDestroy();

	delete this;
}
