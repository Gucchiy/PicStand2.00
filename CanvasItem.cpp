// CanvasItem.cpp: CCanvasItem �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CanvasItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CCanvasItem::CCanvasItem( CWnd* pAppWnd, UINT uItemBitmapID )
{
	m_pAppWnd = pAppWnd;

	CDC*	pDC = pAppWnd->GetDC();

	m_CanvasItemDC.CreateCompatibleDC( pDC );
	m_CanvasItemBitmap.LoadBitmap( uItemBitmapID );
	m_CanvasItemDC.SelectObject( &m_CanvasItemBitmap );
	
	pAppWnd->ReleaseDC( pDC );

	BITMAP	bmInfo;

	m_CanvasItemBitmap.GetBitmap( &bmInfo );

	m_CanvasItemRect.top = 0;
	m_CanvasItemRect.left = 0;
	m_CanvasItemRect.bottom = bmInfo.bmHeight - 1;	// �{���̓o�O�H
	m_CanvasItemRect.right = bmInfo.bmWidth - 1;


}

CCanvasItem::~CCanvasItem()
{
	m_CanvasItemDC.DeleteDC();
	m_CanvasItemBitmap.DeleteObject();
}

void CCanvasItem::DrawTo( CDC* pDC, int nX, int nY )
//	Description:
//		���z DC �� pDC �Ŏ������ DC ��ɓW�J
//	pDC:
//		�\������ DC �B
{
	pDC->BitBlt(
		nX, nY, m_CanvasItemRect.Width(), m_CanvasItemRect.Height(),
		&m_CanvasItemDC, 0, 0, SRCCOPY );
}
