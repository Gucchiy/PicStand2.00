// CanvasItem.h: CCanvasItem クラスのインターフェイス
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

	// 表示する DC を持つ Window へのポインタ
	CWnd*	m_pAppWnd;

	// 仮想 DC 
	CDC		m_CanvasItemDC;
	CBitmap	m_CanvasItemBitmap;

	// 仮想 DC の Size
	CRect	m_CanvasItemRect;

public:

	// 仮想 DC の取得
	CDC* GetCanvasItemDC(){ return &m_CanvasItemDC; }

	CCanvasItem( CWnd* pAppWnd, UINT uItemID );
	virtual ~CCanvasItem();

	// 仮想 DC を pDC で示される DC 上に展開
	virtual void DrawTo( CDC* pDC, int nX, int nY );

	// サイズの取得
	CRect GetCanvasItemRect(){ return m_CanvasItemRect; }

};

#endif // !defined(AFX_CANVASITEM_H__C48A6BC1_5126_11D4_968B_444553540000__INCLUDED_)
