/*----------------------------------------------------------------
	CCanvas Definition
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

#if !defined(AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_)
#define AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCanvas  
{
protected:

	// 表示する DC を持つ Window へのポインタ
	CWnd*	m_pAppWnd;

	// 仮想 DC 
	CDC		m_CanvasDC;
	CBitmap	m_CanvasBitmap;

	// 基となるフレーム
	CDC		m_FrameDC;
	CBitmap	m_FrameBitmap;

	// 仮想 DC の Size
	CRect	m_CanvasRect;

public:

	// 仮想 DC の取得
	CDC* GetCanvasDC(){ return &m_CanvasDC; }

public:
	CCanvas( CWnd* pAppWnd, UINT uFrameBitmapID );
	virtual ~CCanvas();

	// 仮想 DC を m_FrameBitmap で初期化
	virtual void ClearCanvas();

	// 仮想 DC を pDC で示される DC 上に展開
	virtual void DrawTo( CDC* pDC );
	virtual void DrawTo( CDC* pDC, int nX, int nY );

	// サイズの取得
	CRect GetCanvasRect(){ return m_CanvasRect; }

};

#endif // !defined(AFX_CANVAS_H__C51AC50A_DFEA_4FDB_BD9C_3BDEA43972FF__INCLUDED_)
