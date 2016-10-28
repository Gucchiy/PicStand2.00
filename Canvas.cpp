/*----------------------------------------------------------------
	CCanvas Imprementation
  ----------------------------------------------------------------
	Description:
		���z DC �N���X�B
		���̃N���X�ō쐬����� DC �ɕ`�悵�A
		���̏�ŕ\�� DC ��ɓ]��(CCanvass::DrawTo)���邱�ƂŁA
		�������}�����`�悪�\�ɂȂ�܂��B
  
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
// �\�z/����
//////////////////////////////////////////////////////////////////////

CCanvas::CCanvas( CWnd* pAppWnd, UINT uFrameBitmapID )
//	Description:
//		�R���X�g���N�^
//	pAppWnd:
//		�\������ DC ������ CWnd Instance �ւ̃|�C���^
//	uFrameBitmapID:
//		���z DC ��̌��ƂȂ� Bitmap �ւ̃��\�[�X ID
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
	m_CanvasRect.bottom = bmInfo.bmHeight - 1;	// �{���̓o�O�炵���B�B
	m_CanvasRect.right = bmInfo.bmWidth - 1;

}

CCanvas::~CCanvas()
//	Description:
//		�f�X�g���N�^
{
	m_CanvasDC.DeleteDC();
	m_CanvasBitmap.DeleteObject();

	m_FrameDC.DeleteDC();
	m_CanvasBitmap.DeleteObject();
}

void CCanvas::ClearCanvas()
//	Description:
//		���z DC �� m_FrameBitmap �ŏ�����
{
	m_CanvasDC.BitBlt( 0, 0,
		m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_FrameDC, 0, 0, SRCCOPY );
}

void CCanvas::DrawTo( CDC* pDC )
//	Description:
//		���z DC �� pDC �Ŏ������ DC ��ɓW�J
//	pDC:
//		�\������ DC �B
{
	pDC->BitBlt(
		0, 0, m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_CanvasDC, 0, 0, SRCCOPY );
}

void CCanvas::DrawTo( CDC* pDC, int nX, int nY )
//	Description:
//		���z DC �� pDC �Ŏ������ DC ��ɓW�J
//	pDC:
//		�\������ DC �B
{
	pDC->BitBlt(
		nX, nY, m_CanvasRect.Width(), m_CanvasRect.Height(),
		&m_CanvasDC, 0, 0, SRCCOPY );
}
