// CanvasItem.h: CCanvasItem �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CANVASITEM_H__C48A6BC1_5126_11D4_968B_444553540000__INCLUDED_)
#define AFX_CANVASITEM_H__C48A6BC1_5126_11D4_968B_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCanvasItem  
{
protected:

	// �\������ DC ������ Window �ւ̃|�C���^
	CWnd*	m_pAppWnd;

	// ���z DC 
	CDC		m_CanvasItemDC;
	CBitmap	m_CanvasItemBitmap;

	// ���z DC �� Size
	CRect	m_CanvasItemRect;

public:

	// ���z DC �̎擾
	CDC* GetCanvasItemDC(){ return &m_CanvasItemDC; }

	CCanvasItem( CWnd* pAppWnd, UINT uItemID );
	virtual ~CCanvasItem();

	// ���z DC �� pDC �Ŏ������ DC ��ɓW�J
	virtual void DrawTo( CDC* pDC, int nX, int nY );

	// �T�C�Y�̎擾
	CRect GetCanvasItemRect(){ return m_CanvasItemRect; }

};

#endif // !defined(AFX_CANVASITEM_H__C48A6BC1_5126_11D4_968B_444553540000__INCLUDED_)
