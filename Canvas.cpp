/*----------------------------------------------------------------
	CCanvas Imprementation
  ----------------------------------------------------------------
	Description:
		仮想 DC クラス。
		このクラスで作成される DC に描画し、
		その上で表示 DC 上に転送(CCanvass::DrawTo)することで、
		ちらつきを抑えた描画が可能になります。
  
	Auther:
		Yoshihiro Yamaguchi MPD 2-2-4

	Define:
		Canvas.h

	Implement:
		Canvas.cpp

	History:

	00/06/23	Initial Check-in
  ----------------------------------------------------------------*/

#include "stdafx.h"
#include "Canvas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CCanvas::CCanvas( CWnd* pAppWnd, UINT uFrameBitmapID )
//	Description:
//		コンストラクタ
//	pAppWnd:
//		表示する DC を持つ CWnd Instance へのポインタ
//	uFrameBitmapID:
//		仮想 DC 上の元となる Bitmap へのリソース ID
{
	m_pAppWnd = pAppWnd;

	CDC*	pDC = pAppWnd->GetDC();

	m_CanvasDC.CreateCompatibleDC( pDC );
	m_CanvasBitmap.LoadBitmap( uFrameBitmapID );
	m_CanvasDC.SelectObject( &m_CanvasBitmap );
	
	m_FrameDC.CreateCompatibleDC( pDC );
	m_FrameBitmap.LoadBitmap( uFrameBitmapID );
	m_FrameDC.SelectObject( &m_FrameBitmap );

	pAppWnd->ReleaseDC( pDC );

	BITMAP	bmInfo;

	m_CanvasBitmap.GetBitmap( &bmInfo );

	m_CanvasRect.top = 0;
	m_CanvasRect.left = 0;
	m_CanvasRect.bottom = bmInfo.bmHeight - 1;	// 本当はバグらしい。。
	m_CanvasRect.right = bmInfo.bmWidth - 1;

}

CCanvas::~CCanvas()
//	Description:
//		デストラクタ
{
	m_CanvasDC.DeleteDC();
	m_CanvasBitmap.DeleteObject();

	m_FrameDC.DeleteDC();
	m_CanvasBitmap.DeleteObject();
}

void CCanvas::ClearCanvas()
//	Description:
//		仮想 DC を m_FrameBitmap で初期化
{
	m_CanvasDC.BitBlt( 0, 0,
		m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_FrameDC, 0, 0, SRCCOPY );
}

void CCanvas::DrawTo( CDC* pDC )
//	Description:
//		仮想 DC を pDC で示される DC 上に展開
//	pDC:
//		表示する DC 。
{
	pDC->BitBlt(
		0, 0, m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_CanvasDC, 0, 0, SRCCOPY );
}

void CCanvas::DrawTo( CDC* pDC, int nX, int nY )
//	Description:
//		仮想 DC を pDC で示される DC 上に展開
//	pDC:
//		表示する DC 。
{
	pDC->BitBlt(
		nX, nY, m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_CanvasDC, 0, 0, SRCCOPY );
}
